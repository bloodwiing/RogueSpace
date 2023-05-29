#include "jage/script/frame/opacityflashscript.hpp"

#include "jage/runtime/time.hpp"

using jage::script::frame::OpacityFlashScript;

OpacityFlashScript::OpacityFlashScript(jage::script::abc::ScriptableABC* node, float duration)
        : m_duration(duration)
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

    m_node->setOpacity(m_timer / m_duration);
}

void OpacityFlashScript::onDeath() {

}

void OpacityFlashScript::resetTimer() {
    m_timer = m_duration;
}
