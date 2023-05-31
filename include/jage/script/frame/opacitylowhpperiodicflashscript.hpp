#ifndef JAGE_OPACITY_LOW_HP_PERIODIC_FLASH_SCRIPT_HPP
#define JAGE_OPACITY_LOW_HP_PERIODIC_FLASH_SCRIPT_HPP

#include "jage/script/frame/opacityflashscript.hpp"
#include "jage/event/damageevent.hpp"
#include "jage/event/healevent.hpp"

namespace jage::script::frame {

    class OpacityLowHPPeriodicFlashScript
            : public OpacityFlashScript
            , public event::DamageEvent
            , public event::HealEvent
    {
    public:
        OpacityLowHPPeriodicFlashScript(abc::ScriptableABC* node, float duration, float maxValue, float minValue, float healthReq);

        void onUpdate() override;

        void notify(const float& delta, const float& current, const float& max) override;
        void notify(node::actor::DynamicActor* source, const float& delta, const float& current, const float& max) override;

    private:
        float m_healthReq;

        bool m_active = false;
    };
}

#endif //JAGE_OPACITY_LOW_HP_PERIODIC_FLASH_SCRIPT_HPP
