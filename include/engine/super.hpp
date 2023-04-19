#ifndef SUPER_CLASS_H
#define SUPER_CLASS_H

#define GLFW_INCLUDE_NONE
#include <glfw3.h>

#include "graphics/window.hpp"

/// \brief      The main Static container for accessing important aspects
class Super {
public:
    /// \brief          Begins the initialisation process of important systems and creates a Window
    /// \param width    The width of the Window
    /// \param height   The height of the Window
    static void init(int width, int height);

    /// \return         The created Window during the game's initialisation process
    static Window* getWindow();

private:
    /// The created Window
    static Window* m_window;
};

#endif //SUPER_CLASS_H
