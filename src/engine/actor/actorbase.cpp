#include "engine/actor/actorbase.h"

std::string ActorBase::getTypeName() const {
    return "RAW_ActorBase";
}

ActorBase::ActorBase(Scene* scene, ActorBase *parent, std::string& name)
    : m_parent(parent)
    , m_name(name)
{ }

ActorBase::~ActorBase() {
    for (auto& [name, child] : m_children) {
        delete child.value;
    }
}

std::map<std::string, ActorBase::ChildEntry> ActorBase::getChildren() const {
    return m_children;
}

ActorBase* ActorBase::getChild(const std::string &name) const {
    if (m_children.find(name) == m_children.end())
        return nullptr;
    return m_children.at(name).value;
}

ActorBase* ActorBase::getParent() const {
    return m_parent;
}

std::string ActorBase::getName() const {
    return m_name;
}

glm::mat4 ActorBase::getWorldMatrix() const {
    return glm::mat4(1.0f);
}

void ActorBase::update() {
    for (auto& [name, child] : m_children) {
        if (child.value != nullptr)
            child.value->update();
    }
}

void ActorBase::draw(Shader& shader) {
    for (auto& [name, child] : m_children) {
        if (child.value != nullptr)
            child.value->draw(shader);
    }
}

std::string ActorBase::toHierarchyString(uint16_t indent /* = 0 */) const {
    std::string result = m_name + ": " + getTypeName() + "\n";
    for (const auto& iter : m_children) {
        result += std::string(" | ", indent * 3) + " > ";
        result += iter.second.value->toHierarchyString(indent + 1);
    }
    return result;
}
