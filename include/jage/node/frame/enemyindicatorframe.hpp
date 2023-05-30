#ifndef JAGE_ENEMY_INDICATOR_FRAME_HPP
#define JAGE_ENEMY_INDICATOR_FRAME_HPP

#include "jage/node/frame/basicframe.hpp"
#include "jage/node/frame/spriteframe.hpp"

namespace jage::node::frame {

    class EnemyIndicatorFrame
            : public BasicFrame
    {
    public:
        EnemyIndicatorFrame(JAGE_FRAME_ARGS);

        void update() override;

    private:
        std::vector<SpriteFrame*> m_sprites;
    };
}

#endif //JAGE_ENEMY_INDICATOR_FRAME_HPP
