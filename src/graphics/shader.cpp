#include <iostream>

#include "graphics/shader.hpp"
#include "utils.hpp"

GLuint Shader::loadShaderFile(const std::string &file_name, GLenum type) {
    GLuint id = glCreateShader(type);

    const std::string vertex_source = readFileContents(file_name);
    const char* vertex_code = vertex_source.c_str();

    glShaderSource(id, 1, &vertex_code, nullptr);
    glCompileShader(id);

    return id;
}

Shader::Shader()
    : m_ID(0)
    , m_error(true)
{ }

Shader::Shader(const std::string& vertex_file, const std::string& fragment_file)
    : m_error(false)
{
    GLuint vertID = loadShaderFile(vertex_file, GL_VERTEX_SHADER);
    checkShaderErrors(vertID, "Vertex", vertex_file);

    GLuint fragID = loadShaderFile(fragment_file, GL_FRAGMENT_SHADER);
    checkShaderErrors(fragID, "Fragment", fragment_file);

    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertID);
    glAttachShader(m_ID, fragID);
    glLinkProgram(m_ID);

    glDeleteShader(vertID);
    glDeleteShader(fragID);

    checkProgramErrors();
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
        throw std::runtime_error(std::string("Error compiling OpenGL ") + type + " shader:\n" + file + " - " + infoLog);
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
        throw std::runtime_error(std::string("Error linking OpenGL program:\n") + infoLog);
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
