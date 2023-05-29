#ifndef JAGE_AI_CONTROLLER_SCRIPT_HPP
#define JAGE_AI_CONTROLLER_SCRIPT_HPP

#include <random>

#include "jage/node/actor/shipactor.hpp"
#include "jage/script/abc/script_abc.hpp"
#include "jage/script/actor/weaponscript.hpp"

namespace jage::script::actor {

    class AIControllerScript : public abc::AttachableScriptABC<jage::node::actor::ShipActor> {
    public:
        explicit AIControllerScript(abc::ScriptableABC* node);

        void onAttach() override;
        void onSpawn() override;
        void onUpdate() override;
        void onDeath() override;

        void setTarget(jage::node::actor::ShipActor* target);

    protected:
        void runSearch(const glm::vec3& predicted, float distance);
        void runSeek(const glm::vec3& predicted, float distance);
        void runFlee(const glm::vec3& predicted, float distance);
        void runOrbit(const glm::vec3& predicted, float distance);

        float getTargetDistance(const glm::vec3& target);
        glm::vec3 predictTargetPosition(const glm::vec3& target, float distance);

        void slowDown();
        void turnToVector(const glm::vec3& prevVector, glm::vec3 vector, float& angleDifference);

        void resetEasing();
        glm::vec3 easeBetweenVectors(const glm::vec3& a, const glm::vec3& b);

    private:
        enum State {
            SEARCHING,
            SEEKING,
            FLEEING,
            ORBITING
        };

        State m_state;

        static std::mt19937 random;

        // Control
        const float m_sensitivity = 2.5f;
        const float m_maxTurnRate = 0.9f * m_sensitivity;
        const float m_minTurnRate = 0.6f * m_sensitivity;

        // Seeking
        const float m_seekAngleBegin = 0.2f;
        const float m_seekAngleEnd = 0.5f;

        // Fleeing
        glm::vec3 m_fleeVector = glm::vec3(0.0);

        // Orbiting
        float m_orbitDuration = -1.0f;
        std::uniform_real_distribution<float> m_orbitApplyDuration = std::uniform_real_distribution<float>(2.0f, 5.0f);
        float m_orbitAngle = 0.0f;
        std::uniform_real_distribution<float> m_orbitApplyAngle = std::uniform_real_distribution<float>(-glm::pi<float>(), glm::pi<float>());
        glm::vec3 m_orbitVector = glm::vec3(0.0f, 0.0f, 0.0f);

        // Distances to change mode
        const float m_seekDistance = 30.0f;
        const float m_attackDistance = 100.0f;
        const float m_fleeDistance = 8.0f;

        // Easing
        float m_vectorChangeEase = 1.0f;
        const float m_easeMultiplier = 0.3f;

        jage::node::actor::ShipActor* m_target = nullptr;

        WeaponScript* m_weaponScript;
    };
}

#endif //JAGE_AI_CONTROLLER_SCRIPT_HPP
