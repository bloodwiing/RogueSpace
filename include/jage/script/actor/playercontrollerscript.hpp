#ifndef JAGE_PLAYER_CONTROLLER_SCRIPT_HPP
#define JAGE_PLAYER_CONTROLLER_SCRIPT_HPP

#include "jage/node/actor/shipactor.hpp"
#include "jage/script/actor/camerashakescript.hpp"
#include "jage/script/actor/weaponscript.hpp"
#include "jage/script/abc/script_abc.hpp"

namespace jage::script::actor {

    class PlayerControllerScript
            : public abc::AttachableScriptABC<jage::node::actor::ShipActor>
    {
    public:
        explicit PlayerControllerScript(abc::ScriptableABC* node, std::weak_ptr<CameraShakeScript> cameraShake);

        void onAttach() override;
        void onSpawn() override;
        void onUpdate() override;
        void onDeath() override;

        void onKeyboardInput() override;
        void onMouseInput() override;

    private:
        float m_sensitivity = 2.5f;

        std::weak_ptr<CameraShakeScript> m_cameraShakeScript;
        std::weak_ptr<WeaponScript> m_weaponScript;
    };
}

#endif //JAGE_PLAYER_CONTROLLER_SCRIPT_HPP
