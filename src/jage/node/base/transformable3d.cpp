#include "jage/node/base/transformable3d.hpp"

#include <glm/gtc/quaternion.hpp>

using jage::node::base::Transformable3D;

glm::vec3 Transformable3D::getWorldPosition() const {
    return {getWorldMatrix()[4]};
}

void Transformable3D::translate(const glm::vec3& tra) {
    setTranslation(tra + getTranslation());
}

void Transformable3D::rotate(const glm::quat& rot) {
    setRotation(glm::normalize(rot * getRotation()));
}

void Transformable3D::scale(const glm::vec3& sca) {
    setScale(sca * getScale());
}
