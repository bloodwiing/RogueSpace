#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "vbo.h"

class VAO {
public:
    VAO();

    void linkAttribute(VBO& vbo, GLuint layout, GLint size, GLenum type, GLsizei stride, const GLvoid *offset);
    void bind();
    void unbind();
    void destroy();

    GLuint getID() const;

private:
    GLuint ID;
};

#endif //VAO_CLASS_H
