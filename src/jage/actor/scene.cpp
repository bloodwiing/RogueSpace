#include "jage/actor/scene.hpp"

#include <iostream>

#include "jage/actor/camera.hpp"
#include "jage/actor/abc/actor_abc.hpp"
#include "jage/runtime/window.hpp"

using jage::actor::Scene;

std::string Scene::m_hierarchyDisplayName = "root";

std::string Scene::getTypeName() const {
    return "Scene";
}

Scene::Scene()
    : ActorABC(nullptr, m_hierarchyDisplayName, Tag::SYSTEM, false)
    , m_taggedMap(utility::EnumSize<jage::Tag>::value, std::vector<std::weak_ptr<abc::ActorABC>>())
{ }

Utility::QuickList<std::shared_ptr<jage::actor::abc::ActorABC>> Scene::getVolatileChildren() const {
    return m_volatileActors;
}

void Scene::tagActorToMap(const std::shared_ptr<abc::ActorABC>& actor) {
    if (!actor->isVolatile())
        m_taggedMap[actor->getTag()].push_back(actor);
}

glm::vec3 Scene::getTranslation() const {
    return glm::vec3(0.0);
}

glm::quat Scene::getRotation() const {
    return {1.0, 0.0, 0.0, 0.0};
}

glm::vec3 Scene::getScale() const {
    return glm::vec3(1.0);
}

glm::vec3 Scene::getOrientation() const {
    return {1.0f, 0.0f, 0.0f};
}

glm::vec3 Scene::getUp() const {
    return {0.0f, 1.0f, 0.0f};
}

glm::vec3 Scene::getWorldPosition() const {
    return glm::vec3(0.0f);
}

void Scene::update() {
    abc::ActorABC::update();

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

void Scene::draw(jage::graphics::Shader &shader) {
    abc::ActorABC::draw(shader);

    for (const auto& child : m_volatileActors) {
        if (child)
            child->draw(shader);
    }
}
