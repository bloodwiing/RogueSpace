#include "engine/actor.h"

Actor::Actor(Scene *scene, Actor *parent)
    : HierarchyContainer<Scene, Actor>(parent)
    , m_scene(scene)
{ }

template<class T>
T *Actor::addChild() {
    HierarchyContainer::addChild<T>(m_scene, this);
}

std::string Actor::getName() const {
    return m_name;
}

Scene *Actor::getScene() const {
    return m_scene;
}

glm::vec3 Actor::getTranslation() const {
    return glm::vec3(0.0f);
}

glm::quat Actor::getRotation() const {
    return {1.0f, 0.0f, 0.0f, 0.0f};
}

glm::vec3 Actor::getScale() const {
    return glm::vec3(1.0f);
}
