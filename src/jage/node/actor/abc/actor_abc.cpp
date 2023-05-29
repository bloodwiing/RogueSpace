#include "jage/node/actor/abc/actor_abc.hpp"

#include <iostream>

#include "jage/node/scene.hpp"

using jage::node::actor::abc::ActorABC;

std::string ActorABC::getTypeName() const {
    return "ActorABC (ABSTRACT BASE CLASS)";
}

ActorABC::ActorABC(JAGE_ACTOR_ARGS)
        : node::abc::NodeABC<ActorABC>(parent, std::move(name))
        , m_scene(scene)
        , m_tag(tag)
        , m_volatile(isVolatile)
{

}

jage::node::Scene* ActorABC::getScene() const {
    return m_scene;
}

jage::Tag ActorABC::getTag() const {
    return m_tag;
}

bool ActorABC::isVolatile() const {
    return m_volatile;
}

void ActorABC::setTag(jage::Tag tag) {
    m_tag = tag;
}

void ActorABC::update() {
    DyingBase::updateDeathTimer();
    script::abc::ScriptableABC::update();
    NodeABC::update();
}

void ActorABC::spawn() {
    m_scene->tagActorToMap(shared_from_this());
}

void ActorABC::kill() {
    DyingBase::kill();
}

void ActorABC::kill(float delay) {
    DyingBase::kill(delay);
}

bool ActorABC::isDead() const {
    return DyingBase::isDead();
}
