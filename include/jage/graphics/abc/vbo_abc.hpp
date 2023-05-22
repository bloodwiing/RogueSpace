#ifndef JAGE_VBO_ABC_HPP
#define JAGE_VBO_ABC_HPP

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>

#include "jage/graphics/abc/oglbuffer_abc.hpp"

namespace jage::graphics::abc {

    /// \brief      Vertex Buffer Object
    /// \details    OpenGL Array Buffer
    template<class TVertex>
    class VBObjectABC
            : public OGLBufferABC {
    public:
        typedef TVertex VertexType;

        VBObjectABC();

        /// \brief          Creates the Buffer Object with Vertex data
        /// \param vertices The list of mesh vertices
        explicit VBObjectABC(const std::vector<TVertex>& vertices);
    };
}

#include "vbo_abc_impl.tpp"

#endif //JAGE_VBO_ABC_HPP
