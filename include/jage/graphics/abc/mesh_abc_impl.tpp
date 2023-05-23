template<class TVAO>
jage::graphics::abc::MeshABC<TVAO>::MeshABC(const std::vector<VertexType>& vertices, const std::vector<GLuint>& indices)
        : m_vertices(vertices)
        , m_indices(indices)
        , m_VAO()
{

}

template<class TVAO>
jage::graphics::abc::MeshABC<TVAO>::MeshABC(const MeshABC<TVAO>& mesh)
        : MeshABC(mesh.m_vertices, mesh.m_indices)
{

}
