#include "utils.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <fstream>
#include <limits>
#include <algorithm>
#include <iostream>

void glfwErrorCallback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
};

void initializeOpenGL() {
    glfwSetErrorCallback(glfwErrorCallback);
    if (glfwInit() == GLFW_FALSE) {
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

std::string readFileContents(std::string filename, std::ios_base::openmode mode /* = std::ios_base::in */) {
#if _WIN32
    if (filename.find(':') == std::string::npos)
        filename = getProcessDirectory() + filename;
#elif __unix__
    if (filename[0] != '/')
        filename = getProcessDirectory() + filename;
#endif

    std::ifstream stream(filename, mode);

    stream.ignore(std::numeric_limits<std::streamsize>::max());
    auto size = stream.gcount();
    stream.seekg(0, std::ios::beg);
    stream.clear();

    std::string result(size, '\0');
    stream.read(&result[0], size);

    if (!(mode & std::ios::binary))
        unixifyLineEndings(result);

    return result;
}

#define MAX_PATH 2048

#if _WIN32
#include <windows.h>
std::string getProcessDirectory() {
    char path[MAX_PATH];
    std::string res(path, GetModuleFileName(nullptr, path, MAX_PATH));
    std::replace(res.begin(), res.end(), '\\', '/');
    return res.substr(0, res.find_last_of('/') + 1);
}
#elif __unix__
#include <climits>
#include <unistd.h>
std::string getProcessDirectory() {
    char path[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", path, PATH_MAX);
    std::string res(path, (count > 0) ? count : 0);
    return res.substr(0, res.find_last_of('/') + 1);
}
#endif

void unixifyLineEndings(std::string &text) {
    std::string::size_type pos = 0;
    while ((pos = text.find("\r\n", pos)) != std::string::npos )
        text.erase(pos, 1);
}
