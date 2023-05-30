#ifndef JAGE_SCORE_FRAME_HPP
#define JAGE_SCORE_FRAME_HPP

#include "jage/node/frame/basicframe.hpp"
#include "jage/node/frame/spriteframe.hpp"

namespace jage::node::frame {

    class ScoreFrame
            : public BasicFrame
    {
    public:
        ScoreFrame(JAGE_FRAME_ARGS, std::string digitFilePath, int minSize = 0);

        void setScore(long score);

        [[nodiscard]] long getScore() const;

        void update() override;

    private:
        std::string m_digitFilePath;

        std::vector<std::shared_ptr<graphics::mesh2d::Sprite>> m_digits;

        std::vector<SpriteFrame*> m_scoreFrames;

        int getSizeOfNumber(long number) const;

        bool m_outdatedScore = false;

        long m_score;
        int m_size = 0;
        const int m_minSize;
    };
}

#endif //JAGE_SCORE_FRAME_HPP
