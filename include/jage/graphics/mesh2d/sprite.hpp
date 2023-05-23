#ifndef JAGE_SPRITE_HPP
#define JAGE_SPRITE_HPP

#include "jage/graphics/texture.hpp"
#include "jage/graphics/shader.hpp"
#include "jage/type/rect.hpp"
#include "jage/runtime/asset/abc/asset_abc.hpp"

namespace jage::graphics::mesh2d {

    class Sprite
            : jage::runtime::asset::abc::AssetABC<Sprite>
    {
    public:
        Sprite(const std::shared_ptr<Texture>& texture, const jage::type::RectI32& rect);
        Sprite(std::string filePath, const jage::type::RectI32& rect);
        Sprite(const Sprite& ref);
        ~Sprite() = default;

        [[nodiscard]] jage::type::RectI32 getTextureXYRect() const;
        [[nodiscard]] jage::type::RectF getTextureUVRect() const;

        bool applyTexture(Shader& shader);

    private:
        std::string m_filePath;

        std::shared_ptr<Texture> m_texture;
        jage::type::RectI32 m_rect;

        void onQueue(int priority) override;
    };
}

#endif //JAGE_SPRITE_HPP
