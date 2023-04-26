#include "graphics/mesh.hpp"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

Graphics::Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, Material& material)
    : m_vertices(vertices)
    , m_indices(indices)
    , m_material(material)
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

void Graphics::Mesh::draw(
        Shader& shader,
        Camera* camera,
        glm::mat4 relative /* = glm::mat4(1.0f) */,
        glm::mat4 model /* = glm::mat4(1.0f) */)
{
    if (shader.isErrored())
        return;

    shader.activate();
    m_VAO.bind();

    m_material.apply(shader);

    camera->applyMatrix(shader, "CameraMatrix");
    glUniform3f(shader.getUniform("CameraPos"), camera->getTranslation().x, camera->getTranslation().y, camera->getTranslation().z);

    glUniformMatrix4fv(shader.getUniform("Relative"), 1, GL_FALSE, glm::value_ptr(relative));
    glUniformMatrix4fv(shader.getUniform("Model"), 1, GL_FALSE, glm::value_ptr(model));

    glDrawElements(GL_TRIANGLES, (GLint)m_indices.size(), GL_UNSIGNED_INT, nullptr);
}
