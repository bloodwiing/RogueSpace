#include "jage/actor/scene.hpp"

#include <iostream>

#include "jage/actor/camera.hpp"
#include "jage/actor/abc/actor_abc.hpp"
#include "jage/runtime/window.hpp"

using jage::actor::Scene;

std::string Scene::m_hierarchyDisplayName = "root";

std::string Scene::getTypeName() const {
    return "Scene";
}

Scene::Scene()
    : ActorABC(nullptr, m_hierarchyDisplayName)
    , m_freeFly(false)
    , m_freeFlyCamera(new Camera(this, nullptr, "root_freeFlyCamera"))
{ }

Utility::QuickList<std::shared_ptr<jage::actor::abc::ActorABC>> Scene::getVolatileChildren() const {
    return m_volatileActors;
}

glm::vec3 Scene::getTranslation() const {
    return glm::vec3(0.0);
}

glm::quat Scene::getRotation() const {
    return {1.0, 0.0, 0.0, 0.0};
}

glm::vec3 Scene::getScale() const {
    return glm::vec3(1.0);
}

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

    abc::ActorABC::update();

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

void Scene::draw(jage::graphics::Shader &shader) {
    abc::ActorABC::draw(shader);

    for (const auto& child : m_volatileActors) {
        if (child)
            child->draw(shader);
    }
}

bool Scene::isInFreeFlight() const {
    return m_freeFly;
}
