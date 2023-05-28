#include "jage/graphics/mesh2d/sprite.hpp"

#include <utility>

#include "jage/runtime/asset/assetmanager.hpp"

using jage::graphics::mesh2d::Sprite;
using jage::type::RectF;
using jage::type::RectI32;
using jage::runtime::asset::AssetManager;

std::shared_ptr<Sprite> Sprite::defaultSprite = nullptr;

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
    const auto corner = RectI32::PairType(m_data["x"].as<int>(), m_data["y"].as<int>());
    m_rect = RectI32(corner, m_data["width"].as<int>(), m_data["height"].as<int>());

    std::string directory = runtime::asset::AssetStream::getFileDirectory(m_filePath);

    m_texture = AssetManager::getInstance()->get<AssetManager::Types::Texture>(directory + m_data["texture"].as<std::string>());
}

Sprite::Sprite()
        : m_data()
        , m_rect(1.0f, 1.0f)
        , m_texture(Texture::getDefaultTexture())
{

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

std::shared_ptr<Sprite> Sprite::getDefaultSprite() {
    if (!defaultSprite)
        defaultSprite = std::make_shared<Sprite>();
    return defaultSprite;
}

void Sprite::clearDefaultSprite() {
    defaultSprite.reset();
    defaultSprite = nullptr;
}

RectI32 Sprite::getTextureXYRect() const {
    return m_rect;
}

RectF Sprite::getTextureUVRect() const {
    return m_rect.as<RectF>() / m_texture->getSizeRect().getSize();
}

bool Sprite::apply(jage::graphics::Shader& shader) {
    if (shader.isErrored())
        return false;

    m_texture->prepare();
    if (!m_texture->isReady())
        return false;
    m_texture->assign(shader, "Texture0", 0);
    m_texture->bind(0);

    auto rect = getTextureUVRect();
    glUniform2f(shader.getUniform("UVCorner1"), rect.x1, rect.y1);
    glUniform2f(shader.getUniform("UVCorner2"), rect.x2, rect.y2);

    return true;
}

void Sprite::onQueue(int priority) {
    m_texture->enqueue();
}
