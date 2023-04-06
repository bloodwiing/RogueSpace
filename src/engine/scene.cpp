#include "engine/scene.h"

std::string Scene::m_sceneName = "root";

std::string Scene::getTypeName() const {
    return "Scene";
}

Scene::Scene()
    : ActorBase(nullptr, nullptr, m_sceneName)
{ }

// Todo: bullets