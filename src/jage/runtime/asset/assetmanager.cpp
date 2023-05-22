#include "jage/runtime/asset/assetmanager.hpp"

using jage::runtime::asset::AssetManager;
using jage::runtime::asset::abc::AssetABC;
using jage::graphics::model::Model;
using jage::graphics::Texture;
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
std::shared_ptr<Model> jage::runtime::asset::AssetManager::get(const std::string &fileName, int priority /* = ASSET_STREAM_BASE_PRIORITY */) {
    std::lock_guard<std::mutex> lock(m_modelMutex);
    if (m_models.find(fileName) == m_models.end()) {
        auto model = load<Model>(fileName, priority);
        m_models[fileName] = model;
    }
    return std::static_pointer_cast<Model>(m_models.at(fileName));
}

template<>
std::shared_ptr<Texture> jage::runtime::asset::AssetManager::get(const std::string &fileName, int priority /* = ASSET_STREAM_BASE_PRIORITY */) {
    std::lock_guard<std::mutex> lock(m_textureMutex);
    if (m_textures.find(fileName) == m_textures.end()) {
        auto texture = load<Texture>(fileName, priority);
        m_textures[fileName] = texture;
    }
    return std::static_pointer_cast<Texture>(m_textures.at(fileName));
}
