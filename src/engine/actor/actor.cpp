#include "engine/actor/actor.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"

#include "engine/time.hpp"

namespace Actors = Engine::Actors;

std::string Actors::Actor::getTypeName() const {
    return "Actor";
}

Actors::Actor::Actor(Engine::Scene *scene, ActorBase *parent, std::string name)
    : ActorBase(scene, parent, name)
    , m_scene(scene)
    , m_dead(false)
{ }

Engine::Scene *Actors::Actor::getScene() const {
    return m_scene;
}

bool Actors::Actor::isDead() const {
    return m_dead;
}

glm::vec3 Actors::Actor::getTranslation() const {
    return glm::vec3(0.0f);
}

glm::quat Actors::Actor::getRotation() const {
    return {1.0f, 0.0f, 0.0f, 0.0f};
}

glm::vec3 Actors::Actor::getScale() const {
    return glm::vec3(1.0f);
}

void Actors::Actor::markDead(float wait /* = -1.0f */) {
    if (wait <= 0.0f)
        m_dead = true;
    else
        m_deathTimer = wait;
}

void Actors::Actor::update() {
    if (m_deathTimer >= 0.0f) {
        m_deathTimer -= Time::getDeltaFloat();
        if (m_deathTimer <= 0.0f) {
            m_dead = true;
            m_deathTimer = -1.0f;
        }
    }
    ActorBase::update();
}

void Actors::Actor::draw(Graphics::Shader& shader) {
    for (auto& [name, child] : m_children) {
        if (child.value != nullptr)
            child.value->draw(shader);
    }
}
