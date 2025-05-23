#ifndef JAGE_SHADER_HPP
#define JAGE_SHADER_HPP

#include <glad/glad.h>
#include <string>
#include <stdexcept>

#include "jage/runtime/asset/abc/asset_abc.hpp"

namespace jage::graphics {

    /// \brief      Shader program
    /// \details    OpenGL Shader Program
    class Shader
            : public jage::runtime::asset::abc::AssetABC<Shader> {
    public:
        Shader();
        /// \brief                  Loads a new OpenGL program with the given Vertex and Fragment shader source files
        /// \param vertexFile      Path to a Vertex shader
        /// \param fragmentFile    Path to a Fragment shader
        Shader(std::string vertexFile, std::string fragmentFile);
        explicit Shader(const std::string& fileName);
        ~Shader();

        static std::shared_ptr<Shader> create(std::string vertexFile, std::string fragmentFile);
        static std::shared_ptr<Shader> create(const std::string& fileName);

        void onQueue(int priority) override;

        /// \brief          Makes the Shader Program active
        void activate();
        /// \brief          Deletes the Shader Program
        void destroy();

        /// \brief          Returns an ID for this Shader's program's uniform
        /// \param uniform  The name of the uniform
        /// \return         The ID of the uniform
        [[nodiscard]] GLint getUniform(const char* uniform);

        /// \return         - true, if Shader failed to load
        ///                 - false, if succeeded
        [[nodiscard]] bool isErrored() const;

        /// \return         Shader Program OpenGL ID
        [[nodiscard]] GLuint getID() const;

        class ShaderError;

        class CompileError;
        class ProgramError;

    private:
        std::string m_fragmentFile;
        std::string m_vertexFile;
        /// Shader Program OpenGL ID
        GLuint m_ID;
        /// Shader Program compiling status
        bool m_error;

        /// \brief              Helper function to load either Shader into OpenGL
        /// \param filePath    The Path to a shader file
        /// \param type         The type of shader to load
        /// \return             The ID of the compiled shader
        static GLuint loadShaderFile(const std::string &filePath, GLenum type);

        /// \brief              Checks for shader compile errors
        /// \param shaderID     The ID of the shader to check
        /// \param type         The name type of shader (just for reporting)
        /// \param file         The path of the source file (just for reporting)
        void checkShaderErrors(GLuint shaderID, const std::string &type, const std::string &file);
        /// \brief              Checks for program errors
        void checkProgramErrors();

        Shader& operator=(const Shader& ref);
    };

    class Shader::ShaderError : public std::runtime_error {
    public:
        ShaderError(const std::string& text, GLchar* infoLog);
    };

    class Shader::CompileError : Shader::ShaderError {
    public:
        CompileError(const std::string& type, const std::string& file, GLchar* infoLog);

        [[nodiscard]] std::string getFile() const;

    private:
        const std::string& m_file;
    };

    class Shader::ProgramError : Shader::ShaderError {
    public:
        explicit ProgramError(GLchar* infoLog);
    };
}

#endif //JAGE_SHADER_HPP
