#include "engine/actor/physicsactor.h"

void PhysicsActor::update(GLFWwindow *window, double delta) {
    if (m_velocity.x == 0.0f and m_velocity.y == 0.0f and m_velocity.z == 0.0f)
        return;

    translate(m_velocity * (float)delta);
    m_velocity -= m_velocity * ((float)delta * m_weight);
    if (glm::length(m_velocity) <= 0.001f)
        m_velocity = glm::vec3(0.0f);
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
