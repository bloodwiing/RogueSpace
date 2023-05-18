#ifndef JAGE_CAMERA_HPP
#define JAGE_CAMERA_HPP

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "jage/node/scene.hpp"
#include "jage/node/actor/dynamicactor.hpp"
#include "jage/node/actor/abc/actor_abc.hpp"
#include "jage/graphics/shader.hpp"

namespace jage::node::actor {

    /// \brief      A DynamicActor that can be used as a point to render all in-engine 3D Graphics
    class Camera : public DynamicActor {
    public:
        /// \note           Should not be used raw, please use addChild
        /// \param scene    Containing Scene of the Actor node
        /// \param parent   Parent of the Actor node
        /// \param name     Name of the Actor node
        /// \see            Scene#addChild
        /// \see            Actor#addChild
        Camera(JAGE_ACTOR_ARGS);
        ~Camera();

        /// \brief              Updates the Camera Matrix based off of the World Matrix and Camera settings
        /// \param fov_degrees  The perspective degrees
        /// \param near_plane   The nearest plane where geometry can intersect the viewing frustum
        /// \param far_plane    The furthest plane where geometry can intersect the viewing frustum
        void updateMatrix(float fov_degrees, float near_plane, float far_plane);
        /// \brief          Sets the current Camera Matrix as a uniform for a Shader
        /// \param shader   The Shader program to update
        /// \param uniform  The name of the uniform to update
        void applyMatrix(jage::graphics::Shader& shader, const char* uniform);

        /// \returns        The currently active camera
        static Camera* getActiveCamera();

        /// \brief          Makes the Camera statically accessible and used as the main camera for rendering
        void setActive() const;

        void update() override;

    protected:
        [[nodiscard]] std::string getTypeName() const override;

    private:
        /// The calculated Camera matrix, result of the View and Projection matrices
        glm::mat4 m_matrix = glm::mat4(1.0f);

        /// The currently active Camera pointer
        static Camera* m_active;

        /// The speed multiplier for translational flying
        float m_flySpeed = 1.0f;
        /// The speed multiplier for rotating the Actor around based on mouse delta
        float m_flySensitivity = 100.0f;
        /// A flag for if the mouse is being captured and hidden
        bool m_flyClicked = false;

        using DynamicActor::addChild;
    };
}

#endif //JAGE_CAMERA_HPP
