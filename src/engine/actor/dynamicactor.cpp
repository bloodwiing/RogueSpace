#include "engine/actor/dynamicactor.hpp"

#include <glm/gtx/matrix_decompose.hpp>

std::string DynamicActor::getTypeName() const {
    return "DynamicActor";
}

DynamicActor::DynamicActor(Scene* scene, ActorBase* parent, std::string name)
    : Actor(scene, parent, name)
{ }

void DynamicActor::update() {
    if (m_needsMatrixUpdate) {
        auto trans = glm::translate(glm::mat4(1.0f), getTranslation());
        auto rot = glm::mat4_cast(getRotation());
        auto sca = glm::scale(glm::mat4(1.0f), getScale());

        glm::mat4 parentMatrix = getParent() != nullptr ? getParent()->getWorldMatrix() : glm::mat4(1.0f);
        m_worldMatrix = parentMatrix * trans * rot * sca;
        m_needsMatrixUpdate = false;

        for (auto& [name, child] : m_children) {
            auto dynamicChild = dynamic_cast<DynamicActor*>(child.value);
            if (dynamicChild != nullptr)
                dynamicChild->flagForMatrixUpdate();
        }
    }
    Actor::update();
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

glm::mat4 DynamicActor::getWorldMatrix() const {
    return m_worldMatrix;
}

void DynamicActor::setTranslation(const glm::vec3 &tra) {
    m_translation = tra;
    flagForMatrixUpdate();
}

void DynamicActor::setRotation(const glm::quat &rot) {
    m_rotation = rot;
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
    m_rotation = glm::normalize(m_rotation * rot);
    flagForMatrixUpdate();
}

void DynamicActor::scale(const glm::vec3 &sca) {
    m_scale *= sca;
    flagForMatrixUpdate();
}

void DynamicActor::flagForMatrixUpdate() {
    m_needsMatrixUpdate = true;
}
