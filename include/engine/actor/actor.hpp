#ifndef ACTOR_CLASS_H
#define ACTOR_CLASS_H

#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

#include "engine/script.hpp"
#include "engine/scene.hpp"

class ActorBase;

class Actor : public ActorBase {
public:
    Actor(Scene* scene, ActorBase* parent, std::string name);

    template<class T>
    T* addChild(std::string name);
    template<class T, class... Args>
    T* addChild(std::string name, Args&&... args);

    [[nodiscard]] Scene* getScene() const;

    [[nodiscard]] virtual glm::vec3 getTranslation() const;
    [[nodiscard]] virtual glm::quat getRotation() const;
    [[nodiscard]] virtual glm::vec3 getScale() const;

    virtual void setTranslation(const glm::vec3& tra) {};
    virtual void setRotation(const glm::quat& rot) {};
    virtual void setScale(const glm::vec3& sca) {};

    void draw(Shader &shader) override;

protected:
    [[nodiscard]] std::string getTypeName() const override;

    Scene* m_scene;

    std::vector<Script> m_scripts;
};

#include "actor_impl.tpp"

#endif //ACTOR_CLASS_H
