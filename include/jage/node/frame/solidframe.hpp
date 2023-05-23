#ifndef JAGE_SOLID_FRAME_HPP
#define JAGE_SOLID_FRAME_HPP

#include "jage/node/frame/basicframe.hpp"
#include "jage/graphics/mesh2d/sprite.hpp"
#include "jage/graphics/shader.hpp"

namespace jage::node::frame {

    class SolidFrame
            : public BasicFrame
    {
    public:
        SolidFrame(JAGE_FRAME_ARGS, std::shared_ptr<jage::graphics::Shader> shader);

        void draw() override;

        virtual void setSprite(std::shared_ptr<jage::graphics::mesh2d::Sprite> sprite);

        virtual std::shared_ptr<jage::graphics::mesh2d::Sprite> getSprite() const;

    protected:
        void updateReflow() override;

    private:
        graphics::mesh2d::Quad2D m_quad;
        std::shared_ptr<jage::graphics::mesh2d::Sprite> m_sprite;
        std::shared_ptr<jage::graphics::Shader> m_shader;
    };
}

#endif //JAGE_SOLID_FRAME_HPP
