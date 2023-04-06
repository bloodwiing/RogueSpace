#ifndef SCENE_CLASS_H
#define SCENE_CLASS_H

#include <vector>

#include "engine/actor/actorbase.h"
#include "engine/actor/actor.h"

#include "quicklist.h"

class Scene : public ActorBase {
public:
    Scene();

    template<class T>
    T* addChild(std::string name);
    template<class T, class... Args>
    T* addChild(std::string name, Args&&... args);

private:
    static std::string m_sceneName;
};

#include "scene_impl.tpp"

#endif //SCENE_CLASS_H
