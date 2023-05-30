#include "jage/script/frame/notificationkillscript.hpp"

#include "jage/runtime/time.hpp"

using jage::script::frame::NotificationKillScript;
using jage::runtime::Time;

NotificationKillScript::NotificationKillScript(abc::ScriptableABC* node, float appearTime, float stayTime, float removeTime)
        : m_appearTime(appearTime)
        , m_stayTime(stayTime)
        , m_removeTime(removeTime)
{
    validate(node);
}

void NotificationKillScript::onAttach() {

}

void NotificationKillScript::onSpawn() {

}

void NotificationKillScript::onUpdate() {
    if (m_count <= 0)
        return;

    m_time += Time::getDeltaFloat();

    if (m_time <= m_appearTime) {
        float value = 1.0f - std::pow(1.0f - m_time / m_appearTime, 3.0f);

        m_node->setScale(glm::vec2(1 / value, value));
        m_node->setOpacity(1.0f);
        m_node->setAdd(1.0f - value, 1.0f - value, 1.0f - value);

    } else if (m_time <= m_stayTime) {
        m_node->setScale(glm::vec2(1.0f));
        m_node->setAdd(0.0f, 0.0f, 0.0f);

    } else if (m_time <= m_removeTime) {
        float value = 1.0f - std::pow((m_time - m_stayTime) / (m_removeTime - m_stayTime), 3.0f);

        m_node->setOpacity(value);

    } else {
        --m_count;
        m_time = 0.0f;
        m_node->setOpacity(0.0f);
    }
}

void NotificationKillScript::onDeath() {

}

void NotificationKillScript::notify(node::actor::DynamicActor* source) {
    ++m_count;
}
