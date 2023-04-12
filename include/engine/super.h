#ifndef SUPER_CLASS_H
#define SUPER_CLASS_H

#define GLFW_INCLUDE_NONE
#include <glfw3.h>

#include "graphics/window.h"

class Super {
public:
    static void init(int width, int height);

    static Window* getWindow();

private:
    static Window* m_window;
};

#endif //SUPER_CLASS_H
