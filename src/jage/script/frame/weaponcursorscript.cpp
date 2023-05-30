#include "jage/script/frame/weaponcursorscript.hpp"

#include "jage/runtime/time.hpp"

using jage::script::frame::WeaponCursorScript;
using jage::runtime::Time;

WeaponCursorScript::WeaponCursorScript(abc::ScriptableABC *node, float add, float duration)
        : m_add(add)
        , m_duration(duration)
{
    validate(node);
}

void WeaponCursorScript::onAttach() {

}

void WeaponCursorScript::onSpawn() {

}

void WeaponCursorScript::onUpdate() {
    if (m_time <= 0)
        return;

    m_time -= Time::getDeltaFloat();

    m_node->setOpacity(m_node->getMultiply().a * (1.0f + (m_time / m_duration) * m_add));
}

void WeaponCursorScript::onDeath() {

}

void WeaponCursorScript::notify() {
    m_time = m_duration;
}
