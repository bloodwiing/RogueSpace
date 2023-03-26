#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include <vector>
#include <json/json.h>

#include "mesh.h"

using json = nlohmann::json;

class Model {
public:
    Model(const char* filename);

    void draw(Shader& shader, Camera& camera);

private:
    const char* m_filename;
    std::vector<uint8_t> m_data;
    json m_json;

    std::vector<Mesh> meshes;
    std::vector<glm::vec3> meshTranslations;
    std::vector<glm::quat> meshRotations;
    std::vector<glm::vec3> meshScales;
    std::vector<glm::mat4> meshMatrices;

    std::unordered_map<std::string, Texture> loadedTexNames;

    void loadMesh(uint32_t meshIndex);

    void traverseNode(uint16_t nodeIndex, glm::mat4 matrix = glm::mat4(1.0f));

    std::vector<uint8_t> getData();
    std::vector<float> getFloats(json accessor);
    std::vector<GLuint> getIndices(json accessor);
    std::vector<Texture> getTextures();

    std::vector<Vertex> assembleVertices(
            std::vector<glm::vec3> positions,
            std::vector<glm::vec3> normals,
            std::vector<glm::vec2> texCoords);

    template<class TVec>
    std::vector<TVec> groupFloatsVec(std::vector<float> floats);

    static void setVector(std::vector<float>::iterator& iterator, glm::vec2& vector);
    static void setVector(std::vector<float>::iterator& iterator, glm::vec3& vector);
    static void setVector(std::vector<float>::iterator& iterator, glm::vec4& vector);
};

#endif //MODEL_CLASS_H
