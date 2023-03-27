#include "graphics/camera.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/rotate_vector.hpp>

Camera::Camera(unsigned int width, unsigned int height, glm::vec3 position)
    : m_width(width)
    , m_height(height)
    , m_position(position)
{  }

void Camera::updateMatrix(float fov_degrees, float near_plane, float far_plane) {
    glm::mat4 view(1.0f);
    glm::mat4 proj(1.0f);

    view = glm::lookAt(m_position, m_position + m_orientation, m_up);
    proj = glm::perspective(glm::radians(fov_degrees), (float)m_width / (float)m_height, near_plane, far_plane);

    m_matrix = proj * view;
}

glm::vec3 Camera::getPosition() const {
    return m_position;
}

void Camera::applyMatrix(Shader& shader, const char* uniform) {
    glUniformMatrix4fv(shader.getUniform(uniform), 1, GL_FALSE, glm::value_ptr(m_matrix));
}

void Camera::handleInputs(GLFWwindow *window, float delta) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        m_position += m_speed * m_orientation * delta;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        m_position += m_speed * -m_orientation * delta;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        m_position += m_speed * -glm::normalize(glm::cross(m_orientation, m_up)) * delta;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        m_position += m_speed * glm::normalize(glm::cross(m_orientation, m_up)) * delta;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        m_position += m_speed * m_up * delta;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        m_position += m_speed * -m_up * delta;
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        m_speed = 5.0f;
    } else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
        m_speed = 1.0f;
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !m_clicked) {
        m_clicked = true;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        glfwSetCursorPos(window, (float)m_width / 2, (float)m_height / 2);
    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        m_clicked = false;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    if (m_clicked) {
        double mouse_x, mouse_y;
        glfwGetCursorPos(window, &mouse_x, &mouse_y);

        float rot_x = m_sensitivity * (float)(mouse_x - ((float)m_width / 2)) / (float)m_width,
              rot_y = m_sensitivity * (float)(mouse_y - ((float)m_height / 2)) / (float)m_height;

        glm::vec3 new_orientation = glm::rotate(m_orientation, glm::radians(-rot_y), glm::normalize(glm::cross(m_orientation, m_up)));

        if (!(glm::angle(new_orientation, m_up) <= glm::radians(5.0f) or glm::angle(new_orientation, -m_up) <= glm::radians(5.0f))) {
            m_orientation = new_orientation;
        }

        m_orientation = glm::rotate(m_orientation, glm::radians(-rot_x), m_up);

        glfwSetCursorPos(window, (double)m_width / 2, (double)m_height / 2);
    }
}
