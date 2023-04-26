#include <vector>
#include "graphics/vbo.hpp"

Graphics::VBO::VBO(std::vector<Vertex>& vertices)
    : m_ID(0)
{
    glGenBuffers(1, &m_ID);
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
    glBufferData(GL_ARRAY_BUFFER, (GLint)(vertices.size() * sizeof(Vertex)), vertices.data(), GL_STATIC_DRAW);
}

void Graphics::VBO::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void Graphics::VBO::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Graphics::VBO::destroy() const {
    glDeleteBuffers(1, &m_ID);
}

GLuint Graphics::VBO::getID() const {
    return m_ID;
}
