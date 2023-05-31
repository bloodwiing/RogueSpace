#include "jage/script/frame/opacitydamageflashscript.hpp"

using jage::script::frame::OpacityDamageFlashScript;

OpacityDamageFlashScript::OpacityDamageFlashScript(jage::script::abc::ScriptableABC* node, float duration, float maxValue)
        : OpacityFlashScript(node, duration, maxValue)
{

}

void OpacityDamageFlashScript::notify(node::actor::DynamicActor* source, const float& delta, const float& current, const float& max) {
    resetTimer();
}
