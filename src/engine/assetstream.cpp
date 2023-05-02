#include "engine/assetstream.hpp"

#include <stdexcept>
#include <thread>
#include <fstream>

using std::ios;

Engine::AssetStream* Engine::AssetStream::m_instance = nullptr;

Engine::AssetStream::AssetStream()
    : m_thread(asyncLoop)
{ }

Engine::AssetStream &Engine::AssetStream::getInstance() {
    if (m_instance == nullptr)
        m_instance = new AssetStream();
    return *m_instance;
}

bool Engine::AssetStream::getCachedTextAsset(const std::string &filePath, const AssetStream::textCallback &callback) {
    std::lock_guard<std::mutex> lock(m_cachedAssetsMutex);
    if (getInstance().m_cachedAssets.find(filePath) != getInstance().m_cachedAssets.end()) {
        callback(getInstance().m_cachedAssets.at(filePath));
        return true;
    }
    return false;
}

bool Engine::AssetStream::getCachedBinaryAsset(const std::string &filePath, const AssetStream::binaryCallback &callback) {
    std::lock_guard<std::mutex> lock(m_cachedAssetsMutex);
    if (getInstance().m_cachedAssets.find(filePath) != getInstance().m_cachedAssets.end()) {
        auto asset = getInstance().m_cachedAssets.at(filePath);
        callback((const uint8_t*)asset->c_str(), asset->length());
        return true;
    }
    return false;
}

void Engine::AssetStream::saveToCache(const std::string &filePath, const std::shared_ptr<const std::string>& data) {
    std::lock_guard<std::mutex> lock(m_cachedAssetsMutex);
    getInstance().m_cachedAssets[filePath] = data;
}

void Engine::AssetStream::getTextAssetAsync(const std::string& filePath, const AssetStream::textCallback& callback) {
    if (getCachedTextAsset(filePath, callback))
        return;

    std::lock_guard<std::mutex> lock(m_assetQueueMutex);
    getInstance().m_assetQueue.emplace((AssetQueueEntry){
        .filePath = filePath,
        .callback = callback,
        .mode = ios::in
    });
}

void Engine::AssetStream::getBinaryAssetAsync(const std::string& filePath, const AssetStream::binaryCallback& callback) {
    if (getCachedBinaryAsset(filePath, callback))
        return;

    std::lock_guard<std::mutex> lock(m_assetQueueMutex);
    getInstance().m_assetQueue.emplace((AssetQueueEntry){
        .filePath = filePath,
        .callback = [callback](const std::shared_ptr<const std::string>& data) { callback((const uint8_t*)data->c_str(), data->length()); },
        .mode = ios::in | ios::binary
    });
}

void Engine::AssetStream::getTextAsset(const std::string &filePath, const Engine::AssetStream::textCallback &callback) {
    if (getCachedTextAsset(filePath, callback))
        return;

    const std::shared_ptr<const std::string> result = readFileContents(filePath);
    saveToCache(filePath, result);
    callback(result);
}

void Engine::AssetStream::getBinaryAsset(const std::string &filePath, const Engine::AssetStream::binaryCallback &callback) {
    if (getCachedBinaryAsset(filePath, callback))
        return;

    const std::shared_ptr<const std::string> result = readFileContents(filePath);
    saveToCache(filePath, result);
    callback((const uint8_t*)result->c_str(), result->length());
}

void Engine::AssetStream::shutdown() {
    getInstance().m_active = false;
}

void Engine::AssetStream::asyncLoop() {
    while (getInstance().m_active) {
        AssetQueueEntry entry;
        if (!getInstance().getNextQuery(entry)) {
            std::this_thread::yield();
            continue;
        }

        if (getInstance().getCachedTextAsset(entry.filePath, entry.callback))
            continue;

        const std::shared_ptr<const std::string> result = asyncReadFileContents(entry.filePath, entry.mode);
        getInstance().saveToCache(entry.filePath, result);
        entry.callback(result);
    }
}

std::shared_ptr<const std::string> Engine::AssetStream::asyncReadFileContents(std::string filePath, ios::openmode mode) {
    makePathAbsolute(filePath);

    std::ifstream stream(filePath, mode);

    const size_t chunkSize = 1048576 << 8;
    size_t reservedSpace = chunkSize * 8;
    size_t index = 0;

    std::string result(reservedSpace, '\0');

    while (!stream.eof() and getInstance().m_active) {
        if (index >= reservedSpace) {
            reservedSpace <<= 1;
            result.resize(reservedSpace);
        }
        stream.read(&result[index], chunkSize);
        index += stream.gcount();
        std::this_thread::yield();
    }

    result.resize(index);

    if (!(mode & std::ios::binary))
        unixifyLineEndings(result);

    return std::make_shared<const std::string>(result.begin(), result.end());
}

std::shared_ptr<const std::string> Engine::AssetStream::readFileContents(std::string filePath, std::ios::openmode mode) {
    makePathAbsolute(filePath);

    std::ifstream stream(filePath, mode);

    stream.ignore(std::numeric_limits<std::streamsize>::max());
    auto size = stream.gcount();
    stream.seekg(0, std::ios::beg);
    stream.clear();

    std::string result(size, '\0');
    stream.read(&result[0], size);

    if (!(mode & std::ios::binary))
        unixifyLineEndings(result);

    return std::make_shared<const std::string>(result.begin(), result.end());
}

#define MAX_PATH 2048
#if _WIN32
#include <windows.h>
std::string Engine::AssetStream::getProcessDirectory() {
    char path[MAX_PATH];
    std::string res(path, GetModuleFileName(nullptr, path, MAX_PATH));
    std::replace(res.begin(), res.end(), '\\', '/');
    return res.substr(0, res.find_last_of('/') + 1);
}
#elif __unix__
#include <climits>
#include <unistd.h>
std::string Engine::AssetStream::getProcessDirectory() {
    char path[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", path, PATH_MAX);
    std::string res(path, (count > 0) ? count : 0);
    return res.substr(0, res.find_last_of('/') + 1);
}
#endif

void Engine::AssetStream::makePathAbsolute(std::string &path) {
#if _WIN32
    if (path.find(':') == std::string::npos)
        path = getProcessDirectory() + path;
#elif __unix__
    if (path[0] != '/')
        path = getProcessDirectory() + path;
#endif
}

void Engine::AssetStream::unixifyLineEndings(std::string &text) {
    std::string::size_type pos = 0;
    while ((pos = text.find("\r\n", pos)) != std::string::npos )
        text.erase(pos, 1);
}

bool Engine::AssetStream::getNextQuery(Engine::AssetStream::AssetQueueEntry& entry) {
    std::lock_guard<std::mutex> lock(m_assetQueueMutex);
    if (m_assetQueue.empty())
        return false;
    entry = m_assetQueue.front();
    m_assetQueue.pop();
    return true;
}
