#ifndef JAGE_OPACITY_COMBAT_FLICKER_SCRIPT_HPP
#define JAGE_OPACITY_COMBAT_FLICKER_SCRIPT_HPP

#include "jage/script/frame/opacityflickerscript.hpp"
#include "jage/event/damageevent.hpp"

namespace jage::script::frame {

    class OpacityCombatFlickerScript
            : public OpacityFlickerScript
            , public event::DamageEvent
    {
    public:
        OpacityCombatFlickerScript(abc::ScriptableABC* node, float state1, float state2, float period, float duration);

        void onUpdate() override;

        void notify(node::actor::DynamicActor* source, const float& delta, const float& current, const float& max) override;

    private:
        float m_duration = 0.0f;

        float m_time = 0.0f;
    };
}

#endif //JAGE_OPACITY_COMBAT_FLICKER_SCRIPT_HPP
