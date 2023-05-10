#ifndef JAGE_PLAYER_CONTROLLER_SCRIPT_HPP
#define JAGE_PLAYER_CONTROLLER_SCRIPT_HPP

#include "jage/actor/shipactor.hpp"
#include "jage/script/camerashakescript.hpp"
#include "jage/script/abc/script_abc.hpp"

namespace jage::script {

    class PlayerControllerScript : public abc::AttachableScriptABC<jage::actor::ShipActor> {
    public:
        explicit PlayerControllerScript(jage::actor::abc::ActorABC *node, CameraShakeScript* cameraShake);

        void onAttach() override;
        void onSpawn() override;
        void onUpdate() override;
        void onDeath() override;

        void onKeyboardInput() override;
        void onMouseInput() override;

    private:
        float m_sensitivity = 2.5f;

        float m_fireCoolDown = 0.0f;
        bool m_fireFromLeft = true;

        CameraShakeScript* m_cameraShakeScript;
    };
}

#endif //JAGE_PLAYER_CONTROLLER_SCRIPT_HPP
