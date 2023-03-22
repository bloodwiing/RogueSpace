#include "graphics/camera.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/rotate_vector.hpp>

Camera::Camera(unsigned int width, unsigned int height, glm::vec3 position)
    : width(width)
    , height(height)
    , position(position)
{  }

void Camera::applyMVP(float fov_degrees, float near_plane, float far_plane, Shader &shader, const char *uniform) {
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);

    view = glm::lookAt(position, position + orientation, up);
    proj = glm::perspective(glm::radians(fov_degrees), (float)width / (float)height, near_plane, far_plane);

    glUniformMatrix4fv(shader.getUniform(uniform), 1, GL_FALSE, glm::value_ptr(proj * view));
}

void Camera::handleInputs(GLFWwindow *window, float delta) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        position += speed * orientation * delta;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        position += speed * -orientation * delta;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        position += speed * -glm::normalize(glm::cross(orientation, up)) * delta;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        position += speed * glm::normalize(glm::cross(orientation, up)) * delta;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        position += speed * up * delta;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        position += speed * -up * delta;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        speed = 5.0f;
    } else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
        speed = 1.0f;
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        double mouse_x, mouse_y;
        glfwGetCursorPos(window, &mouse_x, &mouse_y);

        float rot_x = sensitivity * (float)(mouse_x - ((float)width / 2)) / (float)width * delta,
              rot_y = sensitivity * (float)(mouse_y - ((float)height / 2)) / (float)height * delta;

        glm::vec3 new_orientation = glm::rotate(orientation, glm::radians(-rot_y), glm::normalize(glm::cross(orientation, up)));

        if (!(glm::angle(new_orientation, up) <= glm::radians(5.0f) or glm::angle(new_orientation, -up) <= glm::radians(5.0f))) {
            orientation = new_orientation;
        }

        orientation = glm::rotate(orientation, glm::radians(-rot_x), up);

        glfwSetCursorPos(window, (double)width / 2, (double)height / 2);
    } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}
