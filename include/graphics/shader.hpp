#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include "glad/glad.h"
#include <string>

/// \brief      Shader program
/// \details    OpenGL Shader Program
class Shader {
public:
    Shader();
    /// \brief                  Loads a new OpenGL program with the given Vertex and Fragment shader source files
    /// \param vertex_file      Path to a Vertex shader
    /// \param fragment_file    Path to a Fragment shader
    Shader(const std::string& vertex_file, const std::string& fragment_file);

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

private:
    /// Shader Program OpenGL ID
    GLuint m_ID;
    /// Shader Program compiling status
    bool m_error;

    /// \brief              Helper function to load either Shader into OpenGL
    /// \param file_name    The Path to a shader file
    /// \param type         The type of shader to load
    /// \return             The ID of the compiled shader
    static GLuint loadShaderFile(const std::string &file_name, GLenum type);

    /// \brief              Checks for shader compile errors
    /// \param shaderID     The ID of the shader to check
    /// \param type         The name type of shader (just for reporting)
    /// \param file         The path of the source file (just for reporting)
    void checkShaderErrors(GLuint shaderID, const std::string &type, const std::string &file);
    /// \brief              Checks for program errors
    void checkProgramErrors();
};

#endif //SHADER_CLASS_H
