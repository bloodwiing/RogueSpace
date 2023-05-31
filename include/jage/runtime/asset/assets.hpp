#ifndef JAGE_ASSETS_HPP
#define JAGE_ASSETS_HPP

#include "assetmanager.hpp"
#include "assetstream.hpp"

namespace jage::runtime::asset {

    class Assets
            : public AssetManager::Types
    {
    public:
        template<class T>
        static std::shared_ptr<T> get(std::string filePath, int priority = JAGE_ASSET_BASE_PRIORITY);

        template<class T>
        static std::shared_ptr<T> get();
    };
}

#include "assets_impl.tpp"

#endif //JAGE_ASSETS_HPP
