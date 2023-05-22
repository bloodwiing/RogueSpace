#ifndef JAGE_OGL_BUFFER_ABC_HPP
#define JAGE_OGL_BUFFER_ABC_HPP

#include <glad/glad.h>

namespace jage::graphics::abc {

    class OGLBufferABC {
    public:
        OGLBufferABC();
        explicit OGLBufferABC(GLenum bufferType);
        ~OGLBufferABC();

        /// \brief          Makes the Buffer Object active
        virtual void bind() const;
        /// \brief          Makes no Buffer Object active (inactive)
        virtual void unbind() const;
        /// \brief          Deletes the Buffer
        virtual void destroy() const;

        /// \return         Array Buffer OpenGL ID
        [[nodiscard]] GLuint getID() const;

    protected:
        /// Array Buffer OpenGL ID
        GLuint m_ID;

        GLenum m_bufferType;

    private:
        bool m_destroyed = false;
    };
}

#endif //JAGE_OGL_BUFFER_ABC_HPP
