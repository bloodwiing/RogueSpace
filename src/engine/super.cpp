#include "engine/super.hpp"

#include "graphics/texture.hpp"
#include "graphics/material.hpp"

std::unique_ptr<Engine::Super> Engine::Super::instance = std::unique_ptr<Engine::Super>();

Engine::Super& Engine::Super::getInstance() {
    return *instance;
}

Engine::Super::Super(int width, int height)
    : m_window(new Graphics::Window(width, height))
{
    m_window->activate();

    GLubyte whiteTextureBytes[] = {
            0xFF, 0xFF, 0xFF, 0xFF
    };
    Graphics::Texture::createDefaultTexture(whiteTextureBytes, 1, 1, 4);
}

void Engine::Super::initialise(int width, int height) {
    instance = std::make_unique<Super>(width, height);
}

Graphics::Window* Engine::Super::getWindow() {
    return m_window;
}
