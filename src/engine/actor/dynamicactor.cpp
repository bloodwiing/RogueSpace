#include "engine/actor/dynamicactor.h"

glm::vec3 DynamicActor::getTranslation() const {
    return m_translation;
}

glm::quat DynamicActor::getRotation() const {
    return m_rotation;
}

glm::vec3 DynamicActor::getScale() const {
    return m_scale;
}

void DynamicActor::setTranslation(const glm::vec3 &tra) {
    m_translation = tra;
}

void DynamicActor::setRotation(const glm::quat &rot) {
    m_rotation = rot;
}

void DynamicActor::setScale(const glm::vec3 &sca) {
    m_scale = sca;
}

void DynamicActor::translate(const glm::vec3 &tra) {
    m_translation += tra;
}

void DynamicActor::rotate(const glm::quat &rot) {
    m_rotation *= rot;
}

void DynamicActor::scale(const glm::vec3 &sca) {
    m_scale *= sca;
}
