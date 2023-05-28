#ifndef JAGE_SPRITE_FRAME_HPP
#define JAGE_SPRITE_FRAME_HPP

#include "jage/node/frame/solidframe.hpp"

namespace jage::node::frame {

    class SpriteFrame
            : public SolidFrame
    {
    public:
        SpriteFrame(JAGE_FRAME_ARGS, std::shared_ptr<jage::graphics::mesh2d::Sprite> sprite);
        SpriteFrame(JAGE_FRAME_ARGS, const std::string& filePath);

        void draw() override;

        virtual void setSprite(std::shared_ptr<jage::graphics::mesh2d::Sprite> sprite);

        virtual std::shared_ptr<jage::graphics::mesh2d::Sprite> getSprite() const;

    protected:
        std::shared_ptr<jage::graphics::mesh2d::Sprite> getInternalSprite() const override;

    protected:
        std::shared_ptr<jage::graphics::mesh2d::Sprite> m_sprite;
    };
}

#endif //JAGE_SPRITE_FRAME_HPP
