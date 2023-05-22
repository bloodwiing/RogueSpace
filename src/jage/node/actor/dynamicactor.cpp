#include "jage/node/actor/dynamicactor.hpp"

#include <glm/gtx/matrix_decompose.hpp>

using jage::node::actor::DynamicActor;

std::string DynamicActor::getTypeName() const {
    return "DynamicActor";
}

DynamicActor::DynamicActor(JAGE_ACTOR_ARGS)
    : StaticActor(parent, std::move(name), scene, tag, isVolatile)
{ }

void DynamicActor::update() {
    updateTransformations();
    StaticActor::update();
}

void DynamicActor::updateTransformations() {
    if (!m_needsMatrixUpdate)
        return;

    Transformable3DABC::updateTransformations(getParent() != nullptr ? getParent()->getWorldMatrix() : glm::mat4(1.0f));
    m_needsMatrixUpdate = false;

    if (m_needsVectorUpdate) {
        m_up = glm::normalize(glm::mat3(m_worldMatrix) * glm::vec3(0.0f, 1.0f, 0.0f));
        m_orientation = glm::normalize(glm::mat3(m_worldMatrix) * glm::vec3(0.0f, 0.0f, -1.0f));
    }

    for (auto& [name, child] : m_children) {
        auto dynamicChild = dynamic_cast<DynamicActor*>(child.value.get());
        if (dynamicChild != nullptr) {
            dynamicChild->flagForMatrixUpdate();
            if (m_needsVectorUpdate)
                dynamicChild->flagForVectorUpdate();
        }
    }

    m_needsVectorUpdate = false;
}

glm::vec3 DynamicActor::getTranslation() const {
    return m_translation;
}

glm::quat DynamicActor::getRotation() const {
    return m_rotation;
}

glm::vec3 DynamicActor::getScale() const {
    return m_scale;
}

glm::vec3 DynamicActor::getOrientation() const {
    return m_orientation;
}

glm::vec3 DynamicActor::getUp() const {
    return m_up;
}

glm::vec3 DynamicActor::getWorldPosition() const {
    return {getWorldMatrix()[3]};
}

glm::mat4 DynamicActor::getWorldMatrix() const {
    return m_worldMatrix;
}

void DynamicActor::setWorldMatrix(const glm::mat4& mat) {
    m_worldMatrix = mat;
}

void DynamicActor::setTranslation(const glm::vec3 &tra) {
    m_translation = tra;
    flagForMatrixUpdate();
}

void DynamicActor::setRotation(const glm::quat &rot) {
    m_rotation = rot;
    flagForVectorUpdate();
    flagForMatrixUpdate();
}

void DynamicActor::setScale(const glm::vec3 &sca) {
    m_scale = sca;
    flagForMatrixUpdate();
}

void DynamicActor::setMatrix(const glm::mat4 &mat) {
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(mat, m_scale, m_rotation, m_translation, skew, perspective);
    m_rotation = glm::conjugate(m_rotation);
    flagForMatrixUpdate();
}

void DynamicActor::flagForMatrixUpdate() {
    m_needsMatrixUpdate = true;
}

void DynamicActor::flagForVectorUpdate() {
    m_needsVectorUpdate = true;
}
