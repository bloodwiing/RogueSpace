#ifndef JAGE_MESH_HPP
#define JAGE_MESH_HPP

#include <vector>
#include <string>
#include <atomic>

#include <glm/detail/type_quat.hpp>

#include "jage/graphics/model/vao.hpp"
#include "jage/graphics/model/ebo.hpp"
#include "jage/actor/camera.hpp"
#include "jage/graphics/texture.hpp"
#include "jage/graphics/material.hpp"

namespace jage::graphics::model {

    /// \brief          A 3D Geometry container
    /// \details        Stores all relevant vertex information about itself so it can be drawn without extra data
    class Mesh {
    public:
        /// \brief          Creates a 3D Mesh by making and storing a Vertex Array Object
        /// \param vertices The list of Vertex objects
        /// \param indices  The list of Indices that build a stream of Triangles from Vertices
        /// \param material The Material used for rendering the Mesh
        /// \see            Vertex
        Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, Material& material);
        Mesh(const Mesh& mesh);

        /// \brief          Draws the Mesh to the screen
        /// \param shader   The Shader program to use when rendering
        /// \param camera   The Camera reference for Perspective and View frustum calculation
        /// \param relative The Relative-to-Model Transformation.
        ///                 This is used to position nodes of the same mesh first
        /// \param model    The Absolute-to-World Transformation.
        ///                 This is used to position the whole model after the Relative Transformation is applied
        void draw(
                Shader& shader,
                jage::actor::Camera* camera,
                glm::mat4 relative = glm::mat4(1.0f),
                glm::mat4 model = glm::mat4(1.0f));

    private:
        /// The list of Vertex objects
        std::vector<Vertex> m_vertices;
        /// The list of Indices that build a stream of Triangles from Vertices
        std::vector<GLuint> m_indices;
        /// The Material used for rendering the Mesh
        Material m_material;

        std::atomic<bool> m_initialised;

        void initialise();

        /// The Vertex Array Object created from the Vertex and Index arrays
        VAO m_VAO;
    };
}

#endif //JAGE_MESH_HPP
