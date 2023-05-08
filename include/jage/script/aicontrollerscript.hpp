#ifndef JAGE_AI_CONTROLLER_SCRIPT_HPP
#define JAGE_AI_CONTROLLER_SCRIPT_HPP

#include "jage/actor/shipactor.hpp"
#include "jage/script/abc/script_abc.hpp"

namespace jage::script {

    class AIControllerScript : public abc::ScriptABC {
    public:
        typedef jage::actor::ShipActor RequiredNodeType;

        explicit AIControllerScript(jage::actor::abc::ActorABC *node);

        void onAttach() override;
        void onSpawn() override;
        void onUpdate() override;
        void onDeath() override;

        void setTarget(jage::actor::ShipActor* target);

    private:
        RequiredNodeType* m_node;

        float m_sensitivity = 2.5f;

        float m_fireCoolDown = 0.0f;
        bool m_fireFromLeft = true;

        jage::actor::ShipActor* m_target = nullptr;
    };
}

#endif //JAGE_AI_CONTROLLER_SCRIPT_HPP
