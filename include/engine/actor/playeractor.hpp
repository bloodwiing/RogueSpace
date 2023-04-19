#ifndef PLAYER_ACTOR_CLASS_H
#define PLAYER_ACTOR_CLASS_H

#include "physicsactor.hpp"

/// \brief          A Keyboard and Mouse controlled subclass of PhysicsActor.
/// \details        This actor reacts to Keyboard and Mouse input and applies force and torque to itself based
///                 on input events
class PlayerActor : public PhysicsActor {
public:
    /// \note           Should not be used raw, please use addChild
    /// \param scene    Containing Scene of the Actor node
    /// \param parent   Parent of the Actor node
    /// \param name     Name of the Actor node
    /// \see            Scene#addChild
    /// \see            Actor#addChild
    PlayerActor(Scene *scene, ActorBase *parent, std::string name);

    void update() override;

protected:
    [[nodiscard]] std::string getTypeName() const override;

private:
    /// The orientation vector where the PlayerActor is currently looking at
    glm::vec3 m_orientation = glm::vec3(0.0f, 0.0f, -1.0f),
    /// The vector pointing upwards from the Actor's perspective
              m_up = glm::vec3(0.0f, 1.0f, 0.0f);

    /// The speed multiplier for applying movement Force
    float m_linearSpeed = 3.0f,
    /// The speed multiplier for applying rotational Torque
          m_angularSpeed = 0.05f,
    /// The speed multiplier for rotating the Actor around based on mouse delta
          m_sensitivity = 100.0f;

    /// A pre-set value for the Mass of the PhysicsActor for PlayerActor
    static const float mass;
    /// A pre-set value for the Drag of the PhysicsActor for PlayerActor
    static const float drag;

    /// A flag for if the mouse is being captured and hidden
    bool m_clicked = false;

    /// Cool down timer before spawning another Bullet Actor
    float m_fireCoolDown = 0.0f;
};

#endif //PLAYER_ACTOR_CLASS_H
