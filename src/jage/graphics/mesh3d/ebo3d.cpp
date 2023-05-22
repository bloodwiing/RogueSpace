#include "jage/graphics/mesh3d/ebo3d.hpp"

using jage::graphics::mesh3d::EBO3D;

EBO3D::EBO3D(std::vector<GLuint> indices)
    : m_ID(0)
{
    glGenBuffers(1, &m_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLint)(indices.size() * sizeof(GLuint)), indices.data(), GL_STATIC_DRAW);
}

void EBO3D::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void EBO3D::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO3D::destroy() const {
    glDeleteBuffers(1, &m_ID);
}

GLuint EBO3D::getID() const {
    return m_ID;
}
