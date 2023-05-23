#include "jage/engine.hpp"

#include <iostream>

#include "jage/runtime/time.hpp"
#include "jage/system/super.hpp"
#include "jage/runtime/asset/assetstream.hpp"
#include "jage/node/actor/modelactor.hpp"
#include "jage/node/actor/shipactor.hpp"
#include "jage/node/actor/physicsactor.hpp"
#include "jage/node/frame/basicframe.hpp"
#include "jage/script/playercontrollerscript.hpp"
#include "jage/script/aicontrollerscript.hpp"
#include "jage/script/weaponscript.hpp"
#include "jage/script/colliderscript.hpp"
#include "jage/script/collisionreceiverscript.hpp"
#include "jage/script/healthscript.hpp"
#include "jage/utility/utility.hpp"

using jage::JAGEngine;

JAGEngine JAGEngine::instance = JAGEngine();

JAGEngine::~JAGEngine() {
    m_scene.reset();
    m_canvas.reset();

    jage::system::Super::destroy();

    jage::runtime::asset::AssetStream::shutdown();

    glfwTerminate();
}

JAGEngine &JAGEngine::getInstance() {
    return instance;
}

void JAGEngine::init() {
    utility::initializeOpenGL();

    jage::system::Super::initialise(width, height);
    jage::runtime::Time::setMaxFramerate(framerate);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}

void JAGEngine::loop() {
    using jage::runtime::Time;
    using jage::runtime::Window;

    Time::init();

    while (!Window::getActive()->isClosing()) {

        glClearColor(0.005f, 0.008f, 0.058f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        Time::update();

        m_scene->update();
        m_scene->draw();

        glDisable(GL_DEPTH_TEST);

        m_canvas->update();
        m_canvas->draw();

        Window::getActive()->swapBuffers();

        glfwPollEvents();

        Time::waitForNextFrame();
    }
}

void JAGEngine::loadScene() {
    using namespace jage::node::actor;
    using namespace jage::node::frame;

    m_scene = std::make_unique<jage::node::Scene>();

    // 3D

    auto sphere = m_scene->addChild<ModelActor>("sphere", Tag::ENVIRONMENT, "./res/sphere/sphere.gltf");
    sphere->translate(glm::vec3(10.0f, 2.0f, 0.0f));

//    auto map = m_scene->addChild<ModelActor>("map", "./res/map/scene.gltf");
//    map->translate(glm::vec3(0.0f, -7.0f, 0.0f));

    auto player = m_scene->addChild<ShipActor>("Player", Tag::PLAYER);
    auto camera = player->addChild<Camera>("Camera", Tag::CAMERA, 45.0f, 0.001f, 1000.0f);
    auto cameraShakeScript = camera->attachScript<script::CameraShakeScript>(0.0f, 0.05f);
    camera->setActive();
    player->attachScript<script::WeaponScript>(60.0f, Tag::ENEMY);
    player->attachScript<script::PlayerControllerScript>(cameraShakeScript);
    player->attachScript<script::CollisionReceiverScript>(1.0f);
    player->attachScript<script::HealthScript>(100.0f);

    auto starship = m_scene->addChild<ShipActor>("Starship", Tag::ENEMY);
    starship->attachScript<script::WeaponScript>(60.0f, Tag::PLAYER);
    starship->attachScript<script::CollisionReceiverScript>(1.0f);
    starship->attachScript<script::HealthScript>(100.0f);
    auto controller = starship->attachScript<script::AIControllerScript>();
    controller->setTarget(player);
    try {
        auto starship_model = starship->addChild<ModelActor>("model", Tag::MESH, "./res/starship/Starship01.gltf");
    } catch (std::exception& e) {
        std::cerr << e.what();
    }
    starship->translate(glm::vec3(100.0f, 0.0f, 0.0f));

    std::cout << m_scene.get();

    // 2D

    m_canvas = std::make_unique<jage::node::Canvas>(type::RectI32(1000, 1000));

    m_canvas->addChild<BasicFrame>("Test", type::RectI32(500, 500), type::RectF(0.5f, 0.5f));
}
