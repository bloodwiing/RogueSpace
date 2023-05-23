#ifndef JAGE_BASIC_CANVAS_HPP
#define JAGE_BASIC_CANVAS_HPP

#include "jage/node/frame/abc/frame_abc.hpp"
#include "jage/graphics/mesh2d/quad2d.hpp"

namespace jage::node::frame {

    class BasicFrame
            : public abc::FrameABC {
    public:
        friend class jage::node::Canvas;

        BasicFrame(JAGE_FRAME_ARGS);

        glm::mat3 getWorldMatrix() const override;
        glm::vec2 getTranslation() const override;
        float getRotation() const override;
        glm::vec2 getScale() const override;

        void setWorldMatrix(const glm::mat3& mat) override;
        void setTranslation(const glm::vec2& tra) override;
        void setRotation(const float& rot) override;
        void setScale(const glm::vec2& sca) override;

        void update() override;

    protected:
        glm::vec2 m_translation = glm::vec2(0.0f);
        float m_rotation = 0.0f;
        glm::vec2 m_scale = glm::vec2(1.0f);
        glm::mat3 m_worldMatrix = glm::mat3(1.0f);

        bool m_needsMatrixUpdate = false;

        void updateTransformations();

        void markForMatrixUpdate();
    };
}

#endif //JAGE_BASIC_CANVAS_HPP
