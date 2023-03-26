#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include "shader.h"

enum TextureType {
    TEX_DIFFUSE,
    TEX_SPECULAR
};

class Texture {
public:
    Texture() = default;
    explicit Texture(const char* filename, TextureType type, GLuint slot);
    Texture(const Texture& original) = default;

    void assign(Shader& shader, const char* uniform, GLint unit);
    void bind();
    void unbind();
    void destroy();

    GLuint getID();
    TextureType getTextureType();

private:
    GLuint ID;
    GLuint slot;

    TextureType type;

    int width, height, channels;
};

#endif //TEXTURE_CLASS_H
