#include "engine/actor/playeractor.h"

#include <glm/gtx/rotate_vector.hpp>

#include "engine/time.h"
#include "graphics/window.h"
#include "graphics/camera.h"

const float PlayerActor::mass = 0.5f;
const float PlayerActor::drag = 1.5f;

std::string PlayerActor::getTypeName() const {
    return "PlayerActor";
}

PlayerActor::PlayerActor(Scene *scene, ActorBase *parent, std::string name)
    : PhysicsActor(scene, parent, name, mass, drag)
{ }

void PlayerActor::update() {
    if (m_scene->isInFreeFlight()) {
        PhysicsActor::update();
        return;
    }

    if (IS_KEY(GLFW_KEY_W, GLFW_PRESS)) {
        addForce(m_linearSpeed * m_orientation * Time::getDeltaFloat());
    }
    if (IS_KEY(GLFW_KEY_S, GLFW_PRESS)) {
        addForce(m_linearSpeed * -m_orientation * Time::getDeltaFloat());
    }

    if (IS_KEY(GLFW_KEY_A, GLFW_PRESS)) {
        addTorque(m_angularSpeed * m_orientation * Time::getDeltaFloat());
    }
    if (IS_KEY(GLFW_KEY_D, GLFW_PRESS)) {
        addTorque(m_angularSpeed * -m_orientation * Time::getDeltaFloat());
    }

    if (IS_KEY(GLFW_KEY_LEFT_SHIFT, GLFW_PRESS)) {
        m_linearSpeed = 10.0f;
    } else if (IS_KEY(GLFW_KEY_LEFT_SHIFT, GLFW_RELEASE)) {
        m_linearSpeed = 3.0f;
    }

    if (IS_MOUSE(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS) && !m_clicked) {
        m_clicked = true;
        glfwSetInputMode(Window::getActive()->getWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        RESET_MOUSE();
    }
    if (IS_KEY(GLFW_KEY_ESCAPE, GLFW_PRESS)) {
        m_clicked = false;
        glfwSetInputMode(Window::getActive()->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
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
    }

    PhysicsActor::update();
}
