#ifndef JAGE_MESH_ABC_HPP
#define JAGE_MESH_ABC_HPP

#include <vector>
#include <string>
#include <atomic>

#include <glm/detail/type_quat.hpp>

#include "jage/node/actor/camera.hpp"
#include "jage/graphics/material.hpp"
#include "jage/graphics/abc/ebo.hpp"

namespace jage::graphics::abc {

    template<class TVAO>
    class MeshABC {
    public:
        typedef typename TVAO::VertexType VertexType;

        /// \brief          Creates a 3D Mesh by making and storing a Vertex Array Object
        /// \param vertices The list of Vertex objects
        /// \param indices  The list of Indices that build a stream of Triangles from Vertices
        /// \param material The Material used for rendering the Mesh
        /// \see            Vertex
        MeshABC(const std::vector<VertexType>& vertices, const std::vector<GLuint>& indices, const Material& material);
        MeshABC(const MeshABC<TVAO>& mesh);

    protected:
        /// The list of Vertex objects
        std::vector<VertexType> m_vertices;
        /// The list of Indices that build a stream of Triangles from Vertices
        std::vector<GLuint> m_indices;

        /// The Vertex Array Object created from the Vertex and Index arrays
        TVAO m_VAO;

        /// The Material used for rendering the Mesh
        Material m_material;

        bool m_initialised = false;

        virtual void initialise() = 0;
    };
}

#include "mesh_abc_impl.tpp"

#endif //JAGE_MESH_ABC_HPP
