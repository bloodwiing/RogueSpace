#include "jage/node/abc/transformable2d_abc.hpp"

#include <glm/gtx/matrix_transform_2d.hpp>

using jage::node::abc::Transformable2DABC;

glm::vec2 Transformable2DABC::getWorldPosition() const {
    return {getWorldMatrix()[2]};
}

void Transformable2DABC::translate(const glm::vec2& tra) {
    setTranslation(tra + getTranslation());
}

void Transformable2DABC::rotate(const float& rot) {
    setRotation(rot + getRotation());
}

void Transformable2DABC::scale(const glm::vec2& sca) {
    setScale(sca * getScale());
}

void Transformable2DABC::updateTransformations(const glm::mat3& parentMatrix) {
    auto trans = glm::translate(glm::mat3(1.0f), getTranslation());
    auto rot = glm::rotate(glm::mat3(1.0f), getRotation());
    auto sca = glm::scale(glm::mat3(1.0f), getScale());

    setWorldMatrix(parentMatrix * trans * rot * sca);
}
