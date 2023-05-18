#include "jage/script/collisionreceiverscript.hpp"

using jage::script::CollisionReceiverScript;

CollisionReceiverScript::CollisionReceiverScript(jage::node::actor::abc::ActorABC* node, float radius)
    : m_radius(radius)
{
    validate(node);
}

void CollisionReceiverScript::onAttach() {

}

void CollisionReceiverScript::onSpawn() {

}

void CollisionReceiverScript::onUpdate() {

}

void CollisionReceiverScript::onDeath() {

}

float CollisionReceiverScript::getRadius() const {
    return m_radius;
}

void CollisionReceiverScript::runCollision(jage::node::actor::DynamicActor*& other) {
    onCollide.notifyAll(other);
}

void CollisionReceiverScript::setRadius(float radius) {
    m_radius = radius;
}
