#include "jage/node/frame/abc/frame_abc.hpp"

#include "jage/node/canvas.hpp"

using jage::node::frame::abc::FrameABC;

FrameABC::FrameABC(JAGE_FRAME_ARGS)
        : node::abc::NodeABC<FrameABC>(parent, std::move(name))
        , m_canvas(canvas)
        , m_rectParent(rectParent)
        , m_rect(rect)
        , m_anchor(anchor)
{

}

jage::node::Canvas* FrameABC::getCanvas() const {
    return m_canvas;
}

jage::node::abc::RectNodeABC* FrameABC::getRectParent() const {
    return m_rectParent;
}

jage::type::RectI32 FrameABC::getRect() const {
    return m_rect;
}

jage::type::RectF FrameABC::getAnchor() const {
    return m_anchor;
}

jage::type::RectF FrameABC::getPhysicalRect() const {
    return m_physicalRect;
}

jage::type::RectF FrameABC::getScreenRect() const {
    return (getPhysicalRect() / m_canvas->getPhysicalRect().getSize()) * 2.0f - 1.0f;
}

void FrameABC::setRect(const jage::type::RectI32& rect) {
    m_rect = rect;
    markForReflow();
}

void FrameABC::setAnchor(const jage::type::RectF& anchor) {
    m_anchor = anchor;
    markForReflow();
}

void FrameABC::update() {
    DyingBase::updateDeathTimer();
    script::abc::ScriptableABC::update();
    NodeABC::update();
}

void FrameABC::kill() {
    DyingBase::kill();
}

void FrameABC::kill(float delay) {
    DyingBase::kill(delay);
}

bool FrameABC::isDead() const {
    return DyingBase::isDead();
}

void FrameABC::updateReflow() {
    if (!m_needsRectReflow)
        return;

    m_physicalRect = m_rect.scalePhysical(getRectParent()->getRect(), getRectParent()->getPhysicalRect(), m_anchor).as<jage::type::RectF>();

    for (auto& [name, child] : m_children) {
        child.value->markForReflow();
    }
}

void FrameABC::markForReflow() {
    m_needsRectReflow = true;
}

std::string FrameABC::getTypeName() const {
    return "Frame ABSTRACT BASE CLASS";
}
