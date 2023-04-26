#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gmock/gmock-matchers.h>

#include "engine/time.hpp"
#include "engine/scene.hpp"

#include <thread>

using namespace testing;

TEST(Scene, actorInstantiation) {
    using Engine::Scene;
    namespace Actors = Engine::Actors;

    auto* scene = new Scene();

    auto* child1 = scene->addChild<Actors::Actor>("Child1");
    auto* child2 = scene->addChild<Actors::Actor>("Child1");

    ASSERT_EQ(child1->getName(), "Child1");
    ASSERT_EQ(child2->getName(), "Child1 (2)");
    ASSERT_EQ(scene->getChildren().size(), 2);

    ASSERT_EQ(child1->getScene(), scene);
    ASSERT_EQ(child2->getScene(), scene);
}

TEST(Scene, volatileActorInstantiation) {
    using Engine::Scene;
    namespace Actors = Engine::Actors;

    auto* scene = new Scene();

    auto* child1 = scene->addVolatileChild<Actors::Actor>("Child1");
    auto* child2 = scene->addVolatileChild<Actors::Actor>("Child1");

    ASSERT_EQ(child1->getName(), "Child1");
    ASSERT_EQ(child2->getName(), "Child1");
    ASSERT_EQ(scene->getVolatileChildren().getSize(), 2);

    ASSERT_EQ(child1->getScene(), scene);
    ASSERT_EQ(child2->getScene(), scene);
}

TEST(Actor, volatileChildLifeCycle) {
    using Engine::Scene;
    using Engine::Time;
    namespace Actors = Engine::Actors;

    auto* scene = new Scene();

    auto* child1 = scene->addVolatileChild<Actors::Actor>("");
    auto* child2 = scene->addVolatileChild<Actors::Actor>("");
    auto* child12 = scene->addVolatileChild<Actors::Actor>("");

    Time::init();
    Time::setMaxFramerate(144);
    Time::update();

    ASSERT_FALSE(child1->isDead());
    child2->markDead();
    ASSERT_TRUE(child2->isDead());
    child12->markDead(0.001f);
    ASSERT_FALSE(child12->isDead());

    Time::waitForNextFrame();
    Time::update();

    ASSERT_FALSE(child12->isDead());
    child12->update();
    ASSERT_TRUE(child12->isDead());

    scene->update();

    ASSERT_EQ(scene->getVolatileChildren().getSize(), 1);

    child1->markDead(0.001f);

    Time::waitForNextFrame();
    Time::update();
    scene->update();

    ASSERT_EQ(scene->getVolatileChildren().getSize(), 0);
}

class RecursionTestSuccess : std::exception
{ };

class RecursionTest : public Engine::Actors::Actor {
public:
    RecursionTest(Engine::Scene* scene, ActorBase* actor, std::string name)
            : Actor(scene, actor, std::move(name))
    { }

    void update() override {
        throw RecursionTestSuccess();
    }

    void draw(Graphics::Shader &shader) override {
        throw RecursionTestSuccess();
    }
};

TEST(Actor, volatileRecursion) {
    using Engine::Scene;
    namespace Actors = Engine::Actors;

    auto* scene = new Scene();

    auto* child1 = scene->addVolatileChild<RecursionTest>("Child1");

    Graphics::Shader shader;

    ASSERT_THROW(scene->update(), RecursionTestSuccess);
    ASSERT_THROW(scene->draw(shader), RecursionTestSuccess);
}