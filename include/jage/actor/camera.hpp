#ifndef JAGE_CAMERA_HPP
#define JAGE_CAMERA_HPP

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "jage/actor/scene.hpp"
#include "jage/actor/dynamicactor.hpp"
#include "jage/actor/abc/actor_abc.hpp"
#include "jage/graphics/shader.hpp"

namespace jage::actor {

    /// \brief      A DynamicActor that can be used as a point to render all in-engine 3D Graphics
    class Camera : public DynamicActor {
    public:
        /// \note           Should not be used raw, please use addChild
        /// \param scene    Containing Scene of the Actor node
        /// \param parent   Parent of the Actor node
        /// \param name     Name of the Actor node
        /// \see            Scene#addChild
        /// \see            Actor#addChild
        Camera(Scene *scene, abc::ActorABC *parent, std::string name);
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

        /// \brief              Helper function to copy camera Transformations from one Camera to another
        /// \param camera       The origin Camera to copy from
        /// \param copyUpVector An option to also copy the UP vector
        void copyOrientation(Camera* camera, bool copyUpVector = true);
        /// \brief          PlayerActor inspired Keyboard and Mouse controllable update event
        /// \details        Used for Free Fly controls
        void freeFlyUpdate();

    protected:
        [[nodiscard]] std::string getTypeName() const override;

    private:
        /// The orientation vector where the Camera is currently looking at
        glm::vec3 m_orientation = glm::vec3(1.0f, 0.0f, 0.0f),
        /// The vector pointing upwards from the Actor's perspective
        m_up = glm::vec3(0.0f, 1.0f, 0.0f);

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
    };
}

#endif //JAGE_CAMERA_HPP
