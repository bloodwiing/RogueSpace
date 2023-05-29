#include "jage/script/frame/opacitydamageflashscript.hpp"

using jage::script::frame::OpacityDamageFlashScript;

OpacityDamageFlashScript::OpacityDamageFlashScript(jage::script::abc::ScriptableABC* node, float duration)
        : OpacityFlashScript(node, duration)
{

}

void OpacityDamageFlashScript::notify(const float& delta, const float& current, const float& max) {
    resetTimer();
}
