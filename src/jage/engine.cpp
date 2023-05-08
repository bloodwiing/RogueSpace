#include "jage/engine.hpp"

#include <iostream>

#include "jage/runtime/time.hpp"
#include "jage/system/super.hpp"
#include "jage/runtime/assetstream.hpp"
#include "jage/actor/modelactor.hpp"
#include "jage/actor/shipactor.hpp"
#include "jage/actor/physicsactor.hpp"
#include "jage/script/playercontrollerscript.hpp"
#include "jage/script/aicontrollerscript.hpp"
#include "jage/utility/utility.hpp"

using jage::JAGEngine;

JAGEngine JAGEngine::instance = JAGEngine();

JAGEngine::JAGEngine() = default;

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

    m_shader = std::make_unique<jage::graphics::Shader>("./res/default.vert", "./res/default.frag");
}

void JAGEngine::loop() {
    using jage::runtime::Time;
    using jage::runtime::Window;

    Time::init();

    while (!Window::getActive()->isClosing()) {

        glClearColor(0.07f, 0.05f, 0.21f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Time::update();

        m_scene->update();

        if (!m_shader->isErrored()) {
            m_shader->activate();
            auto* camera = jage::actor::Camera::getActiveCamera();
            camera->updateMatrix(45.0f, 0.001f, 10000.0f);
        }

        m_scene->draw(*m_shader);

        Window::getActive()->swapBuffers();

        glfwPollEvents();

        Time::waitForNextFrame();
    }

    jage::runtime::AssetStream::shutdown();

    m_shader->destroy();
    glfwTerminate();
}

void JAGEngine::loadScene() {
    using namespace jage::actor;

    m_scene = std::make_unique<Scene>();

    auto sphere = m_scene->addChild<ModelActor>("sphere", "./res/sphere/sphere.gltf");
    sphere->translate(glm::vec3(10.0f, 2.0f, 0.0f));

    auto map = m_scene->addChild<ModelActor>("map", "./res/map/scene.gltf");
    map->translate(glm::vec3(0.0f, -7.0f, 0.0f));

    auto player = m_scene->addChild<ShipActor>("Player");
    player->attachScript<script::PlayerControllerScript>();
    auto camera = player->addChild<Camera>("Camera");
    camera->setActive();

    auto starship = m_scene->addChild<ShipActor>("Starship");
    starship->scale(glm::vec3(0.50f));
    auto controller = starship->attachScript<script::AIControllerScript>();
    controller->setTarget(player);
    try {
        auto starship_model = starship->addChild<ModelActor>("model", "./res/starship/Starship01.gltf");
    } catch (std::exception& e) {
        std::cerr << e.what();
    }
    starship->translate(glm::vec3(4.0f, 0.0f, 0.0f));

    auto starship2 = m_scene->addChild<ShipActor>("Starship2");
    starship2->scale(glm::vec3(0.50f));
    auto controller2 = starship2->attachScript<script::AIControllerScript>();
    controller2->setTarget(player);
    try {
        auto starship_model = starship2->addChild<ModelActor>("model2", "./res/bullet/BulletTemp.gltf");
    } catch (std::exception& e) {
        std::cerr << e.what();
    }
    starship2->translate(glm::vec3(4.0f, 0.0f, 4.0f));
    starship2->setScale(glm::vec3(10.0f));
//    starship->rotate(glm::quat(glm::vec3(0.0f, 0.0f, glm::pi<float>() / 2.0f)));
//    starship->setLinearVelocity(glm::vec3(10.0f, 0.0f, 0.0f));

    std::cout << m_scene.get();
}
