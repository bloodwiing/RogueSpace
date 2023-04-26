#include "graphics/ebo.hpp"

Graphics::EBO::EBO(std::vector<GLuint> indices)
    : m_ID(0)
{
    glGenBuffers(1, &m_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLint)(indices.size() * sizeof(GLuint)), indices.data(), GL_STATIC_DRAW);
}

void Graphics::EBO::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void Graphics::EBO::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Graphics::EBO::destroy() const {
    glDeleteBuffers(1, &m_ID);
}

GLuint Graphics::EBO::getID() const {
    return m_ID;
}
