#ifndef SCENE_CLASS_H
#define SCENE_CLASS_H

#include <vector>

#include "hierarchycontainer.h"
#include "actor.h"

class Scene : public HierarchyContainer<Scene, Actor> {
public:
    Scene();

    template<class T>
    T *addChild();
};

#endif //SCENE_CLASS_H
