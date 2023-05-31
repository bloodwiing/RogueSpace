#ifndef JAGE_OPACITY_SCORE_FLASH_SCRIPT_HPP
#define JAGE_OPACITY_SCORE_FLASH_SCRIPT_HPP

#include "jage/script/frame/opacityflashscript.hpp"
#include "jage/event/scoreupdateevent.hpp"

namespace jage::script::frame {

    class OpacityScoreFlashScript
            : public OpacityFlashScript
            , public jage::event::ScoreUpdateEvent
    {
    public:
        OpacityScoreFlashScript(abc::ScriptableABC* node, float duration, float maxValue);

        void notify(long score) override;
    };
}

#endif //JAGE_OPACITY_SCORE_FLASH_SCRIPT_HPP
