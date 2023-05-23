#ifndef JAGE_WEAPON_SCRIPT_HPP
#define JAGE_WEAPON_SCRIPT_HPP

#include "jage/script/abc/script_abc.hpp"
#include "jage/node/actor/dynamicactor.hpp"

namespace jage::script {

    class WeaponScript : public abc::AttachableScriptABC<jage::node::actor::DynamicActor> {
    public:
        WeaponScript(abc::ScriptableABC* node, float bulletSpeed, Tag bulletTargetTag);

        void onAttach() override;
        void onSpawn() override;
        void onUpdate() override;
        void onDeath() override;

        void shootThisFrame(const glm::vec3& extraVelocity, const glm::vec3& orientation, const glm::vec3& up);
        void shootThisFrame(const glm::vec3& extraVelocity);

        [[nodiscard]] float getBulletSpeed() const;
        void setBulletSpeed(float bulletSpeed);

    private:
        float m_bulletSpeed;

        float m_fireCoolDown = 0.0f;
        bool m_fireFromLeft = true;

        Tag m_bulletTargetTag;
    };
}

#endif //JAGE_WEAPON_SCRIPT_HPP
