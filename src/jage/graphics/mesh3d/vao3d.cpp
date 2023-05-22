#include "jage/graphics/mesh3d/vao3d.hpp"

using jage::graphics::mesh3d::VAO3D;

VAO3D::VAO3D()
    : m_ID(0)
{
    glGenVertexArrays(1, &m_ID);
}

void VAO3D::linkAttribute(VBO3D& vbo, GLuint layout, GLint size, GLenum type, GLsizei stride, const GLvoid *offset) const {
    vbo.bind();
    glBindVertexArray(m_ID);
    glVertexAttribPointer(layout, size, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    vbo.unbind();
}

void VAO3D::bind() const {
    glBindVertexArray(m_ID);
}

void VAO3D::unbind() const {
    glBindVertexArray(0);
}

void VAO3D::destroy() const {
    glDeleteVertexArrays(1, &m_ID);
}

GLuint VAO3D::getID() const {
    return m_ID;
}
