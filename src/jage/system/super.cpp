#include "jage/system/super.hpp"

#include "jage/graphics/material.hpp"
#include "jage/graphics/texture.hpp"

using jage::system::Super;

std::unique_ptr<Super> Super::instance = std::unique_ptr<Super>();

Super& Super::getInstance() {
    return *instance;
}

Super::Super(int width, int height)
    : m_window(new jage::runtime::Window(width, height))
{
    m_window->activate();

    GLubyte whiteTextureBytes[] = {
            0xFF, 0xFF, 0xFF, 0xFF
    };
    jage::graphics::Texture::createDefaultTexture(whiteTextureBytes, 1, 1, 4);
}

Super::~Super() {
    m_window->close();
    delete m_window;
    m_window = nullptr;
}

void Super::initialise(int width, int height) {
    instance = std::make_unique<Super>(width, height);
}

void Super::destroy() {
    jage::graphics::Material::clearDefaultMaterial();
    jage::graphics::Texture::clearDefaultTexture();
    instance.reset();
}

jage::runtime::Window* Super::getWindow() {
    return m_window;
}
