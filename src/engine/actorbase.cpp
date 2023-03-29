#include "engine/actorbase.h"

ActorBase::ActorBase(ActorBase *parent)
    : m_parent(parent)
{ }

ActorBase::~ActorBase() {
    for (const ActorBase* child : m_children) {
        delete child;
    }
}

std::vector<ActorBase*> ActorBase::getChildren() const {
    return m_children;
}

ActorBase* ActorBase::getParent() const {
    return m_parent;
}
