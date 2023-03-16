#include "graphics/texture.h"

Texture::Texture(const char *file_name, int force_channels /* = 0 */, GLuint reuse_texture_id /* = 0 */, int flags /* = SOIL_FLAG_INVERT_Y */) {
    ID = SOIL_load_OGL_texture(file_name, force_channels, reuse_texture_id, flags);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void Texture::bind() {
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
