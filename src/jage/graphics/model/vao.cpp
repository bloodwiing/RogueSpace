#include "jage/graphics/model/vao.hpp"

using jage::graphics::model::VAO;

VAO::VAO()
    : m_ID(0)
{
    glGenVertexArrays(1, &m_ID);
}

void VAO::linkAttribute(VBO& vbo, GLuint layout, GLint size, GLenum type, GLsizei stride, const GLvoid *offset) const {
    vbo.bind();
    glBindVertexArray(m_ID);
    glVertexAttribPointer(layout, size, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    vbo.unbind();
}

void VAO::bind() const {
    glBindVertexArray(m_ID);
}

void VAO::unbind() const {
    glBindVertexArray(0);
}

void VAO::destroy() const {
    glDeleteVertexArrays(1, &m_ID);
}

GLuint VAO::getID() const {
    return m_ID;
}
