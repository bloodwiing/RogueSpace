#include "jage/actor/camera.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glad/glad.h>

#include "jage/runtime/time.hpp"
#include "jage/runtime/window.hpp"

using jage::actor::Camera;
using glm::mat4;
using glm::vec3;
using glm::vec4;
using glm::normalize;

Camera* Camera::m_active = nullptr;

std::string Camera::getTypeName() const {
    return "Camera";
}

Camera::Camera(Scene *scene, abc::ActorABC *parent, std::string name)
    : DynamicActor(scene, parent, name)
{  }

Camera::~Camera() {
    DynamicActor::~DynamicActor();
    if (m_active == this)
        m_active = nullptr;
}

void Camera::updateMatrix(float fov_degrees, float near_plane, float far_plane) {
    using jage::runtime::Window;

    mat4 view(1.0f);
    mat4 proj(1.0f);

    vec3 point = glm::column(DynamicActor::getWorldMatrix(), 3);

    view = glm::lookAt(point, point + m_orientation, m_up);
    proj = glm::perspective(glm::radians(fov_degrees), Window::getActive()->getAspectRatio(), near_plane, far_plane);

    m_matrix = proj * view;
}

void Camera::applyMatrix(jage::graphics::Shader& shader, const char* uniform) {
    glUniformMatrix4fv(shader.getUniform(uniform), 1, GL_FALSE, glm::value_ptr(m_matrix));
}

Camera* Camera::getActiveCamera() {
    return m_active;
}

void Camera::setActive() const {
    m_active = (Camera*)this;
}

void Camera::update() {
    DynamicActor::update();

    m_up = normalize(vec4(0.0f, 1.0f, 0.0f, 0.0f) * DynamicActor::getWorldMatrix());
    m_orientation = normalize(vec4(1.0f, 0.0f, 0.0f, 0.0f) * DynamicActor::getWorldMatrix());
}
