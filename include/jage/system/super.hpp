#ifndef JAGE_SUPER_HPP
#define JAGE_SUPER_HPP

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <memory>

#include "jage/runtime/window.hpp"

namespace jage::system {

    /// \brief      The main Static container for accessing important aspects
    class Super {
    public:
        Super(int width, int height);
        ~Super();

        [[nodiscard]] static Super& getInstance();

        static void initialise(int width, int height);
        static void destroy();

        /// \return         The created Window during the game's initialisation process
        std::shared_ptr<jage::runtime::Window> getWindow();

    private:
        Super(const Super& ref);

        static std::unique_ptr<Super> instance;

        /// The created Window
        std::shared_ptr<jage::runtime::Window> m_window;

        Super& operator=(const Super& ref);
    };
}

#endif //JAGE_SUPER_HPP
