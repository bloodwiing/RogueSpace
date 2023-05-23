#ifndef JAGE_MESH_2D_HPP
#define JAGE_MESH_2D_HPP

#include <vector>
#include <string>
#include <atomic>

#include <glm/detail/type_quat.hpp>

#include "jage/graphics/abc/mesh_abc.hpp"
#include "jage/graphics/mesh2d/vao2d.hpp"
#include "jage/node/actor/camera.hpp"
#include "jage/graphics/texture.hpp"
#include "jage/graphics/mesh2d/sprite.hpp"

namespace jage::graphics::mesh2d {

    /// \brief          A 3D Geometry container
    /// \details        Stores all relevant vertex information about itself so it can be drawn without extra data
    class Mesh2D
            : public graphics::abc::MeshABC<VAO2D> {
    public:
        Mesh2D(const std::vector<VertexType>& vertices, const std::vector<GLuint>& indices, const Sprite& sprite);
        Mesh2D(const Mesh2D& mesh);

        /// \brief          Draws the Mesh to the screen
        /// \param shader   The Shader program to use when rendering
        /// \param camera   The Camera reference for Perspective and View frustum calculation
        /// \param model    The Absolute-to-Screen Transformation
        void draw(
                Shader& shader,
                glm::mat3 frame = glm::mat3(1.0f));

    protected:
        void initialise() override;

        Sprite m_sprite;
    };
}

#endif //JAGE_MESH_2D_HPP
