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

    auto healthFx = canvas->addChild<SpriteFrame>("HealthFX", RectI32::Grow(215, 78, 165, 32), Anchor::BottomLeft, "./res/sprite/hud/Gradient.sprite");
    healthFx->flipHorizontally(true);
    canvas->addChild<SpriteFrame>("HealthValueBar", RectI32(50, 50, 380, 106), Anchor::BottomLeft, "./res/sprite/hud/BarFull.sprite");
    canvas->addChild<SpriteFrame>("IconWarning", RectI32(405, 50, 461, 106), Anchor::BottomLeft, "./res/sprite/hud/IconWarning.sprite");

    canvas->addChild<SpriteFrame>("ScoreFX", RectI32::Grow(1705, 80, 165, 32), Anchor::BottomRight, "./res/sprite/hud/Gradient.sprite");
    canvas->addChild<ScoreFrame>("ScoreNumber", RectI32(1870, 50, 1870, 50), Anchor::BottomRight, "./res/sprite/hud/Digit", 4);
    canvas->addChild<SpriteFrame>("ScoreText", RectI32(1703, 122, 1810, 146), Anchor::BottomRight, "./res/sprite/hud/TextScore.sprite");

    auto ring = canvas->addChild<SpriteFrame>("Ring", RectI32::Grow(960, 540, 422, 422), Anchor::MiddleCenter, "./res/sprite/hud/RingOuter.sprite");
    ring->addChild<SpriteFrame>("RingInner", RectI32::Grow(422, 422, 47, 47), Anchor::MiddleCenter, "./res/sprite/hud/RingInner.sprite");
    ring->addChild<SpriteFrame>("RingWeapon", RectI32::Grow(422, 422, 35, 35), Anchor::MiddleCenter, "./res/sprite/hud/RingWeapon.sprite");
    ring->addChild<SpriteFrame>("RingDeadzone", RectI32::Grow(422, 422, 11, 11), Anchor::MiddleCenter, "./res/sprite/hud/RingDeadzone.sprite");

    canvas->addChild<SpriteFrame>("Notification", RectI32::Grow(960, 340, 150, 19), Anchor::Custom(0.5f, 0.25f, 0.5f, 0.25f), "./res/sprite/hud/NotificationEliminated.sprite");

    canvas->addChild<SpriteFrame>("Warning", RectI32::Grow(960, 1025, 252, 16), Anchor::TopCenter, "./res/sprite/hud/Warning.sprite");

    return canvas;
}
