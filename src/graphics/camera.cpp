#include "graphics/camera.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_access.hpp>

Camera* Camera::m_active = nullptr;

Camera::Camera(Scene *scene, ActorBase *parent, std::string name, int width, int height)
    : DynamicActor(scene, parent, name)
    , m_width(width)
    , m_height(height)
{  }

Camera::~Camera() {
    DynamicActor::~DynamicActor();
    if (m_active == this)
        m_active = nullptr;
}

void Camera::setOrientation(const glm::vec3& orientation, const glm::vec3& up) {
    m_orientation = orientation;
    m_up = up;
}

void Camera::updateMatrix(float fov_degrees, float near_plane, float far_plane) {
    glm::mat4 view(1.0f);
    glm::mat4 proj(1.0f);

    glm::vec3 point = glm::column(DynamicActor::getWorldMatrix(), 3);

    view = glm::lookAt(point, point + m_orientation, m_up);
    proj = glm::perspective(glm::radians(fov_degrees), (float)m_width / (float)m_height, near_plane, far_plane);

    m_matrix = proj * view;
}

void Camera::applyMatrix(Shader& shader, const char* uniform) {
    glUniformMatrix4fv(shader.getUniform(uniform), 1, GL_FALSE, glm::value_ptr(m_matrix));
}

Camera* Camera::getActiveCamera() {
    return m_active;
}

void Camera::setActive() const {
    m_active = (Camera*)this;
}
