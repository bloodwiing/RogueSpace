#ifndef JAGE_VAO_ABC_HPP
#define JAGE_VAO_ABC_HPP

#include <glad/glad.h>

#include "jage/graphics/abc/oglbuffer_abc.hpp"

namespace jage::graphics::abc {

    /// \brief      OpenGL Vertex Array Object
    /// \details    Defines the Vertex data structure
    template<class TVBO>
    class VAObjectABC
            : public OGLBufferABC {
    public:
        VAObjectABC();

        void create();

        typedef TVBO VBOType;
        typedef typename TVBO::VertexType VertexType;

        /// \brief          Defines a section of data in a Vertex buffer as an Attribute
        /// \param vbo      The Vertex buffer to reference
        /// \param layout   Layout in the shader
        /// \param size     The size of the Attribute (in bytes)
        /// \param type     The type of the Attribute
        /// \param stride   The size of data per Vertex (in bytes)
        /// \param offset   The initial offset for this attribute in Vertex data
        void linkAttribute(TVBO& vbo, GLuint layout, GLint size, GLenum type, GLsizei stride, const GLvoid *offset) const;

        void bind() const override;
        void unbind() const override;
        void destroy() const override;
    };
}

#include "vao_abc_impl.tpp"

#endif //JAGE_VAO_ABC_HPP
