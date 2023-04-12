#include "engine/actor/physicsactor.hpp"

#include "engine/time.hpp"

std::string PhysicsActor::getTypeName() const {
    return "PhysicsActor";
}

PhysicsActor::PhysicsActor(Scene* scene, ActorBase* parent, std::string name, float weight, float drag)
    : DynamicActor(scene, parent, name)
    , m_weight(weight)
    , m_drag(drag)
    , m_linearVelocity(0.0f)
    , m_angularVelocity(0.0f)
{ }

void PhysicsActor::update() {
    if (!isVectorZero(m_linearVelocity)) {
        translate(m_linearVelocity * Time::getDeltaFloat());
        m_linearVelocity -= m_linearVelocity * (Time::getDeltaFloat() * m_weight);
        if (glm::length(m_linearVelocity) <= 0.001f)
            m_linearVelocity = glm::vec3(0.0f);
    }

    if (!isVectorZero(m_angularVelocity)) {
        rotate(glm::quat(m_angularVelocity) * Time::getDeltaFloat());
        m_angularVelocity -= m_angularVelocity * (Time::getDeltaFloat() * m_drag);
        if (glm::length(m_angularVelocity) <= 0.0001f)
            m_angularVelocity = glm::vec3(0.0f);
    }

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

bool PhysicsActor::isVectorZero(const glm::vec3 &vector) {
    return vector.x == 0.0f and vector.y == 0.0f and vector.z == 0.0f;
}
