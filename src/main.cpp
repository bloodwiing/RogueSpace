#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include "graphics/model.h"
#include "engine/physicsactor.h"

const int width = 1366,
          height = 700;

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


    Model model("./res/map/scene.gltf");
    Shader shader("./res/default.vert", "./res/default.frag");


    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));


    Model cube("./res/cube/Cube.gltf");
    PhysicsActor actor{};
    actor.setWeight(0.5f);
    actor.setVelocity(glm::vec3(5.0f, 1.0f, 0.0f));


    glm::vec4 lightColor(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos(0.0f, 5.0f, 0.0f);
    if (!shader.isErrored()) {
        shader.activate();
        glUniform4f(shader.getUniform("LightColour"), lightColor.r, lightColor.g, lightColor.b, lightColor.a);
        glUniform3f(shader.getUniform("LightPos"), lightPos.x, lightPos.y, lightPos.z);
    }


    double start_time = glfwGetTime();
    double prev_time = start_time;


    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.07f, 0.05f, 0.21f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        double new_time = glfwGetTime();
        double delta = new_time - prev_time;
        prev_time = new_time;

        camera.handleInputs(window, (float)delta);
        camera.updateMatrix(45.0f, 0.001f, 100.0f);

        actor.update(window, delta);

        if (!shader.isErrored()) {
            shader.activate();
            glUniform3f(shader.getUniform("CameraPos"), camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
        }

        model.draw(shader, camera);
        for (size_t i = 0; i < cube.m_meshes.size(); ++i) {
            cube.m_meshes[i].draw(shader, camera, cube.m_meshMatrices[i], actor.getPosition());
        }

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
