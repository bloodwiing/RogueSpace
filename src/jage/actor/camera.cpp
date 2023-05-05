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

void Camera::copyOrientation(Camera *camera, bool copyUpVector /* = true */) {
    m_orientation = normalize(camera->m_orientation);
    if (copyUpVector)
        m_up = normalize(camera->m_up);
}

void Camera::freeFlyUpdate() {
    using jage::runtime::Time;
    using jage::runtime::Window;

    if (JAGE_IS_KEY(GLFW_KEY_W, GLFW_PRESS)) {
        translate(m_flySpeed * m_orientation * Time::getDeltaFloat());
    }
    if (JAGE_IS_KEY(GLFW_KEY_S, GLFW_PRESS)) {
        translate(m_flySpeed * -m_orientation * Time::getDeltaFloat());
    }
    if (JAGE_IS_KEY(GLFW_KEY_A, GLFW_PRESS)) {
        translate(m_flySpeed * -normalize(glm::cross(m_orientation, m_up)) * Time::getDeltaFloat());
    }
    if (JAGE_IS_KEY(GLFW_KEY_D, GLFW_PRESS)) {
        translate(m_flySpeed * normalize(glm::cross(m_orientation, m_up)) * Time::getDeltaFloat());
    }
    if (JAGE_IS_KEY(GLFW_KEY_E, GLFW_PRESS)) {
        translate(m_flySpeed * m_up * Time::getDeltaFloat());
    }
    if (JAGE_IS_KEY(GLFW_KEY_Q, GLFW_PRESS)) {
        translate(m_flySpeed * -m_up * Time::getDeltaFloat());
    }

    if (JAGE_IS_KEY(GLFW_KEY_SPACE, GLFW_PRESS)) {
        m_flySpeed = 5.0f;
    } else if (JAGE_IS_KEY(GLFW_KEY_SPACE, GLFW_RELEASE)) {
        m_flySpeed = 1.0f;
    }

    if (JAGE_IS_MOUSE(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS) && !m_flyClicked) {
        m_flyClicked = true;
        glfwSetInputMode(Window::getActive()->getWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        JAGE_RESET_MOUSE();
    }
    if (JAGE_IS_KEY(GLFW_KEY_ESCAPE, GLFW_PRESS)) {
        m_flyClicked = false;
        glfwSetInputMode(Window::getActive()->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    if (m_flyClicked) {
        double rot_x, rot_y;
        JAGE_GET_RELATIVE_MOUSE(rot_x, rot_y);

        rot_x *= m_flySensitivity;
        rot_y *= m_flySensitivity;

        using glm::rotate;
        using glm::angle;
        using glm::radians;

        glm::vec3 new_orientation = rotate(m_orientation, radians(-(float)rot_y), normalize(glm::cross(m_orientation, m_up)));

        if (not (
                angle(new_orientation, m_up) <= radians(5.0f)
                or angle(new_orientation, -m_up) <= radians(5.0f))) {
            m_orientation = new_orientation;
        }

        m_orientation = rotate(m_orientation, radians(-(float)rot_x), m_up);

        JAGE_RESET_MOUSE();
    }

    DynamicActor::update();
}
