#include "jage/graphics/model/model.hpp"

#include <utility>
#include <glm/gtc/type_ptr.hpp>

#include "jage/runtime/assetmanager.hpp"

using jage::graphics::model::Model;
using jage::runtime::AssetStream;

Model::Model(std::string fileName)
    : m_fileName(std::move(fileName))
    , m_ready(false)
{ }

std::shared_ptr<Model> Model::create(std::string fileName) {
    return std::make_shared<Model>(std::move(fileName));
}

void Model::queue(int priority /* = ASSET_STREAM_BASE_PRIORITY */) {
    if (m_ready)
        return;
    AssetStream::getInstance().getTextAsset(
            m_fileName,
            [self = shared_from_this(), priority](const std::shared_ptr<const std::string>& content){
                self->m_json = json::parse(*content);

                self->getTextures(priority);
                self->getData(priority);
            });
}

bool Model::isReady() const {
    return m_ready;
}

void Model::draw(Shader& shader, glm::mat4 worldMatrix /* = glm::mat4(1.0f) */) {
    if (!isReady())
        return;
    for (size_t i = 0; i < m_meshes.size(); ++i) {
        m_meshes[i].draw(shader, jage::node::actor::Camera::getActiveCamera(), m_meshMatrices[i], worldMatrix);
    }
}

void Model::loadMesh(uint32_t meshIndex) {
    json& primitive = m_json["meshes"][meshIndex]["primitives"][0];

    uint8_t accPositionIndex = primitive["attributes"]["POSITION"];
    uint8_t accNormalIndex = primitive["attributes"]["NORMAL"];
    uint8_t accTexCoordIndex = primitive["attributes"]["TEXCOORD_0"];
    uint8_t accIndicesIndex = primitive["indices"];

    auto positionFloats = getFloats(m_json["accessors"][accPositionIndex]);
    auto positions = groupFloatsVec<glm::vec3>(positionFloats);

    auto normalFloats = getFloats(m_json["accessors"][accNormalIndex]);
    auto normals = groupFloatsVec<glm::vec3>(normalFloats);

    auto texCoordFloats = getFloats(m_json["accessors"][accTexCoordIndex]);
    auto texCoords = groupFloatsVec<glm::vec2>(texCoordFloats);

    auto vertices = assembleVertices(positions, normals, texCoords);
    auto indices = getIndices(m_json["accessors"][accIndicesIndex]);

    bool hasMaterial = primitive.find("material") != primitive.end();
    if (hasMaterial) {
        uint8_t materialIndex = m_json["meshes"][meshIndex]["primitives"][0]["material"];
        auto material = getMaterial(m_json["materials"][materialIndex], m_textures);
        m_meshes.emplace_back(vertices, indices, material);
    }
    else {
        m_meshes.emplace_back(vertices, indices, Material::getDefaultMaterial());
    }
}

void Model::traverseNode(uint16_t nodeIndex, glm::mat4 matrix) {
    json& node = m_json["nodes"][nodeIndex];

    glm::vec3 translation(0.0f);
    if (node.find("translation") != node.end()) {
        float data[3];
        for (size_t i = 0; i < node["translation"].size(); ++i)
            data[i] = node["translation"][i];
        translation = glm::make_vec3(data);
    }

    glm::quat rotation(1.0f, 0.0f, 0.0f, 0.0f);
    if (node.find("rotation") != node.end()) {
        rotation = glm::quat(node["rotation"][3],
                             node["rotation"][0],
                             node["rotation"][1],
                             node["rotation"][2]);
    }

    glm::vec3 scale(1.0f);
    if (node.find("scale") != node.end()) {
        float data[3];
        for (size_t i = 0; i < node["scale"].size(); ++i)
            data[i] = node["scale"][i];
        scale = glm::make_vec3(data);
    }

    glm::mat4 mat(1.0f);
    if (node.find("matrix") != node.end()) {
        float data[16];
        for (size_t i = 0; i < node["matrix"].size(); ++i)
            data[i] = node["matrix"][i];
        mat = glm::make_mat4(data);
    }

    auto trans = glm::translate(glm::mat4(1.0f), translation);
    auto rot = glm::mat4_cast(rotation);
    auto sca = glm::scale(glm::mat4(1.0f), scale);

    glm::mat4 inheritedMatrix = matrix * mat * trans * rot * sca;

    if (node.find("mesh") != node.end()) {
        m_meshMatrices.push_back(inheritedMatrix);

        loadMesh(node["mesh"]);
    }

    if (node.find("children") != node.end()) {
        for (const auto & i : node["children"]) {
            traverseNode(i, inheritedMatrix);
        }
    }
}

void Model::getData(int priority /* = ASSET_STREAM_BASE_PRIORITY */) {
    using std::string;

    string bytes_text;
    string uri = m_json["buffers"][0]["uri"];

    string directory = AssetStream::getFileDirectory(m_fileName);

    AssetStream::getInstance().getBinaryAssetAsync(
            directory + uri,
            [self = shared_from_this()](const uint8_t* data, size_t size){
                self->m_data = std::vector<uint8_t>(data, data + size);

                uint8_t modelMainScene = self->m_json.value("scene", 0);
                for (uint16_t node : self->m_json["scenes"][modelMainScene]["nodes"])
                    self->traverseNode(node);

                self->m_ready = true;
            }, priority);
}

std::vector<float> Model::getFloats(json accessor) {
    std::vector<float> result;

    uint32_t bufferViewIndex = accessor.value("bufferView", 1);
    uint64_t count = accessor["count"];
    uint64_t accessorByteOffset = accessor.value("byteOffset", 0);
    std::string type = accessor["type"];

    json bufferView = m_json["bufferViews"][bufferViewIndex];
    uint64_t byteOffset = bufferView["byteOffset"];

    uint8_t floatsPerVertex;
    if (type == "SCALAR") floatsPerVertex = 1;
    else if (type == "VEC2") floatsPerVertex = 2;
    else if (type == "VEC3") floatsPerVertex = 3;
    else if (type == "VEC4") floatsPerVertex = 4;
    else throw std::invalid_argument("Type is invalid (not SCALAR, VEC2, VEC3 or VEC4)");

    uint64_t startIndex = byteOffset + accessorByteOffset;
    uint64_t endIndex = startIndex + count * 4 * floatsPerVertex;
    for (uint64_t i = startIndex; i < endIndex; i += 4) {
        uint8_t bytes[] = { m_data[i], m_data[i+1], m_data[i+2], m_data[i+3] };
        float value;
        std::memcpy(&value, bytes, 4);
        result.push_back(value);
    }

    return result;
}

std::vector<GLuint> Model::getIndices(json accessor) {
    std::vector<GLuint> result;

    uint32_t bufferViewIndex = accessor.value("bufferView", 1);
    uint64_t count = accessor["count"];
    uint64_t accessorByteOffset = accessor.value("byteOffset", 0);
    uint16_t componentType = accessor["componentType"];

    json bufferView = m_json["bufferViews"][bufferViewIndex];
    uint64_t byteOffset = bufferView["byteOffset"];

    uint64_t startIndex = byteOffset + accessorByteOffset;
    uint64_t endIndex;
    switch (componentType) {
        case 5125:  // unsigned int
            endIndex = startIndex + count * 4;
            for (uint64_t i = startIndex; i < endIndex; i += 4) {
                uint8_t bytes[] = { m_data[i], m_data[i+1], m_data[i+2], m_data[i+3] };
                uint32_t value;
                std::memcpy(&value, bytes, 4);
                result.push_back((GLuint)value);
            }
            break;
        case 5123:  // unsigned short
            endIndex = startIndex + count * 2;
            for (uint64_t i = startIndex; i < endIndex; i += 2) {
                uint8_t bytes[] = { m_data[i], m_data[i+1] };
                uint16_t value;
                std::memcpy(&value, bytes, 2);
                result.push_back((GLuint)value);
            }
            break;
        case 5122:  // signed short
            endIndex = startIndex + count * 2;
            for (uint64_t i = startIndex; i < endIndex; i += 2) {
                uint8_t bytes[] = { m_data[i], m_data[i+1] };
                int16_t value;
                std::memcpy(&value, bytes, 2);
                result.push_back((GLuint)value);
            }
            break;
        default:
            throw std::invalid_argument("Non-supported Indices component type (not 5125, 5123 or 5122)");
    }

    return result;
}

void Model::getTextures(int priority /* = ASSET_STREAM_BASE_PRIORITY */) {
    m_textures.clear();

    std::string directory = AssetStream::getFileDirectory(m_fileName);

    for (size_t i = 0; i < m_json["images"].size(); ++i) {
        std::string texturePath = m_json["images"][i]["uri"];
        m_textures.push_back(jage::runtime::AssetManager::getInstance()->getTexture(directory + texturePath, priority));
    }
}

jage::graphics::Material Model::getMaterial(json data, std::vector<std::shared_ptr<Texture>>& textures) {
    std::string name = data["name"];
    Material result(name);

    if (data.find("pbrMetallicRoughness") == data.end())
        return result;

    json pbr = data["pbrMetallicRoughness"];

    // base color / diffuse
    glm::vec4 baseColorFactor(1.0);
    if (pbr.find("baseColorFactor") != pbr.end()) {
        std::vector<float> factor = pbr["baseColorFactor"];
        auto iter = factor.begin();
        setVector(iter, baseColorFactor);
    }
    result.setDiffuseFactor(baseColorFactor);

    if (pbr.find("baseColorTexture") != pbr.end()) {
        result.setDiffuse0(
                textures[pbr["baseColorTexture"]["index"]],
                pbr["baseColorTexture"].value("texCoord", 0));
    }

    return result;
}

std::vector<jage::graphics::model::Vertex> Model::assembleVertices(
        std::vector<glm::vec3> positions,
        std::vector<glm::vec3> normals,
        std::vector<glm::vec2> texCoords)
{
    std::vector<Vertex> vertices;
    for (uint64_t i = 0; i < positions.size(); ++i) {
        vertices.push_back(
                Vertex {
                        positions[i],
                        normals[i],
                        glm::vec3(1.0f, 1.0f, 1.0f),
                        texCoords[i]
                });
    }
    return vertices;
}

template<class TVec>
std::vector<TVec> Model::groupFloatsVec(std::vector<float> floats) {
    std::vector<TVec> vectors;
    for (auto i = floats.begin(); i < floats.end();) {
        TVec vec;
        setVector(i, vec);
        vectors.push_back(vec);
    }
    return vectors;
}

void Model::setVector(std::vector<float>::iterator& iterator, glm::vec2& vector) {
    vector = { iterator[0], iterator[1] };
    iterator += 2;
}

void Model::setVector(std::vector<float>::iterator& iterator, glm::vec3& vector) {
    vector = { iterator[0], iterator[1], iterator[2] };
    iterator += 3;
}

void Model::setVector(std::vector<float>::iterator& iterator, glm::vec4& vector) {
    vector = { iterator[0], iterator[1], iterator[2], iterator[3] };
    iterator += 4;
}
