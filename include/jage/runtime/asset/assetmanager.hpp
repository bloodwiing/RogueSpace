#ifndef JAGE_ASSET_MANAGER_HPP
#define JAGE_ASSET_MANAGER_HPP

#include <map>
#include <thread>
#include <mutex>
#include <memory>

#include "jage/runtime/asset/assetstream.hpp"
#include "jage/graphics/model/model.hpp"
#include "jage/graphics/texture.hpp"
#include "jage/runtime/asset/abc/asset_abc.hpp"

namespace jage::runtime::asset {

    using jage::graphics::model::Model;
    using jage::graphics::Texture;

    class AssetManager {
    public:
        static AssetManager* getInstance();

        template<class T>
        std::shared_ptr<T> get(const std::string& fileName, int priority = JAGE_ASSET_BASE_PRIORITY);

    private:
        AssetManager();
        ~AssetManager() = default;

        static AssetManager* m_instance;

        AssetMap<Types::Model> m_models;
        AssetMap<Types::Texture> m_textures;
        AssetMap<Types::Shader> m_shaders;

        mutable std::mutex m_modelMutex, m_textureMutex, m_shaderMutex;

        template<class T>
        std::shared_ptr<T> load(const std::string& fileName, int priority = JAGE_ASSET_BASE_PRIORITY);

        AssetManager& operator=(const AssetManager& ref);
    };
}

#include "assetmanager_impl.tpp"

#endif //JAGE_ASSET_MANAGER_HPP
