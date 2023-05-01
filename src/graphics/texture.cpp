#include "graphics/texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <stdexcept>
#include <utility>

#include <yaml-cpp/yaml.h>
#include <GL/glext.h>

Graphics::Texture::Texture(std::string fileName)
    : m_ID()
    , m_PBO()
    , m_metadata(YAML::LoadFile(fileName + ".meta"))
    , m_fileName(std::move(fileName))
    , m_width(m_metadata["width"].as<int>())
    , m_height(m_metadata["height"].as<int>())
    , m_channels(m_metadata["channels"].as<int>())
    , m_loaded(false)
{
    glGenBuffers(1, &m_PBO);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_PBO);
    glBufferData(GL_PIXEL_UNPACK_BUFFER, m_width * m_height * m_channels, nullptr, GL_STREAM_DRAW);
    glBufferStorage(GL_PIXEL_UNPACK_BUFFER, m_width * m_height * m_channels, nullptr, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);

    m_buffer = glMapBufferRange(GL_PIXEL_UNPACK_BUFFER, 0, m_width * m_height * m_channels, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT | GL_MAP_FLUSH_EXPLICIT_BIT);

    auto error = glGetError();

    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

    glGenTextures(1, &m_ID);

    bind(0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RED, GL_UNSIGNED_BYTE, nullptr);
}

std::shared_ptr<Graphics::Texture> Graphics::Texture::create(const std::string& fileName) {
    return std::make_shared<Texture>(fileName);
}

void Graphics::Texture::queue() {
    Engine::AssetStream::getBinaryAsset(
            m_fileName,
            [self = shared_from_this()](const uint8_t* data, size_t size){
                int height, width, channels;
                stbi_uc* finalData = stbi_load_from_memory((const stbi_uc*)data, (int)size, &width, &height, &channels, 0);
                memcpy(self->m_buffer, finalData, width * height * channels);
                stbi_image_free(finalData);
                self->m_loaded = true;
            });
}

bool Graphics::Texture::isLoaded() {
    if (m_loaded and m_buffer != nullptr) {
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_PBO);
        glFlushMappedBufferRange(GL_PIXEL_UNPACK_BUFFER, 0, m_width * m_height * m_channels);

        auto error = glGetError();

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
        m_buffer = nullptr;

        unbind();
    }
    return m_loaded;
}

void Graphics::Texture::bind(GLint unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Graphics::Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Graphics::Texture::destroy() const {
    glDeleteTextures(1, &m_ID);
}

GLuint Graphics::Texture::getID() const {
    return m_ID;
}

void Graphics::Texture::assign(Shader &shader, const char *uniform, GLint unit) const {
    if (!shader.isErrored()) {
        GLint uniformID = shader.getUniform(uniform);
        shader.activate();
        glUniform1i(uniformID, unit);
    }
}
