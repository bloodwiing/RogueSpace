#include "jage/node/abc/transformable2d_abc.hpp"

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
