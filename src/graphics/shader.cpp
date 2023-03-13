#include <fstream>
#include <iostream>
#include "graphics/shader.h"

std::string Shader::readFileContents(const std::string& file_name) {
    std::string result;
    std::ifstream stream(file_name);
    stream.seekg(0, std::ios::end);
    auto size = stream.tellg();
    result.reserve(size);
    stream.seekg(0, std::ios::beg);
    stream.read(&result[0], size);
    return result;
}

GLuint Shader::loadShaderFile(const std::string &file_name, GLenum type) {
    GLuint id = glCreateShader(type);

    const std::string vertex_source = readFileContents(file_name);
    const char* vertex_code = vertex_source.c_str();

    glShaderSource(id, 1, &vertex_code, nullptr);
    glCompileShader(id);

    return id;
}

Shader::Shader(const std::string& vertex_file, const std::string& fragment_file)
    : error(false)
{
    GLuint vertID = loadShaderFile(vertex_file, GL_VERTEX_SHADER);
    if (checkShaderErrors(vertID, "Vertex", vertex_file))
        return;

    GLuint fragID = loadShaderFile(fragment_file, GL_FRAGMENT_SHADER);
    if (checkShaderErrors(fragID, "Fragment", fragment_file))
        return;

    id = glCreateProgram();
    glAttachShader(id, vertID);
    glAttachShader(id, fragID);
    glLinkProgram(id);

    glDeleteShader(vertID);
    glDeleteShader(fragID);

    checkProgramErrors();
}

Shader::~Shader() {
    glDeleteProgram(id);
}

void Shader::enable() {
    glUseProgram(id);
}

#define ERROR_MESSAGE_LEN 1024

bool Shader::checkShaderErrors(GLuint shaderID, const std::string &type, const std::string &file) {
    GLint status;
    GLchar infoLog[ERROR_MESSAGE_LEN];
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
    if (!status) {
        error = true;
        glGetShaderInfoLog(shaderID, ERROR_MESSAGE_LEN, nullptr, infoLog);
        std::cout << "Error compiling OpenGL " << type << " shader:\n" <<
                file << " - " << infoLog << std::endl;
        return true;
    }
    return false;
}

bool Shader::checkProgramErrors() {
    GLint status;
    GLchar infoLog[ERROR_MESSAGE_LEN];
    glGetProgramiv(id, GL_LINK_STATUS, &status);
    if (!status) {
        error = true;
        glGetProgramInfoLog(id, ERROR_MESSAGE_LEN, nullptr, infoLog);
        std::cout << "Error linking OpenGL program:\n" << infoLog << std::endl;
        return true;
    }
    return false;
}

bool Shader::isErrored() const {
    return error;
}
