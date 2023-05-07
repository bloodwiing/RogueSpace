#include "jage/actor/shipactor.hpp"

#include <glm/gtx/rotate_vector.hpp>

#include "jage/runtime/time.hpp"

using jage::actor::ShipActor;

std::string ShipActor::getTypeName() const {
    return "ShipActor";
}

float ShipActor::weight = 0.01f;
float ShipActor::drag = 1.5f;

ShipActor::ShipActor(jage::actor::Scene *scene, jage::actor::abc::ActorABC *parent, std::string name)
    : PhysicsActor(scene, parent, std::move(name), weight, drag)
{

}

void ShipActor::update() {
    using jage::runtime::Time;

    const auto& orientation = DynamicActor::getOrientation();
    const auto& up = DynamicActor::getUp();

    m_throttle += (m_targetThrottle - m_throttle) * m_throttleEasing * Time::getDeltaFloat();
    translate(orientation * m_throttle * Time::getDeltaFloat());

    m_roll += (m_targetRoll - m_roll) * m_rollEasing * Time::getDeltaFloat();
    rotate(glm::quat(orientation * m_roll * Time::getDeltaFloat()));

    rotate(glm::rotate(glm::radians(m_steer.y), glm::normalize(glm::cross(orientation, up))));
    rotate(glm::rotate(glm::radians(m_steer.x), up));

    PhysicsActor::update();
}

void ShipActor::setThrottle(float throttle) {
    m_targetThrottle = throttle;
}

void ShipActor::setRoll(float roll) {
    m_targetRoll = roll;
}

void ShipActor::setSteer(glm::vec2 euler) {
    m_steer = euler;
}

void jage::actor::ShipActor::throttleForward() {
    setThrottle(m_maxForwardSpeed);
}

void jage::actor::ShipActor::throttleBackward() {
    setThrottle(-m_maxBackwardSpeed);
}

void jage::actor::ShipActor::throttleReset() {
    setThrottle(m_throttle);
}

void jage::actor::ShipActor::rollClockwise() {
    setRoll(m_maxRollSpeed);
}

void jage::actor::ShipActor::rollCounterClockwise() {
    setRoll(-m_maxRollSpeed);
}

void jage::actor::ShipActor::rollReset() {
    setRoll(0.0f);
}
