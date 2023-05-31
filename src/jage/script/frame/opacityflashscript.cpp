#include "jage/script/frame/opacityflashscript.hpp"

#include "jage/runtime/time.hpp"

using jage::script::frame::OpacityFlashScript;

OpacityFlashScript::OpacityFlashScript(jage::script::abc::ScriptableABC* node, float duration, float maxValue, float minValue /* = 0.0f */, float pow /* = 3.0f */)
        : m_duration(duration)
        , m_maxValue(maxValue)
        , m_minValue(minValue)
        , m_pow(pow)
{
    validate(node);
}

void OpacityFlashScript::onAttach() {

}

void OpacityFlashScript::onSpawn() {

}

void OpacityFlashScript::onUpdate() {
    using jage::runtime::Time;

    if (m_timer < 0.0f)
        return;

    m_timer -= Time::getDeltaFloat();

    m_node->setOpacity(std::pow(m_timer / m_duration, m_pow) * (m_maxValue - m_minValue) + m_minValue);
}

void OpacityFlashScript::onDeath() {

}

void OpacityFlashScript::resetTimer() {
    m_timer = m_duration;
}
