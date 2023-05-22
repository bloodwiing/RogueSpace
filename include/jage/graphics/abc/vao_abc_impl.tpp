template<class TVBO>
jage::graphics::abc::VAObjectABC<TVBO>::VAObjectABC()
        : OGLBufferABC()
{

}

template<class TVBO>
void jage::graphics::abc::VAObjectABC<TVBO>::create() {
    glGenVertexArrays(1, &m_ID);
}

template<class TVBO>
void jage::graphics::abc::VAObjectABC<TVBO>::linkAttribute(TVBO& vbo, GLuint layout, GLint size, GLenum type, GLsizei stride, const GLvoid *offset) const {
    vbo.bind();
    glBindVertexArray(getID());
    glVertexAttribPointer(layout, size, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    vbo.unbind();
}

template<class TVBO>
void jage::graphics::abc::VAObjectABC<TVBO>::bind() const {
    glBindVertexArray(m_ID);
}

template<class TVBO>
void jage::graphics::abc::VAObjectABC<TVBO>::unbind() const {
    glBindVertexArray(0);
}

template<class TVBO>
void jage::graphics::abc::VAObjectABC<TVBO>::destroy() const {
    glDeleteVertexArrays(1, &m_ID);
}
