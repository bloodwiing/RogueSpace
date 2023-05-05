#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <vector>
#include <glad/glad.h>

namespace jage::graphics::model {

    /// \brief      Index Buffer Object
    /// \details    Creates and manages an OpenGL Element Array Buffer
    class EBO {
    public:
        /// \brief          Creates the Buffer Object with Index data
        /// \param indices  The list of mesh indices
        explicit EBO(std::vector<GLuint> indices);

        /// \brief          Makes the Index Buffer Object active
        void bind() const;
        /// \brief          Makes no Index Buffer Object active (inactive)
        void unbind() const;
        /// \brief          Deletes the Element Array Buffer
        void destroy() const;

        /// \return         Element Array Buffer OpenGL ID
        [[nodiscard]] GLuint getID() const;

    private:
        /// Element Array Buffer OpenGL ID
        GLuint m_ID;
    };
}

#endif //EBO_CLASS_H
