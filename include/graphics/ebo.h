#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <vector>
#include <glad/glad.h>

class EBO {
public:
    explicit EBO(std::vector<GLuint> indices);

    void bind() const;
    void unbind() const;
    void destroy() const;

    [[nodiscard]] GLuint getID() const;

private:
    GLuint m_ID;
};

#endif //EBO_CLASS_H
