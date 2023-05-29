#include "game/canvas/testcanvas.hpp"

#include "jage/node/frame/anchor.hpp"
#include "jage/node/frame/spriteframe.hpp"

using game::canvas::TestCanvas;
using jage::node::Canvas;
using jage::node::Scene;
using jage::type::RectF;
using jage::type::RectI32;
using jage::node::frame::Anchor;
using namespace jage::node::frame;

std::unique_ptr<Canvas> TestCanvas::create(Scene* scene) {
    auto canvas = std::make_unique<Canvas>(RectI32(1000, 1000));

    canvas->addChild<SpriteFrame>("", RectI32::Grow(80, 80, 30, 30), Anchor::BottomLeft, "./res/sprite/spheres/Blue.sprite")
            ->addChild<SpriteFrame>("", RectI32(0, 0, 30, 30), Anchor::BottomLeft, "./res/sprite/spheres/Blue.sprite");

    canvas->addChild<SpriteFrame>("", RectI32::Grow(80, 920, 30, 30), Anchor::TopLeft, "./res/sprite/spheres/Blue.sprite")
            ->addChild<SpriteFrame>("", RectI32(0, 30, 30, 60), Anchor::TopLeft, "./res/sprite/spheres/Blue.sprite");

    canvas->addChild<SpriteFrame>("", RectI32::Grow(920, 80, 30, 30), Anchor::BottomRight, "./res/sprite/spheres/Blue.sprite")
            ->addChild<SpriteFrame>("", RectI32(30, 0, 60, 30), Anchor::BottomRight, "./res/sprite/spheres/Blue.sprite");

    canvas->addChild<SpriteFrame>("", RectI32::Grow(920, 920, 30, 30), Anchor::TopRight, "./res/sprite/spheres/Blue.sprite")
            ->addChild<SpriteFrame>("", RectI32(30, 30, 60, 60), Anchor::TopRight, "./res/sprite/spheres/Blue.sprite");

    canvas->addChild<SpriteFrame>("", RectI32::Grow(500, 500, 30, 30), Anchor::MiddleCenter, "./res/sprite/spheres/Orange.sprite")
            ->addChild<SpriteFrame>("", RectI32(15, 15, 45, 45), Anchor::MiddleCenter, "./res/sprite/spheres/Orange.sprite");

    canvas->addChild<SpriteFrame>("", RectI32::Grow(80, 500, 30, 30), Anchor::MiddleLeft, "./res/sprite/spheres/Green.sprite")
            ->addChild<SpriteFrame>("", RectI32(0, 15, 30, 45), Anchor::MiddleLeft, "./res/sprite/spheres/Green.sprite");

    canvas->addChild<SpriteFrame>("", RectI32::Grow(920, 500, 30, 30), Anchor::MiddleRight, "./res/sprite/spheres/Green.sprite")
            ->addChild<SpriteFrame>("", RectI32(30, 15, 60, 45), Anchor::MiddleRight, "./res/sprite/spheres/Green.sprite");

    canvas->addChild<SpriteFrame>("", RectI32::Grow(500, 920, 30, 30), Anchor::TopCenter, "./res/sprite/spheres/Green.sprite")
            ->addChild<SpriteFrame>("", RectI32(15, 30, 45, 60), Anchor::TopCenter, "./res/sprite/spheres/Green.sprite");

    canvas->addChild<SpriteFrame>("", RectI32::Grow(500, 80, 30, 30), Anchor::BottomCenter, "./res/sprite/spheres/Green.sprite")
            ->addChild<SpriteFrame>("", RectI32(15, 0, 45, 30), Anchor::BottomCenter, "./res/sprite/spheres/Green.sprite");

    return canvas;
}
