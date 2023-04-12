#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include "graphics/model.hpp"
#include "engine/actor/physicsactor.hpp"
#include "engine/actor/playeractor.hpp"

#include "engine/super.hpp"
#include "engine/time.hpp"

const int width = 1366,
          height = 700;

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    Super::init(width, height);
    Time::setMaxFramerate(144);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);


    Shader shader("./res/default.vert", "./res/default.frag");


    Scene scene;

    auto player = scene.addChild<PlayerActor>("Player");
    auto camera = player->addChild<Camera>("Camera");
    camera->setActive();

    auto ground = scene.addChild<Actor>("Ground");
    auto ground_model = ground->addChild<Model>("model", "./res/map/scene.gltf");

    auto cube = scene.addChild<PhysicsActor>("Cube", 1.0f, 1.0f);
    cube->scale(glm::vec3(0.50f));
    auto cube_model = cube->addChild<Model>("model", "./res/starship/Starship01.gltf");
    cube->setWeight(0.5f);
    cube->setLinearVelocity(glm::vec3(5.0f, 1.0f, 0.0f));

    scene.addChild<Actor>("Bullet");
    scene.addChild<Actor>("Bullet");
    scene.addChild<Actor>("Bullet (3)");
    scene.addChild<Actor>("Bullet");
    scene.addChild<Actor>("Bullet");
    scene.addChild<Actor>("Bullet (3)");
    scene.addChild<Actor>("Bullet");
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
        Camera::getActiveCamera()->updateMatrix(45.0f, 0.001f, 1000.0f);
        auto test = camera->getWorldMatrix();
        scene.draw(shader);

        Window::getActive()->swapBuffers();

        glfwPollEvents();

        Time::waitForNextFrame();
    }

    glfwTerminate();
    return 0;
}
