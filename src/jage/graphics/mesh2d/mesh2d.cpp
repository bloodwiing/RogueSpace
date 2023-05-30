#include "jage/graphics/mesh2d/mesh2d.hpp"

#include <glm/gtc/type_ptr.hpp>

#include "jage/graphics/abc/ebo.hpp"

using jage::graphics::mesh2d::Mesh2D;
using jage::graphics::mesh2d::Sprite;

Mesh2D::Mesh2D(const std::vector<VertexType> &vertices, const std::vector<GLuint> &indices, std::shared_ptr<Sprite> sprite)
        : MeshABC(vertices, indices)
        , m_sprite(std::move(sprite))
{

}

void Mesh2D::draw(
        Shader& shader,
        glm::mat3 frame /* = glm::mat3(1.0f) */)
{
    if (!m_initialised)
        initialise();

    shader.prepare();
    if (!shader.isReady() or shader.isErrored())
        return;

    shader.activate();
    m_VAO.bind();

    if (!m_sprite->apply(shader))
        return;

    glUniformMatrix3fv(shader.getUniform("Frame"), 1, GL_FALSE, glm::value_ptr(frame));

    glDrawElements(GL_TRIANGLES, (GLint)m_indices.size(), GL_UNSIGNED_INT, nullptr);
}

void Mesh2D::setSprite(std::shared_ptr<Sprite> sprite) {
    m_sprite = std::move(sprite);
}

void Mesh2D::initialise() {
    m_VAO.create();
    m_VAO.bind();

    auto VBO = VBO2D(m_vertices);
    auto EBO = abc::EBO(m_indices);

    m_VAO.linkAttribute(VBO, 0, 2, GL_FLOAT, sizeof(Vertex2D), (void *)0);
    m_VAO.linkAttribute(VBO, 1, 3, GL_FLOAT, sizeof(Vertex2D), (void *)(2 * sizeof(float)));
    m_VAO.linkAttribute(VBO, 2, 2, GL_FLOAT, sizeof(Vertex2D), (void *)(5 * sizeof(float)));

    m_VAO.unbind();
    VBO.unbind();
    EBO.unbind();

    m_initialised = true;
}
