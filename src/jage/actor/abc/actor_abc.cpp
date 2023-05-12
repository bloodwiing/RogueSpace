#include "jage/actor/abc/actor_abc.hpp"

#include <iostream>

using jage::actor::abc::ActorABC;

std::string ActorABC::getTypeName() const {
    return "ActorABC (ABSTRACT BASE CLASS)";
}

ActorABC::ActorABC(ActorABC *parent, std::string& name, Tag tag)
    : m_parent(parent)
    , m_name(name)
    , m_tag(tag)
{ }

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

glm::mat4 ActorABC::getWorldMatrix() const {
    return glm::mat4(1.0f);
}

bool ActorABC::isDead() const {
    return false;
}

void ActorABC::setTag(jage::Tag tag) {
    m_tag = tag;
}

void ActorABC::update() {
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

void ActorABC::draw(jage::graphics::Shader& shader) {
    for (auto& [name, child] : m_children) {
        if (child.value)
            child.value->draw(shader);
    }
}

std::string ActorABC::toHierarchyString(uint16_t indent /* = 0 */) const {
    std::string result = m_name + ": " + getTypeName() + "\n";
    for (const auto& iter : m_children) {
        result += std::string(" | ", indent * 3) + " > ";
        result += iter.second.value->toHierarchyString(indent + 1);
    }
    return result;
}

std::ostream& operator<<(std::ostream& stream, ActorABC *actor) {
    stream << actor->toHierarchyString();
    return stream;
}
