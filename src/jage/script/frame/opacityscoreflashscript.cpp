#include "jage/script/frame/opacityscoreflashscript.hpp"

using jage::script::frame::OpacityScoreFlashScript;

OpacityScoreFlashScript::OpacityScoreFlashScript(jage::script::abc::ScriptableABC* node, float duration, float maxValue)
        : OpacityFlashScript(node, duration, maxValue)
{

}

void OpacityScoreFlashScript::notify(long score) {
    resetTimer();
}
