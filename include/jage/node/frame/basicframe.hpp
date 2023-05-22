#ifndef JAGE_BASIC_CANVAS_HPP
#define JAGE_BASIC_CANVAS_HPP

#include "jage/node/frame/abc/frame_abc.hpp"

namespace jage::node::frame {

    class BasicFrame
            : public abc::FrameABC {
    public:
        friend class jage::node::Canvas;

        BasicFrame(JAGE_FRAME_ARGS);
        BasicFrame(JAGE_FRAME_ARGS, const type::RectF& rect, const type::RectF& anchor, glm::vec4 fill = glm::vec4(0.0f));

        type::RectF getRect() const override;
        type::RectF getAnchor() const override;
        type::RectF getPhysicalRect() const override;
        [[nodiscard]] glm::vec4 getFill() const;

        glm::mat3 getWorldMatrix() const override;

        glm::vec2 getTranslation() const override;
        float getRotation() const override;
        glm::vec2 getScale() const override;

        void setTranslation(const glm::vec2 &tra) override;
        void setRotation(const float &rot) override;
        void setScale(const glm::vec2 &sca) override;

        void setRect(const type::RectF& rect);
        void setAnchor(const type::RectF& anchor);
        void setFill(glm::vec4 fill);

        void update() override;

    protected:
        type::RectF m_rect;
        type::RectF m_anchor;

        type::RectF m_physicalRect;

        glm::vec4 m_fill;

        glm::vec2 m_translation = glm::vec2(0.0f);
        float m_rotation = 0.0f;
        glm::vec2 m_scale = glm::vec2(1.0f);
        glm::mat3 m_worldMatrix = glm::mat3(1.0f);

        bool m_needsMatrixUpdate = false;

        void updateReflow();
        void updateTransformations();

        void markForMatrixUpdate();
        void markForReflow();

    private:
        bool m_needsRectReflow = false;
    };
}

#endif //JAGE_BASIC_CANVAS_HPP
