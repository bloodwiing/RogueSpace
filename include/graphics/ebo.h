#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <vector>
#include <glad/glad.h>

class EBO {
public:
    EBO(std::vector<GLuint> indices);

    void bind();
    void unbind();
    void destroy();

    GLuint getID() const;

private:
    GLuint ID;
};

#endif //EBO_CLASS_H
