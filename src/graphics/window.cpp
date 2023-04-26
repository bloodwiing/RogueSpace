#include "graphics/window.hpp"

#include <stdexcept>

#include <glad/glad.h>

Graphics::Window* Graphics::Window::m_active = nullptr;
bool Graphics::Window::m_wasGLLoaded = false;

Graphics::Window::Window(int width, int height)
    : m_width(width)
    , m_height(height)
{
    m_glWindow = glfwCreateWindow(width, height, "Testing", nullptr, nullptr);
    if (m_glWindow == nullptr)
        throw std::runtime_error("Failed to create window");
}

Graphics::Window::~Window() {
    glfwDestroyWindow(m_glWindow);
}

void Graphics::Window::activate() {
    m_active = this;
    glfwMakeContextCurrent(m_glWindow);
    if (!m_wasGLLoaded) {
        gladLoadGL();
        m_wasGLLoaded = true;
    }
    glViewport(0, 0, m_width, m_height);
}

Graphics::Window* Graphics::Window::getActive() {
    return m_active;
}

void Graphics::Window::updateSize(int width, int height) {
    glfwSetWindowSize(m_glWindow, width, height);
    if (m_active == this)
        glViewport(0, 0, width, height);
    m_width = width;
    m_height = height;
}

int Graphics::Window::getWidth() const {
    return m_width;
}

int Graphics::Window::getHeight() const {
    return m_height;
}

float Graphics::Window::getAspectRatio() const {
    return (float)m_width / (float)m_height;
}

GLFWwindow *Graphics::Window::getWindow() const {
    return m_glWindow;
}

void Graphics::Window::swapBuffers() const {
    if (m_glWindow == nullptr)
        return;
    glfwSwapBuffers(m_glWindow);
}

void Graphics::Window::close() {
    if (m_glWindow == nullptr)
        return;
    glfwSetWindowShouldClose(m_glWindow, true);
}

bool Graphics::Window::isClosing() const {
    if (m_glWindow == nullptr)
        return false;
    return glfwWindowShouldClose(m_glWindow);
}

bool Graphics::Window::isKey(int key, int state) const {
    if (m_glWindow == nullptr)
        return false;
    return glfwGetKey(m_glWindow, key) == state;
}

bool Graphics::Window::isMouse(int button, int state) const {
    if (m_glWindow == nullptr)
        return false;
    return glfwGetMouseButton(m_glWindow, button) == state;
}

void Graphics::Window::resetMouse() const {
    if (m_glWindow == nullptr)
        return;
    glfwSetCursorPos(m_glWindow, (float)m_width / 2, (float)m_height / 2);
}

void Graphics::Window::getAbsoluteMouse(int &x, int &y) const {
    if (m_glWindow == nullptr)
        return;
    double mouseX, mouseY;
    glfwGetCursorPos(m_glWindow, &mouseX, &mouseY);
    x = (int)mouseX;
    y = (int)mouseY;
}

void Graphics::Window::getRelativeMouse(double &x, double &y) const {
    if (m_glWindow == nullptr)
        return;
    glfwGetCursorPos(m_glWindow, &x, &y);
    x = (x - ((float)m_width / 2)) / (float)m_width;
    y = (y - ((float)m_height / 2)) / (float)m_height;
}
