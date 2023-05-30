#include "game/canvas/hudcanvas.hpp"

#include "jage/node/frame/anchor.hpp"
#include "jage/node/frame/spriteframe.hpp"
#include "jage/node/frame/scoreframe.hpp"
#include "jage/node/frame/progressbarframe.hpp"
#include "jage/node/frame/squareframe.hpp"
#include "jage/script/actor/healthscript.hpp"
#include "jage/script/actor/scorescript.hpp"
#include "jage/script/frame/opacitydamageflashscript.hpp"
#include "jage/script/frame/progressdamagescript.hpp"
#include "jage/script/frame/followcursorscript.hpp"
#include "jage/script/frame/cursordistanceopacityscript.hpp"
#include "jage/script/frame/scoreupdatescript.hpp"
#include "jage/script/frame/opacityscoreflashscript.hpp"

using game::canvas::HUDCanvas;
using jage::node::Canvas;
using jage::node::Scene;
using jage::type::RectF;
using jage::type::RectI32;
using jage::node::frame::Anchor;
using namespace jage::node::frame;
using namespace jage::script;

std::unique_ptr<Canvas> HUDCanvas::create(Scene* scene) {
    auto player = scene->getChild("Player");
    auto healthScript = player->findScript<actor::HealthScript>();
    auto scoreScript = player->findScript<actor::ScoreScript>();

    // CANVAS
    auto canvas = std::make_unique<Canvas>(RectI32(1920, 1080));

    // FLASH OVERLAY
    auto flash = canvas->addChild<SpriteFrame>("Flash", RectI32(1920, 1080), Anchor::Full, "./res/sprite/Flash.sprite");
    flash->setMultiply(0.835f, 0.082f, 0.416f, 0.0f);
    auto flashScript = flash->attachScript<frame::OpacityDamageFlashScript>(0.5f, 0.2f);
    healthScript.lock()->onDamage += flashScript;

    // HEALTH BAR GLOW
    auto healthFx = canvas->addChild<SpriteFrame>("HealthFX", RectI32::Grow(215, 78, 165, 32), Anchor::BottomLeft, "./res/sprite/hud/Gradient.sprite");
    healthFx->flipHorizontally(true);
    healthFx->setOpacity(0.0f);
    auto healthFlashScript = healthFx->attachScript<frame::OpacityDamageFlashScript>(2.0f, 1.0f);
    healthScript.lock()->onDamage += healthFlashScript;

    // HEALTH BAR
    auto bar = canvas->addChild<ProgressBarFrame>("HealthValueBar", RectI32(50, 50, 380, 106), Anchor::BottomLeft, "./res/sprite/hud/BarFull.sprite", "./res/sprite/hud/BarEmpty.sprite");
    auto barScript = bar->attachScript<frame::ProgressDamageScript>();
    healthScript.lock()->onDamage += barScript;

    // WARNING ICON
    auto iconWarning = canvas->addChild<SpriteFrame>("IconWarning", RectI32(405, 50, 461, 106), Anchor::BottomLeft, "./res/sprite/hud/IconWarning.sprite");
    iconWarning->setOpacity(0.0f);
    auto iconScript = iconWarning->attachScript<frame::OpacityDamageFlashScript>(5.0f, 20.0f);
    healthScript.lock()->onDamage += iconScript;

    // SCORE GLOW
    auto scoreFx = canvas->addChild<SpriteFrame>("ScoreFX", RectI32::Grow(1705, 80, 165, 32), Anchor::BottomRight, "./res/sprite/hud/Gradient.sprite");
    scoreFx->setOpacity(0.0f);
    auto scoreFlashScript = scoreFx->attachScript<frame::OpacityScoreFlashScript>(2.0f, 1.0f);
    scoreScript.lock()->onScoreUpdate += scoreFlashScript;

    // SCORE NUMBER
    auto scoreUI = canvas->addChild<ScoreFrame>("ScoreNumber", RectI32(1870, 50, 1870, 50), Anchor::BottomRight, "./res/sprite/hud/Digit", 4);
    auto scoreUIScript = scoreUI->attachScript<frame::ScoreUpdateScript>();
    scoreScript.lock()->onScoreUpdate += scoreUIScript;

    // "SCORE" TEXT
    canvas->addChild<SpriteFrame>("ScoreText", RectI32(1703, 122, 1810, 146), Anchor::BottomRight, "./res/sprite/hud/TextScore.sprite");

    // CROSSHAIR OUTER
    auto ringContainer = canvas->addChild<SquareFrame>("RingContainer", RectI32(0, 0, 1920, 1080), Anchor::Full);
    ringContainer->scale(glm::vec2(0.8f));
    auto ringOuter = ringContainer->addChild<SpriteFrame>("Ring", RectI32(0, 0, 1920, 1080), Anchor::Full, "./res/sprite/hud/RingOuter.sprite");
    ringOuter->setMultiply(0.235f, 0.192f, 0.729f, 0.20f);

    // CROSSHAIR INNER BLUE (WEAPON LIMIT)
    auto ringInnerBlue = canvas->addChild<SpriteFrame>("RingInner", RectI32::Grow(960, 540, 47, 47), Anchor::MiddleCenter, "./res/sprite/hud/RingInner.sprite");
    ringInnerBlue->setMultiply(0.455f, 0.42f, 0.847f, 0.2f);
    ringInnerBlue->attachScript<frame::FollowCursorScript>(0.4f);

    // CROSSHAIR INNER
    auto ringInner = canvas->addChild<SpriteFrame>("RingInner", RectI32::Grow(960, 540, 47, 47), Anchor::MiddleCenter, "./res/sprite/hud/RingInner.sprite");
    ringInner->setMultiply(1.0f, 1.0f, 1.0f, 0.6f);
    ringInner->attachScript<frame::FollowCursorScript>(-1.0f);

    // CROSSHAIR WEAPON
    auto ringWeapon = ringInner->addChild<SpriteFrame>("RingWeapon", RectI32::Grow(47, 47, 35, 35), Anchor::MiddleCenter, "./res/sprite/hud/RingWeapon.sprite");
    ringWeapon->setMultiply(0.929f, 0.298f, 0.392f, 0.6f);
    ringWeapon->attachScript<frame::CursorDistanceOpacityScript>(0.40f, 0.45f, 0.6f);

    // CROSSHAIR DEADZONE
    auto ringDeadzone = ringInner->addChild<SpriteFrame>("RingDeadzone", RectI32::Grow(47, 47, 11, 11), Anchor::MiddleCenter, "./res/sprite/hud/RingDeadzone.sprite");
    ringDeadzone->setMultiply(1.0f, 1.0f, 1.0f, 1.0f);
    ringDeadzone->attachScript<frame::CursorDistanceOpacityScript>(0.005f, 0.02f, 1.0f);

    // ELIMINATION NOTIFICATION
    canvas->addChild<SpriteFrame>("Notification", RectI32::Grow(960, 340, 150, 19), Anchor::Custom(0.5f, 0.25f, 0.5f, 0.25f), "./res/sprite/hud/NotificationEliminated.sprite");

    // "IN-COMBAT" WARNING LABEL
    canvas->addChild<SpriteFrame>("Warning", RectI32::Grow(960, 1025, 252, 16), Anchor::TopCenter, "./res/sprite/hud/Warning.sprite");

    return canvas;
}
