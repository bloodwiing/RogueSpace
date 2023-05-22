#ifndef JAGE_MESH_HPP
#define JAGE_MESH_HPP

#include <vector>
#include <string>
#include <atomic>

#include <glm/detail/type_quat.hpp>

#include "jage/graphics/mesh3d/vao3d.hpp"
#include "jage/graphics/mesh3d/ebo3d.hpp"
#include "jage/node/actor/camera.hpp"
#include "jage/graphics/texture.hpp"
#include "jage/graphics/material.hpp"

namespace jage::graphics::mesh3d {

    /// \brief          A 3D Geometry container
    /// \details        Stores all relevant vertex information about itself so it can be drawn without extra data
    class Mesh3D {
    public:
        /// \brief          Creates a 3D Mesh by making and storing a Vertex Array Object
        /// \param vertices The list of Vertex objects
        /// \param indices  The list of Indices that build a stream of Triangles from Vertices
        /// \param material The Material used for rendering the Mesh
        /// \see            Vertex
        Mesh3D(std::vector<Vertex3D>& vertices, std::vector<GLuint>& indices, Material& material);
        Mesh3D(const Mesh3D& mesh);

        /// \brief          Draws the Mesh to the screen
        /// \param shader   The Shader program to use when rendering
        /// \param camera   The Camera reference for Perspective and View frustum calculation
        /// \param relative The Relative-to-Model Transformation.
        ///                 This is used to position nodes of the same mesh first
        /// \param model    The Absolute-to-World Transformation.
        ///                 This is used to position the whole model after the Relative Transformation is applied
        void draw(
                Shader& shader,
                jage::node::actor::Camera* camera,
                glm::mat4 relative = glm::mat4(1.0f),
                glm::mat4 model = glm::mat4(1.0f));

    private:
        /// The list of Vertex objects
        std::vector<Vertex3D> m_vertices;
        /// The list of Indices that build a stream of Triangles from Vertices
        std::vector<GLuint> m_indices;
        /// The Material used for rendering the Mesh
        Material m_material;

        std::atomic<bool> m_initialised;

        void initialise();

        /// The Vertex Array Object created from the Vertex and Index arrays
        VAO3D m_VAO;
    };
}

#endif //JAGE_MESH_HPP
