#ifndef ACTOR_BASE_CLASS_H
#define ACTOR_BASE_CLASS_H

#include <map>

#define GLFW_INCLUDE_NONE
#include <glfw3.h>

#include "glm/glm.hpp"

#include "graphics/shader.hpp"

class Scene;

class ActorBase {
protected:
    struct ChildEntry {
        ActorBase* value;
        uint16_t nameRepeat;
    };

public:
    ActorBase(Scene* scene, ActorBase* parent, std::string& name);
    ~ActorBase();

    [[nodiscard]] std::map<std::string, ChildEntry> getChildren() const;
    [[nodiscard]] ActorBase* getChild(const std::string& name) const;

    template<class T>
    T* addChild(Scene* scene, ActorBase* parent, std::string& name);
    template<class T, class... Args>
    T* addChild(Scene* scene, ActorBase* parent, std::string& name, Args&&... args);

    [[nodiscard]] ActorBase* getParent() const;

    [[nodiscard]] std::string getName() const;

    [[nodiscard]] virtual glm::mat4 getWorldMatrix() const;
    [[nodiscard]] virtual bool isDead() const;

    virtual void update();
    virtual void draw(Shader& shader);

    [[nodiscard]] std::string toHierarchyString(uint16_t indent = 0) const;

protected:
    [[nodiscard]] virtual std::string getTypeName() const;

    std::string m_name;
    std::map<std::string, ChildEntry> m_children;
    ActorBase* m_parent;

private:
    template<class T>
    void internalRegisterChild(T* child);
};

#include "actorbase_impl.tpp"

#endif //ACTOR_BASE_CLASS_H
