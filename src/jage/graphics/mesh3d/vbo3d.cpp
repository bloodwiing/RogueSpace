#include "jage/graphics/mesh3d/vbo3d.hpp"

#include <vector>

using jage::graphics::mesh3d::VBO3D;

VBO3D::VBO3D(std::vector<Vertex3D>& vertices)
    : m_ID(0)
{
    glGenBuffers(1, &m_ID);
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
    glBufferData(GL_ARRAY_BUFFER, (GLint)(vertices.size() * sizeof(Vertex3D)), vertices.data(), GL_STATIC_DRAW);
}

void VBO3D::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void VBO3D::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO3D::destroy() const {
    glDeleteBuffers(1, &m_ID);
}

GLuint VBO3D::getID() const {
    return m_ID;
}
