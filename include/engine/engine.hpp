#ifndef ENGINE_CLASS_H
#define ENGINE_CLASS_H

#include <memory>

#include "graphics/shader.hpp"

#include "engine/scene.hpp"

namespace Engine {

    class JAGEngine {
    public:
        static JAGEngine& getInstance();

        void init();
        void loop();

        void loadScene();

    private:
        static JAGEngine instance;

        JAGEngine();

        std::unique_ptr<Graphics::Shader> m_shader;
        std::unique_ptr<Scene> m_scene;

        const int width = 1366,
                  height = 700,
                  framerate = 60;
    };
}

#endif //ENGINE_CLASS_H
