#include "jage/script/frame/opacitylowhpperiodicflashscript.hpp"

using jage::script::frame::OpacityLowHPPeriodicFlashScript;

OpacityLowHPPeriodicFlashScript::OpacityLowHPPeriodicFlashScript(abc::ScriptableABC* node, float duration, float maxValue, float minValue, float healthReq)
        : OpacityFlashScript(node, duration, maxValue, minValue, 1.0f)
        , m_healthReq(healthReq)
{

}

void OpacityLowHPPeriodicFlashScript::onUpdate() {
    if (m_active and m_timer <= 0.0f) {
        resetTimer();
    } else if (!m_active) {
        m_timer = -1.0;
        m_node->setOpacity(0.0f);
    }

    OpacityFlashScript::onUpdate();
}

void OpacityLowHPPeriodicFlashScript::notify(const float& delta, const float& current, const float& max) {
    m_active = current / max <= m_healthReq;
}

void OpacityLowHPPeriodicFlashScript::notify(jage::node::actor::DynamicActor* source, const float& delta, const float& current, const float& max) {
    m_active = current / max <= m_healthReq;
}
