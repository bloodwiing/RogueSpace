#include "jage/script/playercontrollerscript.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/gtx/rotate_vector.hpp>

#include "jage/actor/physicsactor.hpp"
#include "jage/actor/modelactor.hpp"
#include "jage/runtime/time.hpp"
#include "jage/runtime/window.hpp"

using jage::script::PlayerControllerScript;

PlayerControllerScript::PlayerControllerScript(jage::actor::abc::ActorABC *node) {
    auto* cast = dynamic_cast<RequiredNodeType*>(node);
    if (cast == nullptr)
        throw abc::ScriptABC::AttachError();
    m_node = cast;
}

void PlayerControllerScript::onAttach() {

}

void PlayerControllerScript::onSpawn() {

}

void PlayerControllerScript::onUpdate() {
    using jage::runtime::Time;

    if (m_fireCoolDown > 0.0f)
        m_fireCoolDown -= Time::getDeltaFloat();

    onKeyboardInput();
    onMouseInput();
}

void PlayerControllerScript::onDeath() {

}

void PlayerControllerScript::onKeyboardInput() {
    if (JAGE_IS_KEY(GLFW_KEY_W, GLFW_PRESS)) {
        m_node->throttleForward();
    } else if (JAGE_IS_KEY(GLFW_KEY_S, GLFW_PRESS)) {
        m_node->throttleBackward();
    } else {
        m_node->throttleReset();
    }

    if (JAGE_IS_KEY(GLFW_KEY_A, GLFW_PRESS)) {
        m_node->rollCounterClockwise();
    } else if (JAGE_IS_KEY(GLFW_KEY_D, GLFW_PRESS)) {
        m_node->rollClockwise();
    } else {
        m_node->rollReset();
    }
}

void PlayerControllerScript::onMouseInput() {
    double rot_x = 0.0, rot_y = 0.0;
    JAGE_GET_RELATIVE_MOUSE(rot_x, rot_y);

    using jage::runtime::Time;

    const auto& orientation = m_node->getOrientation();
    const auto& up = m_node->getUp();

    glm::vec3 steer = glm::normalize(glm::cross(orientation, up)) * (float)rot_y + up * (float)rot_x;
    m_node->setSteer(steer * m_sensitivity);

    glm::vec4 bulletOrientation = glm::vec4(orientation, 0.0);
    bulletOrientation = bulletOrientation * glm::rotate(glm::radians((float)rot_y * 45.0f), glm::normalize(glm::cross(orientation, up))) * glm::rotate(glm::radians((float)rot_x * 45.0f), up);

    if (m_fireCoolDown <= 0.0f and JAGE_IS_MOUSE(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS)) {
        auto bullet = m_node->getScene()->addVolatileChild<jage::actor::PhysicsActor>("Bullet", 0.0f, 0.0f);
        auto model = bullet->addChild<jage::actor::ModelActor>("model", "./res/bullet/BulletTemp.gltf");

        model->setScale(glm::vec3(0.2));
        bullet->setTranslation(m_node->getWorldPosition());
        if (m_fireFromLeft)
            bullet->translate(-glm::cross(orientation, up) * 0.35f + up * -0.15f);
        else
            bullet->translate(glm::cross(orientation, up) * 0.35f + up * -0.15f);
        bullet->setRotation(glm::quatLookAt((glm::vec3)bulletOrientation, up));
        bullet->addForce((glm::vec3)bulletOrientation * 40.0f + m_node->getThrottleVelocity());
        bullet->markDead(10.0f);

        m_fireCoolDown = 0.1f;
        m_fireFromLeft = !m_fireFromLeft;
    }
}
