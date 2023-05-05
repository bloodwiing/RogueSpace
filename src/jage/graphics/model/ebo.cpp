#include "jage/graphics/model/ebo.hpp"

using jage::graphics::model::EBO;

EBO::EBO(std::vector<GLuint> indices)
    : m_ID(0)
{
    glGenBuffers(1, &m_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLint)(indices.size() * sizeof(GLuint)), indices.data(), GL_STATIC_DRAW);
}

void EBO::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void EBO::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::destroy() const {
    glDeleteBuffers(1, &m_ID);
}

GLuint EBO::getID() const {
    return m_ID;
}
