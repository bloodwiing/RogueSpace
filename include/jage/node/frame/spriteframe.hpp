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
        virtual void setMultiply(glm::vec4 multiply);
        void setMultiply(float r, float g, float b, float a = 1.0f);
        void setOpacity(float a);
        virtual void setAdd(glm::vec4 add);
        void setAdd(float r, float g, float b, float a = 0.0f);

        void flipHorizontally(bool value);
        void flipVertically(bool value);

        void setCropLeft(float value);
        void setCropBottom(float value);
        void setCropRight(float value);
        void setCropTop(float value);

        [[nodiscard]] virtual std::shared_ptr<jage::graphics::mesh2d::Sprite> getSprite() const;
        [[nodiscard]] virtual glm::vec4 getMultiply() const;
        [[nodiscard]] virtual glm::vec4 getAdd() const;

    protected:
        std::shared_ptr<jage::graphics::mesh2d::Sprite> getInternalSprite() const override;

        virtual void updateUVMatrix();

    protected:
        std::shared_ptr<jage::graphics::mesh2d::Sprite> m_sprite;

        glm::vec4 m_multiply = glm::vec4(1.0f);
        glm::vec4 m_add = glm::vec4(0.0f);

        bool m_flipHor = false;
        bool m_flipVer = false;

        glm::mat3 m_uvMatrix = glm::mat3(1.0f);

        type::RectF m_crop = type::RectF(1.0f, 1.0f);
    };
}

#endif //JAGE_SPRITE_FRAME_HPP
