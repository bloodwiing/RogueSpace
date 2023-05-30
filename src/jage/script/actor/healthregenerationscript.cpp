#include "jage/script/actor/healthregenerationscript.hpp"

#include "jage/runtime/time.hpp"

using jage::script::actor::HealthRegenerationScript;
using jage::runtime::Time;

HealthRegenerationScript::HealthRegenerationScript(abc::ScriptableABC* node, float damageDelay, float rate)
        : m_damageDelay(damageDelay)
        , m_rate(rate)
{
    validate(node);
    m_healthScript = dependsOn<HealthScript>();
}

void HealthRegenerationScript::onAttach() {

}

void HealthRegenerationScript::onSpawn() {

}

void HealthRegenerationScript::onUpdate() {
    if (m_time > 0) {
        m_time -= Time::getDeltaFloat();
        return;
    }

    m_healthScript.lock()->heal(m_rate * Time::getDeltaFloat());
}

void HealthRegenerationScript::onDeath() {

}

void HealthRegenerationScript::notify(node::actor::DynamicActor* source, const float& delta, const float& current, const float& max) {
    m_time = m_damageDelay;
}
