#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "graphics/shader.h"
#include "graphics/vbo.h"
#include "graphics/vao.h"
#include "graphics/ebo.h"
#include "graphics/texture.h"
#include "graphics/camera.h"

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

    float vertices[] = {
            // front
            -0.5f, -0.5f, -0.5f,        0.0f, 0.0f,         0.0f,  0.0f, -1.0f,
            -0.5f,  0.5f, -0.5f,        0.0f, 0.5f,         0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,        0.5f, 0.5f,         0.0f,  0.0f, -1.0f,
            0.5f, -0.5f, -0.5f,        0.5f, 0.0f,         0.0f,  0.0f, -1.0f,
            // back
            0.5f, -0.5f,  0.5f,        0.0f, 0.0f,         0.0f,  0.0f,  1.0f,
            0.5f,  0.5f,  0.5f,        0.0f, 0.5f,         0.0f,  0.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,        0.5f, 0.5f,         0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,        0.5f, 0.0f,         0.0f,  0.0f,  1.0f,
            // top
            -0.5f,  0.5f, -0.5f,        0.0f, 0.5f,         0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,        0.0f, 1.0f,         0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,        0.5f, 1.0f,         0.0f,  1.0f,  0.0f,
            0.5f,  0.5f, -0.5f,        0.5f, 0.5f,         0.0f,  1.0f,  0.0f,
            // bottom
            -0.5f, -0.5f,  0.5f,        0.5f, 0.5f,         0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,        0.5f, 1.0f,         0.0f, -1.0f,  0.0f,
            0.5f, -0.5f, -0.5f,        1.0f, 1.0f,         0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,        1.0f, 0.5f,         0.0f, -1.0f,  0.0f,
            // right
            0.5f, -0.5f, -0.5f,        0.0f, 0.0f,         1.0f,  0.0f,  0.0f,
            0.5f,  0.5f, -0.5f,        0.0f, 0.5f,         1.0f,  0.0f,  0.0f,
            0.5f,  0.5f,  0.5f,        0.5f, 0.5f,         1.0f,  0.0f,  0.0f,
            0.5f, -0.5f,  0.5f,        0.5f, 0.0f,         1.0f,  0.0f,  0.0f,
            // left
            -0.5f, -0.5f,  0.5f,        0.0f, 0.0f,       -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,        0.0f, 0.5f,       -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,        0.5f, 0.5f,       -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,        0.5f, 0.0f,       -1.0f,  0.0f,  0.0f,
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

    GLfloat lightVertices[] =
    { //     COORDINATES     //
            -0.1f, -0.1f,  0.1f,
            -0.1f, -0.1f, -0.1f,
            0.1f, -0.1f, -0.1f,
            0.1f, -0.1f,  0.1f,
            -0.1f,  0.1f,  0.1f,
            -0.1f,  0.1f, -0.1f,
            0.1f,  0.1f, -0.1f,
            0.1f,  0.1f,  0.1f
    };

    GLuint lightIndices[] =
    {
            0, 1, 2,
            0, 2, 3,
            0, 7, 4,
            0, 3, 7,
            3, 6, 7,
            3, 2, 6,
            2, 5, 6,
            2, 1, 5,
            1, 4, 5,
            1, 0, 4,
            4, 6, 5,
            4, 7, 6,
    };


    Shader shader("./res/default.vert", "./res/default.frag");

    VAO vao;
    vao.bind();

    VBO vbo(vertices, sizeof(vertices));
    EBO ebo(indices, sizeof(indices));

    vao.linkAttribute(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void *)0);
    vao.linkAttribute(vbo, 1, 2, GL_FLOAT, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    vao.linkAttribute(vbo, 2, 3, GL_FLOAT, 8 * sizeof(float), (void *)(5 * sizeof(float)));
    vao.unbind();
    vbo.unbind();
    ebo.unbind();


    Shader lightShader("./res/light.vert", "./res/light.frag");

    VAO lightVAO;
    lightVAO.bind();

    VBO lightVBO(lightVertices, sizeof(lightVertices));
    EBO lightEBO(lightIndices, sizeof(lightIndices));

    lightVAO.linkAttribute(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
    lightVAO.unbind();
    lightVBO.unbind();
    lightEBO.unbind();


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);


    Texture grassPNG("./res/grass.png");
    grassPNG.assign(shader, "TextureSampler", 0);


    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));


    glm::vec4 lightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    glm::vec3 lightPos = glm::vec3(0.9f, 0.9f, 0.9f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    if (!lightShader.isErrored()) {
        lightShader.activate();
        glUniformMatrix4fv(lightShader.getUniform("Model"), 1, GL_FALSE, glm::value_ptr(lightModel));
        glUniform4f(lightShader.getUniform("LightColour"), lightColour.r, lightColour.g, lightColour.b, lightColour.a);
    }


//    glm::vec3 cubePos = glm::vec3(0.0f, 0.0f, 0.0f);
//    float cubeRot = 12.0f;
//    glm::mat4 cubeModel = glm::mat4(1.0f);
//    cubeModel = glm::translate(cubeModel, cubePos);
//    cubeModel = glm::rotate(cubeModel, glm::radians(cubeRot), glm::vec3(0.0f, 1.0f, 0.0f));

    if (!shader.isErrored()) {
        shader.activate();
//        glUniformMatrix4fv(shader.getUniform("Model"), 1, GL_FALSE, glm::value_ptr(cubeModel));
        glUniform4f(shader.getUniform("LightColour"), lightColour.r, lightColour.g, lightColour.b, lightColour.a);
        glUniform3f(shader.getUniform("LightPos"), lightPos.x, lightPos.y, lightPos.z);
    }


    float start_time = glfwGetTime();
    float prev_time = start_time;


    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.07f, 0.05f, 0.21f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::vec3 cubePos = glm::vec3(0.0f, 0.0f, 0.0f);
        float cubeRot = (glfwGetTime() - start_time) * 8;
        glm::mat4 cubeModel = glm::mat4(1.0f);
        cubeModel = glm::translate(cubeModel, cubePos);
        cubeModel = glm::rotate(cubeModel, glm::radians(cubeRot), glm::vec3(0.0f, 1.0f, 0.0f));

        float new_time = glfwGetTime();
        float delta = new_time - prev_time;
        prev_time = new_time;

        camera.handleInputs(window, delta);
        camera.updateMatrix(45.0f, 0.001f, 100.0f);

        if (!shader.isErrored()) {
            shader.activate();
            camera.applyMatrix(shader, "CameraMatrix");
            glUniformMatrix4fv(shader.getUniform("Model"), 1, GL_FALSE, glm::value_ptr(cubeModel));
            glUniform3f(shader.getUniform("CameraPos"), camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
            vao.bind();
            glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, nullptr);
        }

        if (!lightShader.isErrored()) {
            lightShader.activate();
            camera.applyMatrix(lightShader, "CameraMatrix");
            lightVAO.bind();
            glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, nullptr);
        }

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
