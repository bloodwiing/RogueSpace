#ifndef SUPER_CLASS_H
#define SUPER_CLASS_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <memory>

#include "jage/runtime/window.hpp"

namespace jage::system {

    /// \brief      The main Static container for accessing important aspects
    class Super {
    public:
        Super(int width, int height);

        [[nodiscard]] static Super& getInstance();

        static void initialise(int width, int height);

        /// \return         The created Window during the game's initialisation process
        jage::runtime::Window* getWindow();

    private:
        static std::unique_ptr<Super> instance;

        /// The created Window
        jage::runtime::Window* m_window;
    };
}

#endif //SUPER_CLASS_H
