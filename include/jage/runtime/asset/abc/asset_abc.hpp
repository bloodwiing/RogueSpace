#ifndef JAGE_ASSET_ABC_HPP
#define JAGE_ASSET_ABC_HPP

#include <memory>
#include <atomic>

#define JAGE_ASSET_BASE_PRIORITY 5

namespace jage::runtime::asset::abc {

    template<class T>
    class AssetABC
            : public std::enable_shared_from_this<AssetABC<T>> {
    public:
        typedef T AssetType;

        void enqueue();
        virtual void enqueue(int priority);
        virtual void prepare();

        [[nodiscard]] virtual bool isProcessed() const;
        [[nodiscard]] virtual bool isPrepared() const;
        [[nodiscard]] virtual bool isReady() const;

        [[nodiscard]] AssetABC<T>& asAsset();
        [[nodiscard]] T& asObject();

    protected:
        virtual void onQueue(int priority) = 0;
        virtual void onPrepare() {};

        void markProcessed();

    private:
        std::atomic<bool> m_processed = false;
        std::atomic<bool> m_prepared = false;
    };
}

#include "asset_abc_impl.tpp"

#endif //JAGE_ASSET_ABC_HPP
