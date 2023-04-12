#include "graphics/window.h"

#include <stdexcept>

#include <glad/glad.h>

Window* Window::m_active = nullptr;
bool Window::m_wasGLLoaded = false;

Window::Window(int width, int height)
    : m_width(width)
    , m_height(height)
{
    m_glWindow = glfwCreateWindow(width, height, "Testing", nullptr, nullptr);
    if (m_glWindow == nullptr)
        throw std::runtime_error("Failed to create window");
}

Window::~Window() {
    glfwDestroyWindow(m_glWindow);
}

void Window::activate() {
    m_active = this;
    glfwMakeContextCurrent(m_glWindow);
    if (!m_wasGLLoaded) {
        gladLoadGL();
        m_wasGLLoaded = true;
    }
    glViewport(0, 0, m_width, m_height);
}

Window* Window::getActive() {
    return m_active;
}

void Window::updateSize(int width, int height) {
    glfwSetWindowSize(m_glWindow, width, height);
    if (m_active == this)
        glViewport(0, 0, width, height);
    m_width = width;
    m_height = height;
}

int Window::getWidth() const {
    return m_width;
}

int Window::getHeight() const {
    return m_height;
}

float Window::getAspectRatio() const {
    return (float)m_width / (float)m_height;
}

GLFWwindow *Window::getWindow() const {
    return m_glWindow;
}

void Window::swapBuffers() const {
    glfwSwapBuffers(m_glWindow);
}

void Window::close() {
    glfwSetWindowShouldClose(m_glWindow, true);
}

bool Window::isClosing() const {
    return glfwWindowShouldClose(m_glWindow);
}

bool Window::isKey(int key, int state) const {
    return glfwGetKey(m_glWindow, key) == state;
}

bool Window::isMouse(int button, int state) const {
    return glfwGetMouseButton(m_glWindow, button) == state;
}

void Window::resetMouse() const {
    glfwSetCursorPos(m_glWindow, (float)m_width / 2, (float)m_height / 2);
}

void Window::getAbsoluteMouse(int &x, int &y) const {
    double mouseX, mouseY;
    glfwGetCursorPos(m_glWindow, &mouseX, &mouseY);
    x = (int)mouseX;
    y = (int)mouseY;
}

void Window::getRelativeMouse(double &x, double &y) const {
    glfwGetCursorPos(m_glWindow, &x, &y);
    x = (x - ((float)m_width / 2)) / (float)m_width;
    y = (y - ((float)m_height / 2)) / (float)m_height;
}
