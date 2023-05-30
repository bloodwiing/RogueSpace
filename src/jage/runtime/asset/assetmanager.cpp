#include "jage/runtime/asset/assetmanager.hpp"

using jage::runtime::asset::AssetManager;
using jage::runtime::asset::abc::AssetABC;
using Types = jage::runtime::asset::AssetManager::Types;
using std::shared_ptr;
using std::lock_guard;
using std::mutex;

AssetManager* AssetManager::m_instance = nullptr;

AssetManager* AssetManager::getInstance() {
    if (m_instance == nullptr)
        m_instance = new AssetManager();
    return m_instance;
}

void AssetManager::destroyInstance() {
    if (m_instance != nullptr) {
        m_instance->reset();
        delete m_instance;
    }
    m_instance = nullptr;
}

template<>
std::shared_ptr<Types::Shader> AssetManager::get(const std::string &fileName, int priority /* = ASSET_STREAM_BASE_PRIORITY */) {
    return get<Types::Shader>(m_shaderMutex, m_shaders, fileName, priority);
}

template<>
std::shared_ptr<Types::Model3D> AssetManager::get(const std::string &fileName, int priority /* = ASSET_STREAM_BASE_PRIORITY */) {
    return get<Types::Model3D>(m_modelMutex, m_models, fileName, priority);
}

template<>
std::shared_ptr<Types::Texture> AssetManager::get(const std::string &fileName, int priority /* = ASSET_STREAM_BASE_PRIORITY */) {
    return get<Types::Texture>(m_textureMutex, m_textures, fileName, priority);
}

template<>
std::shared_ptr<Types::Sprite> AssetManager::get(const std::string &fileName, int priority /* = ASSET_STREAM_BASE_PRIORITY */) {
    return get<Types::Sprite>(m_spriteMutex, m_sprites, fileName, priority);
}

void AssetManager::reset() {
    std::scoped_lock<std::mutex, std::mutex, std::mutex, std::mutex> lock(m_shaderMutex, m_modelMutex, m_textureMutex, m_spriteMutex);
    m_shaders.clear();
    m_models.clear();
    m_textures.clear();
    m_sprites.clear();
}
