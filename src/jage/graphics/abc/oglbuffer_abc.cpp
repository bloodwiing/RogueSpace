#include "jage/graphics/abc/oglbuffer_abc.hpp"

using jage::graphics::abc::OGLBufferABC;

OGLBufferABC::OGLBufferABC()
        : m_ID(0)
        , m_bufferType(0)
{

}

OGLBufferABC::OGLBufferABC(GLenum bufferType)
        : m_ID()
        , m_bufferType(bufferType)
{
    glGenBuffers(1, &m_ID);
}

OGLBufferABC::~OGLBufferABC() {
    if (m_destroyed and m_bufferType != 0)
        return;
    glDeleteBuffers(1, &m_ID);
    m_destroyed = true;
}

void OGLBufferABC::bind() const {
    glBindBuffer(m_bufferType, m_ID);
}

void OGLBufferABC::unbind() const {
    glBindBuffer(m_bufferType, 0);
}

void OGLBufferABC::destroy() const {
    glDeleteBuffers(1, &m_ID);
}

GLuint OGLBufferABC::getID() const {
    return m_ID;
}
