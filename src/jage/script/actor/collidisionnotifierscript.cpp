#include "jage/script/actor/collidisionnotifierscript.hpp"

#include "jage/script/actor/collisionlistenerscript.hpp"

using jage::script::actor::CollisionNotifierScript;

CollisionNotifierScript::CollisionNotifierScript(abc::ScriptableABC* node, jage::Tag tagFilter, float radius)
    : m_tagFilter(tagFilter)
    , m_radius(radius)
{
    validate(node);
}

void CollisionNotifierScript::onAttach() {

}

void CollisionNotifierScript::onSpawn() {

}

void CollisionNotifierScript::onUpdate() {
    node::Scene& scene = *m_node->getScene();
    for (auto iter = scene.beginTagged(m_tagFilter); iter != scene.endTagged(m_tagFilter); ++iter) {
        auto* target = iter->findScript<CollisionListenerScript>();

        if (target != nullptr and (target->getRadius() + getRadius()) >= glm::distance(iter->getWorldPosition(), m_node->getWorldPosition())) {
            target->runCollision(m_node);
            m_node->kill();
        }
    }
}

void CollisionNotifierScript::onDeath() {

}

jage::Tag CollisionNotifierScript::getTagFilter() const {
    return m_tagFilter;
}

void CollisionNotifierScript::setTagFilter(jage::Tag tag) {
    m_tagFilter = tag;
}

float CollisionNotifierScript::getRadius() const {
    return m_radius;
}

void CollisionNotifierScript::setRadius(float radius) {
    m_radius = radius;
}
