#include "engine/assetmanager.hpp"

using Graphics::Model;
using Graphics::Texture;

using std::shared_ptr;
using std::lock_guard;
using std::mutex;

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

shared_ptr<Model> Engine::AssetManager::getModel(const std::string &fileName, int priority /* = ASSET_STREAM_BASE_PRIORITY */) {
    lock_guard<mutex> lock(m_modelMutex);
    if (m_models.find(fileName) == m_models.end()) {
        auto model = loadModel(fileName, priority);
        m_models[fileName] = model;
    }
    return m_models.at(fileName);
}

shared_ptr<Texture> Engine::AssetManager::getTexture(const std::string &fileName, int priority /* = ASSET_STREAM_BASE_PRIORITY */) {
    lock_guard<mutex> lock(m_textureMutex);
    if (m_textures.find(fileName) == m_textures.end()) {
        auto texture = loadTexture(fileName, priority);
        m_textures[fileName] = texture;
    }
    return m_textures.at(fileName);
}

shared_ptr<Model> Engine::AssetManager::loadModel(const std::string &fileName, int priority /* = ASSET_STREAM_BASE_PRIORITY */) {
    auto model = Model::create(fileName);
    model->queue(priority);
    return model;
}

shared_ptr<Texture> Engine::AssetManager::loadTexture(const std::string &fileName, int priority /* = ASSET_STREAM_BASE_PRIORITY */) {
    auto texture = Texture::create(fileName);
    texture->queue(priority);
    return texture;
}
