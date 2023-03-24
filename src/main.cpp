#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include "graphics/mesh.h"

const int width = 1920,
          height = 1080;

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

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);


    std::vector<Vertex> vertices =
    {
            Vertex{glm::vec3(-1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
            Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
            Vertex{glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
            Vertex{glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},
    };
    std::vector<GLuint> indices =
    {
            0, 2, 1,
            0, 3, 2
    };
    std::vector<Texture> textures =
    {
            Texture("./res/planks.png", TEX_DIFFUSE, 0, GL_RGBA, GL_UNSIGNED_BYTE),
            Texture("./res/planksSpec.png", TEX_SPECULAR, 1, GL_RED, GL_UNSIGNED_BYTE)
    };

    Shader shader("./res/default.vert", "./res/default.frag");
    Mesh floor(vertices, indices, textures);


    std::vector<Vertex> lightVertices =
    {
            Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
            Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
            Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
            Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
            Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
            Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
            Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
            Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
    };

    std::vector<GLuint> lightIndices =
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

    Shader lightShader("./res/light.vert", "./res/light.frag");
    Mesh light(lightVertices, lightIndices, textures);


    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));


    glm::vec4 lightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    if (!lightShader.isErrored()) {
        lightShader.activate();
        glUniformMatrix4fv(lightShader.getUniform("Model"), 1, GL_FALSE, glm::value_ptr(lightModel));
        glUniform4f(lightShader.getUniform("LightColour"), lightColour.r, lightColour.g, lightColour.b, lightColour.a);
    }


    glm::vec3 cubePos = glm::vec3(0.0f, 0.0f, 0.0f);
    float cubeRot = 12.0f;
    glm::mat4 cubeModel = glm::mat4(1.0f);
    cubeModel = glm::translate(cubeModel, cubePos);
    cubeModel = glm::rotate(cubeModel, glm::radians(cubeRot), glm::vec3(0.0f, 1.0f, 0.0f));

    if (!shader.isErrored()) {
        shader.activate();
        glUniformMatrix4fv(shader.getUniform("Model"), 1, GL_FALSE, glm::value_ptr(cubeModel));
        glUniform4f(shader.getUniform("LightColour"), lightColour.r, lightColour.g, lightColour.b, lightColour.a);
        glUniform3f(shader.getUniform("LightPos"), lightPos.x, lightPos.y, lightPos.z);
    }


    float start_time = glfwGetTime();
    float prev_time = start_time;


    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.07f, 0.05f, 0.21f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float new_time = glfwGetTime();
        float delta = new_time - prev_time;
        prev_time = new_time;

        camera.handleInputs(window, delta);
        camera.updateMatrix(45.0f, 0.001f, 100.0f);

        floor.draw(shader, camera);
        light.draw(lightShader, camera);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    shader.destroy();
    lightShader.destroy();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
