#include "jage/script/actor/healthscript.hpp"

#include <iostream>

#include "jage/script/actor/collisionlistenerscript.hpp"

using jage::script::actor::HealthScript;

HealthScript::HealthScript(abc::ScriptableABC* node, float maxHealth)
    : m_maxHealth(maxHealth)
    , m_health(maxHealth)
{
    validate(node);
    m_collider = dependsOn<CollisionListenerScript>();
}

void HealthScript::onAttach() {
    m_collider->onCollide += shared_from_this();
}

void HealthScript::onSpawn() {

}

void HealthScript::onUpdate() {

}

void HealthScript::onDeath() {

}

void jage::script::actor::HealthScript::damage(float amount) {
    m_health -= amount;
    std::cout << m_node->getName() << " " << m_health << "/" << m_maxHealth << "HP" << std::endl;
    onDamage.notifyAll(amount, m_health, m_maxHealth);
}

void HealthScript::notify(jage::node::actor::StaticActor* notifier) {
    damage(1.0f);
}
