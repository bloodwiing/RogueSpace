#ifndef ACTOR_CLASS_H
#define ACTOR_CLASS_H

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "./script.h"
#include "./scene.h"

class ActorBase;

class Actor : public ActorBase {
public:
    Actor(Scene* scene, ActorBase* parent);

    template<class T>
    T* addChild();
    template<class T, class... Args>
    T* addChild(Args&&... args);

    [[nodiscard]] std::string getName() const;

    [[nodiscard]] Scene* getScene() const;

    [[nodiscard]] virtual glm::vec3 getTranslation() const;
    [[nodiscard]] virtual glm::quat getRotation() const;
    [[nodiscard]] virtual glm::vec3 getScale() const;

protected:
    std::string m_name;
    std::vector<Script> m_scripts;

    Scene* m_scene;
};

#include "actor_impl.tpp"

#endif //ACTOR_CLASS_H
