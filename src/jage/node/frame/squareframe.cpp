#include "jage/node/frame/squareframe.hpp"

using jage::node::frame::SquareFrame;
using jage::type::RectF;

SquareFrame::SquareFrame(JAGE_FRAME_ARGS)
        : BasicFrame(parent, std::move(name), canvas, rectParent, rect, anchor)
{

}

RectF SquareFrame::getPhysicalRect() const {
    return m_squarePhysicalRect;
}

bool SquareFrame::updateReflow() {
    if (!FrameABC::updateReflow())
        return false;

    auto physicalSize = m_physicalRect.getSize();

    float smaller = glm::min(physicalSize.x, physicalSize.y);

    float diffX = physicalSize.x - smaller;
    float diffY = physicalSize.y - smaller;

    float anchorX = (m_anchor.x1 + m_anchor.x2) * 0.5f;
    float anchorY = (m_anchor.y1 + m_anchor.y2) * 0.5f;

    m_squarePhysicalRect = RectF(glm::vec2(m_physicalRect.x1 + diffX * anchorX, m_physicalRect.y1 + diffY * anchorY), smaller, smaller);

    return true;
}
