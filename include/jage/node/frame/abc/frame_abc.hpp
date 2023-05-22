#ifndef JAGE_CANVAS_ABC_HPP
#define JAGE_CANVAS_ABC_HPP

#include "jage/node/abc/node_abc.hpp"
#include "jage/node/abc/transformable2d_abc.hpp"
#include "jage/node/abc/rectnode_abc.hpp"
#include "jage/type/rect.hpp"
#include "jage/node/base/dying_base.hpp"
#include "jage/script/abc/scriptable_abc.hpp"

#define JAGE_FRAME_ARGS JAGE_NODE_ARGS(jage::node::frame::abc::FrameABC), jage::node::Canvas* canvas, jage::node::abc::RectNodeABC* rectParent

namespace jage::node {
    class Canvas;
}

namespace jage::node::frame::abc {

    class FrameABC
            : public node::abc::NodeABC<FrameABC>
            , public node::abc::RectNodeABC
            , public jage::node::abc::Transformable2DABC
            , public script::abc::ScriptableABC
            , public jage::node::base::DyingBase {
    public:
        template<class T>
        T* addChild(std::string name);
        template<class T, class... Args>
        T* addChild(std::string name, Args&&... args);

        [[nodiscard]] Canvas* getCanvas() const;
        [[nodiscard]] RectNodeABC* getRectParent() const;

        void update() override;

        void kill() override;
        void kill(float delay) override;
        bool isDead() const override;

    protected:
        FrameABC(JAGE_FRAME_ARGS);

        [[nodiscard]] std::string getTypeName() const override;

    private:
        Canvas* m_canvas;
        RectNodeABC* m_rectParent;

        using node::abc::NodeABC<FrameABC>::addChild;
        using node::abc::NodeABC<FrameABC>::update;
    };
}

#include "frame_abc_impl.tpp"

#endif //JAGE_CANVAS_ABC_HPP
