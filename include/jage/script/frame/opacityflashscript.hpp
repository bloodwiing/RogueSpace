#ifndef JAGE_OPACITY_FLASH_SCRIPT_HPP
#define JAGE_OPACITY_FLASH_SCRIPT_HPP

#include "jage/script/abc/script_abc.hpp"
#include "jage/node/frame/spriteframe.hpp"

namespace jage::script::frame {

    class OpacityFlashScript : public abc::AttachableScriptABC<jage::node::frame::SpriteFrame> {
    public:
        OpacityFlashScript(abc::ScriptableABC* node, float duration, float maxValue, float minValue = 0.0f, float pow = 3.0f);

        void onAttach() override;
        void onSpawn() override;
        void onUpdate() override;
        void onDeath() override;

        void resetTimer();

    protected:
        float m_timer = -1.0f;

    private:
        float m_duration;
        float m_maxValue;
        float m_minValue;
        float m_pow;
    };
}

#endif //JAGE_OPACITY_FLASH_SCRIPT_HPP
