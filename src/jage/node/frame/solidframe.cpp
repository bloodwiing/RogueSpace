#include <utility>

#include "jage/node/frame/solidframe.hpp"
#include "jage/runtime/asset/assets.hpp"

using jage::node::frame::SolidFrame;
using jage::type::RectF;
using jage::graphics::mesh2d::Sprite;
using jage::graphics::mesh2d::Quad2D;
using jage::graphics::Shader;
using jage::runtime::asset::Assets;

SolidFrame::SolidFrame(JAGE_FRAME_ARGS, std::shared_ptr<Shader> shader)
        : SolidFrame(parent, std::move(name), canvas, rectParent, rect, anchor, std::move(shader), std::move(Assets::get<Assets::Sprite>()))
{

}

SolidFrame::SolidFrame(JAGE_FRAME_ARGS, std::shared_ptr<Shader> shader, std::shared_ptr<Sprite> sprite)
        : BasicFrame(parent, std::move(name), canvas, rectParent, rect, anchor)
        , m_quad(RectF(1.0f, 1.0f), std::move(sprite))
        , m_shader(std::move(shader))
{

}

void SolidFrame::draw() {
    m_quad.draw(*m_shader, BasicFrame::getWorldMatrix());
    BasicFrame::draw();
}

void SolidFrame::updateReflow() {
    FrameABC::updateReflow();
    m_quad = Quad2D(getScreenRect(), getInternalSprite());
}

std::shared_ptr<Sprite> SolidFrame::getInternalSprite() const {
    return Assets::get<Assets::Sprite>();
}
