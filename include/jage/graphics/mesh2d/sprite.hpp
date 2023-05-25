#ifndef JAGE_SPRITE_HPP
#define JAGE_SPRITE_HPP

#include "jage/graphics/texture.hpp"
#include "jage/graphics/shader.hpp"
#include "jage/type/rect.hpp"
#include "jage/runtime/asset/abc/asset_abc.hpp"

namespace jage::graphics::mesh2d {

    class Sprite
            : public jage::runtime::asset::abc::AssetABC<Sprite>
    {
    public:
        Sprite(const std::shared_ptr<Texture>& texture, const jage::type::RectI32& rect);
        explicit Sprite(std::string filePath);
        Sprite();
        static std::shared_ptr<Sprite> create(std::string filePath);
        Sprite(const Sprite& ref);
        ~Sprite() = default;

        [[nodiscard]] static std::shared_ptr<Sprite> getDefaultSprite();
        static void clearDefaultSprite();

        [[nodiscard]] jage::type::RectI32 getTextureXYRect() const;
        [[nodiscard]] jage::type::RectF getTextureUVRect() const;

        bool apply(jage::graphics::Shader &shader);

    private:
        const YAML::Node m_data;

        std::string m_filePath;

        std::shared_ptr<Texture> m_texture;
        jage::type::RectI32 m_rect;

        void onQueue(int priority) override;

        static std::shared_ptr<Sprite> defaultSprite;

        Sprite& operator=(const Sprite& ref);
    };
}

#endif //JAGE_SPRITE_HPP
