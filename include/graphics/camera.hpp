#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include "shader.hpp"
#include <glfw3.h>
#include <glm/glm.hpp>

#include "engine/actor/dynamicactor.hpp"

class Camera : public DynamicActor {
public:
    Camera(Scene *scene, ActorBase *parent, std::string name);
    ~Camera();

    void updateMatrix(float fov_degrees, float near_plane, float far_plane);
    void applyMatrix(Shader& shader, const char* uniform);

    static Camera* getActiveCamera();
    void setActive() const;

    void update() override;

    void copyOrientation(Camera* camera, bool copyUpVector = true);
    void freeFlyUpdate();

protected:
    [[nodiscard]] std::string getTypeName() const override;

private:
    glm::vec3 m_orientation = glm::vec3(0.0f, 0.0f, -1.0f),
              m_up = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::mat4 m_matrix = glm::mat4(1.0f);

    static Camera* m_active;

    float m_flySpeed = 1.0f;
    float m_flySensitivity = 100.0f;
    bool m_flyClicked = false;
};

#endif //CAMERA_CLASS_H
