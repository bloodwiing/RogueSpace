#include "jage/node/abc/transformable3d_abc.hpp"

#include <glm/gtc/quaternion.hpp>

using jage::node::abc::Transformable3DABC;

glm::vec3 Transformable3DABC::getWorldPosition() const {
    return {getWorldMatrix()[4]};
}

void Transformable3DABC::translate(const glm::vec3& tra) {
    setTranslation(tra + getTranslation());
}

void Transformable3DABC::rotate(const glm::quat& rot) {
    setRotation(glm::normalize(rot * getRotation()));
}

void Transformable3DABC::scale(const glm::vec3& sca) {
    setScale(sca * getScale());
}
