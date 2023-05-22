#include "jage/node/scene.hpp"

#include <iostream>

#include "jage/node/actor/camera.hpp"
#include "jage/node/actor/abc/actor_abc.hpp"
#include "jage/runtime/window.hpp"

using jage::node::Scene;

std::string Scene::m_hierarchyDisplayName = "root";

std::string Scene::getTypeName() const {
    return "Scene";
}

Scene::Scene()
    : jage::node::abc::NodeABC<jage::node::actor::abc::ActorABC>(nullptr, m_hierarchyDisplayName)
    , m_taggedMap(utility::EnumSize<jage::Tag>::value, std::vector<std::weak_ptr<actor::abc::ActorABC>>())
{ }

Utility::QuickList<std::shared_ptr<jage::node::actor::abc::ActorABC>> Scene::getVolatileChildren() const {
    return m_volatileActors;
}

void Scene::tagActorToMap(const std::shared_ptr<actor::abc::ActorABC>& actor) {
    if (!actor->isVolatile())
        m_taggedMap[actor->getTag()].push_back(actor);
}

void Scene::update() {
    jage::node::abc::NodeABC<NodeType>::update();

    for (auto iter = m_volatileActors.begin(); iter != m_volatileActors.end();) {
        auto& child = *iter;
        if (child) {
            try {
                child->update();
            } catch (std::exception& e) {
                std::cerr << e.what();
                child.reset();
                iter.safeRemove();
                continue;
            }
            if (child->isDead()) {
                child.reset();
                iter.safeRemove();
            }
        } else {
            child.reset();
            iter.safeRemove();
        }
        ++iter;
    }
}

void Scene::draw() {
    jage::node::abc::NodeABC<NodeType>::draw();

    for (const auto& child : m_volatileActors) {
        if (child) {
            child->draw();
        }
    }
}

Scene::TagIterator Scene::beginTagged(jage::Tag tag) {
    return {m_taggedMap[tag].begin(), m_taggedMap[tag]};
}

Scene::TagIterator Scene::endTagged(jage::Tag tag) {
    return {m_taggedMap[tag].end(), m_taggedMap[tag]};
}

Scene::TagIterator::TagIterator(InternalType::iterator iter, InternalType& original)
    : m_iter(iter)
    , m_original(original)
{
    moveTillMatch();
}

Scene::TagIterator::reference Scene::TagIterator::operator*() {
    return ((actor::StaticActor*)((*m_iter).lock()).get());
}

Scene::TagIterator::pointer Scene::TagIterator::operator->() {
    return *(*this);
}

Scene::TagIterator& Scene::TagIterator::operator++() {
    if (m_iter == m_original.end())
        return *this;

    ++m_iter;
    moveTillMatch();
    return *this;
}

Scene::TagIterator Scene::TagIterator::operator++(int) {
    auto prev = *this;
    ++(*this);
    return prev;
}

bool Scene::TagIterator::operator==(const Scene::TagIterator &other) {
    return this->m_iter == other.m_iter;
}

bool Scene::TagIterator::operator!=(const Scene::TagIterator &other) {
    return this->m_iter != other.m_iter;
}

void Scene::TagIterator::moveTillMatch() {
    while (m_iter != m_original.end()) {
        if (m_iter->expired()) {
            m_iter = m_original.erase(m_iter);
        } else {
            break;
        }
    }
}
