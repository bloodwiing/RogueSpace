#ifndef JAGE_ASSET_ABC_HPP
#define JAGE_ASSET_ABC_HPP

#include <memory>

#define JAGE_ASSET_BASE_PRIORITY 5

namespace jage::runtime::asset::abc {

    template<class T>
    class AssetABC
            : public std::enable_shared_from_this<AssetABC<T>> {
    public:
        typedef T AssetType;

        void queue();
        virtual void queue(int priority) = 0;

        AssetABC<T>& asAsset();
        T& asObject();
    };
}

#include "asset_abc_impl.tpp"

#endif //JAGE_ASSET_ABC_HPP
