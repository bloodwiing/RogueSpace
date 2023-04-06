#include "engine/scene.h"

std::string Scene::m_sceneName = "root";

Scene::Scene()
    : ActorBase(nullptr, nullptr, m_sceneName)
{ }

// Todo: bullets