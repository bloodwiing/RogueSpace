#include "jage/actor/physicsactor.hpp"

#include "jage/runtime/time.hpp"

using jage::actor::PhysicsActor;

std::string PhysicsActor::getTypeName() const {
    return "PhysicsActor";
}

PhysicsActor::PhysicsActor(Scene* scene, abc::ActorABC* parent, std::string name, Tag tag, bool isVolatile, float weight, float drag)
    : DynamicActor(scene, parent, std::move(name), tag, isVolatile)
    , m_weight(weight)
    , m_drag(drag)
    , m_linearVelocity(0.0f)
    , m_angularVelocity(0.0f)
{ }

void PhysicsActor::update() {
    if (applyLinearVelocity(this, m_linearVelocity))
        diminishVelocity(m_linearVelocity, m_weight, 0.001f);

    if (applyAngularVelocity(this, m_angularVelocity))
        diminishVelocity(m_angularVelocity, m_drag, 0.0001f);

    DynamicActor::update();
}

float PhysicsActor::getWeight() const {
    return m_weight;
}

float PhysicsActor::getDrag() const {
    return m_drag;
}

glm::vec3 PhysicsActor::getLinearVelocity() const {
    return m_linearVelocity;
}

glm::vec3 PhysicsActor::getAngularVelocity() const {
    return m_angularVelocity;
}

void PhysicsActor::setWeight(float weight) {
    m_weight = weight;
}

void PhysicsActor::setDrag(float drag) {
    m_drag = drag;
}

void PhysicsActor::setLinearVelocity(const glm::vec3& linear) {
    m_linearVelocity = linear;
}

void PhysicsActor::setAngularVelocity(const glm::vec3& angular) {
    m_angularVelocity = angular;
}

void PhysicsActor::addForce(glm::vec3 force) {
    m_linearVelocity += force;
}

void PhysicsActor::addTorque(glm::vec3 torque) {
    m_angularVelocity += torque;
}

bool PhysicsActor::applyLinearVelocity(DynamicActor* target, const glm::vec3 &linear) {
    using jage::runtime::Time;
    if (!isVectorZero(linear)) {
        target->translate(linear * Time::getDeltaFloat());
        return true;
    }
    return false;
}

bool PhysicsActor::applyAngularVelocity(DynamicActor* target, const glm::vec3 &angular) {
    using jage::runtime::Time;
    if (!isVectorZero(angular)) {
        target->rotate(glm::quat(angular * Time::getDeltaFloat()));
        return true;
    }
    return false;
}

void PhysicsActor::diminishVelocity(glm::vec3 &vector, float influence, float deadZone) {
    using jage::runtime::Time;
    vector -= vector * (Time::getDeltaFloat() * influence);
    if (glm::length(vector) <= deadZone)
        vector = glm::vec3(0.0f);
}

bool PhysicsActor::isVectorZero(const glm::vec3 &vector) {
    return vector.x == 0.0f and vector.y == 0.0f and vector.z == 0.0f;
}
