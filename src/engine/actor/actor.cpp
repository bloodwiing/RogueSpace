#include "engine/actor/actor.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"

#include "engine/time.hpp"

std::string Actor::getTypeName() const {
    return "Actor";
}

Actor::Actor(Scene *scene, ActorBase *parent, std::string name)
    : ActorBase(scene, parent, name)
    , m_scene(scene)
    , m_dead(false)
{ }

Scene *Actor::getScene() const {
    return m_scene;
}

bool Actor::isDead() const {
    return m_dead;
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

void Actor::markDead(float wait /* = -1.0f */) {
    if (wait <= 0.0f)
        m_dead = true;
    else
        m_deathTimer = wait;
}

void Actor::update() {
    if (m_deathTimer >= 0.0f) {
        m_deathTimer -= Time::getDeltaFloat();
        if (m_deathTimer <= 0.0f) {
            m_dead = true;
            m_deathTimer = -1.0f;
        }
    }
    ActorBase::update();
}

void Actor::draw(Shader& shader) {
    for (auto& [name, child] : m_children) {
        if (child.value != nullptr)
            child.value->draw(shader);
    }
}
