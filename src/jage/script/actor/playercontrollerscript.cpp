#include "jage/script/actor/playercontrollerscript.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/gtx/rotate_vector.hpp>
#include <utility>

#include "jage/node/actor/physicsactor.hpp"
#include "jage/node/actor/modelactor.hpp"
#include "jage/runtime/time.hpp"
#include "jage/runtime/window.hpp"

using jage::script::actor::PlayerControllerScript;

PlayerControllerScript::PlayerControllerScript(abc::ScriptableABC* node, std::weak_ptr<CameraShakeScript> cameraShake)
        : m_cameraShakeScript(std::move(cameraShake))
{
    validate(node);
    m_weaponScript = dependsOn<WeaponScript>();
}

void PlayerControllerScript::onAttach() {

}

void PlayerControllerScript::onSpawn() {

}

void PlayerControllerScript::onUpdate() {
    using jage::runtime::Time;

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

    const float shakeAmplitude = (glm::sqrt(glm::abs(m_node->getThrottle()) / m_node->getMaxForwardSpeed()) - 0.8f) * 0.015f;
    m_cameraShakeScript.lock()->setAmplitude(shakeAmplitude);
}

void PlayerControllerScript::onMouseInput() {
    double rot_x = 0.0, rot_y = 0.0;
    JAGE_GET_RELATIVE_MOUSE(rot_x, rot_y);
    float length = glm::length(glm::vec2(rot_x, rot_y));

    using jage::runtime::Time;

    const auto& orientation = m_node->getOrientation();
    const auto& up = m_node->getUp();

    auto shipRot = glm::vec2(rot_x, rot_y);
    shipRot = shipRot / glm::max(glm::length(shipRot), 1.0f);

    glm::vec3 steer = glm::normalize(glm::cross(orientation, up)) * (float)shipRot.y + up * -(float)shipRot.x;

    if (length > 0.02f) {
        m_node->setSteer(steer * m_sensitivity);
    } else if (length > 0.005f) {
        m_node->setSteer(steer * m_sensitivity * ((length - 0.005f) / 0.015f));
    } else {
        m_node->setSteer(glm::vec3(0.0f));
    }

    auto weaponRot = glm::vec2(rot_x, rot_y);
    weaponRot = weaponRot / (glm::max(glm::length(weaponRot), 0.4f) / 0.4f);

    glm::vec4 bulletOrientation = glm::vec4(orientation, 0.0);
    bulletOrientation = glm::rotate(glm::radians((float)weaponRot.y * 45.0f), glm::normalize(glm::cross(orientation, up))) * glm::rotate(glm::radians(-(float)weaponRot.x * 45.0f), up) * bulletOrientation;

    if (JAGE_IS_MOUSE(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS)) {
        m_weaponScript.lock()->shootThisFrame(m_node->getThrottleVelocity(), bulletOrientation, up);
    }
}
