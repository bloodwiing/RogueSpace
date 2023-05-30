#ifndef JAGE_SQUARE_FRAME_HPP
#define JAGE_SQUARE_FRAME_HPP

#include "jage/node/frame/basicframe.hpp"

namespace jage::node::frame {

    class SquareFrame
            : public BasicFrame
    {
    public:
        SquareFrame(JAGE_FRAME_ARGS);

        type::RectF getPhysicalRect() const override;

    protected:
        bool updateReflow() override;

    private:
        type::RectF m_squarePhysicalRect;
    };
}

#endif //JAGE_SQUARE_FRAME_HPP
