#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gmock/gmock-matchers.h>

#include "engine/time.hpp"
#include "engine/actor/actor.hpp"

#include <thread>

using namespace testing;

TEST(Actor, childNaming) {
    using Engine::Actors::Actor;

    auto* actor = new Actor(nullptr, nullptr, "");

    auto* child1 = actor->addChild<Actor>("Child1");
    auto* child2 = actor->addChild<Actor>("Child2");
    auto* child12 = actor->addChild<Actor>("Child1 (2)");
    auto* child122 = actor->addChild<Actor>("Child1");
    auto* child13 = actor->addChild<Actor>("Child1");

    ASSERT_EQ(child1->getName(), "Child1");
    ASSERT_EQ(child2->getName(), "Child2");
    ASSERT_EQ(child12->getName(), "Child1 (2)");
    ASSERT_EQ(child122->getName(), "Child1 (2) (2)");
    ASSERT_EQ(child13->getName(), "Child1 (3)");
    ASSERT_EQ(actor->getChildren().size(), 5);

    ASSERT_EQ(child1->getParent(), actor);
    ASSERT_EQ(child2->getParent(), actor);
    ASSERT_EQ(child12->getParent(), actor);
    ASSERT_EQ(child122->getParent(), actor);
    ASSERT_EQ(child13->getParent(), actor);
}

TEST(Actor, childLifeCycle) {
    using Engine::Actors::Actor;
    using Engine::Time;

    auto* actor = new Actor(nullptr, nullptr, "");

    auto* child1 = actor->addChild<Actor>("Child1");
    auto* child2 = actor->addChild<Actor>("Child2");
    auto* child12 = actor->addChild<Actor>("Child1 (2)");

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

    actor->update();

    ASSERT_EQ(actor->getChildren().size(), 1);

    child1->markDead(0.001f);

    Time::waitForNextFrame();
    Time::update();
    actor->update();

    ASSERT_EQ(actor->getChildren().size(), 0);
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

TEST(Actor, recursion) {
    using Engine::Actors::Actor;

    auto* actor = new Actor(nullptr, nullptr, "");

    auto* child1 = actor->addChild<RecursionTest>("Child1");

    Graphics::Shader shader;

    ASSERT_THROW(actor->update(), RecursionTestSuccess);
    ASSERT_THROW(actor->draw(shader), RecursionTestSuccess);
}