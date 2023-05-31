#ifndef JAGE_OPACITY_DAMAGE_FLASH_SCRIPT_HPP
#define JAGE_OPACITY_DAMAGE_FLASH_SCRIPT_HPP

#include "jage/script/frame/opacityflashscript.hpp"
#include "jage/event/damageevent.hpp"

namespace jage::script::frame {

    class OpacityDamageFlashScript
            : public OpacityFlashScript
            , public jage::event::DamageEvent
    {
    public:
        OpacityDamageFlashScript(abc::ScriptableABC* node, float duration, float maxValue);

        void notify(node::actor::DynamicActor* source, const float& delta, const float& current, const float& max) override;
    };
}

#endif //JAGE_OPACITY_DAMAGE_FLASH_SCRIPT_HPP
