#ifndef JAGE_OPACITY_FLICKER_SCRIPT_HPP
#define JAGE_OPACITY_FLICKER_SCRIPT_HPP

#include "jage/script/abc/script_abc.hpp"
#include "jage/node/frame/spriteframe.hpp"

namespace jage::script::frame {

    class OpacityFlickerScript
            : public abc::AttachableScriptABC<node::frame::SpriteFrame>
    {
    public:
        OpacityFlickerScript(abc::ScriptableABC* node, float state1, float state2, float period);

        void onAttach() override;
        void onSpawn() override;
        void onUpdate() override;
        void onDeath() override;

        void setActive(bool active);

    private:
        float m_state1;
        float m_state2;
        float m_period;

        bool m_active = false;
    };
}

#endif //JAGE_OPACITY_FLICKER_SCRIPT_HPP
