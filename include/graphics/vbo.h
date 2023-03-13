#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>

class VBO {
public:
    VBO(GLfloat* vertices, GLsizeiptr size);

    void bind();
    void unbind();
    void destroy();

private:
    GLuint ID;
};

#endif //VBO_CLASS_H
