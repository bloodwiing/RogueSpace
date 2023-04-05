#include "graphics/screen.h"

#include <stdexcept>

#include <glad/glad.h>

Screen* Screen::m_active = nullptr;
bool Screen::m_wasGLLoaded = false;

Screen::Screen(int width, int height)
    : m_width(width)
    , m_height(height)
{
    m_window = glfwCreateWindow(width, height, "Testing", nullptr, nullptr);
    if (m_window == nullptr)
        throw std::runtime_error("Failed to create window");
}

Screen::~Screen() {
    glfwDestroyWindow(m_window);
}

void Screen::activate() {
    m_active = this;
    glfwMakeContextCurrent(m_window);
    if (!m_wasGLLoaded) {
        gladLoadGL();
        m_wasGLLoaded = true;
    }
    glViewport(0, 0, m_width, m_height);
}

Screen* Screen::getActive() {
    return m_active;
}

void Screen::updateSize(int width, int height) {
    glfwSetWindowSize(m_window, width, height);
    if (m_active == this)
        glViewport(0, 0, width, height);
    m_width = width;
    m_height = height;
}

int Screen::getWidth() const {
    return m_width;
}

int Screen::getHeight() const {
    return m_height;
}

GLFWwindow *Screen::getWindow() const {
    return m_window;
}

void Screen::swapBuffers() const {
    glfwSwapBuffers(m_window);
}

void Screen::close() {
    glfwSetWindowShouldClose(m_window, true);
}

bool Screen::isClosing() const {
    return glfwWindowShouldClose(m_window);
}

bool Screen::isKey(int key, int state) const {
    return glfwGetKey(m_window, key) == state;
}

bool Screen::isMouse(int button, int state) const {
    return glfwGetMouseButton(m_window, button) == state;
}

void Screen::resetMouse() const {
    glfwSetCursorPos(m_window, (float)m_width / 2, (float)m_height / 2);
}

void Screen::getAbsoluteMouse(int &x, int &y) const {
    double mouseX, mouseY;
    glfwGetCursorPos(m_window, &mouseX, &mouseY);
    x = (int)mouseX;
    y = (int)mouseY;
}

void Screen::getRelativeMouse(double &x, double &y) const {
    glfwGetCursorPos(m_window, &x, &y);
    x = (x - ((float)m_width / 2)) / (float)m_width;
    y = (y - ((float)m_height / 2)) / (float)m_height;
}
