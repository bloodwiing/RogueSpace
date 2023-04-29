#include "graphics/texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <stdexcept>

Graphics::Texture::Texture(const char* fileName)
    : m_ID()
    , m_width()
    , m_height()
    , m_channels()
    , m_fileName(fileName)
    , m_loaded(false)
    , m_data(nullptr)
{

}

std::shared_ptr<Graphics::Texture> Graphics::Texture::create(const char* fileName) {
    return std::make_shared<Texture>(fileName);
}

void Graphics::Texture::queue() {
    Engine::AssetStream::getBinaryAsset(
            m_fileName,
            [self = shared_from_this()](const uint8_t* data, size_t size){
                self->m_data = stbi_load_from_memory((const stbi_uc*)data, (int)size, &self->m_width, &self->m_height, &self->m_channels, 0);
            });
}

void Graphics::Texture::loadIfReady() {
    if (m_data && !m_loaded)
        loadFromSTBBytes(this->m_data);
}

void Graphics::Texture::loadFromSTBBytes(stbi_uc* data) {
    glGenTextures(1, &m_ID);

    bind(0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    switch (m_channels) {
        case 4:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            break;
        case 3:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            break;
        case 2:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RG, GL_UNSIGNED_BYTE, data);
            break;
        case 1:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
            break;
        default:
            throw std::invalid_argument("Failed to recognise texture channel count");
    }
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    unbind();

    m_loaded = true;
    m_data = nullptr;
}

bool Graphics::Texture::isLoaded() const {
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
