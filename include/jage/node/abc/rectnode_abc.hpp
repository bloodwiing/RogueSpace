#ifndef JAGE_RECT_NODE_ABC_HPP
#define JAGE_RECT_NODE_ABC_HPP

#include "jage/type/rect.hpp"

namespace jage::node::abc {

    class RectNodeABC {
    public:
        [[nodiscard]] virtual jage::type::RectI32 getRect() const = 0;
        [[nodiscard]] virtual jage::type::RectF getAnchor() const = 0;
        [[nodiscard]] virtual jage::type::RectF getPhysicalRect() const = 0;
    };
}

#endif //JAGE_RECT_NODE_ABC_HPP
