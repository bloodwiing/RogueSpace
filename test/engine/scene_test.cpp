#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gmock/gmock-matchers.h>

#include "engine/time.hpp"
#include "engine/scene.hpp"

#include <thread>

using namespace testing;

TEST(Scene, actorInstantiation) {
    auto* scene = new Scene();

    auto* child1 = scene->addChild<Actor>("Child1");
    auto* child2 = scene->addChild<Actor>("Child1");

    ASSERT_EQ(child1->getName(), "Child1");
    ASSERT_EQ(child2->getName(), "Child1 (2)");
    ASSERT_EQ(scene->getChildren().size(), 2);

    ASSERT_EQ(child1->getScene(), scene);
    ASSERT_EQ(child2->getScene(), scene);
}

TEST(Scene, volatileActorInstantiation) {
    auto* scene = new Scene();

    auto* child1 = scene->addVolatileChild<Actor>("Child1");
    auto* child2 = scene->addVolatileChild<Actor>("Child1");

    ASSERT_EQ(child1->getName(), "Child1");
    ASSERT_EQ(child2->getName(), "Child1");
    ASSERT_EQ(scene->getVolatileChildren().getSize(), 2);

    ASSERT_EQ(child1->getScene(), scene);
    ASSERT_EQ(child2->getScene(), scene);
}

TEST(Actor, volatileChildLifeCycle) {
    auto* scene = new Scene();

    auto* child1 = scene->addVolatileChild<Actor>("");
    auto* child2 = scene->addVolatileChild<Actor>("");
    auto* child12 = scene->addVolatileChild<Actor>("");

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

class RecursionTest : public Actor {
public:
    RecursionTest(Scene* scene, ActorBase* actor, std::string name)
            : Actor(scene, actor, std::move(name))
    { }

    void update() override {
        throw RecursionTestSuccess();
    }

    void draw(Shader &shader) override {
        throw RecursionTestSuccess();
    }
};

TEST(Actor, volatileRecursion) {
    auto* scene = new Scene();

    auto* child1 = scene->addVolatileChild<RecursionTest>("Child1");

    Shader shader;

    ASSERT_THROW(scene->update(), RecursionTestSuccess);
    ASSERT_THROW(scene->draw(shader), RecursionTestSuccess);
}