#include "jage/script/actor/aicontrollerscript.hpp"

#include <glm/gtx/rotate_vector.hpp>

#include "jage/node/actor/physicsactor.hpp"
#include "jage/node/actor/modelactor.hpp"
#include "jage/runtime/time.hpp"

using jage::script::actor::AIControllerScript;

std::mt19937 AIControllerScript::random = std::mt19937(time(nullptr));

AIControllerScript::AIControllerScript(abc::ScriptableABC* node)
    : m_state(State::SEEKING)
{
    validate(node);
    m_weaponScript = dependsOn<WeaponScript>();
}

void AIControllerScript::onAttach() {

}

void AIControllerScript::onSpawn() {

}

void AIControllerScript::onUpdate() {
    using jage::runtime::Time;

    // Don't continue if you have nothing to target
    if (m_target == nullptr)
        return;

    const glm::vec3 target = m_target->getWorldPosition() - m_node->getWorldPosition();

    const float distance = getTargetDistance(target);
    const glm::vec3& predicted = predictTargetPosition(target, distance);

    switch (m_state) {
        case SEARCHING:
            return runSearch(predicted, distance);
        case SEEKING:
            return runSeek(predicted, distance);
        case FLEEING:
            return runFlee(predicted, distance);
        case ORBITING:
            return runOrbit(predicted, distance);
        default:
            return;
    }
}

void AIControllerScript::onDeath() {

}

void AIControllerScript::setTarget(jage::node::actor::ShipActor *target) {
    m_target = target;
}

void AIControllerScript::runSearch(const glm::vec3& predicted, float distance) {
    float angleDifference = 0.0f;
    turnToVector(predicted, predicted, angleDifference);

    slowDown();

    if (angleDifference < m_seekAngleBegin) {
        m_state = State::SEEKING;
    }
}

void AIControllerScript::runSeek(const glm::vec3& predicted, float distance) {
    float angleDifference = 0.0f;
    turnToVector(m_orbitVector, predicted, angleDifference);

    if (angleDifference > m_seekAngleEnd) {
        m_state = State::SEARCHING;
    }

    m_node->throttleForward();

    if (distance < m_fleeDistance) {
        m_state = State::FLEEING;
        m_fleeVector = glm::normalize(predicted + m_node->getUp());
    } else if (distance < m_attackDistance) {
        m_weaponScript->shootThisFrame(m_node->getThrottleVelocity());
    }
}

void AIControllerScript::runFlee(const glm::vec3& predicted, float distance) {
    float angleDifference = 0.0f;
    turnToVector(predicted, m_fleeVector, angleDifference);

    if (distance > m_seekDistance) {
        m_state = State::ORBITING;
        m_orbitDuration = m_orbitApplyDuration(random);
        m_orbitAngle = m_orbitApplyAngle(random);
        resetEasing();
    }

    m_node->throttleForward();
}

void AIControllerScript::runOrbit(const glm::vec3& predicted, float distance) {
    using jage::runtime::Time;

    m_orbitDuration -= Time::getDeltaFloat();

    m_orbitVector = glm::rotate(glm::cross(predicted, m_target->getUp()), m_orbitAngle, predicted);

    float angleDifference = 0.0f;
    turnToVector(m_fleeVector, m_orbitVector, angleDifference);

    m_node->throttleForward();

    if (m_orbitDuration < 0.0f) {
        m_state = State::SEARCHING;
        resetEasing();
    }
}

float AIControllerScript::getTargetDistance(const glm::vec3& target) {
    return glm::length(target - m_node->getThrottle() * jage::runtime::Time::getDeltaFloat());
}

glm::vec3 AIControllerScript::predictTargetPosition(const glm::vec3& target, float distance) {
    glm::vec3 bulletVelocity = (m_node->getMaxForwardSpeed() + m_weaponScript->getBulletSpeed()) * m_node->getOrientation();

    float approachSpeed = glm::length(bulletVelocity - m_target->getThrottleVelocity());
    // Assume approach speed even if it's invalid
    if (approachSpeed == 0.0f)
        approachSpeed = 1.0f;

    const float timeToTarget = distance / approachSpeed;

    return glm::normalize(target + m_target->getThrottleVelocity() * timeToTarget);
}

void AIControllerScript::slowDown() {
    // Slow down to a specific speed
    if (m_node->getThrottle() > 0.9f) {
        m_node->throttleBackward();
    // Keep the speed after
    } else {
        m_node->throttleReset();
    }
}

void AIControllerScript::turnToVector(const glm::vec3& prevVector, glm::vec3 vector, float& angleDifference) {
    // If easing is enabled, ease from an old to a new vector
    vector = easeBetweenVectors(prevVector, vector);

    // Quaternion towards the vector
    glm::quat targetQuaternion = glm::normalize(glm::quatLookAt(vector, m_node->getUp()));

    // Difference in current and goal quaternions
    // A condition is here in case the two quaternions are inverts (which actually means they are still equal rotations, just a different sign)
    angleDifference = glm::sign(m_node->getRotation().w) == glm::sign(targetQuaternion.w)
            ? glm::length(m_node->getRotation() - targetQuaternion)
            : glm::length(m_node->getRotation() + targetQuaternion);

    // Clamp turning rate, so it's not too fast or slow
    float turnRate = glm::max(glm::min(angleDifference * m_sensitivity, m_maxTurnRate), m_minTurnRate);

    // Apply the turn
    m_node->setRotation(glm::normalize(glm::slerp(m_node->getRotation(), targetQuaternion, turnRate * jage::runtime::Time::getDeltaFloat())));
}

void AIControllerScript::resetEasing() {
    m_vectorChangeEase = 0.0f;
}

glm::vec3 AIControllerScript::easeBetweenVectors(const glm::vec3 &a, const glm::vec3 &b) {
    if (m_vectorChangeEase < 1.0f) {
        m_vectorChangeEase += jage::runtime::Time::getDeltaFloat() * m_easeMultiplier;
        return glm::normalize(glm::mix(a, b, m_vectorChangeEase));
    }
    return b;
}
