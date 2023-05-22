template<class TVertex>
jage::graphics::abc::VBObjectABC<TVertex>::VBObjectABC()
        : OGLBufferABC()
{

}

template<class TVertex>
jage::graphics::abc::VBObjectABC<TVertex>::VBObjectABC(const std::vector<TVertex>& vertices)
        : OGLBufferABC(GL_ARRAY_BUFFER)
{
    glBindBuffer(GL_ARRAY_BUFFER, getID());
    glBufferData(GL_ARRAY_BUFFER, (GLint)(vertices.size() * sizeof(TVertex)), vertices.data(), GL_STATIC_DRAW);
}
