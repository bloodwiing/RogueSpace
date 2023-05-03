#include <iostream>

#include "graphics/shader.hpp"
#include "engine/assetstream.hpp"

GLuint Graphics::Shader::loadShaderFile(const std::string &filePath, GLenum type) {
    GLuint id = glCreateShader(type);

    Engine::AssetStream::getInstance().getTextAsset(
            filePath,
            [id](const std::shared_ptr<const std::string>& data) {
                const char* vertexCode = data->c_str();

                glShaderSource(id, 1, &vertexCode, nullptr);
                glCompileShader(id);
            });

    return id;
}

Graphics::Shader::Shader()
    : m_ID(0)
    , m_error(true)
{ }

Graphics::Shader::Shader(const std::string& vertexFile, const std::string& fragmentFile)
    : m_error(false)
{
    GLuint vertID = loadShaderFile(vertexFile, GL_VERTEX_SHADER);
    checkShaderErrors(vertID, "Vertex", vertexFile);

    GLuint fragID = loadShaderFile(fragmentFile, GL_FRAGMENT_SHADER);
    checkShaderErrors(fragID, "Fragment", fragmentFile);

    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertID);
    glAttachShader(m_ID, fragID);
    glLinkProgram(m_ID);

    glDeleteShader(vertID);
    glDeleteShader(fragID);

    checkProgramErrors();
}

void Graphics::Shader::activate() {
    glUseProgram(m_ID);
}

void Graphics::Shader::destroy() {
    glDeleteProgram(m_ID);
}

#define ERROR_MESSAGE_LEN 1024

void Graphics::Shader::checkShaderErrors(GLuint shaderID, const std::string &type, const std::string &file) {
    GLint status;
    GLchar infoLog[ERROR_MESSAGE_LEN];
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
    if (!status) {
        m_error = true;
        glGetShaderInfoLog(shaderID, ERROR_MESSAGE_LEN, nullptr, infoLog);
        throw CompileError(std::string("Error compiling OpenGL ") + type + " shader:\n" + file + " - " + infoLog);
    }
}

void Graphics::Shader::checkProgramErrors() {
    GLint status;
    GLchar infoLog[ERROR_MESSAGE_LEN];
    glGetProgramiv(m_ID, GL_LINK_STATUS, &status);
    if (!status) {
        m_error = true;
        glGetProgramInfoLog(m_ID, ERROR_MESSAGE_LEN, nullptr, infoLog);
        destroy();
        throw ProgramError(std::string("Error linking OpenGL program:\n") + infoLog);
    }
}

bool Graphics::Shader::isErrored() const {
    return m_error;
}

GLuint Graphics::Shader::getID() const {
    return m_ID;
}

GLint Graphics::Shader::getUniform(const char *uniform) {
    return glGetUniformLocation(m_ID, uniform);
}

Graphics::Shader::CompileError::CompileError(const std::string &text)
    : runtime_error(text)
{ }

Graphics::Shader::ProgramError::ProgramError(const std::string &text)
    : runtime_error(text)
{ }
