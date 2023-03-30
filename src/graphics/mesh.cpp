#include "graphics/mesh.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures)
    : m_vertices(vertices)
    , m_indices(indices)
    , m_textures(textures)
    , m_VAO()
{
    m_VAO.bind();

    VBO VBO(vertices);
    EBO EBO(indices);

    m_VAO.linkAttribute(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void *)0);
    m_VAO.linkAttribute(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void *)(3 * sizeof(float)));
    m_VAO.linkAttribute(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void *)(6 * sizeof(float)));
    m_VAO.linkAttribute(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void *)(9 * sizeof(float)));

    m_VAO.unbind();
    VBO.unbind();
    EBO.unbind();
}

void Mesh::draw(
        Shader& shader,
        Camera* camera,
        glm::mat4 relative /* = glm::mat4(1.0f) */,
        glm::mat4 model /* = glm::mat4(1.0f) */)
{
    if (shader.isErrored())
        return;

    shader.activate();
    m_VAO.bind();

    uint16_t diffuse_counter = 0,
             specular_counter = 0;

    for (uint64_t i = 0; i < m_textures.size(); ++i) {
        std::string uniform_name;

        switch (m_textures[i].getTextureType()) {
            case TextureType::TEX_DIFFUSE:
                uniform_name = std::string("Diffuse") + std::to_string(diffuse_counter++);
                break;
            case TextureType::TEX_SPECULAR:
                uniform_name = std::string("Specular") + std::to_string(specular_counter++);
                break;
            default:
                break;
        }

        m_textures[i].assign(shader, uniform_name.c_str(), i);
        m_textures[i].bind();
    }

    camera->applyMatrix(shader, "CameraMatrix");
    glUniform3f(shader.getUniform("CameraPos"), camera->getTranslation().x, camera->getTranslation().y, camera->getTranslation().z);

    glUniformMatrix4fv(shader.getUniform("Relative"), 1, GL_FALSE, glm::value_ptr(relative));
    glUniformMatrix4fv(shader.getUniform("Model"), 1, GL_FALSE, glm::value_ptr(model));

    glDrawElements(GL_TRIANGLES, (GLint)m_indices.size(), GL_UNSIGNED_INT, nullptr);
}
