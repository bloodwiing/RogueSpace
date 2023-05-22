#ifndef JAGE_MESH_3D_HPP
#define JAGE_MESH_3D_HPP

#include <vector>
#include <string>
#include <atomic>

#include <glm/detail/type_quat.hpp>

#include "jage/graphics/abc/mesh_abc.hpp"
#include "jage/graphics/mesh3d/vao3d.hpp"
#include "jage/node/actor/camera.hpp"
#include "jage/graphics/texture.hpp"
#include "jage/graphics/material.hpp"

namespace jage::graphics::mesh3d {

    /// \brief          A 3D Geometry container
    /// \details        Stores all relevant vertex information about itself so it can be drawn without extra data
    class Mesh3D
            : public graphics::abc::MeshABC<VAO3D> {
    public:
        Mesh3D(const std::vector<VertexType>& vertices, const std::vector<GLuint>& indices, const Material& material);
        Mesh3D(const MeshABC<VAO3D>& mesh);

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

    protected:
        void initialise() override;
    };
}

#endif //JAGE_MESH_3D_HPP
