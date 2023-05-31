#include "jage/node/frame/progressbarframe.hpp"

#include "jage/node/frame/anchor.hpp"

using jage::node::frame::ProgressBarFrame;
using jage::node::frame::Anchor;

ProgressBarFrame::ProgressBarFrame(JAGE_FRAME_ARGS, const std::string& fullFilePath, const std::string& emptyFilePath)
        : BasicFrame(parent, std::move(name), canvas, rectParent, rect, anchor)
        , m_progress(0)
{
    m_fullFrame = addChild<SpriteFrame>("Full", m_rect.normalized(), Anchor::Full, fullFilePath);
    m_emptyFrame = addChild<SpriteFrame>("Empty", m_rect.normalized(), Anchor::Full, emptyFilePath);
}

void ProgressBarFrame::setProgress(float progress) {
    m_progress = progress;
    m_fullFrame->setCropRight(progress);
}

float ProgressBarFrame::getProgress() const {
    return m_progress;
}

void ProgressBarFrame::update() {
    BasicFrame::update();
}
