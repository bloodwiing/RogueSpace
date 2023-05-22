#include "jage/node/base/transformable2d.hpp"

using jage::node::base::Transformable2D;

glm::vec2 Transformable2D::getWorldPosition() const {
    return {getWorldMatrix()[2]};
}

void Transformable2D::translate(const glm::vec2& tra) {
    setTranslation(tra + getTranslation());
}

void Transformable2D::rotate(const float& rot) {
    setRotation(rot + getRotation());
}

void Transformable2D::scale(const glm::vec2& sca) {
    setScale(sca * getScale());
}
