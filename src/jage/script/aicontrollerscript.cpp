#include "jage/script/aicontrollerscript.hpp"

#include <glm/gtx/rotate_vector.hpp>

#include "jage/actor/physicsactor.hpp"
#include "jage/actor/modelactor.hpp"
#include "jage/runtime/time.hpp"

using jage::script::AIControllerScript;

std::mt19937 AIControllerScript::random = std::mt19937(time(nullptr));

AIControllerScript::AIControllerScript(jage::actor::abc::ActorABC *node) {
    validate(node);
}

void AIControllerScript::onAttach() {

}

void AIControllerScript::onSpawn() {

}

void AIControllerScript::onUpdate() {
    using jage::runtime::Time;

    const float bulletSpeed = 40.0f;

    // Weapon cool down
    if (m_fireCoolDown > 0.0f)
        m_fireCoolDown -= Time::getDeltaFloat();

    // Don't continue if you have nothing to target
    if (m_target == nullptr)
        return;

    // Direction towards target
    const glm::vec3 toTarget = m_target->getWorldPosition() - m_node->getWorldPosition();
    const float distanceToTarget = glm::length(toTarget - m_node->getThrottle() * Time::getDeltaFloat());
    const float timeToTarget = distanceToTarget / (m_node->getMaxForwardSpeed());

    // Fixed for movement speed
    const glm::vec3 correctedToTarget = toTarget + m_target->getThrottleVelocity() * timeToTarget;
    glm::vec3 toTargetNormal = glm::normalize(correctedToTarget);

    // Fleeing Machine Block
    // If distance to target is too close, save a vector to target, but slightly above it to continue moving there
    // Keep fleeing until distance gets larger
    if (!m_fleeing and distanceToTarget < m_fleeDistance) {
        m_fleeVector = glm::normalize(toTargetNormal + m_node->getUp());
        m_vectorChangeEase = 0.0f;
        m_fleeing = true;
        m_seeking = false;
    }
    else if (m_fleeing and distanceToTarget > m_seekDistance) {
        m_fleeing = false;
        m_seekCoolDown = m_seekApplyCoolDown(random);
        m_orbitAngle = m_orbitApplyAngle(random);
    }

    bool orbiting = false;

    // If fleeing use the remembered vector
    if (m_fleeing)
        toTargetNormal = m_fleeVector;
    // If not (just recently went out of it) ease into the "orbit" vector
    // This mode is only partially interested in the player
    else if (m_seekCoolDown >= 0.0f) {
        orbiting = true;
        m_vectorChangeEase += Time::getDeltaFloat() * m_avoidEaseMultiplier;
        m_seekCoolDown -= Time::getDeltaFloat();
        toTargetNormal = glm::normalize(glm::mix(m_fleeVector, glm::rotate(glm::cross(toTargetNormal, m_target->getUp()), m_orbitAngle, toTargetNormal), m_vectorChangeEase));
        if (m_seekCoolDown < 0.0f) {
            m_vectorChangeEase = 0.0f;
        }
    }
    // When it ends, the AI will ease into the actual target vector
    else if (m_vectorChangeEase < 1.0f) {
        m_vectorChangeEase += Time::getDeltaFloat() * m_avoidEaseMultiplier;
        toTargetNormal = glm::normalize(glm::mix(m_fleeVector, toTargetNormal, m_vectorChangeEase));
    }

    // Quaternion towards the vector
    glm::quat targetQuaternion = glm::normalize(glm::quatLookAt(toTargetNormal, m_node->getUp()));
    // Difference in current and goal quaternions
    // A condition is here in case the two quaternions are inverts (which actually means they are still equal rotations, just a different sign)
    const float targetAngleDiff = glm::sign(m_node->getRotation().w) == glm::sign(targetQuaternion.w) ?
                                  glm::length(m_node->getRotation() - targetQuaternion) :
                                  glm::length(m_node->getRotation() + targetQuaternion);

    // Clamp turning rate, so it's not too fast or slow
    float turnRate = glm::max(glm::min(targetAngleDiff * m_sensitivity, m_maxTurnRate), m_minTurnRate);

    // Apply the turn
    m_node->setRotation(glm::normalize(glm::slerp(m_node->getRotation(), targetQuaternion, turnRate * Time::getDeltaFloat())));

    // Seeking Machine Block
    // "Seek" the target (engage forward thrusters) if not already, not orbiting and the angle is close enough
    if (!m_seeking and !m_fleeing and !orbiting and targetAngleDiff < m_seekAngleBegin)
        m_seeking = true;
    // Stop seeking the target if the angle goes off too far
    else if (m_seeking and !m_fleeing and targetAngleDiff > m_seekAngleEnd)
        m_seeking = false;

    // Only go forward if Avoiding or Seeking or Orbiting
    if (m_seeking or m_fleeing or orbiting) {
        m_node->throttleForward();
    } else {
        // Otherwise slow down to a specific speed
        if (m_node->getThrottle() > 0.9f) {
            m_node->throttleBackward();
        // Keep the speed after
        } else {
            m_node->throttleReset();
        }
    }

    // Firing
    if ((m_seeking and !m_fleeing) and distanceToTarget < m_attackDistance and m_fireCoolDown <= 0.0f) {
        const auto& orientation = m_node->getOrientation();
        const auto& up = m_node->getUp();

        auto bullet = m_node->getScene()->addVolatileChild<jage::actor::PhysicsActor>("Bullet", 0.0f, 0.0f);
        auto model = bullet->addChild<jage::actor::ModelActor>("model", "./res/bullet/BulletTemp.gltf");

        model->setScale(glm::vec3(0.2));
        bullet->setTranslation(m_node->getWorldPosition());
        if (m_fireFromLeft)
            bullet->translate(-glm::cross(orientation, up) * 0.35f + up * -0.15f);
        else
            bullet->translate(glm::cross(orientation, up) * 0.35f + up * -0.15f);
        bullet->setRotation(glm::quatLookAt((glm::vec3)glm::vec4(orientation, 0.0), up));
        bullet->addForce((glm::vec3)glm::vec4(orientation, 0.0) * bulletSpeed + m_node->getThrottleVelocity());
        bullet->markDead(10.0f);

        m_fireCoolDown = 0.1f;
        m_fireFromLeft = !m_fireFromLeft;
    }
}

void AIControllerScript::onDeath() {

}

void jage::script::AIControllerScript::setTarget(jage::actor::ShipActor *target) {
    m_target = target;
}

//void AIControllerScript::onKeyboardInput() {
//    if (JAGE_IS_KEY(GLFW_KEY_W, GLFW_PRESS)) {
//        m_node->throttleForward();
//    } else if (JAGE_IS_KEY(GLFW_KEY_S, GLFW_PRESS)) {
//        m_node->throttleBackward();
//    } else {
//        m_node->throttleReset();
//    }
//
//    if (JAGE_IS_KEY(GLFW_KEY_A, GLFW_PRESS)) {
//        m_node->rollCounterClockwise();
//    } else if (JAGE_IS_KEY(GLFW_KEY_D, GLFW_PRESS)) {
//        m_node->rollClockwise();
//    } else {
//        m_node->rollReset();
//    }
//}

//void AIControllerScript::onMouseInput() {
//    double rot_x = 0.0, rot_y = 0.0;
//    JAGE_GET_RELATIVE_MOUSE(rot_x, rot_y);
//
//    using jage::runtime::Time;
//
//    const auto& orientation = m_node->getOrientation();
//    const auto& up = m_node->getUp();
//
//    glm::vec3 steer = glm::normalize(glm::cross(orientation, up)) * (float)rot_y + up * (float)rot_x;
//    m_node->setSteer(steer * m_sensitivity);
//
//    glm::vec4 bulletOrientation = glm::vec4(orientation, 0.0);
//    bulletOrientation = bulletOrientation * glm::rotate(glm::radians((float)rot_y * 45.0f), glm::normalize(glm::cross(orientation, up))) * glm::rotate(glm::radians((float)rot_x * 45.0f), up);
//
//    if (m_fireCoolDown <= 0.0f and JAGE_IS_MOUSE(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS)) {
//        auto bullet = m_node->getScene()->addVolatileChild<jage::actor::PhysicsActor>("Bullet", 0.0f, 0.0f);
//        auto model = bullet->addChild<jage::actor::ModelActor>("model", "./res/bullet/BulletTemp.gltf");
//
//        model->setScale(glm::vec3(0.2));
//        bullet->setTranslation(m_node->getTranslation());
//        if (m_fireFromLeft)
//            bullet->translate(-glm::cross(orientation, up) * 0.35f + up * -0.15f);
//        else
//            bullet->translate(glm::cross(orientation, up) * 0.35f + up * -0.15f);
//        bullet->setRotation(glm::quatLookAt((glm::vec3)bulletOrientation, up));
//        bullet->addForce((glm::vec3)bulletOrientation * 40.0f + m_node->getThrottleVelocity());
//        bullet->markDead(10.0f);
//
//        m_fireCoolDown = 0.1f;
//        m_fireFromLeft = !m_fireFromLeft;
//    }
//}
