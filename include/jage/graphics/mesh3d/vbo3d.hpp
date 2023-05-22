#ifndef JAGE_VBO_HPP
#define JAGE_VBO_HPP

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>

#include "jage/graphics/abc/vbo_abc.hpp"

namespace jage::graphics::mesh3d {

    /// \brief      A Mesh Vertex
    /// \details    Each Vertex containing relative data for a few attributes
    struct Vertex3D {
        /// Position of the Vertex
        glm::vec3 position;
        /// Normal coordinate of the Vertex (outwards)
        glm::vec3 normal;
        /// Colour multiply
        glm::vec3 colour;
        /// UV coordinate
        glm::vec2 texCoord;
    };

    typedef abc::VBObjectABC<Vertex3D> VBO3D;
}

#endif //JAGE_VBO_HPP
