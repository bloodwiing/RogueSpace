#include "game/canvas/hudcanvas.hpp"

#include "jage/node/frame/anchor.hpp"
#include "jage/node/frame/spriteframe.hpp"
#include "jage/node/frame/scoreframe.hpp"

using game::canvas::HUDCanvas;
using jage::node::Canvas;
using jage::type::RectF;
using jage::type::RectI32;
using jage::node::frame::Anchor;
using namespace jage::node::frame;

std::unique_ptr<Canvas> HUDCanvas::create() {
    auto canvas = std::make_unique<Canvas>(RectI32(1920, 1080));

    auto flash = canvas->addChild<SpriteFrame>("Flash", RectI32(1920, 1080), Anchor::Full, "./res/sprite/flash.sprite");
    flash->setMultiply(0.835f, 0.082f, 0.416f, 0.2f);

    canvas->addChild<SpriteFrame>("HealthBar", RectI32(50, 50, 380, 106), Anchor::BottomLeft, "./res/sprite/hud/BarFull.sprite");
    canvas->addChild<SpriteFrame>("IconWarning", RectI32(405, 50, 461, 106), Anchor::BottomLeft, "./res/sprite/hud/IconWarning.sprite");

    auto score = canvas->addChild<ScoreFrame>("Score", RectI32(1, 1), Anchor::BottomRight, "./res/sprite/hud/Digit", 4);
    score->setScore(1);

    return canvas;
}
