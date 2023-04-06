#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include "shader.h"
#include <glfw3.h>
#include <glm/glm.hpp>

#include "engine/actor/dynamicactor.h"

class Camera : public DynamicActor {
public:
    Camera(Scene *scene, ActorBase *parent, std::string name, int width, int height);
    ~Camera();

    void setOrientation(const glm::vec3& orientation, const glm::vec3& up);
    void updateMatrix(float fov_degrees, float near_plane, float far_plane);
    void applyMatrix(Shader& shader, const char* uniform);

    static Camera* getActiveCamera();
    void setActive() const;

protected:
    [[nodiscard]] std::string getTypeName() const override;

private:
    glm::vec3 m_orientation = glm::vec3(0.0f, 0.0f, -1.0f),
              m_up = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::mat4 m_matrix = glm::mat4(1.0f);

    unsigned int m_width,
                 m_height;

    static Camera* m_active;
};

#endif //CAMERA_CLASS_H
