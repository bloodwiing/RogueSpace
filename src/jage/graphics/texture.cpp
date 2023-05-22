#include "jage/graphics/texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <stdexcept>
#include <utility>
#include <yaml-cpp/yaml.h>
#include <GL/glext.h>

using jage::graphics::Texture;
using jage::runtime::asset::AssetStream;

std::shared_ptr<Texture> Texture::defaultTexture = std::shared_ptr<Texture>();

Texture::Texture(const std::string& filePath)
    : m_metadata(YAML::LoadFile(filePath + ".meta"))
    , m_activeLOD(-1)
    , m_main(LOD::create(filePath, m_metadata, this))
{
    std::string directory = AssetStream::getFileDirectory(filePath);

    YAML::Node LODs = m_metadata["lod"];
    if (LODs.IsDefined() && LODs.IsSequence()) {
        for (auto iter = LODs.begin(); iter != LODs.end(); ++iter) {
            m_levels.push_back(LOD::create(directory + (*iter)["file"].as<std::string>(), *iter, this));
        }
    }
}

std::shared_ptr<Texture> Texture::create(const std::string& fileName) {
    return std::make_shared<Texture>(fileName);
}

Texture::Texture(GLubyte *bytes, int width, int height, int channels)
    : m_metadata()
    , m_activeLOD(0)
    , m_main(LOD::create(bytes, width, height, channels, 0, 100, this))
{

}

std::shared_ptr<Texture> Texture::create(GLubyte *bytes, int width, int height, int channels) {
    return std::make_shared<Texture>(bytes, width, height, channels);
}

void Texture::createDefaultTexture(GLubyte *bytes, int width, int height, int channels) {
    defaultTexture = create(bytes, width, height, channels);
}

void Texture::clearDefaultTexture() {
    defaultTexture.reset();
    defaultTexture = nullptr;
}

std::shared_ptr<Texture> Texture::getDefaultTexture() {
    return defaultTexture;
}

void Texture::onQueue(int priority) {
    m_main->enqueue(priority);
    for (auto& level : m_levels) {
        level->enqueue(priority);
    }
}

void Texture::onPrepare() {
    std::shared_ptr<LOD> LOD;
    if (!getActiveLOD(LOD))
        return;

    LOD->prepare();
}

bool Texture::isProcessed() const {
    std::shared_ptr<LOD> LOD;
    if (!getActiveLOD(LOD))
        return false;

    return LOD->isProcessed();
}

bool Texture::isPrepared() const {
    std::shared_ptr<LOD> LOD;
    if (!getActiveLOD(LOD))
        return false;

    return LOD->isPrepared();
}

bool Texture::isReady() const {
    std::shared_ptr<LOD> LOD;
    if (!getActiveLOD(LOD))
        return false;

    return LOD->isReady();
}

void Texture::bind(GLint unit) const {
    std::shared_ptr<LOD> LOD;
    if (!getActiveLOD(LOD))
        return;

    return LOD->bind(unit);
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::destroy() const {
    m_main->destroy();
    for (auto& level : m_levels) {
        level->destroy();
    }
}

GLuint Texture::getID() const {
    std::shared_ptr<LOD> LOD;
    if (!getActiveLOD(LOD))
        return 0;

    return LOD->getID();
}

void Texture::assign(Shader &shader, const char *uniform, GLint unit) const {
    if (!shader.isErrored()) {
        GLint uniformID = shader.getUniform(uniform);
        shader.activate();
        glUniform1i(uniformID, unit);
    }
}

bool Texture::getActiveLOD(std::shared_ptr<LOD> &LOD) const {
    if (m_activeLOD == -1)
        return false;

    if (m_activeLOD == 0)
        LOD = m_main;
    else
        LOD = m_levels[m_activeLOD - 1];

    return true;
}

bool Texture::setActiveLOD(int level) {
    ++m_LODsLoaded;

    if (m_LODsLoaded == m_levels.size() + 1) {
        for (auto& lod : m_levels) {
            lod->destroy();
        }
        m_levels.clear();
    }

    if (level == 0 or (level > m_activeLOD && m_activeLOD != 0)) {
        m_activeLOD = level;
        return true;
    }

    return false;
}

Texture::LOD::LOD(std::string fileName, const YAML::Node &node, Texture* container)
    : m_ID()
    , m_PBO()
    , m_fileName(std::move(fileName))
    , m_width(node["width"].as<int>())
    , m_height(node["height"].as<int>())
    , m_channels(node["channels"].as<int>())
    , m_level(node["level"].as<int>())
    , m_priority(node["priority"].as<int>())
    , m_container(container)
{
    glGenBuffers(1, &m_PBO);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_PBO);
    glBufferData(GL_PIXEL_UNPACK_BUFFER, m_width * m_height * m_channels, nullptr, GL_STREAM_DRAW);
    glBufferStorage(GL_PIXEL_UNPACK_BUFFER, m_width * m_height * m_channels, nullptr, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT);

    m_buffer = glMapBufferRange(GL_PIXEL_UNPACK_BUFFER, 0, m_width * m_height * m_channels, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_FLUSH_EXPLICIT_BIT);

    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

    glGenTextures(1, &m_ID);

    bind(0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RED, GL_UNSIGNED_BYTE, nullptr);
}

std::shared_ptr<Texture::LOD> Texture::LOD::create(const std::string &fileName, const YAML::Node &node, Texture* container) {
    return std::make_shared<LOD>(fileName, node, container);
}

Texture::LOD::LOD(GLubyte *bytes, int width, int height, int channels, int level, int priority, Texture *container)
    : m_ID()
    , m_PBO()
    , m_width(width)
    , m_height(height)
    , m_channels(channels)
    , m_buffer(nullptr)
    , m_level(level)
    , m_container(container)
    , m_priority(priority)
    , m_fileName()
{
    glGenTextures(1, &m_ID);

    bind(0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, getChannelEnumFromCount(m_channels), GL_UNSIGNED_BYTE, bytes);

    unbind();

    markProcessed();
}

std::shared_ptr<Texture::LOD>
Texture::LOD::create(GLubyte *bytes, int width, int height, int channels, int level, int priority, Texture *container) {
    return std::make_shared<LOD>(bytes, width, height, channels, level, priority, container);
}

Texture::LOD::~LOD() {
    glDeleteTextures(1, &m_ID);
    if (m_PBO != 0) {
        glDeleteBuffers(1, &m_PBO);
    }
}

void Texture::LOD::onQueue(int priority) {
    AssetStream::getInstance().getBinaryAssetAsync(
            m_fileName,
            [self = shared_from_this()](const uint8_t* data, size_t size){
                Texture::LOD& lod = self->asObject();

                int height, width, channels;
                stbi_uc* finalData = stbi_load_from_memory((const stbi_uc*)data, (int)size, &width, &height, &channels, 0);
                memcpy(lod.m_buffer, finalData, width * height * channels);
                stbi_image_free(finalData);
                lod.markProcessed();

                lod.m_container->setActiveLOD(lod.m_level);
            }, priority + m_priority);
}

void Texture::LOD::onPrepare() {
    bind(0);

    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_PBO);
    glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
    m_buffer = nullptr;

    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, getChannelEnumFromCount(m_channels), GL_UNSIGNED_BYTE, nullptr);

    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

    unbind();
}

void Texture::LOD::bind(GLint unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture::LOD::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::LOD::destroy() const {
    glDeleteBuffers(1, &m_ID);
    glDeleteBuffers(1, &m_PBO);
}

GLenum Texture::LOD::getChannelEnumFromCount(int channels) {
    switch (channels) {
        case 4:
            return GL_RGBA;
        case 3:
            return GL_RGB;
        case 2:
            return GL_RG;
        case 1:
            return GL_RED;
        default:
            throw std::invalid_argument("Failed to recognise texture channel count");
    }
}

GLuint Texture::LOD::getID() const {
    return m_ID;
}

int Texture::LOD::getLevel() const {
    return m_level;
}
