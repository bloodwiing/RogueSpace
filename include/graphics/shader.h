#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include "glad/glad.h"
#include <string>

class Shader {
public:
    Shader(const std::string& vertex_file, const std::string& fragment_file);
    ~Shader();

    void activate();
    void destroy();

    GLint getUniform(const char* uniform);

    bool isErrored() const;

    GLuint getID() const;

private:
    GLuint ID;
    bool error;

    static GLuint loadShaderFile(const std::string &file_name, GLenum type);

    bool checkShaderErrors(GLuint shaderID, const std::string &type, const std::string &file);
    bool checkProgramErrors();
};

#endif //SHADER_CLASS_H
