#include <iostream>
#include "glad/glad.h"
#include <glfw3.h>

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(500, 500, "Testing", NULL, NULL);
    if (window == nullptr) {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    gladLoadGL();

    glViewport(0, 0, 500, 500);

    const char *vertexShaderSource = ""
        "#version 330 core\n"
        "layout (location = 0) in vec3 pos;\n"
        "void main() {\n"
        "  gl_Position = vec4(pos, 1.0);\n"
        "}\0";
    const char *fragmentShaderSource = ""
         "#version 330 core\n"
         "out vec4 FragColor;\n"
         "void main() {\n"
         "  FragColor = vec4(0.5, 0.9, 0.4, 1.0);\n"
         "}\0";

    GLuint vertID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertID, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertID);

    GLuint fragID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragID, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragID);

    GLuint progID = glCreateProgram();
    glAttachShader(progID, vertID);
    glAttachShader(progID, fragID);
    glLinkProgram(progID);

    glDeleteShader(vertID);
    glDeleteShader(fragID);

    float vertices[] = {
            -0.5, -0.5, 0.0,
            0.5, -0.5, 0.0,
            0.0, 0.5, 0.0
    };

    GLuint vaoID, vboID;

    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.07f, 0.05f, 0.21f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(progID);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
