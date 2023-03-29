#ifndef SCENE_CLASS_H
#define SCENE_CLASS_H

#include <vector>

#include "actorbase.h"
#include "actor.h"

class Scene : public ActorBase {
public:
    Scene();

    template<class T>
    T *addChild();
};

#include "scene_impl.tpp"

#endif //SCENE_CLASS_H
