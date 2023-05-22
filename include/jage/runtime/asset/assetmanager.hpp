#ifndef JAGE_ASSET_MANAGER_HPP
#define JAGE_ASSET_MANAGER_HPP

#include <map>
#include <thread>
#include <mutex>
#include <memory>

#include "jage/runtime/asset/assetstream.hpp"
#include "jage/graphics/mesh3d/model3d.hpp"
#include "jage/graphics/texture.hpp"
#include "jage/graphics/shader.hpp"
#include "jage/runtime/asset/abc/asset_abc.hpp"

namespace jage::runtime::asset {

    class AssetManager {
    public:
        class Types {
        public:
            typedef jage::graphics::mesh3d::Model3D Model3D;
            typedef jage::graphics::Texture Texture;
            typedef jage::graphics::Shader Shader;
        };

        static AssetManager* getInstance();

        template<class T>
        std::shared_ptr<T> get(const std::string& fileName, int priority = JAGE_ASSET_BASE_PRIORITY);

    private:
        AssetManager();
        ~AssetManager() = default;

        template<class T>
        using AssetMap = std::map<std::string, std::shared_ptr<abc::AssetABC<T>>>;

        static AssetManager* m_instance;

        AssetMap<Types::Model3D> m_models;
        AssetMap<Types::Texture> m_textures;
        AssetMap<Types::Shader> m_shaders;

        mutable std::mutex m_modelMutex, m_textureMutex, m_shaderMutex;

        template<class T>
        static std::shared_ptr<T> get(std::mutex& mutex, AssetMap<T>& map, const std::string& fileName, int priority = JAGE_ASSET_BASE_PRIORITY);

        template<class T>
        static std::shared_ptr<T> load(const std::string& fileName, int priority = JAGE_ASSET_BASE_PRIORITY);

        AssetManager& operator=(const AssetManager& ref);
    };
}

#include "assetmanager_impl.tpp"

#endif //JAGE_ASSET_MANAGER_HPP
