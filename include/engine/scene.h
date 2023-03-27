#ifndef SCENE_CLASS_H
#define SCENE_CLASS_H

#include <vector>

#include "actor.h"

class Scene {
private:
    std::vector<Actor> m_actors;
};

#endif //SCENE_CLASS_H
