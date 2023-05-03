#include "engine/assetstream.hpp"

#include <stdexcept>
#include <thread>
#include <fstream>
#include <filesystem>

using std::ios;
using std::lock_guard;
using std::mutex;
using std::shared_ptr;
using std::string;

namespace filesystem = std::filesystem;

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
    lock_guard<mutex> lock(m_cachedAssetsMutex);
    if (getInstance().m_cachedAssets.find(filePath) != getInstance().m_cachedAssets.end()) {
        callback(getInstance().m_cachedAssets.at(filePath));
        return true;
    }
    return false;
}

bool Engine::AssetStream::getCachedBinaryAsset(const std::string &filePath, const AssetStream::binaryCallback &callback) {
    lock_guard<mutex> lock(m_cachedAssetsMutex);
    if (getInstance().m_cachedAssets.find(filePath) != getInstance().m_cachedAssets.end()) {
        auto asset = getInstance().m_cachedAssets.at(filePath);
        callback((uint8_t*)asset->c_str(), asset->length());
        return true;
    }
    return false;
}

void Engine::AssetStream::saveToCache(const std::string &filePath, const std::shared_ptr<std::string>& data) {
    lock_guard<mutex> lock(m_cachedAssetsMutex);
    getInstance().m_cachedAssets[filePath] = data;
}

void Engine::AssetStream::getTextAssetAsync(const std::string& filePath, const AssetStream::textCallback& callback, int priority /* = ASSET_STREAM_BASE_PRIORITY */) {
    if (getCachedTextAsset(filePath, callback))
        return;

    lock_guard<mutex> lock(m_assetQueueMutex);
    getInstance().m_assetQueue.emplace((AssetQuery){
        .filePath = filePath,
        .callback = callback,
        .mode = ios::in,
        .priority = priority
    });
}

void Engine::AssetStream::getBinaryAssetAsync(const std::string& filePath, const AssetStream::binaryCallback& callback, int priority /* = ASSET_STREAM_BASE_PRIORITY */) {
    if (getCachedBinaryAsset(filePath, callback))
        return;

    lock_guard<mutex> lock(m_assetQueueMutex);
    getInstance().m_assetQueue.emplace((AssetQuery){
        .filePath = filePath,
        .callback = [callback](const shared_ptr<string>& data) { callback((uint8_t*)data->c_str(), data->length()); },
        .mode = ios::in | ios::binary,
        .priority = priority
    });
}

void Engine::AssetStream::getTextAsset(const std::string &filePath, const Engine::AssetStream::textCallback &callback) {
    if (getCachedTextAsset(filePath, callback))
        return;

    shared_ptr<string> result = readFileContents(filePath);
    saveToCache(filePath, result);
    callback(result);
}

void Engine::AssetStream::getBinaryAsset(const std::string &filePath, const Engine::AssetStream::binaryCallback &callback) {
    if (getCachedBinaryAsset(filePath, callback))
        return;

    shared_ptr<string> result = readFileContents(filePath);
    saveToCache(filePath, result);
    callback((uint8_t*)result->c_str(), result->length());
}

void Engine::AssetStream::shutdown() {
    getInstance().m_active = false;
}

void Engine::AssetStream::asyncLoop() {
    while (getInstance().m_active) {
        AssetQuery entry;
        if (!getInstance().getNextQuery(entry)) {
            std::this_thread::yield();
            continue;
        }

        if (getInstance().getCachedTextAsset(entry.filePath, entry.callback))
            continue;

        shared_ptr<string> result = asyncReadFileContents(entry.filePath, entry.mode);
        getInstance().saveToCache(entry.filePath, result);
        entry.callback(result);
    }
}

std::shared_ptr<std::string> Engine::AssetStream::asyncReadFileContents(std::string filePath, ios::openmode mode) {
    makePathAbsolute(filePath);

    filesystem::path p(filePath);
    if (!filesystem::exists(p))
        return std::make_shared<string>();
    auto size = (long long)filesystem::file_size(p);

    std::ifstream stream(filePath, mode | ios::binary);

    const long long chunkSize = 0xF000;
    long long index = 0;

    shared_ptr<string> result = std::make_shared<string>();
    result->resize(size, '\0');

    while (!stream.eof() and getInstance().m_active) {
        stream.read(&(*result)[index], chunkSize > size - index + 1 ? size - index + 1 : chunkSize);
        index += stream.gcount();
        std::this_thread::yield();
    }

    if (!(mode & ios::binary)) {
        result->back() = '\0';
        unixifyLineEndings(*result);
    }

    return result;
}

std::shared_ptr<std::string> Engine::AssetStream::readFileContents(std::string filePath, std::ios::openmode mode) {
    makePathAbsolute(filePath);

    filesystem::path p(filePath);
    if (!filesystem::exists(p))
        return std::make_shared<std::string>();
    auto size = (long long)filesystem::file_size(p);
    p.clear();

    shared_ptr<string> result = std::make_shared<string>();
    result->resize(size, '\0');

    std::ifstream stream(filePath, mode | ios::binary);

    stream.read(&(*result)[0], size);

    if (!(mode & ios::binary)) {
        unixifyLineEndings(*result);
    }

    return result;
}

#define MAX_PATH 2048
#if _WIN32
#include <windows.h>
std::string Engine::AssetStream::getProcessDirectory() {
    char path[MAX_PATH];
    string res(path, GetModuleFileName(nullptr, path, MAX_PATH));
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
    if (path.find(':') == string::npos)
        path = getProcessDirectory() + path;
#elif __unix__
    if (path[0] != '/')
        path = getProcessDirectory() + path;
#endif
}

void Engine::AssetStream::unixifyLineEndings(std::string &text) {
    string::size_type pos = 0;
    while ((pos = text.find("\r\n", pos)) != string::npos )
        text.erase(pos, 1);
}

bool Engine::AssetStream::getNextQuery(Engine::AssetStream::AssetQuery& entry) {
    lock_guard<mutex> lock(m_assetQueueMutex);
    if (m_assetQueue.empty())
        return false;
    entry = m_assetQueue.top();
    m_assetQueue.pop();
    return true;
}

std::string Engine::AssetStream::getFileDirectory(const std::string &filePath) {
    return filePath.substr(0, filePath.find_last_of('/') + 1);
}

bool Engine::AssetStream::AssetQuery::operator<(const Engine::AssetStream::AssetQuery &other) const {
    return priority < other.priority;
}
