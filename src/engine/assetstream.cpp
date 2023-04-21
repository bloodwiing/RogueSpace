#include "engine/assetstream.h"

#include <stdexcept>
#include <thread>
#include <fstream>

using std::ios;

AssetStream* AssetStream::m_singleton = nullptr;

AssetStream::AssetStream()
    : m_thread(asyncLoop)
{ }

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

void AssetStream::asyncLoop() {
    while (getInstance().m_active) {
        if (getInstance().m_assetQueue.empty()) {
            std::this_thread::yield();
            continue;
        }

        AssetQueueEntry entry = getInstance().m_assetQueue.front();
        getInstance().m_assetQueue.pop();
        entry.callback(asyncReadFileContents(entry.filePath, entry.mode));
    }
}

std::string AssetStream::asyncReadFileContents(const std::string &filePath, ios::openmode mode) {
    std::ifstream stream(filePath, mode);

    const size_t chunkSize = 1024;
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
    }

    result.resize(stream.gcount());

    return result;
}
