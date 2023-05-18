#include "jage/node/actor/shipactor.hpp"

#include <iostream>
#include <glm/gtx/rotate_vector.hpp>

#include "jage/runtime/time.hpp"

using jage::node::actor::ShipActor;

std::string ShipActor::getTypeName() const {
    return "ShipActor";
}

float ShipActor::weight = 0.01f;
float ShipActor::drag = 1.5f;

ShipActor::ShipActor(JAGE_ACTOR_ARGS)
    : PhysicsActor(parent, std::move(name), scene, tag, isVolatile, weight, drag)
{

}

void ShipActor::update() {
    using jage::runtime::Time;

    const auto& orientation = DynamicActor::getOrientation();
    const auto& up = DynamicActor::getUp();

    float throttleMultiplier = 1.0f;
    if (glm::sign(m_throttle) != glm::sign(m_targetThrottle))
        throttleMultiplier = m_stoppingMultiplier;

    m_throttle += (m_targetThrottle - m_throttle) * m_throttleEasing * throttleMultiplier * Time::getDeltaFloat();
    applyLinearVelocity(this, orientation * m_throttle);

    m_roll += (m_targetRoll - m_roll) * m_rollEasing * Time::getDeltaFloat();
    applyAngularVelocity(this, orientation * m_roll);

    float resistance = 1.0f - m_throttle * m_steerResistance;
    rotate(glm::quat(m_steer * resistance * Time::getDeltaFloat()));

    PhysicsActor::update();
}

void ShipActor::setThrottle(float throttle) {
    m_targetThrottle = throttle;
}

void ShipActor::setRoll(float roll) {
    m_targetRoll = roll;
}

void ShipActor::setSteer(glm::vec3 euler) {
    m_steer = euler;
}

float ShipActor::getThrottle() const {
    return m_throttle;
}

glm::vec3 ShipActor::getThrottleVelocity() const {
    return DynamicActor::getOrientation() * m_throttle;
}

void ShipActor::throttleForward() {
    setThrottle(m_maxForwardSpeed);
}

void ShipActor::throttleBackward() {
    setThrottle(-m_maxBackwardSpeed);
}

void ShipActor::throttleReset() {
    setThrottle(m_throttle);
}

float ShipActor::getMaxForwardSpeed() const {
    return m_maxForwardSpeed;
}

float ShipActor::getMaxBackwardSpeed() const {
    return m_maxBackwardSpeed;
}

void ShipActor::rollClockwise() {
    setRoll(m_maxRollSpeed);
}

void ShipActor::rollCounterClockwise() {
    setRoll(-m_maxRollSpeed);
}

void ShipActor::rollReset() {
    setRoll(0.0f);
}

float ShipActor::getMaxRollSpeed() const {
    return m_maxRollSpeed;
}
