#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include "shader.h"

class Texture {
public:
    explicit Texture(const char* filename, GLenum texture_type, GLuint slot, GLenum format, GLenum pixel_type);

    void assign(Shader& shader, const char* uniform, GLint unit);
    void bind();
    void unbind();
    void destroy();

    GLuint getID();

private:
    GLuint ID;
    GLuint slot;

    int width, height, channels;
};

#endif //TEXTURE_CLASS_H
