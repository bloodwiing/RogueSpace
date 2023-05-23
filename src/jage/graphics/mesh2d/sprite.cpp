#include "jage/graphics/mesh2d/sprite.hpp"

#include <utility>

#include "jage/runtime/asset/assetmanager.hpp"

using jage::graphics::mesh2d::Sprite;
using jage::type::RectF;
using jage::type::RectI32;
using jage::runtime::asset::AssetManager;

Sprite::Sprite(const std::shared_ptr<Texture>& texture, const jage::type::RectI32& rect)
        : m_data()
        , m_texture(texture)
        , m_rect(rect)
        , m_filePath()
{

}

Sprite::Sprite(std::string filePath)
        : m_data(YAML::LoadFile(filePath))
        , m_filePath(std::move(filePath))
{
    const auto corner = RectI32::PairType(m_data["top"].as<int>(), m_data["left"].as<int>());
    m_rect = RectI32(corner, m_data["width"].as<int>(), m_data["height"].as<int>());

    m_texture = AssetManager::getInstance()->get<AssetManager::Types::Texture>(m_filePath);
}

std::shared_ptr<Sprite> Sprite::create(std::string filePath) {
    return std::make_shared<Sprite>(std::move(filePath));
}

Sprite::Sprite(const Sprite& ref)
        : jage::runtime::asset::abc::AssetABC<Sprite>()
        , m_rect(ref.m_rect)
        , m_filePath(ref.m_filePath)
        , m_texture(ref.m_texture)
{

}

RectI32 Sprite::getTextureXYRect() const {
    return m_rect;
}

RectF Sprite::getTextureUVRect() const {
    return m_rect.as<RectF>() / m_texture->getSizeRect().getSize();
}

bool Sprite::applyTexture(jage::graphics::Shader &shader) {
    if (shader.isErrored())
        return false;

    m_texture->prepare();
    if (!m_texture->isReady())
        return false;
    m_texture->assign(shader, "Texture0", 0);
    m_texture->bind(0);

    return true;
}

void Sprite::onQueue(int priority) {
    m_texture->enqueue();
}
