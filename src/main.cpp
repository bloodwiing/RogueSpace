#include <iostream>
#include "glad/glad.h"
#include <glfw3.h>

#include "graphics/shader.h"
#include "graphics/vbo.h"
#include "graphics/vao.h"
#include "graphics/ebo.h"

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(500, 500, "Testing", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    gladLoadGL();

    glViewport(0, 0, 500, 500);

    Shader shader("./res/default.vert", "./res/default.frag");

    float vertices[] = {
            -0.5, -0.5, 0.0,    0.0, 0.0,
            0.5, -0.5, 0.0,     1.0, 0.0,
            0.5, 0.5, 0.0,      1.0, 1.0,
            -0.5, 0.5, 0.0,     0.0, 1.0
    };

    unsigned int indices[] = {
            0, 1, 2,
            0, 2, 3
    };

    VAO vao;
    vao.bind();

    VBO vbo(vertices, sizeof(vertices));
    EBO ebo(indices, sizeof(indices));

    vao.linkAttribute(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void *)0);
    vao.linkAttribute(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    vao.unbind();
    vbo.unbind();
    ebo.unbind();

    GLint uniID = glGetUniformLocation(shader.getID(), "scale");

    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.07f, 0.05f, 0.21f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (!shader.isErrored()) {
            shader.activate();
            glUniform1f(uniID, 1.5);
        }
        vao.bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    vao.destroy();
    vbo.destroy();
    ebo.destroy();
    shader.destroy();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
