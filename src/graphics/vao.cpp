#include "graphics/vao.hpp"

Graphics::VAO::VAO()
    : m_ID(0)
{
    glGenVertexArrays(1, &m_ID);
}

void Graphics::VAO::linkAttribute(VBO& vbo, GLuint layout, GLint size, GLenum type, GLsizei stride, const GLvoid *offset) const {
    vbo.bind();
    glBindVertexArray(m_ID);
    glVertexAttribPointer(layout, size, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    vbo.unbind();
}

void Graphics::VAO::bind() const {
    glBindVertexArray(m_ID);
}

void Graphics::VAO::unbind() const {
    glBindVertexArray(0);
}

void Graphics::VAO::destroy() const {
    glDeleteVertexArrays(1, &m_ID);
}

GLuint Graphics::VAO::getID() const {
    return m_ID;
}
