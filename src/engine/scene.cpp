#include "engine/scene.h"

Scene::Scene()
    : HierarchyContainer<Scene, Actor>(nullptr)
{ }

template<class T>
T *Scene::addChild() {
    HierarchyContainer::addChild<T>(this, nullptr);
}
