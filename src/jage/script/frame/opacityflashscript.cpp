#include "jage/script/frame/opacityflashscript.hpp"

#include "jage/runtime/time.hpp"

using jage::script::frame::OpacityFlashScript;

OpacityFlashScript::OpacityFlashScript(jage::script::abc::ScriptableABC* node, float duration, float maxValue)
        : m_duration(duration)
        , m_maxValue(maxValue)
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

    m_node->setOpacity(std::pow(m_timer / m_duration, 3.0f) * m_maxValue);
}

void OpacityFlashScript::onDeath() {

}

void OpacityFlashScript::resetTimer() {
    m_timer = m_duration;
}
