#ifndef JAGE_HEALTH_SCRIPT_HPP
#define JAGE_HEALTH_SCRIPT_HPP

#include "jage/actor/staticactor.hpp"
#include "jage/script/abc/script_abc.hpp"
#include "jage/script/collisionreceiverscript.hpp"
#include "jage/event/collisionevent.hpp"

namespace jage::script {

class HealthScript : public abc::AttachableScriptABC<jage::actor::StaticActor>, public jage::event::CollisionEvent, public std::enable_shared_from_this<HealthScript> {
    public:
        HealthScript(jage::actor::abc::ActorABC* node, float maxHealth);

        void notify(jage::actor::StaticActor* notifier) override;

        void onAttach() override;
        void onSpawn() override;
        void onUpdate() override;
        void onDeath() override;

    private:
        float m_maxHealth;
        float m_health;

        CollisionReceiverScript* m_collider;
    };
}

#endif //JAGE_HEALTH_SCRIPT_HPP
