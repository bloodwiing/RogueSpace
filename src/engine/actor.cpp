#include "engine/actor.h"

Actor::Actor(Scene *scene, ActorBase *parent)
    : ActorBase(parent)
    , m_scene(scene)
{ }

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
