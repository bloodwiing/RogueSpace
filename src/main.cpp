#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include "graphics/model.hpp"
#include "engine/actor/physicsactor.hpp"
#include "engine/actor/playeractor.hpp"

#include "engine/super.hpp"
#include "engine/time.hpp"

#include "utils.hpp"

const int width = 1366,
          height = 700;

int main() {
    initializeOpenGL();

    Super::init(width, height);
    Time::setMaxFramerate(144);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);


    Shader shader;
    try {
        shader = Shader("./res/default.vert", "./res/default.frag");
    } catch (std::exception& e) {
        std::cerr << e.what();
        return -1;
    }


    Scene scene;

    auto player = scene.addChild<PlayerActor>("Player");
    auto camera = player->addChild<Camera>("Camera");
    camera->setActive();

    auto starship = scene.addChild<PhysicsActor>("Starship", 1.0f, 1.0f);
    starship->scale(glm::vec3(0.50f));
    try {
        auto starship_model = starship->addChild<Model>("model", "./res/starship/Starship01.gltf");
    } catch (std::exception& e) {
        std::cerr << e.what();
    }
    starship->setWeight(0.5f);
    starship->setLinearVelocity(glm::vec3(5.0f, 1.0f, 0.0f));

    std::cout << scene.toHierarchyString();


    glm::vec4 lightColor(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos(0.0f, 5.0f, 0.0f);
    if (!shader.isErrored()) {
        shader.activate();
        glUniform4f(shader.getUniform("LightColour"), lightColor.r, lightColor.g, lightColor.b, lightColor.a);
        glUniform3f(shader.getUniform("LightPos"), lightPos.x, lightPos.y, lightPos.z);
    }


    Time::init();


    while (!Window::getActive()->isClosing()) {

        glClearColor(0.07f, 0.05f, 0.21f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Time::update();

        if (!shader.isErrored()) {
            shader.activate();
            glUniform3f(shader.getUniform("CameraPos"), camera->getTranslation().x, camera->getTranslation().y, camera->getTranslation().z);
        }

        scene.update();
        Camera::getActiveCamera()->updateMatrix(45.0f, 0.001f, 10000.0f);
        auto test = camera->getWorldMatrix();
        scene.draw(shader);

        Window::getActive()->swapBuffers();

        glfwPollEvents();

        Time::waitForNextFrame();
    }

    shader.destroy();
    glfwTerminate();
    return 0;
}
