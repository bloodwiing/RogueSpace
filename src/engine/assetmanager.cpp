#include "engine/assetmanager.hpp"

Engine::AssetManager* Engine::AssetManager::m_instance = nullptr;

Engine::AssetManager::AssetManager()
    : m_models()
    , m_textures()
    , m_modelMutex()
    , m_textureMutex()
{

}

Engine::AssetManager *Engine::AssetManager::getInstance() {
    if (m_instance == nullptr)
        m_instance = new AssetManager();
    return m_instance;
}

std::shared_ptr<Graphics::Model> Engine::AssetManager::getModel(const std::string &fileName, int priority /* = ASSET_STREAM_BASE_PRIORITY */) {
    std::lock_guard<std::mutex> lock(m_modelMutex);
    if (m_models.find(fileName) == m_models.end()) {
        auto model = loadModel(fileName, priority);
        m_models[fileName] = model;
    }
    return m_models.at(fileName);
}

std::shared_ptr<Graphics::Texture> Engine::AssetManager::getTexture(const std::string &fileName, int priority /* = ASSET_STREAM_BASE_PRIORITY */) {
    std::lock_guard<std::mutex> lock(m_textureMutex);
    if (m_textures.find(fileName) == m_textures.end()) {
        auto texture = loadTexture(fileName, priority);
        m_textures[fileName] = texture;
    }
    return m_textures.at(fileName);
}

std::shared_ptr<Graphics::Model> Engine::AssetManager::loadModel(const std::string &fileName, int priority /* = ASSET_STREAM_BASE_PRIORITY */) {
    auto model = Graphics::Model::create(fileName);
    model->queue(priority);
    return model;
}

std::shared_ptr<Graphics::Texture> Engine::AssetManager::loadTexture(const std::string &fileName, int priority /* = ASSET_STREAM_BASE_PRIORITY */) {
    auto texture = Graphics::Texture::create(fileName);
    texture->queue(priority);
    return texture;
}
