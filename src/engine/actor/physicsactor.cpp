#include "engine/actor/physicsactor.hpp"

#include "engine/time.hpp"

namespace Actors = Engine::Actors;

std::string Actors::PhysicsActor::getTypeName() const {
    return "PhysicsActor";
}

Actors::PhysicsActor::PhysicsActor(Scene* scene, ActorBase* parent, std::string name, float weight, float drag)
    : DynamicActor(scene, parent, name)
    , m_weight(weight)
    , m_drag(drag)
    , m_linearVelocity(0.0f)
    , m_angularVelocity(0.0f)
{ }

void Actors::PhysicsActor::update() {
    if (applyLinearVelocity(this, m_linearVelocity))
        diminishVelocity(m_linearVelocity, m_weight, 0.001f);

    if (applyAngularVelocity(this, m_angularVelocity))
        diminishVelocity(m_angularVelocity, m_drag, 0.0001f);

    DynamicActor::update();
}

float Actors::PhysicsActor::getWeight() const {
    return m_weight;
}

float Actors::PhysicsActor::getDrag() const {
    return m_drag;
}

glm::vec3 Actors::PhysicsActor::getLinearVelocity() const {
    return m_linearVelocity;
}

glm::vec3 Actors::PhysicsActor::getAngularVelocity() const {
    return m_angularVelocity;
}

void Actors::PhysicsActor::setWeight(float weight) {
    m_weight = weight;
}

void Actors::PhysicsActor::setDrag(float drag) {
    m_drag = drag;
}

void Actors::PhysicsActor::setLinearVelocity(const glm::vec3& linear) {
    m_linearVelocity = linear;
}

void Actors::PhysicsActor::setAngularVelocity(const glm::vec3& angular) {
    m_angularVelocity = angular;
}

void Actors::PhysicsActor::addForce(glm::vec3 force) {
    m_linearVelocity += force;
}

void Actors::PhysicsActor::addTorque(glm::vec3 torque) {
    m_angularVelocity += torque;
}

bool Actors::PhysicsActor::applyLinearVelocity(DynamicActor* target, const glm::vec3 &linear) {
    if (!isVectorZero(linear)) {
        target->translate(linear * Time::getDeltaFloat());
        return true;
    }
    return false;
}

bool Actors::PhysicsActor::applyAngularVelocity(DynamicActor* target, const glm::vec3 &angular) {
    if (!isVectorZero(angular)) {
        target->rotate(glm::quat(angular) * Time::getDeltaFloat());
        return true;
    }
    return false;
}

void Actors::PhysicsActor::diminishVelocity(glm::vec3 &vector, float influence, float deadZone) {
    vector -= vector * (Time::getDeltaFloat() * influence);
    if (glm::length(vector) <= deadZone)
        vector = glm::vec3(0.0f);
}

bool Actors::PhysicsActor::isVectorZero(const glm::vec3 &vector) {
    return vector.x == 0.0f and vector.y == 0.0f and vector.z == 0.0f;
}
