#include "engine/actor/physicsactor.h"

#include "engine/time.h"

PhysicsActor::PhysicsActor(Scene* scene, ActorBase* parent, std::string name, float weight)
    : DynamicActor(scene, parent, name)
    , m_weight(weight)
    , m_velocity(0.0f)
{ }

void PhysicsActor::update() {
    if (m_velocity.x == 0.0f and m_velocity.y == 0.0f and m_velocity.z == 0.0f)
        return;

    translate(m_velocity * Time::getDeltaFloat());
    m_velocity -= m_velocity * (Time::getDeltaFloat() * m_weight);
    if (glm::length(m_velocity) <= 0.001f)
        m_velocity = glm::vec3(0.0f);

    DynamicActor::update();
}

float PhysicsActor::getWeight() const {
    return m_weight;
}

glm::vec3 PhysicsActor::getVelocity() const {
    return m_velocity;
}

void PhysicsActor::setWeight(float weight) {
    m_weight = weight;
}

void PhysicsActor::setVelocity(const glm::vec3& velocity) {
    m_velocity = velocity;
}
