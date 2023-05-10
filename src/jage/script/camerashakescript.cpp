#include "jage/script/camerashakescript.hpp"

#include <glm/glm.hpp>

using jage::script::CameraShakeScript;

std::mt19937 CameraShakeScript::random = std::mt19937(time(nullptr));

CameraShakeScript::CameraShakeScript(jage::actor::abc::ActorABC *node) {
    validate(node);
}

void CameraShakeScript::onAttach() {

}

void CameraShakeScript::onSpawn() {

}

void CameraShakeScript::onUpdate() {
    auto translation = glm::vec3(0.0f);
    translation += m_node->getUp() * (m_offset.y + m_range(random) * m_amplitude);
    translation += glm::normalize(glm::cross(m_node->getOrientation(), m_node->getUp())) * (m_offset.x + m_range(random) * m_amplitude);
    m_node->setTranslation(translation);
}

void CameraShakeScript::onDeath() {

}

void CameraShakeScript::setAmplitude(float amplitude) {
    m_amplitude = amplitude;
}

void CameraShakeScript::setOffset(float x, float y) {
    m_offset = glm::vec2(x, y);
}
