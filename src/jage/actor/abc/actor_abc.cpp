#include "jage/actor/abc/actor_abc.hpp"

#include <iostream>

#include "jage/actor/scene.hpp"

using jage::actor::abc::ActorABC;

std::string ActorABC::getTypeName() const {
    return "ActorABC (ABSTRACT BASE CLASS)";
}

ActorABC::ActorABC(JAGE_ACTOR_ARGS)
    : node::abc::NodeABC<ActorABC>(parent, std::move(name))
    , m_tag(tag)
    , m_volatile(isVolatile)
{

}

void ActorABC::tagToScene(Scene *scene) {
    if (scene != nullptr)
        scene->tagActorToMap(shared_from_this());
}

std::map<std::string, ActorABC::ChildEntry> ActorABC::getChildren() const {
    return m_children;
}

ActorABC* ActorABC::getChild(const std::string &name) const {
    if (m_children.find(name) == m_children.end())
        return nullptr;
    return m_children.at(name).value.get();
}

ActorABC* ActorABC::getParent() const {
    return m_parent;
}

std::string ActorABC::getName() const {
    return m_name;
}

jage::Tag ActorABC::getTag() const {
    return m_tag;
}

bool jage::actor::abc::ActorABC::isVolatile() const {
    return m_volatile;
}

glm::mat4 ActorABC::getWorldMatrix() const {
    return glm::mat4(1.0f);
}

bool ActorABC::isDead() const {
    return false;
}

void ActorABC::setTag(jage::Tag tag) {
    m_tag = tag;
}

std::ostream& operator<<(std::ostream& stream, ActorABC *actor) {
    stream << actor->toHierarchyString();
    return stream;
}
