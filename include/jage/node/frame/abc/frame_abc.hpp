#ifndef JAGE_CANVAS_ABC_HPP
#define JAGE_CANVAS_ABC_HPP

#include "jage/node/abc/node_abc.hpp"
#include "jage/type/rect.hpp"
#include "jage/node/base/dying_base.hpp"

#define JAGE_FRAME_ARGS JAGE_NODE_ARGS(jage::node::frame::abc::FrameABC), jage::node::Canvas* canvas

namespace jage::node {
    class Canvas;
}

namespace jage::node::frame::abc {

    class FrameABC : public node::abc::NodeABC<FrameABC>, public jage::node::base::DyingBase {
    public:
        FrameABC(JAGE_FRAME_ARGS);

        [[nodiscard]] virtual jage::type::RectF getRect() const = 0;
        [[nodiscard]] virtual jage::type::RectF getAnchor() const = 0;
        [[nodiscard]] virtual jage::type::RectF getPhysicalRect() const = 0;

    private:
        Canvas* m_canvas;
    };
}

#endif //JAGE_CANVAS_ABC_HPP
