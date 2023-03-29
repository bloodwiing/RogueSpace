#include "engine/actor.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

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

void Actor::draw(Shader& shader, glm::mat4 transform) {
    auto trans = glm::translate(glm::mat4(1.0f), getTranslation());
    auto rot = glm::mat4_cast(getRotation());
    auto sca = glm::scale(glm::mat4(1.0f), getScale());

    transform = transform * trans * rot * sca;

    for (auto* child : m_children) {
        if (child != nullptr)
            child->draw(shader, transform);
    }
}