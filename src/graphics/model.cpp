#include "graphics/model.h"

#include <glm/gtc/type_ptr.hpp>
#include "utils.h"

std::string Model::getTypeName() const {
    return "Model";
}

Model::Model(Scene *scene, ActorBase *parent, std::string name, const char *filename)
    : DynamicActor(scene, parent, name)
    , m_filename(filename)
{
    std::string content = readFileContents(filename);
    m_json = json::parse(content);

    m_data = getData();

    uint8_t modelMainScene = m_json.value("scene", 0);
    for (uint16_t node : m_json["scenes"][modelMainScene]["nodes"])
        traverseNode(node);
}

void Model::draw(Shader& shader) {
    for (size_t i = 0; i < m_meshes.size(); ++i) {
        m_meshes[i].draw(shader, Camera::getActiveCamera(), m_meshMatrices[i], getWorldMatrix());
    }
}

void Model::loadMesh(uint32_t meshIndex) {
    uint8_t accPositionIndex = m_json["meshes"][meshIndex]["primitives"][0]["attributes"]["POSITION"];
    uint8_t accNormalIndex = m_json["meshes"][meshIndex]["primitives"][0]["attributes"]["NORMAL"];
    uint8_t accTexCoordIndex = m_json["meshes"][meshIndex]["primitives"][0]["attributes"]["TEXCOORD_0"];
    uint8_t accIndicesIndex = m_json["meshes"][meshIndex]["primitives"][0]["indices"];

    auto positionFloats = getFloats(m_json["accessors"][accPositionIndex]);
    auto positions = groupFloatsVec<glm::vec3>(positionFloats);

    auto normalFloats = getFloats(m_json["accessors"][accNormalIndex]);
    auto normals = groupFloatsVec<glm::vec3>(normalFloats);

    auto texCoordFloats = getFloats(m_json["accessors"][accTexCoordIndex]);
    auto texCoords = groupFloatsVec<glm::vec2>(texCoordFloats);

    auto vertices = assembleVertices(positions, normals, texCoords);
    auto indices = getIndices(m_json["accessors"][accIndicesIndex]);
    auto textures = getTextures();

    m_meshes.emplace_back(vertices, indices, textures);
}

void Model::traverseNode(uint16_t nodeIndex, glm::mat4 matrix) {
    json node = m_json["nodes"][nodeIndex];

    glm::vec3 translation(0.0f);
    if (node.find("translation") != node.end()) {
        float data[3];
        for (size_t i = 0; i < node["translation"].size(); ++i)
            data[i] = node["translation"][i];
        translation = glm::make_vec3(data);
    }

    glm::quat rotation(1.0f, 0.0f, 0.0f, 0.0f);
    if (node.find("rotation") != node.end()) {
        float data[4];
        for (size_t i = 0; i < node["rotation"].size(); ++i)
            data[i] = node["rotation"][i];
        rotation = glm::make_quat(data);
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

std::vector<uint8_t> Model::getData() {
    std::string bytes_text;
    std::string uri = m_json["buffers"][0]["uri"];

    std::string file_str = std::string(m_filename);
    std::string directory = file_str.substr(0, file_str.find_last_of('/') + 1);
    bytes_text = readFileContents(directory + uri, std::ios::in | std::ios::binary);

    std::vector<uint8_t> bin_data(bytes_text.begin(), bytes_text.end());
    return bin_data;
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

std::vector<Texture> Model::getTextures() {
    std::vector<Texture> textures;

    std::string file_str = std::string(m_filename);
    std::string directory = file_str.substr(0, file_str.find_last_of('/') + 1);

    for (size_t i = 0; i < m_json["images"].size(); ++i) {
        std::string texturePath = m_json["images"][i]["uri"];

        if (m_loadedTexNames.find(texturePath) != m_loadedTexNames.end()) {
            textures.push_back(m_loadedTexNames[texturePath]);
            continue;
        }

        Texture texture{};
        if (texturePath.find("baseColor") != std::string::npos) {
            texture = Texture((directory + texturePath).c_str(), TEX_DIFFUSE, m_loadedTexNames.size());
        } else if (texturePath.find("metallicRoughness") != std::string::npos) {
            texture = Texture((directory + texturePath).c_str(), TEX_SPECULAR, m_loadedTexNames.size());
        }
        textures.push_back(texture);
        m_loadedTexNames[texturePath] = texture;
    }

    return textures;
}

std::vector<Vertex> Model::assembleVertices(
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
