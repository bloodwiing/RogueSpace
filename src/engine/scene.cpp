#include "engine/scene.hpp"

#include <iostream>

#include "graphics/camera.hpp"
#include "graphics/window.hpp"

std::string Scene::m_hierarchyDisplayName = "root";

std::string Scene::getTypeName() const {
    return "Scene";
}

Scene::Scene()
    : ActorBase(nullptr, nullptr, m_hierarchyDisplayName)
    , m_freeFly(false)
    , m_freeFlyCamera(new Camera(this, nullptr, "root_freeFlyCamera"))
{ }

void Scene::update() {
    if (!m_f2Held and IS_KEY(GLFW_KEY_F2, GLFW_PRESS)) {
        m_f2Held = true;

        if (!m_freeFly) {
            m_prevCamera = Camera::getActiveCamera();
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

void Scene::draw(Shader &shader) {
    ActorBase::draw(shader);

    for (const auto& child : m_volatileActors) {
        if (child)
            child->draw(shader);
    }
}

bool Scene::isInFreeFlight() const {
    return m_freeFly;
}
