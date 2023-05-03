#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include "glad/glad.h"
#include <string>
#include <stdexcept>

namespace Graphics {

    /// \brief      Shader program
    /// \details    OpenGL Shader Program
    class Shader {
    public:
        Shader();
        /// \brief                  Loads a new OpenGL program with the given Vertex and Fragment shader source files
        /// \param vertexFile      Path to a Vertex shader
        /// \param fragmentFile    Path to a Fragment shader
        Shader(const std::string& vertexFile, const std::string& fragmentFile);

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

        class CompileError;
        class ProgramError;

    private:
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
    };

    class Shader::CompileError : public std::runtime_error {
    public:
        CompileError(const std::string& text);
    };

    class Shader::ProgramError : public std::runtime_error {
    public:
        ProgramError(const std::string& text);
    };
}

#endif //SHADER_CLASS_H
