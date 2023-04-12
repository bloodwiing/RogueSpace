#include "engine/scene.h"

#include "graphics/camera.h"
#include "graphics/window.h"

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
}

bool Scene::isInFreeFlight() const {
    return m_freeFly;
}



// Todo: bullets