#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include "graphics/model.h"
#include "engine/actor/physicsactor.h"
#include "engine/actor/playeractor.h"

#include "engine/super.h"
#include "engine/time.h"

const int width = 1366,
          height = 700;

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    Super::init(width, height);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);


    Shader shader("./res/default.vert", "./res/default.frag");


    Scene scene;

    auto player = scene.addChild<PlayerActor>("Player");
    auto camera = player->addChild<Camera>("Camera", width, height);
    camera->setActive();

    auto ground = scene.addChild<Actor>("Ground");
    auto ground_model = ground->addChild<Model>("model", "./res/map/scene.gltf");

    auto cube = scene.addChild<PhysicsActor>("Cube", 1.0f);
    cube->scale(glm::vec3(0.50f));
    auto cube_model = cube->addChild<Model>("model", "./res/suzanne/suzanne.gltf");
    cube->setWeight(0.5f);
    cube->setVelocity(glm::vec3(5.0f, 1.0f, 0.0f));


    glm::vec4 lightColor(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos(0.0f, 5.0f, 0.0f);
    if (!shader.isErrored()) {
        shader.activate();
        glUniform4f(shader.getUniform("LightColour"), lightColor.r, lightColor.g, lightColor.b, lightColor.a);
        glUniform3f(shader.getUniform("LightPos"), lightPos.x, lightPos.y, lightPos.z);
    }


    Time::init();


    while (!Screen::getActive()->isClosing()) {

        glClearColor(0.07f, 0.05f, 0.21f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Time::update();

        if (!shader.isErrored()) {
            shader.activate();
            glUniform3f(shader.getUniform("CameraPos"), camera->getTranslation().x, camera->getTranslation().y, camera->getTranslation().z);
        }

        scene.update();
        camera->updateMatrix(45.0f, 0.001f, 100.0f);
        auto test = camera->getWorldMatrix();
        scene.draw(shader);

        Screen::getActive()->swapBuffers();

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
