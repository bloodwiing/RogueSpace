#include <iostream>
#include <glad/glad.h>
#include <SOIL2.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "graphics/shader.h"
#include "graphics/vbo.h"
#include "graphics/vao.h"
#include "graphics/ebo.h"
#include "graphics/texture.h"

const int width = 500,
          height = 500;

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(width, height, "Testing", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    gladLoadGL();

    glViewport(0, 0, width, height);

    Shader shader("./res/default.vert", "./res/default.frag");

    float vertices[] = {
            // front
            -0.5f, -0.5f, -0.5f,        0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f,         0.0f, 0.5f,
            0.5f, 0.5f, -0.5f,         0.5f, 0.5f,
            0.5f, -0.5f, -0.5f,         0.5f, 0.0f,
            // back
            0.5f, -0.5f, 0.5f,         0.0f, 0.0f,
            0.5f, 0.5f, 0.5f,          0.0f, 0.5f,
            -0.5f, 0.5f, 0.5f,        0.5f, 0.5f,
            -0.5f, -0.5f, 0.5f,        0.5f, 0.0f,
            // top
            -0.5f, 0.5f, -0.5f,       0.0f, 0.5f,
            -0.5f, 0.5f, 0.5f,       0.0f, 1.0f,
            0.5f, 0.5f, 0.5f,       0.5f, 1.0f,
            0.5f, 0.5f, -0.5f,       0.5f, 0.5f,
            // bottom
            -0.5f, -0.5f, 0.5f,       0.5f, 0.5f,
            -0.5f, -0.5f, -0.5f,       0.5f, 1.0f,
            0.5f, -0.5f, -0.5f,       1.0f, 1.0f,
            0.5f, -0.5f, 0.5f,       1.0f, 0.5f,
            // right
            0.5f, -0.5f, -0.5f,        0.0f, 0.0f,
            0.5f, 0.5f, -0.5f,         0.0f, 0.5f,
            0.5f, 0.5f, 0.5f,         0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,         0.5f, 0.0f,
            // left
            -0.5f, -0.5f, 0.5f,         0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f,          0.0f, 0.5f,
            -0.5f, 0.5f, -0.5f,        0.5f, 0.5f,
            -0.5f, -0.5f, -0.5f,        0.5f, 0.0f,
    };

    unsigned int indices[] = {
            //front
            0,1,2,
            2,3,0,

            //back
            4,5,6,
            6,7,4,

            //top
            8,9,10,
            10,11,8,

            //bottom
            12,13,14,
            14,15,12,

            //right
            16,17,18,
            18,19,16,

            //left
            20,21,22,
            22,23,20
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
    GLint textureID = glGetUniformLocation(shader.getID(), "textureSampler");

    Texture grassPNG("./res/grass.png");
    grassPNG.assign(shader, "textureSampler", 0);

    float rotation = 0.0f;
    double time = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.07f, 0.05f, 0.21f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (!shader.isErrored()) {
            shader.activate();

            double now = glfwGetTime();
            if (now - time >= 1.0 / 60) {
                rotation += 0.5f;
                time = now;
            }

            glm::mat4 model(1.0f);
            glm::mat4 view(1.0f);
            glm::mat4 proj(1.0f);

            model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
            view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));
            proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

            glUniformMatrix4fv(shader.getUniform("model"), 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(shader.getUniform("view"), 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(shader.getUniform("proj"), 1, GL_FALSE, glm::value_ptr(proj));
        }
        vao.bind();

        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    vao.destroy();
    vbo.destroy();
    ebo.destroy();
    shader.destroy();
    grassPNG.destroy();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
