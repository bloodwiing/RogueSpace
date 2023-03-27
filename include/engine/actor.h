#ifndef ACTOR_CLASS_H
#define ACTOR_CLASS_H

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#define GLFW_INCLUDE_NONE
#include <glfw3.h>

#include "graphics/shader.h"
#include "graphics/camera.h"

class Actor {
public:
    virtual void update(GLFWwindow* window, double delta) {};
    virtual void draw(Shader& shader, Camera& camera) {};

    [[nodiscard]] glm::vec3 getPosition() const;

protected:
    glm::vec3 m_position;
    glm::quat m_rotation;
    glm::vec3 m_scale;

    std::vector<Actor> m_children;
    std::string m_name;
};

#endif //ACTOR_CLASS_H
