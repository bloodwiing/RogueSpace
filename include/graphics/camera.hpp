#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include "shader.hpp"
#include <glfw3.h>
#include <glm/glm.hpp>

#include "engine/actor/dynamicactor.hpp"

/// \brief      A DynamicActor that can be used as a point to render all in-engine 3D Graphics
class Camera : public DynamicActor {
public:
    /// \note           Should not be used raw, please use addChild
    /// \param scene    Containing Scene of the Actor node
    /// \param parent   Parent of the Actor node
    /// \param name     Name of the Actor node
    /// \see            Scene#addChild
    /// \see            Actor#addChild
    Camera(Scene *scene, ActorBase *parent, std::string name);
    ~Camera();

    /// \brief              Updates the Camera Matrix based off of the World Matrix and Camera settings
    /// \param fov_degrees  The perspective degrees
    /// \param near_plane   The nearest plane where geometry can intersect the viewing frustum
    /// \param far_plane    The furthest plane where geometry can intersect the viewing frustum
    void updateMatrix(float fov_degrees, float near_plane, float far_plane);
    /// \brief          Sets the current Camera Matrix as a uniform for a Shader
    /// \param shader   The Shader program to update
    /// \param uniform  The name of the uniform to update
    void applyMatrix(Shader& shader, const char* uniform);

    static Camera* getActiveCamera();
    void setActive() const;

    void update() override;

    void copyOrientation(Camera* camera, bool copyUpVector = true);
    void freeFlyUpdate();

protected:
    [[nodiscard]] std::string getTypeName() const override;

private:
    glm::vec3 m_orientation = glm::vec3(0.0f, 0.0f, -1.0f),
              m_up = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::mat4 m_matrix = glm::mat4(1.0f);

    static Camera* m_active;

    float m_flySpeed = 1.0f;
    float m_flySensitivity = 100.0f;
    bool m_flyClicked = false;
};

#endif //CAMERA_CLASS_H
