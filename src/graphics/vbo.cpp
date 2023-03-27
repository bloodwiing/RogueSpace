#include <vector>
#include "graphics/vbo.h"

VBO::VBO(std::vector<Vertex>& vertices)
    : m_ID(0)
{
    glGenBuffers(1, &m_ID);
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
    glBufferData(GL_ARRAY_BUFFER, (GLint)(vertices.size() * sizeof(Vertex)), vertices.data(), GL_STATIC_DRAW);
}

void VBO::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void VBO::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::destroy() const {
    glDeleteBuffers(1, &m_ID);
}

GLuint VBO::getID() const {
    return m_ID;
}
