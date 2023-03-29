#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include <vector>
#include <json/json.h>

#include "mesh.h"

#include "engine/actor/dynamicactor.h"

using json = nlohmann::json;

class Model : public DynamicActor {
public:
    explicit Model(Scene *scene, ActorBase *parent, const char* filename);

    void draw(Shader& shader) override;

private:
    const char* m_filename;
    std::vector<uint8_t> m_data;
    json m_json;

    std::vector<Mesh> m_meshes;
    std::vector<glm::vec3> m_meshTranslations;
    std::vector<glm::quat> m_meshRotations;
    std::vector<glm::vec3> m_meshScales;
    std::vector<glm::mat4> m_meshMatrices;

    std::unordered_map<std::string, Texture> m_loadedTexNames;

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
