#ifndef JAGE_HEALTH_REGENERATION_SCRIPT_HPP
#define JAGE_HEALTH_REGENERATION_SCRIPT_HPP

#include "jage/script/abc/script_abc.hpp"
#include "jage/node/actor/dynamicactor.hpp"
#include "jage/event/damageevent.hpp"
#include "jage/script/actor/healthscript.hpp"

namespace jage::script::actor {

    class HealthRegenerationScript
            : public abc::AttachableScriptABC<node::actor::DynamicActor>
            , public event::DamageEvent
    {
    public:
        HealthRegenerationScript(abc::ScriptableABC* node, float damageDelay, float rate);

        void onAttach() override;
        void onSpawn() override;
        void onUpdate() override;
        void onDeath() override;

        void notify(node::actor::DynamicActor* source, const float& delta, const float& current, const float& max) override;

    private:
        float m_damageDelay;
        float m_rate;

        float m_time = 0.0f;

        std::weak_ptr<HealthScript> m_healthScript;
    };
}

#endif //JAGE_HEALTH_REGENERATION_SCRIPT_HPP
