#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 colour;
    glm::vec2 texCoord;
};

class VBO {
public:
    VBO(std::vector<Vertex>& vertices);

    void bind();
    void unbind();
    void destroy();

    GLuint getID() const;

private:
    GLuint ID;
};

#endif //VBO_CLASS_H
