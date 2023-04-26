#include "engine/actor/actorbase.hpp"

#include <iostream>

namespace Actors = Engine::Actors;

std::string Actors::ActorBase::getTypeName() const {
    return "RAW_ActorBase";
}

Actors::ActorBase::ActorBase(Engine::Scene* scene, ActorBase *parent, std::string& name)
    : m_parent(parent)
    , m_name(name)
{ }

std::map<std::string, Actors::ActorBase::ChildEntry> Actors::ActorBase::getChildren() const {
    return m_children;
}

Actors::ActorBase* Actors::ActorBase::getChild(const std::string &name) const {
    if (m_children.find(name) == m_children.end())
        return nullptr;
    return m_children.at(name).value.get();
}

Actors::ActorBase* Actors::ActorBase::getParent() const {
    return m_parent;
}

std::string Actors::ActorBase::getName() const {
    return m_name;
}

glm::mat4 Actors::ActorBase::getWorldMatrix() const {
    return glm::mat4(1.0f);
}

bool Actors::ActorBase::isDead() const {
    return false;
}

void Actors::ActorBase::update() {
    for (auto iter = m_children.begin(); iter != m_children.end();) {
        auto& child = iter->second.value;
        if (child) {
            try {
                child->update();
            } catch (std::exception& e) {
                std::cerr << e.what();
                m_children.erase(iter++);
                continue;
            }
            if (child->isDead()) {
                m_children.erase(iter++);
            } else
                ++iter;
        } else {
            m_children.erase(iter++);
        }
    }
}

void Actors::ActorBase::draw(Graphics::Shader& shader) {
    for (auto& [name, child] : m_children) {
        if (child.value)
            child.value->draw(shader);
    }
}

std::string Actors::ActorBase::toHierarchyString(uint16_t indent /* = 0 */) const {
    std::string result = m_name + ": " + getTypeName() + "\n";
    for (const auto& iter : m_children) {
        result += std::string(" | ", indent * 3) + " > ";
        result += iter.second.value->toHierarchyString(indent + 1);
    }
    return result;
}

std::ostream& operator<<(std::ostream& stream, Actors::ActorBase *actor) {
    stream << actor->toHierarchyString();
    return stream;
}
