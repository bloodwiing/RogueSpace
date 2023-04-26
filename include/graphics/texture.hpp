#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include "shader.hpp"

namespace Graphics {

    /// \brief      Image Texture
    /// \details    OpenGL Texture
    class Texture {
    public:
        /// \brief          Default empty constructor
        Texture() = default;
        /// \brief          Creates and loads a Texture
        /// \details        Uses STB to load Images, so support is dependent on the library
        /// \param filename The path to the Image Texture
        explicit Texture(const char* filename);
        /// \brief          Default copy constructor
        Texture(const Texture& original) = default;

        /// \brief          Assigns a Texture slot to a Shader's sampler
        /// \param shader   The Shader program reference
        /// \param uniform  The name of the uniform
        /// \param unit     The Texture slot
        void assign(Shader& shader, const char* uniform, GLint unit) const;
        /// \brief          Makes the Image Texture active in the specified slot
        void bind(GLint slot) const;
        /// \brief          Makes no Image Texture active (inactive)
        void unbind() const;
        /// \brief          Deletes the Texture
        void destroy() const;

        /// \return         Texture OpenGL ID
        [[nodiscard]] GLuint getID() const;

    private:
        /// Texture OpenGL ID
        GLuint m_ID;

        /// Texture width in pixels
        int m_width,
        /// Texture height in pixels
        m_height,
        /// Texture channel count
        m_channels;
    };
}

#endif //TEXTURE_CLASS_H
