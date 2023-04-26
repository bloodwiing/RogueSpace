#include "engine/actor/dynamicactor.hpp"

#include <glm/gtx/matrix_decompose.hpp>

namespace Actors = Engine::Actors;

std::string Actors::DynamicActor::getTypeName() const {
    return "DynamicActor";
}

Actors::DynamicActor::DynamicActor(Scene* scene, ActorBase* parent, std::string name)
    : Actor(scene, parent, name)
{ }

void Actors::DynamicActor::update() {
    if (m_needsMatrixUpdate) {
        auto trans = glm::translate(glm::mat4(1.0f), getTranslation());
        auto rot = glm::mat4_cast(getRotation());
        auto sca = glm::scale(glm::mat4(1.0f), getScale());

        glm::mat4 parentMatrix = getParent() != nullptr ? getParent()->getWorldMatrix() : glm::mat4(1.0f);
        m_worldMatrix = parentMatrix * trans * rot * sca;
        m_needsMatrixUpdate = false;

        for (auto& [name, child] : m_children) {
            auto dynamicChild = dynamic_cast<DynamicActor*>(child.value.get());
            if (dynamicChild != nullptr)
                dynamicChild->flagForMatrixUpdate();
        }
    }
    Actor::update();
}

glm::vec3 Actors::DynamicActor::getTranslation() const {
    return m_translation;
}

glm::quat Actors::DynamicActor::getRotation() const {
    return m_rotation;
}

glm::vec3 Actors::DynamicActor::getScale() const {
    return m_scale;
}

glm::mat4 Actors::DynamicActor::getWorldMatrix() const {
    return m_worldMatrix;
}

void Actors::DynamicActor::setTranslation(const glm::vec3 &tra) {
    m_translation = tra;
    flagForMatrixUpdate();
}

void Actors::DynamicActor::setRotation(const glm::quat &rot) {
    m_rotation = rot;
    flagForMatrixUpdate();
}

void Actors::DynamicActor::setScale(const glm::vec3 &sca) {
    m_scale = sca;
    flagForMatrixUpdate();
}

void Actors::DynamicActor::setMatrix(const glm::mat4 &mat) {
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(mat, m_scale, m_rotation, m_translation, skew,perspective);
    m_rotation = glm::conjugate(m_rotation);
    flagForMatrixUpdate();
}

void Actors::DynamicActor::translate(const glm::vec3 &tra) {
    m_translation += tra;
    flagForMatrixUpdate();
}

void Actors::DynamicActor::rotate(const glm::quat &rot) {
    m_rotation = glm::normalize(m_rotation * rot);
    flagForMatrixUpdate();
}

void Actors::DynamicActor::scale(const glm::vec3 &sca) {
    m_scale *= sca;
    flagForMatrixUpdate();
}

void Actors::DynamicActor::flagForMatrixUpdate() {
    m_needsMatrixUpdate = true;
}
