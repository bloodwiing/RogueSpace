#include "engine/actor/playeractor.h"

#include <glm/gtx/rotate_vector.hpp>

#include "engine/time.h"
#include "graphics/screen.h"
#include "graphics/camera.h"

std::string PlayerActor::getTypeName() const {
    return "PlayerActor";
}

PlayerActor::PlayerActor(Scene *scene, ActorBase *parent, std::string name)
    : PhysicsActor(scene, parent, name, 0.5f)
{ }

void PlayerActor::update() {
    if (IS_KEY(GLFW_KEY_W, GLFW_PRESS)) {
        m_velocity += m_speed * m_orientation * Time::getDeltaFloat();
    }
    if (IS_KEY(GLFW_KEY_S, GLFW_PRESS)) {
        m_velocity += m_speed * -m_orientation * Time::getDeltaFloat();
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

    if (IS_KEY(GLFW_KEY_SPACE, GLFW_PRESS)) {
        m_speed = 10.0f;
    } else if (IS_KEY(GLFW_KEY_SPACE, GLFW_RELEASE)) {
        m_speed = 3.0f;
    }

    if (IS_MOUSE(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS) && !m_clicked) {
        m_clicked = true;
        glfwSetInputMode(Screen::getActive()->getWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        RESET_MOUSE();
    }
    if (IS_KEY(GLFW_KEY_ESCAPE, GLFW_PRESS)) {
        m_clicked = false;
        glfwSetInputMode(Screen::getActive()->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    if (m_clicked) {
        double rot_x, rot_y;
        GET_RELATIVE_MOUSE(rot_x, rot_y);

        rot_x *= m_sensitivity;
        rot_y *= m_sensitivity;

        rotate(glm::rotate(glm::radians((float)rot_y), glm::normalize(glm::cross(m_orientation, m_up))));
        rotate(glm::rotate(glm::radians((float)rot_x), m_up));

        m_up = glm::vec3(0.0f, 1.0f, 0.0f) * DynamicActor::getRotation();
        m_orientation = glm::vec3(0.0f, 0.0f, -1.0f) * DynamicActor::getRotation();

        RESET_MOUSE();

        Camera::getActiveCamera()->setOrientation(m_orientation, m_up);
    }

    PhysicsActor::update();
}
