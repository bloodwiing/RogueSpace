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
    explicit VBO(std::vector<Vertex>& vertices);

    void bind() const;
    void unbind() const;
    void destroy() const;

    [[nodiscard]] GLuint getID() const;

private:
    GLuint m_ID;
};

#endif //VBO_CLASS_H
