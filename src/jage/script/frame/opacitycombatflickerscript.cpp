#include "jage/script/frame/opacitycombatflickerscript.hpp"
#include "jage/runtime/time.hpp"

using jage::script::frame::OpacityCombatFlickerScript;
using jage::runtime::Time;

OpacityCombatFlickerScript::OpacityCombatFlickerScript(abc::ScriptableABC *node, float state1, float state2, float period, float duration)
        : OpacityFlickerScript(node, state1, state2, period)
        , m_duration(duration)
{

}

void OpacityCombatFlickerScript::onUpdate() {
    if (m_time <= 0.0f) {
        setActive(false);
        return;
    }

    setActive(true);
    m_time -= Time::getDeltaFloat();

    OpacityFlickerScript::onUpdate();
}

void OpacityCombatFlickerScript::notify(node::actor::DynamicActor* source, const float& delta, const float& current, const float& max) {
    m_time = m_duration;
}
