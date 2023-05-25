#include "jage/node/frame/spriteframe.hpp"

#include "jage/runtime/asset/assets.hpp"

using jage::node::frame::SpriteFrame;
using jage::node::frame::SolidFrame;
using jage::graphics::mesh2d::Sprite;
using jage::graphics::mesh2d::Quad2D;
using jage::graphics::Shader;
using jage::runtime::asset::Assets;

SpriteFrame::SpriteFrame(JAGE_FRAME_ARGS, std::shared_ptr<Sprite> sprite)
        : SolidFrame(parent, std::move(name), canvas, rectParent, rect, anchor, Assets::get<Assets::Shader>("./res/shader/ui"), sprite)
        , m_sprite(std::move(sprite))
{

}

void jage::node::frame::SpriteFrame::draw() {
    m_sprite->applyTexture(*m_shader);
    SolidFrame::draw();
}

void SpriteFrame::setSprite(std::shared_ptr<Sprite> sprite) {
    m_sprite = std::move(sprite);
    m_quad = Quad2D(getScreenRect(), getSprite());
}

std::shared_ptr<Sprite> SpriteFrame::getSprite() const {
    return m_sprite;
}

std::shared_ptr<Sprite> SpriteFrame::getInternalSprite() const {
    return getSprite();
}
