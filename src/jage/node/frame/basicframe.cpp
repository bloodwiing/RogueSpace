#include "jage/node/frame/basicframe.hpp"

using jage::node::frame::BasicFrame;

BasicFrame::BasicFrame(JAGE_FRAME_ARGS)
    : FrameABC(parent, std::move(name), canvas)
    , m_rect(0.0f, 0.0f)
    , m_anchor(1.0f, 1.0f)
    , m_fill(0.0f)
{

}

BasicFrame::BasicFrame(JAGE_FRAME_ARGS, const jage::type::RectF& rect, const jage::type::RectF& anchor, glm::vec4 fill /* = glm::vec4(0.0f) */)
    : FrameABC(parent, std::move(name), canvas)
    , m_rect(rect)
    , m_anchor(anchor)
    , m_fill(fill)
{

}

jage::type::RectF BasicFrame::getRect() const {
    return m_rect;
}

jage::type::RectF BasicFrame::getAnchor() const {
    return m_anchor;
}

jage::type::RectF BasicFrame::getPhysicalRect() const {
    return m_physicalRect;
}

glm::vec4 BasicFrame::getFill() const {
    return m_fill;
}

bool jage::node::frame::BasicFrame::isDead() const {
    return m_dead;
}

void BasicFrame::setRect(const jage::type::RectF& rect) {
    m_rect = rect;
    markForReflow();
}

void BasicFrame::setAnchor(const jage::type::RectF& anchor) {
    m_anchor = anchor;
    markForReflow();
}

void BasicFrame::setFill(glm::vec4 fill) {
    m_fill = fill;
}

void BasicFrame::markDead(float wait /* = -1.0f */) {
    if (wait <= 0.0f)
        m_dead = true;
    else
        m_deathTimer = wait;
}

void BasicFrame::update() {
    using jage::runtime::Time;

    if (m_deathTimer >= 0.0f) {
        m_deathTimer -= Time::getDeltaFloat();
        if (m_deathTimer <= 0.0f) {
            m_dead = true;
            m_deathTimer = -1.0f;
        }
    }

    if (m_needsRectReflow) {
        m_physicalRect = m_rect.scalePhysical(m_parent->getRect(), m_parent->getPhysicalRect(), m_anchor);

        for (auto& [name, child] : m_children) {
            auto canvasChild = dynamic_cast<BasicFrame*>(child.value.get());
            if (canvasChild != nullptr) {
                canvasChild->markForReflow();
            }
        }
    }

    NodeABC::update();
}

void BasicFrame::markForReflow() {
    m_needsRectReflow = true;
}
