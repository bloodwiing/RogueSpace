#ifndef JAGE_CANVAS_HPP
#define JAGE_CANVAS_HPP

#include "jage/node/abc/node_abc.hpp"
#include "jage/node/abc/rectnode_abc.hpp"
#include "jage/node/frame/abc/frame_abc.hpp"

#define JAGE_CANVAS_FRAME_ARGS std::string name

namespace jage::node {

    class Canvas
            : public abc::NodeABC<frame::abc::FrameABC>
            , public abc::RectNodeABC {
    public:
        explicit Canvas(const jage::type::RectF& rect);

        template<class T>
        T* addChild(JAGE_CANVAS_FRAME_ARGS);
        template<class T, class... Args>
        T* addChild(JAGE_CANVAS_FRAME_ARGS, Args&&... args);

        type::RectF getRect() const override;
        type::RectF getAnchor() const override;
        type::RectF getPhysicalRect() const override;

        void update() override;

    private:
        jage::type::RectF m_rect;
        jage::type::RectF m_screenRect;

        jage::type::RectI32 m_prevScreenRect = jage::type::RectI32();

        using jage::node::abc::NodeABC<jage::node::frame::abc::FrameABC>::addChild;
    };
}

#include "canvas_impl.tpp"

#endif //JAGE_CANVAS_HPP
