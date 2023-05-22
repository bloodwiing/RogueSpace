#include "jage/node/actor/staticactor.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include "jage/runtime/time.hpp"

using jage::node::actor::StaticActor;
using glm::vec3;

std::string StaticActor::getTypeName() const {
    return "StaticActor";
}

StaticActor::StaticActor(JAGE_ACTOR_ARGS)
    : ActorABC(parent, std::move(name), scene, tag, isVolatile)
{

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

glm::vec3 StaticActor::getOrientation() const {
    return {1.0f, 0.0f, 0.0f};
}

glm::vec3 StaticActor::getUp() const {
    return {0.0f, 1.0f, 0.0f};
}

glm::vec3 StaticActor::getWorldPosition() const {
    return glm::vec3(0.0f);
}

void StaticActor::draw(jage::graphics::Shader& shader) {
    for (auto& [name, child] : m_children) {
        if (child.value != nullptr)
            child.value->draw(shader);
    }
}
