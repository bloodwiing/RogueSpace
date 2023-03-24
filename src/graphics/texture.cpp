#include "graphics/texture.h"
#include <stb/stb_image.h>

Texture::Texture(const char* filename, GLenum texture_type, GLuint slot, GLenum format, GLenum pixel_type)
    : slot(slot)
{
    stbi_set_flip_vertically_on_load(true);

    uint8_t* bytes = stbi_load(filename, &width, &height, &channels, 0);

    glGenTextures(1, &ID);

    bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(texture_type, 0, GL_RGBA, width, height, 0, format, pixel_type, bytes);
    glGenerateMipmap(texture_type);

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

void Texture::assign(Shader &shader, const char *uniform, GLint unit) {
    if (!shader.isErrored()) {
        GLint uniformID = shader.getUniform(uniform);
        shader.activate();
        glUniform1i(uniformID, unit);
    }
}
