#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>

/// \brief      A Mesh Vertex
/// \details    Each Vertex containing relative data for a few attributes
struct Vertex {
    /// Position of the Vertex
    glm::vec3 position;
    /// Normal coordinate of the Vertex (outwards)
    glm::vec3 normal;
    /// Colour multiply
    glm::vec3 colour;
    /// UV coordinate
    glm::vec2 texCoord;
};

/// \brief      Vertex Buffer Object
/// \details    OpenGL Array Buffer
class VBO {
public:
    /// \brief          Creates the Buffer Object with Vertex data
    /// \param vertices The list of mesh vertices
    explicit VBO(std::vector<Vertex>& vertices);

    /// \brief          Makes the Vertex Buffer Object active
    void bind() const;
    /// \brief          Makes no Vertex Buffer Object active (inactive)
    void unbind() const;
    /// \brief          Deletes the Array Buffer
    void destroy() const;

    /// \return         Array Buffer OpenGL ID
    [[nodiscard]] GLuint getID() const;

private:
    /// Array Buffer OpenGL ID
    GLuint m_ID;
};

#endif //VBO_CLASS_H
