#include "jage/script/frame/opacityflickerscript.hpp"

#include "jage/runtime/time.hpp"

using jage::script::frame::OpacityFlickerScript;
using jage::runtime::Time;

OpacityFlickerScript::OpacityFlickerScript(abc::ScriptableABC* node, float state1, float state2, float period)
        : m_state1(state1)
        , m_state2(state2)
        , m_period(period)
{
    validate(node);
}

void OpacityFlickerScript::onAttach() {

}

void OpacityFlickerScript::onSpawn() {

}

void OpacityFlickerScript::onUpdate() {
    if (!m_active)
        return;

    if ((long)std::floor(Time::getFrameTime().count() / m_period) % 2 == 0) {
        m_node->setOpacity(m_state1);
    } else {
        m_node->setOpacity(m_state2);
    }
}

void OpacityFlickerScript::onDeath() {

}

void OpacityFlickerScript::setActive(bool active) {
    m_active = active;
    if (!active)
        m_node->setOpacity(0.0f);
}
