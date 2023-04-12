#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include "shader.h"

class Texture {
public:
    Texture() = default;
    explicit Texture(const char* filename);
    Texture(const Texture& original) = default;

    void assign(Shader& shader, const char* uniform, GLint unit) const;
    void bind(GLint slot) const;
    void unbind() const;
    void destroy() const;

    [[nodiscard]] GLuint getID() const;

private:
    GLuint m_ID;

    int m_width, m_height, m_channels;
};

#endif //TEXTURE_CLASS_H
