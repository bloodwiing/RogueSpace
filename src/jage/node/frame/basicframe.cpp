#include "jage/node/frame/basicframe.hpp"

#include <glm/matrix.hpp>

using jage::node::frame::BasicFrame;

BasicFrame::BasicFrame(JAGE_FRAME_ARGS)
    : FrameABC(parent, std::move(name), canvas, rectParent)
    , m_rect(0.0f, 0.0f)
    , m_anchor(1.0f, 1.0f)
    , m_fill(0.0f)
{

}

BasicFrame::BasicFrame(JAGE_FRAME_ARGS, const jage::type::RectF& rect, const jage::type::RectF& anchor, glm::vec4 fill /* = glm::vec4(0.0f) */)
    : FrameABC(parent, std::move(name), canvas, rectParent)
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

void BasicFrame::update() {
    base::DyingBase::updateDeathTimer();
    updateReflow();
    updateTransformations();
    abc::FrameABC::update();
}

void BasicFrame::updateReflow() {
    if (!m_needsRectReflow)
        return;

    m_physicalRect = m_rect.scalePhysical(getRectParent()->getRect(), getRectParent()->getPhysicalRect(), m_anchor);

    for (auto& [name, child] : m_children) {
        auto canvasChild = dynamic_cast<BasicFrame*>(child.value.get());
        if (canvasChild != nullptr) {
            canvasChild->markForReflow();
        }
    }
}

void BasicFrame::updateTransformations() {
    if (!m_needsMatrixUpdate)
        return;

    Transformable2DABC::updateTransformations(getParent() != nullptr ? getParent()->getWorldMatrix() : glm::mat3(1.0f));
    m_needsMatrixUpdate = false;

    for (auto& [name, child] : m_children) {
        auto canvasChild = dynamic_cast<BasicFrame*>(child.value.get());
        if (canvasChild != nullptr) {
            canvasChild->markForReflow();
        }
    }
}

void BasicFrame::markForReflow() {
    m_needsRectReflow = true;
}

glm::mat3 BasicFrame::getWorldMatrix() const {
    return m_worldMatrix;
}

glm::vec2 BasicFrame::getTranslation() const {
    return m_translation;
}

float BasicFrame::getRotation() const {
    return m_rotation;
}

glm::vec2 BasicFrame::getScale() const {
    return m_scale;
}

void BasicFrame::setTranslation(const glm::vec2 &tra) {
    m_translation = tra;
    markForMatrixUpdate();
}

void BasicFrame::setRotation(const float &rot) {
    m_rotation = rot;
    markForMatrixUpdate();
}

void BasicFrame::setScale(const glm::vec2 &sca) {
    m_scale = sca;
    markForMatrixUpdate();
}

void BasicFrame::markForMatrixUpdate() {
    m_needsMatrixUpdate = true;
}
