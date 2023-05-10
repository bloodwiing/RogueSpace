#ifndef JAGE_ASSET_STREAM_HPP
#define JAGE_ASSET_STREAM_HPP

#include <string>
#include <map>
#include <queue>
#include <functional>
#include <ios>
#include <thread>
#include <memory>
#include <mutex>
#include <condition_variable>

#define JAGE_ASSET_STREAM_BASE_PRIORITY 5

namespace jage::runtime {

    class AssetStream {
    public:
        typedef std::function<void(std::shared_ptr<std::string> data)> textCallback;
        typedef std::function<void(uint8_t* data, size_t size)> binaryCallback;

        static AssetStream& getInstance();

        bool getCachedTextAsset(const std::string& filePath, const textCallback& callback);
        bool getCachedBinaryAsset(const std::string& filePath, const binaryCallback& callback);
        void saveToCache(const std::string& filePath, const std::shared_ptr<std::string>& data);

        void getTextAssetAsync(const std::string& filePath, const textCallback& callback, int priority = JAGE_ASSET_STREAM_BASE_PRIORITY);
        void getBinaryAssetAsync(const std::string& filePath, const binaryCallback& callback, int priority = JAGE_ASSET_STREAM_BASE_PRIORITY);

        void getTextAsset(const std::string& filePath, const textCallback& callback);
        void getBinaryAsset(const std::string& filePath, const binaryCallback& callback);

        static void shutdown();
        static void asyncLoop();

        /// \brief          Reads the file from the path in the filename and returns the data of it
        /// \details        Will automatically convert Windows style line endings (\r\n) to UNIX style (\n) if the mode is not std::ios::binary
        /// \param filename The path of the file to read
        /// \param mode     The mode which to use when reading the file. Can be used along with std::ios::binary, but then
        ///                 the resulting std::string is better to be converted to a C string
        /// \return         The string representing the file contents
        /// \see            unixifyLineEndings
        static std::shared_ptr<std::string> readFileContents(std::string filePath, std::ios::openmode mode = std::ios::in);
        /// \brief          Finds and creates a string representing the current process' directory
        /// \details        Useful for looking up files relative to the executable and not working directory
        /// \return         The string path to the directory
        static std::string getProcessDirectory();
        static void makePathAbsolute(std::string& path);
        /// \brief          Converts Windows style \r\n line endings to UNIX style \n new line endings
        static void unixifyLineEndings(std::string& text);
        static std::string getFileDirectory(const std::string& filePath);

    private:
        AssetStream();

        std::thread m_thread;

        struct AssetQuery {
            std::string filePath;
            textCallback callback;
            std::ios::openmode mode = std::ios::in;
            int priority;

            bool operator<(const AssetQuery& other) const;
        };

        bool m_active = true;

        static AssetStream* m_instance;

        std::priority_queue<AssetQuery, std::vector<AssetQuery>, std::less<>> m_assetQueue;
        std::mutex m_assetQueueMutex;
        std::condition_variable m_assetQueueCV;
        std::map<const std::string, std::shared_ptr<std::string>> m_cachedAssets;
        std::mutex m_cachedAssetsMutex;

        static std::shared_ptr<std::string> asyncReadFileContents(std::string filePath, std::ios::openmode mode = std::ios::in);

        bool getNextQuery(AssetQuery& entry);
    };
}

#endif //JAGE_ASSET_STREAM_HPP
