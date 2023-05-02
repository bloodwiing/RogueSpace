#ifndef ASSET_MANAGER_CLASS_H
#define ASSET_MANAGER_CLASS_H

#include <map>
#include <thread>
#include <mutex>
#include <memory>

#include "engine/assetstream.hpp"

#include "graphics/model.hpp"
#include "graphics/texture.hpp"

namespace Engine {

    class AssetManager {
    public:
        static AssetManager* getInstance();

        std::shared_ptr<Graphics::Model> getModel(const std::string& fileName, int priority = ASSET_STREAM_BASE_PRIORITY);
        std::shared_ptr<Graphics::Texture> getTexture(const std::string& fileName, int priority = ASSET_STREAM_BASE_PRIORITY);

    private:
        AssetManager();

        static AssetManager* m_instance;

        std::map<std::string, std::shared_ptr<Graphics::Model>> m_models;
        std::map<std::string, std::shared_ptr<Graphics::Texture>> m_textures;

        mutable std::mutex m_modelMutex,
                           m_textureMutex;

        std::shared_ptr<Graphics::Model> loadModel(const std::string& fileName, int priority = ASSET_STREAM_BASE_PRIORITY);
        std::shared_ptr<Graphics::Texture> loadTexture(const std::string& fileName, int priority = ASSET_STREAM_BASE_PRIORITY);
    };
}

#endif //ASSET_MANAGER_CLASS_H
