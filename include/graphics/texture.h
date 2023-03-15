#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glfw3.h>
#include <SOIL2.h>

class Texture {
public:
    explicit Texture(const char* file_name, int force_channels = 0, GLuint reuse_texture_id = 0, int flags = SOIL_FLAG_INVERT_Y);

    void bind();
    void unbind();
    void destroy();

    GLuint getID();

private:
    GLuint ID;
};

#endif //TEXTURE_CLASS_H
