#ifndef PHYSICS_ACTOR_CLASS_H
#define PHYSICS_ACTOR_CLASS_H

#include <glm/glm.hpp>

#include "./dynamicactor.h"

class PhysicsActor : public DynamicActor {
public:
    PhysicsActor(Scene* scene, ActorBase* parent, float weight);

    void update() override;

    [[nodiscard]] float getWeight() const;
    [[nodiscard]] glm::vec3 getVelocity() const;

    void setWeight(float weight);
    void setVelocity(const glm::vec3& velocity);

protected:
    float m_weight;
    glm::vec3 m_velocity;
};

#endif //PHYSICS_ACTOR_CLASS_H
