#ifndef JAGE_ENEMY_SPAWNER_SCRIPT_HPP
#define JAGE_ENEMY_SPAWNER_SCRIPT_HPP

#include "jage/script/abc/script_abc.hpp"
#include "jage/node/actor/dynamicactor.hpp"
#include "jage/node/actor/shipactor.hpp"
#include "jage/event/damageevent.hpp"
#include "jage/script/actor/healthscript.hpp"
#include "jage/script/actor/scorescript.hpp"

namespace jage::script::actor {

    class EnemySpawnerScript
            : public abc::AttachableScriptABC<node::actor::DynamicActor>
            , public event::DamageEvent
            , public std::enable_shared_from_this<EnemySpawnerScript>
    {
    public:
        EnemySpawnerScript(abc::ScriptableABC* node);

        void onAttach() override;
        void onSpawn() override;
        void onUpdate() override;
        void onDeath() override;

        void notify(node::actor::DynamicActor* source, const float& delta, const float& current, const float& max) override;

        static void setup(node::Scene* worldScene, node::actor::ShipActor* player, std::weak_ptr<ScoreScript> playerScoreScript);

        static void spawnOne(float maxHealth);
        static void spawnWave();

    private:
        std::weak_ptr<HealthScript> m_healthScript;

        static int wave;
        static int alive;

        static node::Scene* scene;
        static node::actor::ShipActor* playerTarget;
        static std::weak_ptr<ScoreScript> scoreScript;
    };
}

#endif //JAGE_ENEMY_SPAWNER_SCRIPT_HPP
