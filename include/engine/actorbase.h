#ifndef ACTOR_BASE_CLASS_H
#define ACTOR_BASE_CLASS_H

#include <vector>

#define GLFW_INCLUDE_NONE
#include <glfw3.h>

#include <glm/glm.hpp>

#include "graphics/shader.h"

class Scene;

class ActorBase {
public:
    explicit ActorBase(ActorBase* parent);
    ~ActorBase();

    [[nodiscard]] std::vector<ActorBase*> getChildren() const;
    template<class T>
    T* addChild(Scene* scene, ActorBase* parent);
    template<class T, class... Args>
    T* addChild(Scene* scene, ActorBase* parent, Args&&... args);

    [[nodiscard]] ActorBase* getParent() const;

    virtual void update(GLFWwindow* window, double delta) {};
    virtual void draw(Shader& shader, glm::mat4 transform);

protected:
    std::vector<ActorBase*> m_children;
    ActorBase* m_parent;
};

#include "actorbase_impl.tpp"

#endif //ACTOR_BASE_CLASS_H
