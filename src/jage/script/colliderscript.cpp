#include "jage/script/colliderscript.hpp"

#include "jage/script/collisionreceiverscript.hpp"

using jage::script::ColliderScript;

ColliderScript::ColliderScript(jage::actor::abc::ActorABC *node, jage::Tag tagFilter, float radius)
    : m_tagFilter(tagFilter)
    , m_radius(radius)
{
    validate(node);
}

void ColliderScript::onAttach() {

}

void ColliderScript::onSpawn() {

}

void ColliderScript::onUpdate() {
    actor::Scene& scene = *m_node->getScene();
    for (auto iter = scene.beginTagged(m_tagFilter); iter != scene.endTagged(m_tagFilter); ++iter) {
        auto* target = iter->findScript<CollisionReceiverScript>();

        if (target != nullptr and (target->getRadius() + getRadius()) >= glm::distance(iter->getWorldPosition(), m_node->getWorldPosition())) {
            target->onCollide(m_node);
            m_node->markDead();
        }
    }
}

void ColliderScript::onDeath() {

}

jage::Tag ColliderScript::getTagFilter() const {
    return m_tagFilter;
}

void ColliderScript::setTagFilter(jage::Tag tag) {
    m_tagFilter = tag;
}

float ColliderScript::getRadius() const {
    return m_radius;
}

void ColliderScript::setRadius(float radius) {
    m_radius = radius;
}
