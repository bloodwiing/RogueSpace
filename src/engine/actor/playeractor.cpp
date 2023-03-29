#include "engine/actor/playeractor.h"

#include <glm/gtx/rotate_vector.hpp>

#include "graphics/screen.h"
#include "graphics/camera.h"

PlayerActor::PlayerActor(Scene *scene, ActorBase *parent)
        : PhysicsActor(scene, parent)
{
    setWeight(0.5f);
}

void PlayerActor::update(GLFWwindow *window, double delta) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        m_velocity += m_speed * m_orientation * (float)delta;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        m_velocity += m_speed * -m_orientation * (float)delta;
    }
//    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
//        m_translation += m_speed * -glm::normalize(glm::cross(m_orientation, m_up)) * delta;
//    }
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
//        m_translation += m_speed * glm::normalize(glm::cross(m_orientation, m_up)) * delta;
//    }
//    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
//        m_translation += m_speed * m_up * delta;
//    }
//    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
//        m_translation += m_speed * -m_up * delta;
//    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        m_speed = 10.0f;
    } else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
        m_speed = 3.0f;
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !m_clicked) {
        m_clicked = true;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        glfwSetCursorPos(window, (float)Screen::getInstance()->width / 2, (float)Screen::getInstance()->height / 2);
    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        m_clicked = false;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    if (m_clicked) {
        double mouse_x, mouse_y;
        glfwGetCursorPos(window, &mouse_x, &mouse_y);

        float rot_x = m_sensitivity * (float)(mouse_x - ((float)Screen::getInstance()->width / 2)) / (float)Screen::getInstance()->width,
                rot_y = m_sensitivity * (float)(mouse_y - ((float)Screen::getInstance()->height / 2)) / (float)Screen::getInstance()->height;

        m_orientation = glm::rotate(m_orientation, glm::radians(-rot_y), glm::normalize(glm::cross(m_orientation, m_up)));
        m_orientation = glm::rotate(m_orientation, glm::radians(-rot_x), m_up);

        glfwSetCursorPos(window, (double)Screen::getInstance()->width / 2, (double)Screen::getInstance()->height / 2);

        Camera::getActiveCamera()->setOrientation(m_orientation, m_up);
    }

    PhysicsActor::update(window, delta);
}
