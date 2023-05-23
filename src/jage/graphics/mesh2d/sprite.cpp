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

jage::type::RectI32 Sprite::getTextureXYRect() const {
    return jage::type::RectI32();
}

jage::type::RectF Sprite::getTextureUVRect() const {
    return jage::type::RectF();
}

void Sprite::applyTexture(jage::graphics::Shader &shader) {

}

void Sprite::onQueue(int priority) {

}
