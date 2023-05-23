#include "jage/utility/utility.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace utility = jage::utility;

void glfwErrorCallback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

void utility::initializeOpenGL() {
    glfwSetErrorCallback(glfwErrorCallback);
    if (glfwInit() == GLFW_FALSE) {
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
