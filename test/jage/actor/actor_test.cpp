#include "jage/node/actor/staticactor.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gmock/gmock-matchers.h>
#include <thread>

#include "jage/runtime/time.hpp"

using jage::node::actor::StaticActor;
using namespace testing;

TEST(Actor, childNaming) {
    auto* actor = new StaticActor(nullptr, "", nullptr, jage::Tag::UNTAGGED, false);

    auto* child1 = actor->addChild<StaticActor>("Child1", jage::Tag::UNTAGGED);
    auto* child2 = actor->addChild<StaticActor>("Child2", jage::Tag::UNTAGGED);
    auto* child12 = actor->addChild<StaticActor>("Child1 (2)", jage::Tag::UNTAGGED);
    auto* child122 = actor->addChild<StaticActor>("Child1", jage::Tag::UNTAGGED);
    auto* child13 = actor->addChild<StaticActor>("Child1", jage::Tag::UNTAGGED);

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
    using jage::runtime::Time;

    auto* actor = new StaticActor(nullptr, "", nullptr, jage::Tag::UNTAGGED, false);

    auto* child1 = actor->addChild<StaticActor>("Child1", jage::Tag::UNTAGGED);
    auto* child2 = actor->addChild<StaticActor>("Child2", jage::Tag::UNTAGGED);
    auto* child12 = actor->addChild<StaticActor>("Child1 (2)", jage::Tag::UNTAGGED);

    Time::init();
    Time::setMaxFramerate(144);
    Time::update();

    ASSERT_FALSE(child1->isDead());
    child2->kill();
    ASSERT_TRUE(child2->isDead());
    child12->kill(0.001f);
    ASSERT_FALSE(child12->isDead());

    Time::waitForNextFrame();
    Time::update();

    ASSERT_FALSE(child12->isDead());
    child12->update();
    ASSERT_TRUE(child12->isDead());

    actor->update();

    ASSERT_EQ(actor->getChildren().size(), 1);

    child1->kill(0.001f);

    Time::waitForNextFrame();
    Time::update();
    actor->update();

    ASSERT_EQ(actor->getChildren().size(), 0);
}

class RecursionTestSuccess : std::exception
{ };

class RecursionTest : public jage::node::actor::StaticActor {
public:
    RecursionTest(JAGE_ACTOR_ARGS)
        : StaticActor(parent, std::move(name), scene, tag, isVolatile)
    { }

    void update() override {
        throw RecursionTestSuccess();
    }

    void draw() override {
        throw RecursionTestSuccess();
    }
};

TEST(Actor, recursion) {
    auto* actor = new StaticActor(nullptr, "", nullptr, jage::Tag::UNTAGGED, false);

    actor->addChild<RecursionTest>("Child1", jage::Tag::UNTAGGED);

    ASSERT_THROW(actor->update(), RecursionTestSuccess);
    ASSERT_THROW(actor->draw(), RecursionTestSuccess);
}