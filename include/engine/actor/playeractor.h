#ifndef PLAYER_ACTOR_CLASS_H
#define PLAYER_ACTOR_CLASS_H

#include "physicsactor.h"

class PlayerActor : public PhysicsActor {
public:
    PlayerActor(Scene *scene, ActorBase *parent, std::string name);

    void update() override;

protected:
    [[nodiscard]] std::string getTypeName() const override;

private:
    glm::vec3 m_orientation = glm::vec3(0.0f, 0.0f, -1.0f),
              m_up = glm::vec3(0.0f, 1.0f, 0.0f);

    float m_speed = 3.0f,
          m_sensitivity = 100.0f;

    bool m_clicked = false;
};

#endif //PLAYER_ACTOR_CLASS_H
