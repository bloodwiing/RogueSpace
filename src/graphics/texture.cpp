#include "graphics/texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <stdexcept>

Texture::Texture(const char* filename)
    : m_ID()
    , m_width()
    , m_height()
    , m_channels()
{
    uint8_t* bytes = stbi_load(filename, &m_width, &m_height, &m_channels, 0);

    glGenTextures(1, &m_ID);

    bind(0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    switch (m_channels) {
        case 4:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
            break;
        case 3:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
            break;
        case 2:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RG, GL_UNSIGNED_BYTE, bytes);
            break;
        case 1:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RED, GL_UNSIGNED_BYTE, bytes);
            break;
        default:
            throw std::invalid_argument("Failed to recognise texture channel count");
    }
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(bytes);

    unbind();
}

void Texture::bind(GLint unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::destroy() const {
    glDeleteTextures(1, &m_ID);
}

GLuint Texture::getID() const {
    return m_ID;
}

void Texture::assign(Shader &shader, const char *uniform, GLint unit) const {
    if (!shader.isErrored()) {
        GLint uniformID = shader.getUniform(uniform);
        shader.activate();
        glUniform1i(uniformID, unit);
    }
}
