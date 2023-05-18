#ifndef JAGE_PLAYER_CONTROLLER_SCRIPT_HPP
#define JAGE_PLAYER_CONTROLLER_SCRIPT_HPP

#include "jage/node/actor/shipactor.hpp"
#include "jage/script/camerashakescript.hpp"
#include "jage/script/weaponscript.hpp"
#include "jage/script/abc/script_abc.hpp"

namespace jage::script {

    class PlayerControllerScript : public abc::AttachableScriptABC<jage::node::actor::ShipActor> {
    public:
        explicit PlayerControllerScript(jage::node::actor::abc::ActorABC *node, CameraShakeScript* cameraShake);

        void onAttach() override;
        void onSpawn() override;
        void onUpdate() override;
        void onDeath() override;

        void onKeyboardInput() override;
        void onMouseInput() override;

    private:
        float m_sensitivity = 2.5f;

        CameraShakeScript* m_cameraShakeScript;
        WeaponScript* m_weaponScript;
    };
}

#endif //JAGE_PLAYER_CONTROLLER_SCRIPT_HPP
