#include "jage/actor/dynamicactor.hpp"

#include <glm/gtx/matrix_decompose.hpp>

using jage::actor::DynamicActor;

std::string DynamicActor::getTypeName() const {
    return "DynamicActor";
}

DynamicActor::DynamicActor(Scene* scene, abc::ActorABC* parent, std::string name, Tag tag, bool isVolatile)
    : StaticActor(scene, parent, std::move(name), tag, isVolatile)
{ }

void DynamicActor::update() {
    if (m_needsMatrixUpdate) {
        auto trans = glm::translate(glm::mat4(1.0f), getTranslation());
        auto rot = glm::mat4_cast(getRotation());
        auto sca = glm::scale(glm::mat4(1.0f), getScale());

        glm::mat4 parentMatrix = getParent() != nullptr ? getParent()->getWorldMatrix() : glm::mat4(1.0f);
        m_worldMatrix = parentMatrix * trans * rot * sca;
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

    StaticActor::update();
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

glm::vec3 jage::actor::DynamicActor::getOrientation() const {
    return m_orientation;
}

glm::vec3 jage::actor::DynamicActor::getUp() const {
    return m_up;
}

glm::vec3 DynamicActor::getWorldPosition() const {
    return {getWorldMatrix()[3]};
}

glm::mat4 DynamicActor::getWorldMatrix() const {
    return m_worldMatrix;
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
    glm::decompose(mat, m_scale, m_rotation, m_translation, skew,perspective);
    m_rotation = glm::conjugate(m_rotation);
    flagForMatrixUpdate();
}

void DynamicActor::translate(const glm::vec3 &tra) {
    m_translation += tra;
    flagForMatrixUpdate();
}

void DynamicActor::rotate(const glm::quat &rot) {
    m_rotation = glm::normalize(rot * m_rotation);
    flagForVectorUpdate();
    flagForMatrixUpdate();
}

void DynamicActor::scale(const glm::vec3 &sca) {
    m_scale *= sca;
    flagForMatrixUpdate();
}

void DynamicActor::flagForMatrixUpdate() {
    m_needsMatrixUpdate = true;
}

void jage::actor::DynamicActor::flagForVectorUpdate() {
    m_needsVectorUpdate = true;
}
