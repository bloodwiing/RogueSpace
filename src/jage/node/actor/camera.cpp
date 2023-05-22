#include "jage/node/actor/camera.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glad/glad.h>

#include "jage/runtime/time.hpp"
#include "jage/runtime/window.hpp"

using jage::node::actor::Camera;
using glm::mat4;
using glm::vec3;
using glm::vec4;
using glm::normalize;

Camera* Camera::active = nullptr;

std::string Camera::getTypeName() const {
    return "Camera";
}

Camera::Camera(JAGE_ACTOR_ARGS, float fov, float near, float far)
    : DynamicActor(parent, std::move(name), scene, tag, isVolatile)
    , m_fov(fov)
    , m_near(near)
    , m_far(far)
{  }

Camera::~Camera() {
    if (active == this)
        active = nullptr;
}

void Camera::updateMatrix() {
    if (!isActive())
        return;

    using jage::runtime::Window;

    mat4 view(1.0f);
    mat4 proj(1.0f);

    vec3 point = glm::column(DynamicActor::getWorldMatrix(), 3);

    view = glm::lookAt(point, point + DynamicActor::getOrientation(), DynamicActor::getUp());
    proj = glm::perspective(glm::radians(m_fov), Window::getActive()->getAspectRatio(), m_near, m_far);

    m_matrix = proj * view;
}

void Camera::applyMatrix(jage::graphics::Shader& shader, const char* uniform) {
    glUniformMatrix4fv(shader.getUniform(uniform), 1, GL_FALSE, glm::value_ptr(m_matrix));
}

Camera* Camera::getActiveCamera() {
    return active;
}

void Camera::setActive() const {
    active = (Camera*)this;
}

bool Camera::isActive() const {
    return active == this;
}

void Camera::update() {
    DynamicActor::update();
    updateMatrix();
}
