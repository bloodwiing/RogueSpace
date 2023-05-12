#ifndef JAGE_COLLISION_RECEIVER_SCRIPT_HPP
#define JAGE_COLLISION_RECEIVER_SCRIPT_HPP

#include "jage/actor/dynamicactor.hpp"
#include "jage/script/abc/script_abc.hpp"

namespace jage::script {

    class CollisionReceiverScript : public abc::AttachableScriptABC<jage::actor::DynamicActor> {
    public:
        explicit CollisionReceiverScript(jage::actor::abc::ActorABC* node, float radius);

        void onAttach() override;
        void onSpawn() override;
        void onUpdate() override;
        void onDeath() override;

        void onCollide(jage::actor::DynamicActor*& other);

        [[nodiscard]] float getRadius() const;
        void setRadius(float radius);

    private:
        float m_radius;
    };
}

#endif //JAGE_COLLISION_RECEIVER_SCRIPT_HPP
