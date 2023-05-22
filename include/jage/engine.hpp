#ifndef JAGE_ENGINE_HPP
#define JAGE_ENGINE_HPP

#include <memory>

#include "jage/graphics/shader.hpp"
#include "jage/node/scene.hpp"
#include "jage/node/canvas.hpp"

namespace jage {

    class JAGEngine {
    public:
        static JAGEngine& getInstance();

        void init();
        void loop();

        void loadScene();

    private:
        static JAGEngine instance;

        JAGEngine() = default;
        ~JAGEngine();

        std::unique_ptr<jage::graphics::Shader> m_shader;
        std::unique_ptr<jage::node::Scene> m_scene;
        std::unique_ptr<jage::node::Canvas> m_canvas;

        const int width = 1366,
                  height = 700,
                  framerate = 60;
    };
}

#endif //JAGE_ENGINE_HPP
