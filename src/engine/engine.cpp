#include "engine/engine.hpp"

#include <iostream>

#include "engine/time.hpp"
#include "engine/super.hpp"
#include "engine/assetstream.hpp"

#include "engine/actor/modelactor.hpp"
#include "engine/actor/playeractor.hpp"
#include "engine/actor/physicsactor.hpp"

#include "utils.hpp"

Engine::JAGEngine Engine::JAGEngine::instance = JAGEngine();

Engine::JAGEngine::JAGEngine() = default;

Engine::JAGEngine &Engine::JAGEngine::getInstance() {
    return instance;
}

void Engine::JAGEngine::init() {
    Utility::initializeOpenGL();

    Super::initialise(width, height);
    Time::setMaxFramerate(144);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    m_shader = std::make_unique<Graphics::Shader>("./res/default.vert", "./res/default.frag");
}

void Engine::JAGEngine::loop() {
    Time::init();

    while (!Graphics::Window::getActive()->isClosing()) {

        glClearColor(0.07f, 0.05f, 0.21f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Time::update();

        m_scene->update();

        if (!m_shader->isErrored()) {
            m_shader->activate();
            auto* camera = Graphics::Camera::getActiveCamera();
            camera->updateMatrix(45.0f, 0.001f, 10000.0f);
        }

        m_scene->draw(*m_shader);

        Graphics::Window::getActive()->swapBuffers();

        glfwPollEvents();

        Time::waitForNextFrame();
    }

    AssetStream::shutdown();

    m_shader->destroy();
    glfwTerminate();
}

void Engine::JAGEngine::loadScene() {
    using namespace Actors;

    m_scene = std::make_unique<Scene>();

    auto sphere = m_scene->addChild<ModelActor>("sphere", "./res/sphere/sphere.gltf");
    sphere->translate(glm::vec3(10.0f, 2.0f, 0.0f));

    auto map = m_scene->addChild<ModelActor>("map", "./res/map/scene.gltf");
    map->translate(glm::vec3(0.0f, -7.0f, 0.0f));

    auto player = m_scene->addChild<PlayerActor>("Player");
    auto camera = player->addChild<Graphics::Camera>("Camera");
    camera->setActive();

    auto starship = m_scene->addChild<PhysicsActor>("Starship", 1.0f, 1.0f);
    starship->scale(glm::vec3(0.50f));
    try {
        auto starship_model = starship->addChild<ModelActor>("model", "./res/starship/Starship01.gltf");
    } catch (std::exception& e) {
        std::cerr << e.what();
    }
    starship->setWeight(0.5f);
    starship->translate(glm::vec3(4.0f, 0.0f, 0.0f));
    starship->rotate(glm::quat(glm::vec3(0.0f, 0.0f, glm::pi<float>() / 2.0f)));
//    starship->setLinearVelocity(glm::vec3(10.0f, 0.0f, 0.0f));

    std::cout << m_scene.get();
}
