#include "engine/actor/actor.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"

std::string Actor::getTypeName() const {
    return "Actor";
}

Actor::Actor(Scene *scene, ActorBase *parent, std::string name)
    : ActorBase(scene, parent, name)
    , m_scene(scene)
{ }

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

void Actor::draw(Shader& shader) {
    for (auto& [name, child] : m_children) {
        if (child.value != nullptr)
            child.value->draw(shader);
    }
}
