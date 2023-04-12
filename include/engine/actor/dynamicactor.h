#ifndef DYNAMIC_ACTOR_CLASS_H
#define DYNAMIC_ACTOR_CLASS_H

#include "actor.h"

class DynamicActor : public Actor {
public:
    DynamicActor(Scene* scene, ActorBase* parent, std::string name);

    void update() override;

    [[nodiscard]] glm::vec3 getTranslation() const override;
    [[nodiscard]] glm::quat getRotation() const override;
    [[nodiscard]] glm::vec3 getScale() const override;

    [[nodiscard]] glm::mat4 getWorldMatrix() const override;

    void setTranslation(const glm::vec3& tra) override;
    void setRotation(const glm::quat& rot) override;
    void setScale(const glm::vec3& sca) override;
    void setMatrix(const glm::mat4& mat);

    void translate(const glm::vec3& tra);
    void rotate(const glm::quat& rot);
    void scale(const glm::vec3& sca);

    void flagForMatrixUpdate();

protected:
    [[nodiscard]] std::string getTypeName() const override;

private:
    glm::vec3 m_translation = glm::vec3(0.0f);
    glm::quat m_rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    glm::vec3 m_scale = glm::vec3(1.0f);

    glm::mat4 m_worldMatrix = glm::mat4(1.0f);

    bool m_needsMatrixUpdate = false;
};

#endif //DYNAMIC_ACTOR_CLASS_H
