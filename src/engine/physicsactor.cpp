#include "engine/physicsactor.h"

void PhysicsActor::update(GLFWwindow *window, double delta) {
    if (m_velocity.x == 0.0f and m_velocity.y == 0.0f and m_velocity.z == 0)
        return;

    m_position += m_velocity * (float)delta;
    m_velocity -= m_velocity * ((float)delta * m_weight);
    if (glm::length(m_velocity) <= 0.001f)
        m_velocity = glm::vec3(0.0f, 0.0f, 0.0f);
}

void PhysicsActor::setWeight(float weight) {
    m_weight = weight;
}

void PhysicsActor::setVelocity(glm::vec3 velocity) {
    m_velocity = velocity;
}
