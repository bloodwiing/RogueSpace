#include "jage/system/super.hpp"

#include "jage/graphics/mesh3d/material.hpp"
#include "jage/graphics/mesh2d/sprite.hpp"
#include "jage/graphics/texture.hpp"

using jage::system::Super;

std::unique_ptr<Super> Super::instance = std::unique_ptr<Super>();

Super& Super::getInstance() {
    return *instance;
}

Super::Super(int width, int height) {
    m_window = std::make_shared<jage::runtime::Window>(width, height);
    m_window->activate();
}

Super::~Super() {
    m_window->close();
    m_window.reset();
    m_window = nullptr;
}

void Super::initialise(int width, int height) {
    instance = std::make_unique<Super>(width, height);
}

void Super::destroy() {
    jage::graphics::mesh3d::Material::clearDefaultMaterial();
    instance.reset();
}

std::shared_ptr<jage::runtime::Window> Super::getWindow() {
    return m_window;
}
