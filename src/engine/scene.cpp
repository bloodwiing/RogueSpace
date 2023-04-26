#include "engine/scene.hpp"

#include <iostream>

#include "graphics/camera.hpp"
#include "graphics/window.hpp"

std::string Engine::Scene::m_hierarchyDisplayName = "root";

std::string Engine::Scene::getTypeName() const {
    return "Scene";
}

Engine::Scene::Scene()
    : ActorBase(nullptr, nullptr, m_hierarchyDisplayName)
    , m_freeFly(false)
    , m_freeFlyCamera(new Graphics::Camera(this, nullptr, "root_freeFlyCamera"))
{ }

Utility::QuickList<std::shared_ptr<Engine::Actors::ActorBase>> Engine::Scene::getVolatileChildren() const {
    return m_volatileActors;
}

void Engine::Scene::update() {
    if (!m_f2Held and IS_KEY(GLFW_KEY_F2, GLFW_PRESS)) {
        m_f2Held = true;

        if (!m_freeFly) {
            m_prevCamera = Graphics::Camera::getActiveCamera();
            m_freeFlyCamera->copyOrientation(m_prevCamera, false);
            m_freeFlyCamera->setMatrix(m_prevCamera->getWorldMatrix());
            m_freeFlyCamera->setActive();
        } else {
            m_prevCamera->setActive();
            m_prevCamera = nullptr;
        }

        m_freeFly = !m_freeFly;
    }
    else if (m_f2Held and IS_KEY(GLFW_KEY_F2, GLFW_RELEASE)) {
        m_f2Held = false;
    }

    if (m_freeFly) {
        m_freeFlyCamera->freeFlyUpdate();
    }

    ActorBase::update();

    for (auto iter = m_volatileActors.begin(); iter != m_volatileActors.end();) {
        auto& child = *iter;
        if (child) {
            try {
                child->update();
            } catch (std::exception& e) {
                std::cerr << e.what();
                child.reset();
                iter.safeRemove();
                continue;
            }
            if (child->isDead()) {
                child.reset();
                iter.safeRemove();
            }
        } else {
            child.reset();
            iter.safeRemove();
        }
        ++iter;
    }
}

void Engine::Scene::draw(Graphics::Shader &shader) {
    ActorBase::draw(shader);

    for (const auto& child : m_volatileActors) {
        if (child)
            child->draw(shader);
    }
}

bool Engine::Scene::isInFreeFlight() const {
    return m_freeFly;
}
