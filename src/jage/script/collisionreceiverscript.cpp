#include "jage/script/collisionreceiverscript.hpp"

#include <iostream>

using jage::script::CollisionReceiverScript;

CollisionReceiverScript::CollisionReceiverScript(jage::actor::abc::ActorABC* node, float radius)
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

void CollisionReceiverScript::onCollide(jage::actor::DynamicActor *&other) {
    std::cout << "Hit to " << m_node->getName() << " by " << other->getName() << std::endl;
}

void CollisionReceiverScript::setRadius(float radius) {
    m_radius = radius;
}
