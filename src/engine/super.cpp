#include "engine/super.hpp"

#include "graphics/material.hpp"

Graphics::Window* Engine::Super::m_window = nullptr;

void Engine::Super::init(int width, int height) {
    m_window = new Graphics::Window(width, height);
    if (m_window != nullptr)
        m_window->activate();

    Graphics::Material::createDefaultMaterial("Default");
}

Graphics::Window* Engine::Super::getWindow() {
    return m_window;
}
