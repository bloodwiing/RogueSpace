#ifndef JAGE_SHIP_ACTOR_HPP
#define JAGE_SHIP_ACTOR_HPP

#include "jage/node/actor/physicsactor.hpp"
#include "jage/node/actor/abc/actor_abc.hpp"

namespace jage::node::actor {

    class ShipActor : public PhysicsActor {
    public:
        ShipActor(JAGE_ACTOR_ARGS);

        void update() override;

        void setThrottle(float throttle);
        void setRoll(float roll);
        void setSteer(glm::vec3 euler);

        [[nodiscard]] float getThrottle() const;
        [[nodiscard]] glm::vec3 getThrottleVelocity() const;

        void throttleForward();
        void throttleBackward();
        void throttleReset();

        [[nodiscard]] float getMaxForwardSpeed() const;
        [[nodiscard]] float getMaxBackwardSpeed() const;

        void rollClockwise();
        void rollCounterClockwise();
        void rollReset();

        [[nodiscard]] float getMaxRollSpeed() const;

    protected:
        [[nodiscard]] std::string getTypeName() const override;

    private:
        const float m_maxForwardSpeed = 30.0f;
        const float m_maxBackwardSpeed = 15.5f;
        const float m_maxRollSpeed = 3.5f;

        const float m_throttleEasing = 0.3f;
        const float m_rollEasing = 3.0f;

        const float m_stoppingMultiplier = 2.0f;

        const float m_steerResistance = 1.0f / m_maxForwardSpeed * 0.7f;

        static float weight;
        static float drag;

        float m_targetThrottle = 0.0f;
        float m_targetRoll = 0.0f;

        float m_throttle = 0.0f;
        float m_roll = 0.0f;

        glm::vec3 m_steer = glm::vec3(0.0f);
    };
}

#endif //JAGE_SHIP_ACTOR_HPP
