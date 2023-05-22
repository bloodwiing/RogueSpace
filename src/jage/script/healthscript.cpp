#include "jage/script/healthscript.hpp"

#include <iostream>

#include "jage/script/collisionreceiverscript.hpp"

using jage::script::HealthScript;

HealthScript::HealthScript(abc::ScriptableABC* node, float maxHealth)
    : m_maxHealth(maxHealth)
    , m_health(maxHealth)
{
    validate(node);
    m_collider = dependsOn<CollisionReceiverScript>();
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

void HealthScript::notify(jage::node::actor::StaticActor* notifier) {
    m_health -= 1.0f;
    std::cout << m_node->getName() << " " << m_health << "/" << m_maxHealth << "HP" << std::endl;
}
