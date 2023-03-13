#include "graphics/vao.h"

VAO::VAO() {
    glGenVertexArrays(1, &ID);
}

void VAO::linkAttribute(VBO vbo, GLuint layout, GLint size, GLenum type, GLsizei stride, const GLvoid *offset) {
    vbo.bind();
    glBindVertexArray(ID);
    glVertexAttribPointer(layout, size, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    vbo.unbind();
}

void VAO::bind() {
    glBindVertexArray(ID);
}

void VAO::unbind() {
    glBindVertexArray(0);
}

void VAO::destroy() {
    glDeleteVertexArrays(1, &ID);
}
