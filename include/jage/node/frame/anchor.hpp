#ifndef JAGE_ANCHORS_HPP
#define JAGE_ANCHORS_HPP

#include "jage/type/rect.hpp"

namespace jage::node::frame {

    class Anchor {
    public:
        static const type::RectF TopLeft;
        static const type::RectF TopCenter;
        static const type::RectF TopRight;

        static const type::RectF MiddleLeft;
        static const type::RectF MiddleCenter;
        static const type::RectF MiddleRight;

        static const type::RectF BottomLeft;
        static const type::RectF BottomCenter;
        static const type::RectF BottomRight;

        static const type::RectF Top;
        static const type::RectF Middle;
        static const type::RectF Bottom;

        static const type::RectF Left;
        static const type::RectF Center;
        static const type::RectF Right;

        static const type::RectF Full;

        typedef type::RectF Custom;
    };
}

#endif //JAGE_ANCHORS_HPP
