#include "jage/node/actor/staticactor.hpp"

#include <glm/gtc/quaternion.hpp>

using jage::node::actor::StaticActor;
using glm::vec3;

std::string StaticActor::getTypeName() const {
    return "StaticActor";
}

StaticActor::StaticActor(JAGE_ACTOR_ARGS)
    : ActorABC(parent, std::move(name), scene, tag, isVolatile)
{

}

glm::mat4 StaticActor::getWorldMatrix() const {
    return glm::mat4(1.0f);
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
