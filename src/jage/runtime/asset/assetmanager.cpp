#include "jage/runtime/asset/assetmanager.hpp"

using jage::runtime::asset::AssetManager;
using jage::runtime::asset::abc::AssetABC;
using Types = jage::runtime::asset::AssetManager::Types;
using std::shared_ptr;
using std::lock_guard;
using std::mutex;

AssetManager* AssetManager::m_instance = nullptr;

AssetManager::AssetManager()
    : m_models()
    , m_textures()
    , m_shaders()
    , m_modelMutex()
    , m_textureMutex()
    , m_shaderMutex()
{ }

AssetManager *AssetManager::getInstance() {
    if (m_instance == nullptr)
        m_instance = new AssetManager();
    return m_instance;
}

template<>
std::shared_ptr<Types::Model3D> jage::runtime::asset::AssetManager::get(const std::string &fileName, int priority /* = ASSET_STREAM_BASE_PRIORITY */) {
    return get<Types::Model3D>(m_modelMutex, m_models, fileName, priority);
}

template<>
std::shared_ptr<Types::Texture> jage::runtime::asset::AssetManager::get(const std::string &fileName, int priority /* = ASSET_STREAM_BASE_PRIORITY */) {
    return get<Types::Texture>(m_textureMutex, m_textures, fileName, priority);
}

template<>
std::shared_ptr<Types::Shader> jage::runtime::asset::AssetManager::get(const std::string &fileName, int priority /* = ASSET_STREAM_BASE_PRIORITY */) {
    return get<Types::Shader>(m_shaderMutex, m_shaders, fileName, priority);
}
