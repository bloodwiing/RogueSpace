#include "engine/super.hpp"

Graphics::Window* Engine::Super::m_window = nullptr;

void Engine::Super::init(int width, int height) {
    m_window = new Graphics::Window(width, height);
    if (m_window != nullptr)
        m_window->activate();
}

Graphics::Window* Engine::Super::getWindow() {
    return m_window;
}
