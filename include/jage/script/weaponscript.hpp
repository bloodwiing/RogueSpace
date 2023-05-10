#ifndef JAGE_WEAPON_SCRIPT_HPP
#define JAGE_WEAPON_SCRIPT_HPP

#include "jage/script/abc/script_abc.hpp"
#include "jage/actor/dynamicactor.hpp"

namespace jage::script {

    class WeaponScript : public abc::AttachableScriptABC<jage::actor::DynamicActor> {
    public:
        WeaponScript(jage::actor::abc::ActorABC *node, float bulletSpeed);

        void onAttach() override;
        void onSpawn() override;
        void onUpdate() override;
        void onDeath() override;

        void shootThisFrame(glm::vec3 extraVelocity);

        [[nodiscard]] float getBulletSpeed() const;
        void setBulletSpeed(float bulletSpeed);

    private:
        float m_bulletSpeed;

        float m_fireCoolDown = 0.0f;
        bool m_fireFromLeft = true;
    };
};

#endif //JAGE_WEAPON_SCRIPT_HPP
