#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>

#include "jage/graphics/model/vbo.hpp"

namespace jage::graphics::model {

    /// \brief      OpenGL Vertex Array Object
    /// \details    Defines the Vertex data structure
    class VAO {
    public:
        VAO();

        /// \brief          Defines a section of data in a Vertex buffer as an Attribute
        /// \param vbo      The Vertex buffer to reference
        /// \param layout   Layout in the shader
        /// \param size     The size of the Attribute (in bytes)
        /// \param type     The type of the Attribute
        /// \param stride   The size of data per Vertex (in bytes)
        /// \param offset   The initial offset for this attribute in Vertex data
        void linkAttribute(VBO& vbo, GLuint layout, GLint size, GLenum type, GLsizei stride, const GLvoid *offset) const;

        /// \brief          Makes the Vertex Array Object active
        void bind() const;
        /// \brief          Makes no Vertex Array Object active (inactive)
        void unbind() const;
        /// \brief          Deletes the Vertex Array
        void destroy() const;

        /// \return         Vertex Array OpenGL ID
        [[nodiscard]] GLuint getID() const;

    private:
        /// Vertex Array OpenGL ID
        GLuint m_ID;
    };
}

#endif //VAO_CLASS_H
