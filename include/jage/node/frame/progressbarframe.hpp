#ifndef JAGE_BASIC_CANVAS_HPP
#define JAGE_BASIC_CANVAS_HPP

#include "jage/node/frame/basicframe.hpp"
#include "jage/node/frame/spriteframe.hpp"

namespace jage::node::frame {

    class ProgressBarFrame
            : public BasicFrame {
    public:
        friend class jage::node::Canvas;

        ProgressBarFrame(JAGE_FRAME_ARGS, const std::string& fullFilePath, const std::string& emptyFilePath);

        void setProgress(float progress);

        [[nodiscard]] float getProgress() const;

        void update() override;

    protected:
        float m_progress;

        SpriteFrame* m_fullFrame;
        SpriteFrame* m_emptyFrame;
    };
}

#endif //JAGE_BASIC_CANVAS_HPP
