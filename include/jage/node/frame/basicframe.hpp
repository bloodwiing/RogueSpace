#ifndef JAGE_BASIC_CANVAS_HPP
#define JAGE_BASIC_CANVAS_HPP

#include "jage/node/frame/abc/frame_abc.hpp"

namespace jage::node::frame {

    class BasicFrame : public abc::FrameABC {
    public:
        friend class jage::node::Canvas;

        BasicFrame(JAGE_FRAME_ARGS);
        BasicFrame(JAGE_FRAME_ARGS, const type::RectF& rect, const type::RectF& anchor, glm::vec4 fill = glm::vec4(0.0f));

        type::RectF getRect() const override;
        type::RectF getAnchor() const override;
        type::RectF getPhysicalRect() const override;
        [[nodiscard]] glm::vec4 getFill() const;
        bool isDead() const override;

        void setRect(const type::RectF& rect);
        void setAnchor(const type::RectF& anchor);
        void setFill(glm::vec4 fill);

        void markDead(float wait = -1.0f);

        void update() override;

    protected:
        type::RectF m_rect;
        type::RectF m_anchor;

        type::RectF m_physicalRect;

        glm::vec4 m_fill;

        void markForReflow();

    private:
        bool m_needsRectReflow = false;

        float m_deathTimer = -1.0f;
        bool m_dead = false;
    };
}

#endif //JAGE_BASIC_CANVAS_HPP
