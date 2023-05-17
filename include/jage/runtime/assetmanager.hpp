#ifndef JAGE_ASSET_MANAGER_HPP
#define JAGE_ASSET_MANAGER_HPP

#include <map>
#include <thread>
#include <mutex>
#include <memory>

#include "jage/runtime/assetstream.hpp"
#include "jage/graphics/model/model.hpp"
#include "jage/graphics/texture.hpp"

namespace jage::runtime {

    using jage::graphics::model::Model;
    using jage::graphics::Texture;

    class AssetManager {
    public:
        static AssetManager* getInstance();

        std::shared_ptr<Model> getModel(const std::string& fileName, int priority = JAGE_ASSET_STREAM_BASE_PRIORITY);
        std::shared_ptr<Texture> getTexture(const std::string& fileName, int priority = JAGE_ASSET_STREAM_BASE_PRIORITY);

    private:
        AssetManager();
        ~AssetManager() = default;

        static AssetManager* m_instance;

        std::map<std::string, std::shared_ptr<Model>> m_models;
        std::map<std::string, std::shared_ptr<Texture>> m_textures;

        mutable std::mutex m_modelMutex,
                           m_textureMutex;

        std::shared_ptr<Model> loadModel(const std::string& fileName, int priority = JAGE_ASSET_STREAM_BASE_PRIORITY);
        std::shared_ptr<Texture> loadTexture(const std::string& fileName, int priority = JAGE_ASSET_STREAM_BASE_PRIORITY);

        AssetManager& operator=(const AssetManager& ref);
    };
}

#endif //JAGE_ASSET_MANAGER_HPP
