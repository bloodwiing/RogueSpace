#include "engine/actor/actorbase.h"

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

glm::mat4 ActorBase::getWorldMatrix() const {
    return glm::mat4(1.0f);
}

void ActorBase::update(GLFWwindow* window, double delta) {
    for (auto* child : m_children) {
        if (child != nullptr)
            child->update(window, delta);
    }
}

void ActorBase::draw(Shader& shader) {
    for (auto* child : m_children) {
        if (child != nullptr)
            child->draw(shader);
    }
}
