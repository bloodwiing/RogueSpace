#include "jage/engine.hpp"

#include "jage/runtime/time.hpp"
#include "jage/system/super.hpp"
#include "jage/runtime/asset/assetstream.hpp"
#include "jage/runtime/asset/assetmanager.hpp"
#include "jage/utility/utility.hpp"

using jage::JAGEngine;

JAGEngine JAGEngine::instance = JAGEngine();

JAGEngine::~JAGEngine() {
    m_scene.reset();
    m_canvas.reset();

    jage::runtime::asset::AssetManager::getInstance()->reset();
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

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
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

        if (m_scene) {
            m_scene->update();
            m_scene->draw();
        }

        glDisable(GL_DEPTH_TEST);

        if (m_canvas) {
            m_canvas->update();
            m_canvas->draw();
        }

        Window::getActive()->swapBuffers();

        glfwPollEvents();

        Time::waitForNextFrame();
    }
}

void JAGEngine::loadScene(std::function<std::unique_ptr<node::Scene>()> sceneGenerator) {
    if (m_scene) {
        m_scene.reset();
        m_scene = nullptr;
    }

    m_scene = sceneGenerator();
}

void JAGEngine::loadCanvas(std::function<std::unique_ptr<node::Canvas>()> canvasGenerator) {
    if (m_canvas) {
        m_canvas.reset();
        m_canvas = nullptr;
    }

    m_canvas = canvasGenerator();
}
