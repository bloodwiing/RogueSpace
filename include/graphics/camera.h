#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include "shader.h"
#include <glfw3.h>
#include <glm/glm.hpp>

class Camera {
public:
    Camera(unsigned int width, unsigned int height, glm::vec3 position);

    void applyMVP(float fov_degrees, float near_plane, float far_plane, Shader& shader, const char* uniform);
    void handleInputs(GLFWwindow* window, float delta);

private:
    glm::vec3 position,
              orientation = glm::vec3(0.0f, 0.0f, -1.0f),
              up = glm::vec3(0.0f, 1.0f, 0.0f);

    unsigned int width,
                 height;

    float speed = 1.0f,
          sensitivity = 100000.0f;

    bool clicked = false;
};

#endif //CAMERA_CLASS_H
