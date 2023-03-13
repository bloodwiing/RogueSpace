#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>

class EBO {
public:
    EBO(GLuint* indices, GLsizeiptr size);

    void bind();
    void unbind();
    void destroy();

    GLuint getID() const;

private:
    GLuint ID;
};

#endif //EBO_CLASS_H
