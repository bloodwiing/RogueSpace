#include "engine/super.hpp"

#include "graphics/texture.hpp"
#include "graphics/material.hpp"

Graphics::Window* Engine::Super::m_window = nullptr;

void Engine::Super::init(int width, int height) {
    m_window = new Graphics::Window(width, height);
    if (m_window != nullptr)
        m_window->activate();

    GLubyte whiteTextureBytes[] = {
            0xFF, 0xFF, 0xFF, 0xFF
    };
    Graphics::Texture::createDefaultTexture(whiteTextureBytes, 1, 1, 4);
}

Graphics::Window* Engine::Super::getWindow() {
    return m_window;
}
