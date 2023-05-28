#include "jage/node/frame/scoreframe.hpp"

#include "jage/runtime/asset/assets.hpp"
#include "jage/node/frame/anchor.hpp"
#include "jage/runtime/time.hpp"

using jage::node::frame::ScoreFrame;
using jage::runtime::asset::Assets;
using jage::type::RectI32;
using jage::node::frame::Anchor;

ScoreFrame::ScoreFrame(JAGE_FRAME_ARGS, std::string digitFilePath, int minSize /* = 0 */)
        : BasicFrame(parent, std::move(name), canvas, rectParent, rect, anchor)
        , m_digitFilePath(std::move(digitFilePath))
        , m_score(0)
        , m_minSize(minSize)
{
    for (int i = 0; i < 10; ++i) {
        m_digits.push_back(Assets::get<Assets::Sprite>(m_digitFilePath + std::to_string(i) + ".sprite"));
    }
}

void ScoreFrame::setScore(long score) {
    m_score = score;
    m_outdatedScore = true;
}

long ScoreFrame::getScore() const {
    return m_score;
}

void ScoreFrame::update() {
    static float timer = 0.0f;
    timer += jage::runtime::Time::getDeltaFloat();
    if (timer > 0.02f) {
        setScore(m_score + 1);
        timer = 0.0f;
    }

    int newSize = getSizeOfNumber(m_score);
    if (newSize > m_size) {
        for (; newSize > m_size; ++m_size) {
            m_scoreFrames.push_back(addChild<SpriteFrame>(
                    "Digit",
                    RectI32(-94, 50, -50, 110) + glm::vec<2, int>(getRectParent()->getRect().getSize().x, 0) - glm::vec<2, int>(m_size * 49, 0),
                    Anchor::BottomRight,
                    m_digits[0]));
        }
    }

    if (m_outdatedScore) {
        auto score = m_score;
        for (auto& scoreFrame : m_scoreFrames) {
            scoreFrame->setSprite(m_digits[score % 10]);
            scoreFrame->setMultiply(1.0f, 1.0f, 1.0f, score == 0 ? 0.5f : 1.0f);
            score /= 10;
        }
        m_outdatedScore = false;
    }

    BasicFrame::update();
}


int ScoreFrame::getSizeOfNumber(long number) {
    int size = number ? (int)floor(log10((double)number)) + 1 : 0;
    if (size < m_minSize)
        return m_minSize;
    return size;
}
