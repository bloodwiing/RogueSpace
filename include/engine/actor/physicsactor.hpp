#ifndef PHYSICS_ACTOR_CLASS_H
#define PHYSICS_ACTOR_CLASS_H

#include <glm/glm.hpp>

#include "./dynamicactor.hpp"

class PhysicsActor : public DynamicActor {
public:
    PhysicsActor(Scene* scene, ActorBase* parent, std::string name, float weight, float drag);

    void update() override;

    [[nodiscard]] float getWeight() const;
    [[nodiscard]] float getDrag() const;
    [[nodiscard]] glm::vec3 getLinearVelocity() const;
    [[nodiscard]] glm::vec3 getAngularVelocity() const;

    void setWeight(float weight);
    void setDrag(float drag);
    void setLinearVelocity(const glm::vec3& linear);
    void setAngularVelocity(const glm::vec3& angular);

    void addForce(glm::vec3 force);
    void addTorque(glm::vec3 torque);

    [[nodiscard]] static inline bool isVectorZero(const glm::vec3& vector);

protected:
    [[nodiscard]] std::string getTypeName() const override;

    float m_weight;
    float m_drag;

    glm::vec3 m_linearVelocity;
    glm::vec3 m_angularVelocity;
};

#endif //PHYSICS_ACTOR_CLASS_H
