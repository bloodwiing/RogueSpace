#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include "shader.hpp"
#include "engine/assetstream.h"

#include <memory>
#include <thread>
#include <atomic>

#include <stb/stb_image.h>

#include <yaml-cpp/yaml.h>

namespace Graphics {

    /// \brief      Image Texture
    /// \details    OpenGL Texture
    class Texture : public std::enable_shared_from_this<Texture> {
    public:
        /// \brief          Default empty constructor
        Texture() = default;
        /// \brief          Creates and loads a Texture
        /// \details        Uses STB to load Images, so support is dependent on the library
        /// \param filename The path to the Image Texture
        explicit Texture(std::string filename);
        static std::shared_ptr<Texture> create(const std::string& fileName);

        void queue();

        [[nodiscard]] bool isLoaded();

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
        std::atomic<bool> m_loaded;

        /// Texture OpenGL ID
        GLuint m_ID;
        GLuint m_PBO;

        const YAML::Node m_metadata;

        /// Texture width in pixels
        const int m_width,
        /// Texture height in pixels
                  m_height,
        /// Texture channel count
                  m_channels;

        void* m_buffer;

        const std::string m_fileName;
    };
}

#endif //TEXTURE_CLASS_H
