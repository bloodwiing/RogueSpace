#include "utils.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <fstream>
#include <limits>

void initializeOpenGL() {
#ifndef OPENGL_INITIALIZED
#define OPENGL_INITIALIZED
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
}

std::string readFileContents(const std::string &filename, std::ios_base::openmode mode /* = std::ios_base::in */) {
    std::ifstream stream(filename, mode);

    stream.ignore(std::numeric_limits<std::streamsize>::max());
    auto size = stream.gcount();
    stream.seekg(0, std::ios::beg);
    stream.clear();

    std::string result(size, '\0');
    stream.read(&result[0], size);

    return result;
}
