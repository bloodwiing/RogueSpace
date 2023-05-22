#include "jage/graphics/mesh3d/mesh3d.hpp"

#include <glm/gtc/type_ptr.hpp>

#include "jage/graphics/abc/ebo.hpp"

using jage::graphics::mesh3d::Mesh3D;

Mesh3D::Mesh3D(const std::vector<VertexType> &vertices, const std::vector<GLuint> &indices, const jage::graphics::Material &material)
        : MeshABC(vertices, indices, material)
{

}

Mesh3D::Mesh3D(const jage::graphics::abc::MeshABC<jage::graphics::mesh3d::VAO3D>& mesh)
        : MeshABC(mesh)
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
    m_VAO.create();
    m_VAO.bind();

    auto VBO = VBO3D(m_vertices);
    auto EBO = abc::EBO(m_indices);

    m_VAO.linkAttribute(VBO, 0, 3, GL_FLOAT, sizeof(Vertex3D), (void *)0);
    m_VAO.linkAttribute(VBO, 1, 3, GL_FLOAT, sizeof(Vertex3D), (void *)(3 * sizeof(float)));
    m_VAO.linkAttribute(VBO, 2, 3, GL_FLOAT, sizeof(Vertex3D), (void *)(6 * sizeof(float)));
    m_VAO.linkAttribute(VBO, 3, 2, GL_FLOAT, sizeof(Vertex3D), (void *)(9 * sizeof(float)));

    m_VAO.unbind();
    VBO.unbind();
    EBO.unbind();

    m_initialised = true;
}
