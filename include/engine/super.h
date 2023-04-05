#ifndef SUPER_CLASS_H
#define SUPER_CLASS_H

#define GLFW_INCLUDE_NONE
#include <glfw3.h>

#include "graphics/screen.h"

class Super {
public:
    static void init(int width, int height);

    static Screen* getScreen();

private:
    static Screen* m_screen;
};

#endif //SUPER_CLASS_H
