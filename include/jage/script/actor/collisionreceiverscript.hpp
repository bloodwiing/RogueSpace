#ifndef JAGE_COLLISION_RECEIVER_SCRIPT_HPP
#define JAGE_COLLISION_RECEIVER_SCRIPT_HPP

#include "jage/node/actor/dynamicactor.hpp"
#include "jage/script/abc/script_abc.hpp"
#include "jage/event/collisionevent.hpp"

namespace jage::script::actor {

    class CollisionReceiverScript : public abc::AttachableScriptABC<jage::node::actor::DynamicActor> {
    public:
        explicit CollisionReceiverScript(abc::ScriptableABC* node, float radius);

        void onAttach() override;
        void onSpawn() override;
        void onUpdate() override;
        void onDeath() override;

        void runCollision(jage::node::actor::DynamicActor*& other);

        jage::event::CollisionEvent::Manager onCollide;

        [[nodiscard]] float getRadius() const;
        void setRadius(float radius);

    private:
        float m_radius;
    };
}

#endif //JAGE_COLLISION_RECEIVER_SCRIPT_HPP
