#include "graphics/camera.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_access.hpp>

#include "engine/time.h"

#include "graphics/window.h"

Camera* Camera::m_active = nullptr;

std::string Camera::getTypeName() const {
    return "Camera";
}

Camera::Camera(Scene *scene, ActorBase *parent, std::string name)
    : DynamicActor(scene, parent, name)
{  }

Camera::~Camera() {
    DynamicActor::~DynamicActor();
    if (m_active == this)
        m_active = nullptr;
}

void Camera::updateMatrix(float fov_degrees, float near_plane, float far_plane) {
    glm::mat4 view(1.0f);
    glm::mat4 proj(1.0f);

    glm::vec3 point = glm::column(DynamicActor::getWorldMatrix(), 3);

    view = glm::lookAt(point, point + m_orientation, m_up);
    proj = glm::perspective(glm::radians(fov_degrees), Window::getActive()->getAspectRatio(), near_plane, far_plane);

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

void Camera::update() {
    DynamicActor::update();

    m_up = glm::normalize(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f) * DynamicActor::getWorldMatrix());
    m_orientation = glm::normalize(glm::vec4(0.0f, 0.0f, -1.0f, 0.0f) * DynamicActor::getWorldMatrix());
}

void Camera::copyOrientation(Camera *camera, bool copyUpVector /* = true */) {
    m_orientation = glm::normalize(camera->m_orientation);
    if (copyUpVector)
        m_up = glm::normalize(camera->m_up);
}

void Camera::freeFlyUpdate() {
    if (IS_KEY(GLFW_KEY_W, GLFW_PRESS)) {
        translate(m_flySpeed * m_orientation * Time::getDeltaFloat());
    }
    if (IS_KEY(GLFW_KEY_S, GLFW_PRESS)) {
        translate(m_flySpeed * -m_orientation * Time::getDeltaFloat());
    }
    if (IS_KEY(GLFW_KEY_A, GLFW_PRESS)) {
        translate(m_flySpeed * -glm::normalize(glm::cross(m_orientation, m_up)) * Time::getDeltaFloat());
    }
    if (IS_KEY(GLFW_KEY_D, GLFW_PRESS)) {
        translate(m_flySpeed * glm::normalize(glm::cross(m_orientation, m_up)) * Time::getDeltaFloat());
    }
    if (IS_KEY(GLFW_KEY_E, GLFW_PRESS)) {
        translate(m_flySpeed * m_up * Time::getDeltaFloat());
    }
    if (IS_KEY(GLFW_KEY_Q, GLFW_PRESS)) {
        translate(m_flySpeed * -m_up * Time::getDeltaFloat());
    }

    if (IS_KEY(GLFW_KEY_SPACE, GLFW_PRESS)) {
        m_flySpeed = 5.0f;
    } else if (IS_KEY(GLFW_KEY_SPACE, GLFW_RELEASE)) {
        m_flySpeed = 1.0f;
    }

    if (IS_MOUSE(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS) && !m_flyClicked) {
        m_flyClicked = true;
        glfwSetInputMode(Window::getActive()->getWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        RESET_MOUSE();
    }
    if (IS_KEY(GLFW_KEY_ESCAPE, GLFW_PRESS)) {
        m_flyClicked = false;
        glfwSetInputMode(Window::getActive()->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    if (m_flyClicked) {
        double rot_x, rot_y;
        GET_RELATIVE_MOUSE(rot_x, rot_y);

        rot_x *= m_flySensitivity;
        rot_y *= m_flySensitivity;

        glm::vec3 new_orientation = glm::rotate(m_orientation, glm::radians(-(float)rot_y), glm::normalize(glm::cross(m_orientation, m_up)));

        if (not (
                glm::angle(new_orientation, m_up) <= glm::radians(5.0f)
                or glm::angle(new_orientation, -m_up) <= glm::radians(5.0f))) {
            m_orientation = new_orientation;
        }

        m_orientation = glm::rotate(m_orientation, glm::radians(-(float)rot_x), m_up);

        RESET_MOUSE();
    }

    DynamicActor::update();
}
