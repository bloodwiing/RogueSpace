#ifndef ASSET_STREAM_CLASS_H
#define ASSET_STREAM_CLASS_H

#include <string>
#include <map>
#include <queue>
#include <functional>
#include <ios>
#include <thread>
#include <memory>

namespace Engine {

    class AssetStream {
    public:
        typedef std::function<void(std::shared_ptr<const std::string> data)> textCallback;
        typedef std::function<void(const uint8_t* data, size_t size)> binaryCallback;

        static AssetStream& getInstance();
        static void getTextAsset(const std::string& filePath, const textCallback& callback);
        static void getBinaryAsset(const std::string& filePath, const binaryCallback& callback);

        static void shutdown();
        static void asyncLoop();

    private:
        AssetStream();

        std::thread m_thread;

        struct AssetQueueEntry {
            const std::string filePath;
            const textCallback callback;
            std::ios::openmode mode;
        };

        bool m_active = true;

        static AssetStream* m_singleton;

        std::queue<AssetQueueEntry> m_assetQueue;
        std::map<const std::string, std::shared_ptr<const std::string> > m_cachedAssets;

        static std::shared_ptr<const std::string> asyncReadFileContents(std::string filePath, std::ios::openmode mode = std::ios::in);
    };
}

#endif //ASSET_STREAM_CLASS_H
