#include "jage/graphics/mesh3d/mesh3d.hpp"

#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

using jage::graphics::mesh3d::Mesh3D;

Mesh3D::Mesh3D(std::vector<Vertex3D>& vertices, std::vector<GLuint>& indices, Material& material)
    : m_vertices(vertices)
    , m_indices(indices)
    , m_material(material)
    , m_initialised(false)
    , m_VAO()
{

}

Mesh3D::Mesh3D(const Mesh3D &mesh)
    : m_vertices(mesh.m_vertices)
    , m_indices(mesh.m_indices)
    , m_material(mesh.m_material)
    , m_initialised(false)
    , m_VAO()
{

}

void Mesh3D::draw(
        Shader& shader,
        jage::node::actor::Camera* camera,
        glm::mat4 relative /* = glm::mat4(1.0f) */,
        glm::mat4 model /* = glm::mat4(1.0f) */)
{
    if (!m_initialised)
        initialise();

    shader.prepare();
    if (!shader.isReady() or shader.isErrored())
        return;

    shader.activate();
    m_VAO.bind();

    if (!m_material.apply(shader))
        return;

    camera->applyMatrix(shader, "CameraMatrix");
    glUniform3f(shader.getUniform("CameraPos"), camera->getTranslation().x, camera->getTranslation().y, camera->getTranslation().z);

    glUniformMatrix4fv(shader.getUniform("Relative"), 1, GL_FALSE, glm::value_ptr(relative));
    glUniformMatrix4fv(shader.getUniform("Model"), 1, GL_FALSE, glm::value_ptr(model));

    glDrawElements(GL_TRIANGLES, (GLint)m_indices.size(), GL_UNSIGNED_INT, nullptr);
}

void Mesh3D::initialise() {
    m_VAO = VAO3D();
    m_VAO.bind();

    VBO3D VBO(m_vertices);
    EBO3D EBO(m_indices);

    m_VAO.linkAttribute(VBO, 0, 3, GL_FLOAT, sizeof(Vertex3D), (void *)0);
    m_VAO.linkAttribute(VBO, 1, 3, GL_FLOAT, sizeof(Vertex3D), (void *)(3 * sizeof(float)));
    m_VAO.linkAttribute(VBO, 2, 3, GL_FLOAT, sizeof(Vertex3D), (void *)(6 * sizeof(float)));
    m_VAO.linkAttribute(VBO, 3, 2, GL_FLOAT, sizeof(Vertex3D), (void *)(9 * sizeof(float)));

    m_VAO.unbind();
    VBO.unbind();
    EBO.unbind();

    m_initialised = true;
}
