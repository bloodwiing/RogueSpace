#include "jage/graphics/mesh2d/sprite.hpp"

#include <utility>

using jage::graphics::mesh2d::Sprite;

Sprite::Sprite(const std::shared_ptr<Texture>& texture, const jage::type::RectI32& rect)
        : m_texture(texture)
        , m_rect(rect)
        , m_filePath()
{

}

Sprite::Sprite(std::string filePath)
        : m_texture()
        , m_rect()
        , m_filePath(std::move(filePath))
{

}

Sprite::Sprite(const Sprite& ref)
        : jage::runtime::asset::abc::AssetABC<Sprite>()
        , m_rect(ref.m_rect)
        , m_filePath(ref.m_filePath)
        , m_texture(ref.m_texture)
{

}

jage::type::RectI32 Sprite::getTextureXYRect() const {
    return jage::type::RectI32();
}

jage::type::RectF Sprite::getTextureUVRect() const {
    return jage::type::RectF();
}

bool Sprite::applyTexture(jage::graphics::Shader &shader) {
    return false;
}

void Sprite::onQueue(int priority) {

}
