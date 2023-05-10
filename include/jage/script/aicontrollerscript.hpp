#ifndef JAGE_AI_CONTROLLER_SCRIPT_HPP
#define JAGE_AI_CONTROLLER_SCRIPT_HPP

#include <random>

#include "jage/actor/shipactor.hpp"
#include "jage/script/abc/script_abc.hpp"
#include "jage/script/weaponscript.hpp"

namespace jage::script {

    class AIControllerScript : public abc::AttachableScriptABC<jage::actor::ShipActor> {
    public:
        explicit AIControllerScript(jage::actor::abc::ActorABC *node);

        void onAttach() override;
        void onSpawn() override;
        void onUpdate() override;
        void onDeath() override;

        void setTarget(jage::actor::ShipActor* target);

    private:
        const float m_sensitivity = 2.5f;
        const float m_maxTurnRate = 0.9f * m_sensitivity;
        const float m_minTurnRate = 0.6f * m_sensitivity;

        glm::vec3 m_fleeVector = glm::vec3(0.0);
        const float m_avoidEaseMultiplier = 0.3f;

        bool m_fleeing = false;
        bool m_seeking = false;

        static std::mt19937 random;

        float m_seekCoolDown = -1.0f;
        std::uniform_real_distribution<float> m_seekApplyCoolDown = std::uniform_real_distribution<float>(2.0f, 5.0f);
        float m_orbitAngle = 0.0f;
        std::uniform_real_distribution<float> m_orbitApplyAngle = std::uniform_real_distribution<float>(-glm::pi<float>(), glm::pi<float>());

        const float m_seekAngleBegin = 0.2f;
        const float m_seekAngleEnd = 0.5f;

        const float m_seekDistance = 30.0f;
        const float m_attackDistance = 100.0f;
        const float m_fleeDistance = 8.0f;

        float m_vectorChangeEase = 1.0f;

        WeaponScript* m_weaponScript;

        jage::actor::ShipActor* m_target = nullptr;
    };
}

#endif //JAGE_AI_CONTROLLER_SCRIPT_HPP
