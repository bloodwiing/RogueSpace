#ifndef PHYSICS_ACTOR_CLASS_H
#define PHYSICS_ACTOR_CLASS_H

#include <glm/glm.hpp>

#include "actor.h"

class PhysicsActor : public Actor {
public:
    void update(GLFWwindow *window, double delta) override;

    void setWeight(float weight);
    void setVelocity(glm::vec3 velocity);

protected:
    float m_weight;
    glm::vec3 m_velocity;
};

#endif //PHYSICS_ACTOR_CLASS_H
