#ifndef JAGE_EBO_HPP
#define JAGE_EBO_HPP

#include <vector>
#include <glad/glad.h>

#include "jage/graphics/abc/oglbuffer_abc.hpp"

namespace jage::graphics::abc {

    /// \brief      Index Buffer Object
    /// \details    Creates and manages an OpenGL Element Array Buffer
    class EBO
            : public OGLBufferABC {
    public:
        EBO();

        /// \brief          Creates the Buffer Object with Index data
        /// \param indices  The list of mesh indices
        explicit EBO(std::vector<GLuint> indices);
    };
}

#endif //JAGE_EBO_HPP
