#include "jage/node/frame/abc/frame_abc.hpp"

using jage::node::frame::abc::FrameABC;

FrameABC::FrameABC(JAGE_FRAME_ARGS)
    : node::abc::NodeABC<FrameABC>(parent, std::move(name))
    , m_canvas(canvas)
    , m_rectParent(rectParent)
{

}

jage::node::Canvas* FrameABC::getCanvas() const {
    return m_canvas;
}

jage::node::abc::RectNodeABC* FrameABC::getRectParent() const {
    return m_rectParent;
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

std::string FrameABC::getTypeName() const {
    return "Frame ABSTRACT BASE CLASS";
}
