#include <iostream>
#include "glad/glad.h"
#include <glfw3.h>
#include "graphics/shader.h"

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

    Shader shader("./res/shader.vert", "./res/shader.frag");

    float vertices[] = {
            -0.5, -0.5, 0.0,
            0.5, -0.5, 0.0,
            0.5, 0.5, 0.0,
            -0.5, 0.5, 0.0
    };

    unsigned int indices[] = {
            0, 1, 2,
            0, 2, 3
    };

    GLuint vaoID, vboID, eboID;

    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &eboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.07f, 0.05f, 0.21f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (!shader.isErrored())
            shader.enable();
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
