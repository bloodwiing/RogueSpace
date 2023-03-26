#include "graphics/texture.h"
#include <stb/stb_image.h>
#include <stdexcept>

Texture::Texture(const char* filename, TextureType type, GLuint slot)
    : slot(slot)
    , type(type)
    , ID()
    , width()
    , height()
    , channels()
{
    stbi_set_flip_vertically_on_load(true);

    uint8_t* bytes = stbi_load(filename, &width, &height, &channels, 0);

    glGenTextures(1, &ID);

    bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    switch (channels) {
        case 4:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
            break;
        case 3:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
            break;
        case 2:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RG, GL_UNSIGNED_BYTE, bytes);
            break;
        case 1:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, bytes);
            break;
        default:
            throw std::invalid_argument("Failed to recognise texture channel count");
    }
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(bytes);

    unbind();
}

void Texture::bind() {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::destroy() {
    glDeleteTextures(1, &ID);
}

GLuint Texture::getID() {
    return ID;
}

TextureType Texture::getTextureType() {
    return type;
}

void Texture::assign(Shader &shader, const char *uniform, GLint unit) {
    if (!shader.isErrored()) {
        GLint uniformID = shader.getUniform(uniform);
        shader.activate();
        glUniform1i(uniformID, unit);
    }
}
