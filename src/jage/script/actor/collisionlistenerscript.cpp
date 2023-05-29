#include "jage/script/actor/collisionlistenerscript.hpp"

using jage::script::actor::CollisionListenerScript;

CollisionListenerScript::CollisionListenerScript(abc::ScriptableABC* node, float radius)
    : m_radius(radius)
{
    validate(node);
}

void CollisionListenerScript::onAttach() {

}

void CollisionListenerScript::onSpawn() {

}

void CollisionListenerScript::onUpdate() {

}

void CollisionListenerScript::onDeath() {

}

float CollisionListenerScript::getRadius() const {
    return m_radius;
}

void CollisionListenerScript::runCollision(jage::node::actor::DynamicActor*& other) {
    onCollide.notifyAll(other);
}

void CollisionListenerScript::setRadius(float radius) {
    m_radius = radius;
}
