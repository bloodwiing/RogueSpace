#include <utility>

#include "jage/node/frame/solidframe.hpp"

using jage::node::frame::SolidFrame;
using jage::type::RectF;
using jage::graphics::mesh2d::Sprite;
using jage::graphics::mesh2d::Quad2D;
using jage::graphics::Shader;

SolidFrame::SolidFrame(JAGE_FRAME_ARGS, std::shared_ptr<Shader> shader)
        : BasicFrame(parent, std::move(name), canvas, rectParent, rect, anchor)
        , m_sprite(Sprite::getDefaultSprite())
        , m_quad(RectF(1.0f, 1.0f), Sprite::getDefaultSprite())
        , m_shader(std::move(shader))
{

}

void SolidFrame::draw() {
    m_quad.draw(*m_shader, BasicFrame::getWorldMatrix());
    BasicFrame::draw();
}

void SolidFrame::updateReflow() {
    FrameABC::updateReflow();
    m_quad = Quad2D(getScreenRect(), getSprite());
}

void SolidFrame::setSprite(std::shared_ptr<Sprite> sprite) {
    m_sprite = std::move(sprite);
    m_quad = Quad2D(getScreenRect(), getSprite());
}

std::shared_ptr<Sprite> SolidFrame::getSprite() const {
    return m_sprite;
}
