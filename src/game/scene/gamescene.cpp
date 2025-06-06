#include "game/scene/gamescene.hpp"

#include "jage/node/actor/actors.hpp"
#include "jage/tags.hpp"
#include "jage/script/actor/actorscripts.hpp"

using game::scene::GameScene;
using jage::node::Scene;
using jage::Tag;
using namespace jage::node::actor;
using namespace jage::script::actor;

std::unique_ptr<Scene> GameScene::create() {
    auto scene = std::make_unique<Scene>();

//    auto sphere = scene->addChild<ModelActor>("sphere", Tag::ENVIRONMENT, "./res/model/builtin/sphere/sphere.gltf");
//    sphere->translate(glm::vec3(10.0f, 2.0f, 0.0f));

    auto player = scene->addChild<ShipActor>("Player", Tag::PLAYER);
    auto camera = player->addChild<Camera>("Camera", Tag::CAMERA, 45.0f, 0.001f, 1000.0f);
    auto cameraShakeScript = camera->attachScript<CameraShakeScript>(0.0f, 0.05f);
    camera->setActive();
    player->attachScript<WeaponScript>(60.0f, Tag::ENEMY, 3.0f);
    player->attachScript<PlayerControllerScript>(cameraShakeScript);
    player->attachScript<CollisionListenerScript>(1.0f);
    auto healthScript = player->attachScript<HealthScript>(100.0f);
    auto regenScript = player->attachScript<HealthRegenerationScript>(5.0f, 2.0f);
    healthScript.lock()->onDamage += regenScript;
    auto scoreScript = player->attachScript<ScoreScript>();

    EnemySpawnerScript::setup(scene.get(), player, scoreScript);
    EnemySpawnerScript::spawnWave();

    return scene;
}
