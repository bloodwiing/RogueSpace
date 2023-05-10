#ifndef JAGE_CAMERA_SHAKE_SCRIPT_HPP
#define JAGE_CAMERA_SHAKE_SCRIPT_HPP

#include <random>

#include "jage/script/abc/script_abc.hpp"
#include "jage/actor/dynamicactor.hpp"

namespace jage::script {

    class CameraShakeScript : public abc::AttachableScriptABC<jage::actor::DynamicActor> {
    public:
        explicit CameraShakeScript(jage::actor::abc::ActorABC *node, float amplitude, float frequency);

        void onAttach() override;
        void onSpawn() override;
        void onUpdate() override;
        void onDeath() override;

        void setAmplitude(float amplitude);
        void setFrequency(float frequency);
        void setOffset(float x, float y);

    private:
        float m_amplitude;
        float m_frequency;
        glm::vec2 m_offset = glm::vec2(0.0f);

        static std::mt19937 random;
        std::uniform_real_distribution<float> m_range = std::uniform_real_distribution<float>(-1.0f, 1.0f);

        float m_cumTime = 1.0f;
        glm::quat m_shakePrev = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
        glm::quat m_shakeNew = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    };
}

#endif //JAGE_CAMERA_SHAKE_SCRIPT_HPP
