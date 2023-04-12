#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "vbo.hpp"

class VAO {
public:
    VAO();

    void linkAttribute(VBO& vbo, GLuint layout, GLint size, GLenum type, GLsizei stride, const GLvoid *offset) const;

    void bind() const;
    void unbind() const;
    void destroy() const;

    [[nodiscard]] GLuint getID() const;

private:
    GLuint m_ID;
};

#endif //VAO_CLASS_H
