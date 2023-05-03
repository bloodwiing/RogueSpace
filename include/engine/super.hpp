#ifndef SUPER_CLASS_H
#define SUPER_CLASS_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <memory>

#include "graphics/window.hpp"

namespace Engine {

    /// \brief      The main Static container for accessing important aspects
    class Super {
    public:
        Super(int width, int height);

        [[nodiscard]] static Engine::Super& getInstance();

        static void initialise(int width, int height);

        /// \return         The created Window during the game's initialisation process
        Graphics::Window* getWindow();

    private:
        static std::unique_ptr<Engine::Super> instance;

        /// The created Window
        Graphics::Window* m_window;
    };
}

#endif //SUPER_CLASS_H
