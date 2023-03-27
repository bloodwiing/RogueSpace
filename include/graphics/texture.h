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
    void bind() const;
    void unbind() const;
    void destroy() const;

    [[nodiscard]] GLuint getID() const;
    [[nodiscard]] TextureType getTextureType() const;

private:
    GLuint m_ID;
    GLuint m_slot;

    TextureType m_type;

    int m_width, m_height, m_channels;
};

#endif //TEXTURE_CLASS_H
