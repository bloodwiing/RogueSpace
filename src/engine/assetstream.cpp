#include "engine/assetstream.h"

#include <stdexcept>
#include <thread>
#include <fstream>

using std::ios;

AssetStream* AssetStream::m_singleton = nullptr;

AssetStream::AssetStream() = default;

AssetStream &AssetStream::getInstance() {
    if (m_singleton == nullptr)
        m_singleton = new AssetStream();
    return *m_singleton;
}

void AssetStream::getTextAsset(const std::string& filePath, const AssetStream::textCallback& callback) {
    if (getInstance().m_cachedAssets.find(filePath) != getInstance().m_cachedAssets.end()) {
        callback(getInstance().m_cachedAssets.at(filePath));
        return;
    }

    getInstance().m_assetQueue.emplace((AssetQueueEntry){
        .filePath = filePath,
        .callback = callback,
        .mode = ios::in
    });
}

void AssetStream::getBinaryAsset(const std::string& filePath, const AssetStream::binaryCallback& callback) {
    if (getInstance().m_cachedAssets.find(filePath) != getInstance().m_cachedAssets.end()) {
        callback((uint8_t*)getInstance().m_cachedAssets.at(filePath).c_str());
        return;
    }

    getInstance().m_assetQueue.emplace((AssetQueueEntry){
        .filePath = filePath,
        .callback = [&callback](const std::string& data) { callback((uint8_t*)data.c_str()); },
        .mode = ios::in | ios::binary
    });
}

void AssetStream::shutdown() {
    getInstance().m_active = false;
}

void readChunk() {

}

void AssetStream::asyncLoop() {
    while (getInstance().m_active) {
        if (getInstance().m_assetQueue.empty()) {
            std::this_thread::yield();
            continue;
        }

        AssetQueueEntry entry = getInstance().m_assetQueue.front();
        getInstance().m_assetQueue.pop();
        entry.callback(asyncReadFileContents(entry.filePath, entry.mode));

        std::this_thread::yield();
    }
}

std::string AssetStream::asyncReadFileContents(const std::string &filePath, ios::openmode mode) {
    std::ifstream stream(filePath, mode);

    stream.ignore(std::numeric_limits<std::streamsize>::max());
    auto size = stream.gcount();
    stream.seekg(0, ios::beg);
    stream.clear();

    std::string result(size, '\0');
    stream.read(&result[0], size);

    return result;
}
