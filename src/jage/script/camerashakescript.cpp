#include "jage/script/camerashakescript.hpp"

#include <glm/glm.hpp>

#include "jage/runtime/time.hpp"

using jage::script::CameraShakeScript;

std::mt19937 CameraShakeScript::random = std::mt19937(time(nullptr));

CameraShakeScript::CameraShakeScript(abc::ScriptableABC* node, float amplitude, float frequency)
    : m_amplitude(amplitude)
    , m_frequency(frequency)
{
    validate(node);
}

void CameraShakeScript::onAttach() {

}

void CameraShakeScript::onSpawn() {

}

void CameraShakeScript::onUpdate() {
    m_cumTime += jage::runtime::Time::getDeltaFloat() / m_frequency;

    if (m_amplitude < 0.001f and m_cumTime >= 1.0f) {
        return;
    }

    if (m_cumTime > 1.0f) {
        m_cumTime = 0.0f;
        m_shakePrev = m_shakeNew;

        glm::vec3 target = glm::vec3(m_offset.y + m_range(random) * m_amplitude, m_offset.x + m_range(random) * m_amplitude, 0.0);
        m_shakeNew = glm::normalize(glm::quat(target));
    }

    const float change = 0.5f - (glm::cos(m_cumTime * glm::pi<float>()) * 0.5f);
    auto rotation = glm::slerp(m_shakePrev, m_shakeNew, change);
    m_node->setRotation(rotation);
}

void CameraShakeScript::onDeath() {

}

void CameraShakeScript::setAmplitude(float amplitude) {
    m_amplitude = amplitude;
}

void CameraShakeScript::setFrequency(float frequency) {
    m_frequency = frequency;
}

void CameraShakeScript::setOffset(float x, float y) {
    m_offset = glm::vec2(x, y);
}
