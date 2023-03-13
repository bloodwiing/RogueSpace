#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "vbo.h"

class VAO {
public:
    VAO();

    void linkVBO(VBO vbo, GLuint layout);
    void bind();
    void unbind();
    void destroy();

private:
    GLuint ID;
};

#endif //VAO_CLASS_H
