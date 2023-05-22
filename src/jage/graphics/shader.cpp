#include "jage/graphics/shader.hpp"

#include <iostream>

#include "jage/runtime/asset/assetstream.hpp"

using jage::graphics::Shader;
using jage::runtime::asset::AssetStream;

GLuint Shader::loadShaderFile(const std::string &filePath, GLenum type) {
    GLuint id = glCreateShader(type);

    AssetStream::getInstance().getTextAsset(
            filePath,
            [id](const std::shared_ptr<const std::string>& data) {
                const char* vertexCode = data->c_str();

                glShaderSource(id, 1, &vertexCode, nullptr);
                glCompileShader(id);
            });

    return id;
}

Shader::Shader()
    : m_ID(0)
    , m_error(true)
{ }

Shader::Shader(std::string vertexFile, std::string fragmentFile)
    : m_error(false)
    , m_ID()
    , m_vertexFile(std::move(vertexFile))
    , m_fragmentFile(std::move(fragmentFile))
{

}

Shader::Shader(const std::string& fileName)
    : Shader(fileName + ".vert", fileName + ".frag")
{

}

Shader::~Shader() {
    if (m_error)
        return;
    glDeleteProgram(m_ID);
}

std::shared_ptr<Shader> Shader::create(std::string vertexFile, std::string fragmentFile) {
    return std::make_shared<Shader>(std::move(vertexFile), std::move(fragmentFile));
}

std::shared_ptr<Shader> Shader::create(const std::string &fileName) {
    return std::make_shared<Shader>(fileName);
}

void Shader::onQueue(int priority) {
    GLuint vertID = loadShaderFile(m_vertexFile, GL_VERTEX_SHADER);
    checkShaderErrors(vertID, "Vertex", m_vertexFile);

    GLuint fragID = loadShaderFile(m_fragmentFile, GL_FRAGMENT_SHADER);
    checkShaderErrors(fragID, "Fragment", m_fragmentFile);

    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertID);
    glAttachShader(m_ID, fragID);
    glLinkProgram(m_ID);

    glDeleteShader(vertID);
    glDeleteShader(fragID);

    checkProgramErrors();

    markProcessed();
}

void Shader::activate() {
    glUseProgram(m_ID);
}

void Shader::destroy() {
    glDeleteProgram(m_ID);
}

#define ERROR_MESSAGE_LEN 1024

void Shader::checkShaderErrors(GLuint shaderID, const std::string &type, const std::string &file) {
    GLint status;
    GLchar infoLog[ERROR_MESSAGE_LEN];
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
    if (!status) {
        m_error = true;
        glGetShaderInfoLog(shaderID, ERROR_MESSAGE_LEN, nullptr, infoLog);
        throw CompileError(type, file, infoLog);
    }
}

void Shader::checkProgramErrors() {
    GLint status;
    GLchar infoLog[ERROR_MESSAGE_LEN];
    glGetProgramiv(m_ID, GL_LINK_STATUS, &status);
    if (!status) {
        m_error = true;
        glGetProgramInfoLog(m_ID, ERROR_MESSAGE_LEN, nullptr, infoLog);
        destroy();
        throw ProgramError(infoLog);
    }
}

bool Shader::isErrored() const {
    return m_error;
}

GLuint Shader::getID() const {
    return m_ID;
}

GLint Shader::getUniform(const char *uniform) {
    return glGetUniformLocation(m_ID, uniform);
}

Shader::ShaderError::ShaderError(const std::string& text, GLchar* infoLog)
    : runtime_error(text + ":\n" + infoLog)
{ }

Shader::CompileError::CompileError(const std::string &type, const std::string &file, GLchar *infoLog)
    : Shader::ShaderError(std::string("Error compiling OpenGL ") + type + " shader (file " + file + ")", infoLog)
    , m_file(file)
{ }

std::string Shader::CompileError::getFile() const {
    return m_file;
}

Shader::ProgramError::ProgramError(GLchar *infoLog)
    : Shader::ShaderError(std::string("Error linking OpenGL program"), infoLog)
{ }
