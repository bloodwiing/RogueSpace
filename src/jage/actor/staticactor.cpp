#include "jage/actor/staticactor.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include "jage/runtime/time.hpp"

using jage::actor::StaticActor;
using glm::vec3;

std::string StaticActor::getTypeName() const {
    return "Actor";
}

StaticActor::StaticActor(Scene *scene, abc::ActorABC *parent, std::string name)
    : ActorABC(parent, name)
    , m_scene(scene)
    , m_dead(false)
{ }

jage::actor::Scene *StaticActor::getScene() const {
    return m_scene;
}

bool StaticActor::isDead() const {
    return m_dead;
}

glm::vec3 StaticActor::getTranslation() const {
    return vec3(0.0f);
}

glm::quat StaticActor::getRotation() const {
    return {1.0f, 0.0f, 0.0f, 0.0f};
}

glm::vec3 StaticActor::getScale() const {
    return vec3(1.0f);
}

void StaticActor::markDead(float wait /* = -1.0f */) {
    if (wait <= 0.0f)
        m_dead = true;
    else
        m_deathTimer = wait;
}

void StaticActor::update() {
    using jage::runtime::Time;
    
    if (m_deathTimer >= 0.0f) {
        m_deathTimer -= Time::getDeltaFloat();
        if (m_deathTimer <= 0.0f) {
            m_dead = true;
            m_deathTimer = -1.0f;
        }
    }
    abc::ActorABC::update();
}

void StaticActor::draw(jage::graphics::Shader& shader) {
    for (auto& [name, child] : m_children) {
        if (child.value != nullptr)
            child.value->draw(shader);
    }
}
