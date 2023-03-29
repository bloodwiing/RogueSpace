#include "engine/actor/dynamicactor.h"

DynamicActor::DynamicActor(Scene* scene, ActorBase* parent)
    : Actor(scene, parent)
{ }

void DynamicActor::update(GLFWwindow *window, double delta) {
    if (m_needsMatrixUpdate) {
        auto trans = glm::translate(glm::mat4(1.0f), getTranslation());
        auto rot = glm::mat4_cast(getRotation());
        auto sca = glm::scale(glm::mat4(1.0f), getScale());

        glm::mat4 parentMatrix = getParent() != nullptr ? getParent()->getWorldMatrix() : glm::mat4(1.0f);
        m_worldMatrix = parentMatrix * trans * rot * sca;
        m_needsMatrixUpdate = false;

        for (auto* child : m_children) {
            auto dynamicChild = dynamic_cast<DynamicActor*>(child);
            if (dynamicChild != nullptr)
                dynamicChild->flagForMatrixUpdate();
        }
    }
    ActorBase::update(window, delta);
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

void DynamicActor::translate(const glm::vec3 &tra) {
    m_translation += tra;
    flagForMatrixUpdate();
}

void DynamicActor::rotate(const glm::quat &rot) {
    m_rotation *= rot;
    flagForMatrixUpdate();
}

void DynamicActor::scale(const glm::vec3 &sca) {
    m_scale *= sca;
    flagForMatrixUpdate();
}

void DynamicActor::flagForMatrixUpdate() {
    m_needsMatrixUpdate = true;
}
