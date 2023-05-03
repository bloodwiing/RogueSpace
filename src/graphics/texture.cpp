#include "graphics/texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <stdexcept>
#include <utility>

#include <yaml-cpp/yaml.h>
#include <GL/glext.h>

std::shared_ptr<Graphics::Texture> Graphics::Texture::defaultTexture = std::shared_ptr<Graphics::Texture>();

Graphics::Texture::Texture(const std::string& filePath)
    : m_metadata(YAML::LoadFile(filePath + ".meta"))
    , m_activeLOD(-1)
    , m_main(LOD::create(filePath, m_metadata, this))
{
    std::string directory = Engine::AssetStream::getFileDirectory(filePath);

    YAML::Node LODs = m_metadata["lod"];
    if (LODs.IsDefined() && LODs.IsSequence()) {
        for (auto iter = LODs.begin(); iter != LODs.end(); ++iter) {
            m_levels.push_back(LOD::create(directory + (*iter)["file"].as<std::string>(), *iter, this));
        }
    }
}

std::shared_ptr<Graphics::Texture> Graphics::Texture::create(const std::string& fileName) {
    return std::make_shared<Texture>(fileName);
}

Graphics::Texture::Texture(GLubyte *bytes, int width, int height, int channels, GLint ID)
    : m_metadata()
    , m_activeLOD(0)
    , m_main(LOD::create(bytes, width, height, channels, 0, 100, ID, this))
{

}

std::shared_ptr<Graphics::Texture> Graphics::Texture::create(GLubyte *bytes, int width, int height, int channels, GLint ID) {
    return std::make_shared<Texture>(bytes, width, height, channels, ID);
}

void Graphics::Texture::createDefaultTexture(GLubyte *bytes, int width, int height, int channels, GLint ID) {
    defaultTexture = create(bytes, width, height, channels, ID);
}

std::shared_ptr<Graphics::Texture> Graphics::Texture::getDefaultTexture() {
    return defaultTexture;
}

void Graphics::Texture::queue(int priority /* = ASSET_STREAM_BASE_PRIORITY */) {
    m_main->queue(priority);
    for (auto& level : m_levels) {
        level->queue(priority);
    }
}

bool Graphics::Texture::isReady() {
    std::shared_ptr<LOD> LOD;
    if (!getActiveLOD(LOD))
        return false;

    return LOD->isReady();
}

void Graphics::Texture::bind(GLint unit) const {
    std::shared_ptr<LOD> LOD;
    if (!getActiveLOD(LOD))
        return;

    return LOD->bind(unit);
}

void Graphics::Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Graphics::Texture::destroy() const {
    m_main->destroy();
    for (auto& level : m_levels) {
        level->destroy();
    }
}

GLuint Graphics::Texture::getID() const {
    std::shared_ptr<LOD> LOD;
    if (!getActiveLOD(LOD))
        return 0;

    return LOD->getID();
}

void Graphics::Texture::assign(Shader &shader, const char *uniform, GLint unit) const {
    if (!shader.isErrored()) {
        GLint uniformID = shader.getUniform(uniform);
        shader.activate();
        glUniform1i(uniformID, unit);
    }
}

bool Graphics::Texture::getActiveLOD(std::shared_ptr<LOD> &LOD) const {
    if (m_activeLOD == -1)
        return false;

    if (m_activeLOD == 0)
        LOD = m_main;
    else
        LOD = m_levels[m_activeLOD - 1];

    return true;
}

bool Graphics::Texture::setActiveLOD(int level) {
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

Graphics::Texture::LOD::LOD(std::string fileName, const YAML::Node &node, Texture* container)
    : m_ID()
    , m_PBO()
    , m_fileName(std::move(fileName))
    , m_width(node["width"].as<int>())
    , m_height(node["height"].as<int>())
    , m_channels(node["channels"].as<int>())
    , m_level(node["level"].as<int>())
    , m_priority(node["priority"].as<int>())
    , m_ready(false)
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

std::shared_ptr<Graphics::Texture::LOD> Graphics::Texture::LOD::create(const std::string &fileName, const YAML::Node &node, Texture* container) {
    return std::make_shared<LOD>(fileName, node, container);
}

Graphics::Texture::LOD::LOD(GLubyte *bytes, int width, int height, int channels, int level, int priority, GLint ID, Graphics::Texture *container)
    : m_ID(ID)
    , m_PBO()
    , m_width(width)
    , m_height(height)
    , m_channels(channels)
    , m_buffer(bytes)
    , m_level(level)
    , m_container(container)
    , m_priority(priority)
    , m_fileName()
    , m_ready(false)
{
    bind(0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, m_channels, GL_UNSIGNED_BYTE, m_buffer);

    unbind();
}

std::shared_ptr<Graphics::Texture::LOD>
Graphics::Texture::LOD::create(GLubyte *bytes, int width, int height, int channels, int level, int priority, GLint ID, Graphics::Texture *container) {
    return std::make_shared<LOD>(bytes, width, height, channels, level, priority, ID, container);
}

void Graphics::Texture::LOD::queue(int priority /* = ASSET_STREAM_BASE_PRIORITY */) {
    if (m_ready)
        return;
    Engine::AssetStream::getInstance().getBinaryAssetAsync(
            m_fileName,
            [self = shared_from_this()](const uint8_t* data, size_t size){
                int height, width, channels;
                stbi_uc* finalData = stbi_load_from_memory((const stbi_uc*)data, (int)size, &width, &height, &channels, 0);
                memcpy(self->m_buffer, finalData, width * height * channels);
                stbi_image_free(finalData);
                self->m_ready = true;

                self->m_container->setActiveLOD(self->m_level);
            }, priority + m_priority);
}

bool Graphics::Texture::LOD::isReady() {
    if (m_ready and m_buffer != nullptr) {
        bind(0);

        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_PBO);
        glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
        m_buffer = nullptr;

        switch (m_channels) {
            case 4:
                glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
                break;
            case 3:
                glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
                break;
            case 2:
                glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, GL_RG, GL_UNSIGNED_BYTE, nullptr);
                break;
            case 1:
                glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, GL_RED, GL_UNSIGNED_BYTE, nullptr);
                break;
            default:
                throw std::invalid_argument("Failed to recognise texture channel count");
        }

        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

        unbind();
    }
    return m_ready;
}

void Graphics::Texture::LOD::bind(GLint unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Graphics::Texture::LOD::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Graphics::Texture::LOD::destroy() const {
    glDeleteBuffers(1, &m_ID);
    glDeleteBuffers(1, &m_PBO);
}

GLuint Graphics::Texture::LOD::getID() const {
    return m_ID;
}

int Graphics::Texture::LOD::getLevel() const {
    return m_level;
}
