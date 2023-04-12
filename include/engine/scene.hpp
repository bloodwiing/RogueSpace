#ifndef SCENE_CLASS_H
#define SCENE_CLASS_H

#include <vector>

#include "engine/actor/actorbase.hpp"
#include "engine/actor/actor.hpp"

#include "quicklist.h"

class Camera;

class Scene : public ActorBase {
public:
    Scene();

    template<class T>
    T* addChild(std::string name);
    template<class T, class... Args>
    T* addChild(std::string name, Args&&... args);

    void update() override;

    [[nodiscard]] bool isInFreeFlight() const;

protected:
    [[nodiscard]] std::string getTypeName() const override;

private:
    static std::string m_hierarchyDisplayName;


    // ----- Free Fly toggle -----

    bool m_freeFly;
    Camera* m_freeFlyCamera;

    bool m_f2Held = false;
    Camera* m_prevCamera = nullptr;
};

#include "scene_impl.tpp"

#endif //SCENE_CLASS_H
