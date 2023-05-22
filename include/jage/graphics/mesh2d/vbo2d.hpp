#ifndef JAGE_VBO_2D_HPP
#define JAGE_VBO_2D_HPP

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>

#include "jage/graphics/abc/vbo_abc.hpp"

namespace jage::graphics::mesh2d {

    /// \brief      A Mesh Vertex
    /// \details    Each Vertex containing relative data for a few attributes
    struct Vertex2D {
        /// Position of the Vertex
        glm::vec2 position;
        /// Colour multiply
        glm::vec3 colour;
        /// UV coordinate
        glm::vec2 texCoord;
    };

    typedef abc::VBObjectABC<Vertex2D> VBO2D;
}

#endif //JAGE_VBO_2D_HPP
