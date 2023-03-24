#include "graphics/texture.h"
#include <stb/stb_image.h>

Texture::Texture(const char* filename, TextureType type, GLuint slot, GLenum format, GLenum pixel_type)
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

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, pixel_type, bytes);
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
