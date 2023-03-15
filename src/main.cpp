#include <iostream>
#include "glad/glad.h"
#include <SOIL2.h>
#include <glfw3.h>
#include <chrono>

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

    using namespace std::chrono;

    GLint uniID = glGetUniformLocation(shader.getID(), "scale");
    GLint textureID = glGetUniformLocation(shader.getID(), "textureSampler");

    GLuint res = SOIL_load_OGL_texture("./res/grass.png", SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    glBindTexture(GL_TEXTURE_2D, res);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    auto now = high_resolution_clock::now();

    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.07f, 0.05f, 0.21f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (!shader.isErrored()) {
            shader.activate();
            glUniform1f(uniID, (float)(duration_cast<microseconds>(high_resolution_clock::now() - now).count()) * 0.0000005f);
            glBindTexture(GL_TEXTURE_2D, res);
            glActiveTexture(textureID);
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
