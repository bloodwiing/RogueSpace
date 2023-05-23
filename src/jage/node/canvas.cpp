#include "jage/node/canvas.hpp"

#include "jage/runtime/window.hpp"
#include "jage/node/frame/basicframe.hpp"

using jage::node::Canvas;

Canvas::Canvas(const jage::type::RectI32& rect)
    : abc::NodeABC<frame::abc::FrameABC>(nullptr, "root canvas")
    , m_rect(rect)
{

}

jage::type::RectI32 Canvas::getRect() const {
    return m_rect;
}

jage::type::RectF Canvas::getAnchor() const {
    return {1.0f, 1.0f};
}

jage::type::RectF Canvas::getPhysicalRect() const {
    return m_screenRect;
}

void Canvas::update() {
    auto screen = jage::runtime::Window::getActive()->getRect();
    if (screen != m_prevScreenRect) {
        m_screenRect = screen.as<jage::type::RectF>();

        for (auto& [name, child] : m_children) {
            auto canvasChild = dynamic_cast<frame::BasicFrame*>(child.value.get());
            if (canvasChild != nullptr) {
                canvasChild->markForReflow();
            }
        }
    }

    jage::node::abc::NodeABC<NodeType>::update();
}
