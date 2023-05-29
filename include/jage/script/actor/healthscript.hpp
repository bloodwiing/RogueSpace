#ifndef JAGE_HEALTH_SCRIPT_HPP
#define JAGE_HEALTH_SCRIPT_HPP

#include "jage/node/actor/staticactor.hpp"
#include "jage/script/abc/script_abc.hpp"
#include "jage/script/actor/collisionlistenerscript.hpp"
#include "jage/event/collisionevent.hpp"
#include "jage/event/damageevent.hpp"

namespace jage::script::actor {

class HealthScript
        : public abc::AttachableScriptABC<jage::node::actor::StaticActor>
        , public jage::event::CollisionEvent
        , public std::enable_shared_from_this<HealthScript>
    {
    public:
        HealthScript(abc::ScriptableABC* node, float maxHealth);

        void notify(jage::node::actor::StaticActor* notifier) override;

        void onAttach() override;
        void onSpawn() override;
        void onUpdate() override;
        void onDeath() override;

        void damage(float amount);

        event::DamageEvent::Manager onDamage;

    private:
        float m_maxHealth;
        float m_health;

        std::weak_ptr<CollisionListenerScript> m_collider;
    };
}

#endif //JAGE_HEALTH_SCRIPT_HPP
