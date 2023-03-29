#ifndef ACTOR_CLASS_H
#define ACTOR_CLASS_H

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#define GLFW_INCLUDE_NONE
#include <glfw3.h>

#include "graphics/shader.h"
#include "graphics/camera.h"
#include "./script.h"
#include "./hierarchycontainer.h"
#include "./scene.h"

class Actor : public HierarchyContainer<Scene, Actor> {
public:
    Actor(Scene* scene, Actor* parent);

    template<class T>
    T *addChild();

    virtual void update(GLFWwindow* window, double delta) {};
    virtual void draw(Shader& shader, Camera& camera) {};

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

#endif //ACTOR_CLASS_H
