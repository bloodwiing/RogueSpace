#include <utility>

#include <glm/gtc/random.hpp>

#include "jage/script/actor/enemyspawnerscript.hpp"
#include "jage/script/actor/weaponscript.hpp"
#include "jage/script/actor/aicontrollerscript.hpp"
#include "jage/node/actor/modelactor.hpp"

using jage::script::actor::EnemySpawnerScript;
using jage::script::abc::ScriptableABC;
using jage::node::Scene;
using jage::node::actor::ShipActor;
using jage::node::actor::ModelActor;
using jage::script::actor::WeaponScript;
using jage::script::actor::AIControllerScript;
using jage::script::actor::ScoreScript;

int EnemySpawnerScript::wave = 1;
int EnemySpawnerScript::alive = 0;

Scene* EnemySpawnerScript::scene = nullptr;
ShipActor* EnemySpawnerScript::playerTarget = nullptr;
std::weak_ptr<ScoreScript> EnemySpawnerScript::scoreScript = std::weak_ptr<ScoreScript>();

EnemySpawnerScript::EnemySpawnerScript(ScriptableABC* node) {
    validate(node);
    m_healthScript = dependsOn<HealthScript>();
}

void EnemySpawnerScript::onAttach() {
    ++alive;
    m_healthScript.lock()->onDamage += shared_from_this();
}

void EnemySpawnerScript::onSpawn() {

}

void EnemySpawnerScript::onUpdate() {

}

void EnemySpawnerScript::onDeath() {
    --alive;
    if (alive == 0) {
        ++wave;
        spawnWave();
    }
}

void EnemySpawnerScript::notify(node::actor::DynamicActor* source, const float& delta, const float& current, const float& max) {
    if (current <= 0)
        m_node->kill();
}

void EnemySpawnerScript::setup(Scene* worldScene, ShipActor* player, std::weak_ptr<ScoreScript> playerScoreScript) {
    scene = worldScene;
    playerTarget = player;
    scoreScript = std::move(playerScoreScript);
}

void EnemySpawnerScript::spawnOne(float maxHealth) {
    auto starship = scene->addChild<ShipActor>("Starship", Tag::ENEMY);
    starship->attachScript<WeaponScript>(60.0f, Tag::PLAYER, 1.0f);
    starship->attachScript<CollisionListenerScript>(1.0f);

    auto starshipHealthScript = starship->attachScript<HealthScript>(maxHealth);
    starshipHealthScript.lock()->onDamage += scoreScript;

    auto controller = starship->attachScript<AIControllerScript>();
    controller.lock()->setTarget(playerTarget);
    starship->addChild<ModelActor>("model", Tag::MESH, "./res/model/trailblazer/starship/Starship01.gltf");
    starship->translate(glm::sphericalRand(400.0f) + playerTarget->getWorldPosition());

    starship->attachScript<EnemySpawnerScript>();
}

void EnemySpawnerScript::spawnWave() {
    int spawnCount = (int)std::floor(0.2f * (float)wave) + 1;
    float maxHealth = 100.0f + 10.0f * (float)wave + (float)(spawnCount - 1) * 30.0f;

    for (; spawnCount > 0; --spawnCount) {
        spawnOne(maxHealth);
    }
}
