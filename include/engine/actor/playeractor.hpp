#ifndef PLAYER_ACTOR_CLASS_H
#define PLAYER_ACTOR_CLASS_H

#include "physicsactor.hpp"

class PlayerActor : public PhysicsActor {
public:
    PlayerActor(Scene *scene, ActorBase *parent, std::string name);

    void update() override;

protected:
    [[nodiscard]] std::string getTypeName() const override;

private:
    glm::vec3 m_orientation = glm::vec3(0.0f, 0.0f, -1.0f),
              m_up = glm::vec3(0.0f, 1.0f, 0.0f);

    float m_linearSpeed = 3.0f,
          m_angularSpeed = 0.05f,
          m_sensitivity = 100.0f;

    static const float mass;
    static const float drag;

    bool m_clicked = false;

    float m_fireCoolDown = 0.0f;
};

#endif //PLAYER_ACTOR_CLASS_H
