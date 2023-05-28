#include "game/canvas/hudcanvas.hpp"

#include "jage/node/frame/anchors.hpp"
#include "jage/node/frame/spriteframe.hpp"

using game::canvas::HUDCanvas;
using jage::node::Canvas;
using jage::type::RectF;
using jage::type::RectI32;
using jage::node::frame::Anchor;
using namespace jage::node::frame;

std::unique_ptr<Canvas> HUDCanvas::create() {
    auto canvas = std::make_unique<Canvas>(RectI32(1920, 1080));

    canvas->addChild<SpriteFrame>("Flash", RectI32(1920, 1080), Anchor::Full, "./res/sprite/flash.sprite");

    return canvas;
}
