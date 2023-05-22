#include "jage/graphics/abc/ebo.hpp"

using jage::graphics::abc::EBO;

EBO::EBO()
        : OGLBufferABC()
{

}

EBO::EBO(std::vector<GLuint> indices)
        : OGLBufferABC(GL_ELEMENT_ARRAY_BUFFER)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, getID());
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLint)(indices.size() * sizeof(GLuint)), indices.data(), GL_STATIC_DRAW);
}
