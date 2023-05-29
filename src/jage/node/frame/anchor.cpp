#include "jage/node/frame/anchor.hpp"

using jage::node::frame::Anchor;
using jage::type::RectF;

const RectF Anchor::TopLeft = RectF(0.0f, 1.0f, 0.0f, 1.0f);
const RectF Anchor::TopCenter = RectF(0.5f, 1.0f, 0.5f, 1.0f);
const RectF Anchor::TopRight = RectF(1.0f, 1.0f, 1.0f, 1.0f);

const RectF Anchor::MiddleLeft = RectF(0.0f, 0.5f, 0.0f, 0.5f);
const RectF Anchor::MiddleCenter = RectF(0.5f, 0.5f, 0.5f, 0.5f);
const RectF Anchor::MiddleRight = RectF(1.0f, 0.5f, 1.0f, 0.5f);

const RectF Anchor::BottomLeft = RectF(0.0f, 0.0f, 0.0f, 0.0f);
const RectF Anchor::BottomCenter = RectF(0.5f, 0.0f, 0.5f, 0.0f);
const RectF Anchor::BottomRight = RectF(1.0f, 0.0f, 1.0f, 0.0f);

const RectF Anchor::Top = RectF(0.0f, 1.0f, 1.0f, 1.0f);
const RectF Anchor::Middle = RectF(0.0f, 0.5f, 1.0f, 0.5f);
const RectF Anchor::Bottom = RectF(0.0f, 0.0f, 1.0f, 0.0f);

const RectF Anchor::Left = RectF(0.0f, 0.0f, 0.0f, 1.0f);
const RectF Anchor::Center = RectF(0.5f, 0.0f, 0.5f, 1.0f);
const RectF Anchor::Right = RectF(1.0f, 0.0f, 1.0f, 1.0f);

const RectF Anchor::Full = RectF(0.0f, 0.0f, 1.0f, 1.0f);