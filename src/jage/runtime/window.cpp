#include "jage/runtime/window.hpp"

#include <stdexcept>
#include <glad/glad.h>

using jage::runtime::Window;

std::shared_ptr<Window> Window::m_active = nullptr;
bool Window::m_wasGLLoaded = false;

void glfwWindowResizeCallback(GLFWwindow* window, int width, int height) {
    if (Window::getActive()->getWindow() == window) {
        Window::getActive()->updateSize(width, height);
    }
}

Window::Window(int width, int height)
    : m_width(width)
    , m_height(height)
{
    m_glWindow = glfwCreateWindow(width, height, "Testing", nullptr, nullptr);
    if (m_glWindow == nullptr)
        throw std::runtime_error("Failed to create window");
}

Window::~Window() {
    if (glfwGetCurrentContext() == m_glWindow)
        glfwMakeContextCurrent(nullptr);
    glfwDestroyWindow(m_glWindow);
}

void Window::activate() {
    m_active = shared_from_this();
    glfwMakeContextCurrent(m_glWindow);
    if (!m_wasGLLoaded) {
        gladLoadGL();
        m_wasGLLoaded = true;
    }
    glViewport(0, 0, m_width, m_height);
    glfwSetWindowSizeCallback(m_glWindow, glfwWindowResizeCallback);
}

std::shared_ptr<Window> Window::getActive() {
    return m_active;
}

void Window::resize(int width, int height) {
    glfwSetWindowSize(m_glWindow, width, height);
    updateSize(width, height);
}

void Window::updateSize(int width, int height) {
    m_width = width;
    m_height = height;
    if (m_active == shared_from_this())
        glViewport(0, 0, width, height);
}

int Window::getWidth() const {
    return m_width;
}

int Window::getHeight() const {
    return m_height;
}

jage::type::RectI32 Window::getRect() const {
    return {m_width, m_height};
}

float Window::getAspectRatio() const {
    return (float)m_width / (float)m_height;
}

GLFWwindow *Window::getWindow() const {
    return m_glWindow;
}

void Window::swapBuffers() const {
    if (m_glWindow == nullptr)
        return;
    glfwSwapBuffers(m_glWindow);
}

void Window::close() {
    if (m_glWindow == nullptr)
        return;
    glfwSetWindowShouldClose(m_glWindow, true);
}

bool Window::isClosing() const {
    if (m_glWindow == nullptr)
        return false;
    return glfwWindowShouldClose(m_glWindow);
}

bool Window::isKey(int key, int state) const {
    if (m_glWindow == nullptr)
        return false;
    return glfwGetKey(m_glWindow, key) == state;
}

bool Window::isMouse(int button, int state) const {
    if (m_glWindow == nullptr)
        return false;
    return glfwGetMouseButton(m_glWindow, button) == state;
}

void Window::resetMouse() const {
    if (m_glWindow == nullptr)
        return;
    glfwSetCursorPos(m_glWindow, (float)m_width / 2, (float)m_height / 2);
}

void Window::getAbsoluteMouse(int &x, int &y) const {
    if (m_glWindow == nullptr)
        return;
    double mouseX, mouseY;
    glfwGetCursorPos(m_glWindow, &mouseX, &mouseY);
    x = (int)mouseX;
    y = m_height - (int)mouseY;
}

void Window::getScreenMouse(double &x, double &y) const {
    if (m_glWindow == nullptr)
        return;
    glfwGetCursorPos(m_glWindow, &x, &y);
    x = x * 2 - m_width;
    y = - y * 2 + m_height;
}

void Window::getRelativeMouse(double &x, double &y) const {
    if (m_glWindow == nullptr)
        return;
    glfwGetCursorPos(m_glWindow, &x, &y);
    double bounds = (m_width > m_height ? (double)m_height : (double)m_width);
    x = (x - ((double)m_width) * 0.5) / bounds;
    y = - (y - ((double)m_height) * 0.5) / bounds;
}
