#ifndef DYNAMIC_ACTOR_CLASS_H
#define DYNAMIC_ACTOR_CLASS_H

#include "engine/actor.h"

class DynamicActor : public Actor {
public:
    [[nodiscard]] glm::vec3 getTranslation() const override;
    [[nodiscard]] glm::quat getRotation() const override;
    [[nodiscard]] glm::vec3 getScale() const override;

    void setTranslation(const glm::vec3& tra);
    void setRotation(const glm::quat& rot);
    void setScale(const glm::vec3& sca);

    void translate(const glm::vec3& tra);
    void rotate(const glm::quat& rot);
    void scale(const glm::vec3& sca);

protected:
    glm::vec3 m_translation = glm::vec3(0.0f);
    glm::quat m_rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    glm::vec3 m_scale = glm::vec3(1.0f);
};

#endif //DYNAMIC_ACTOR_CLASS_H
