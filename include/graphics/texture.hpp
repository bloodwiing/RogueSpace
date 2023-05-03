#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include "shader.hpp"
#include "engine/assetstream.hpp"

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
        /// \brief          Creates and loads a Texture
        /// \details        Uses STB to load Images, so support is dependent on the library
        /// \param filePath The path to the Image Texture
        explicit Texture(const std::string& filePath);
        static std::shared_ptr<Texture> create(const std::string& fileName);
        explicit Texture(GLubyte *bytes, int width, int height, int channels);
        static std::shared_ptr<Texture> create(GLubyte *bytes, int width, int height, int channels);
        static void createDefaultTexture(GLubyte *bytes, int width, int height, int channels);

        [[nodiscard]] static std::shared_ptr<Texture> getDefaultTexture();

        void queue(int priority = ASSET_STREAM_BASE_PRIORITY);

        [[nodiscard]] bool isReady();

        /// \brief          Assigns a Texture slot to a Shader's sampler
        /// \param shader   The Shader program reference
        /// \param uniform  The name of the uniform
        /// \param unit     The Texture slot
        void assign(Shader& shader, const char* uniform, GLint unit) const;
        /// \brief          Makes the Image Texture active in the specified slot
        void bind(GLint unit) const;
        /// \brief          Makes no Image Texture active (inactive)
        void unbind() const;
        /// \brief          Deletes the Texture
        void destroy() const;

        /// \return         Texture OpenGL ID
        [[nodiscard]] GLuint getID() const;

    protected:
        class LOD;

        bool setActiveLOD(int level);

    private:
        const YAML::Node m_metadata;

        std::shared_ptr<LOD> m_main;
        std::vector<std::shared_ptr<LOD>> m_levels;

        std::atomic<int> m_activeLOD;
        std::atomic<int> m_LODsLoaded = 0;

        [[nodiscard]] bool getActiveLOD(std::shared_ptr<LOD>& LOD) const;

        static std::shared_ptr<Texture> defaultTexture;
    };

    class Texture::LOD : public std::enable_shared_from_this<LOD> {
    public:
        LOD(std::string fileName, const YAML::Node& node, Texture* container);
        static std::shared_ptr<LOD> create(const std::string& fileName, const YAML::Node& node, Texture* container);
        LOD(GLubyte* bytes, int width, int height, int channels, int level, int priority, Texture* container);
        static std::shared_ptr<LOD> create(GLubyte* bytes, int width, int height, int channels, int level, int priority, Texture* container);

        void queue(int priority = ASSET_STREAM_BASE_PRIORITY);

        [[nodiscard]] bool isReady();

        void bind(GLint unit) const;
        void unbind() const;
        void destroy() const;

        static GLenum getChannelEnumFromCount(int channels);

        Texture* m_container;

        [[nodiscard]] GLuint getID() const;
        [[nodiscard]] int getLevel() const;

    private:
        std::atomic<bool> m_ready;

        GLuint m_ID;
        GLuint m_PBO;

        void* m_buffer;

        const int m_width;
        const int m_height;
        const int m_channels;

        const int m_level = 0;
        const int m_priority;

        const std::string m_fileName;
    };
}

#endif //TEXTURE_CLASS_H
