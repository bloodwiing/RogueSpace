#ifndef JAGE_CANVAS_HPP
#define JAGE_CANVAS_HPP

#include "jage/node/abc/node_abc.hpp"
#include "jage/node/frame/abc/frame_abc.hpp"

namespace jage::node {

    class Canvas : public frame::abc::FrameABC {
    public:
        explicit Canvas(const jage::type::RectF& rect);

        type::RectF getRect() const override;
        type::RectF getAnchor() const override;
        type::RectF getPhysicalRect() const override;

        void update() override;

    private:
        jage::type::RectF m_rect;
        jage::type::RectF m_screenRect;

        jage::type::Rect<int> m_prevScreenRect = type::Rect<int>();
    };
}

#endif //JAGE_CANVAS_HPP
