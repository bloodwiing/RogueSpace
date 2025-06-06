#include "jage/node/scene.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gmock/gmock-matchers.h>
#include <thread>

#include "jage/runtime/time.hpp"
#include "jage/node/actor/abc/actor_abc.hpp"

using jage::node::Scene;
using namespace testing;

TEST(Scene, actorInstantiation) {
    using namespace jage::node::actor;

    auto* scene = new Scene();

    auto* child1 = scene->addChild<StaticActor>("Child1", jage::Tag::UNTAGGED);
    auto* child2 = scene->addChild<StaticActor>("Child1", jage::Tag::UNTAGGED);

    ASSERT_EQ(child1->getName(), "Child1");
    ASSERT_EQ(child2->getName(), "Child1 (2)");
    ASSERT_EQ(scene->getChildren().size(), 2);

    ASSERT_EQ(child1->getScene(), scene);
    ASSERT_EQ(child2->getScene(), scene);
}

TEST(Scene, volatileActorInstantiation) {
    using namespace jage::node::actor;

    auto* scene = new Scene();

    auto* child1 = scene->addVolatileChild<StaticActor>("Child1", jage::Tag::UNTAGGED);
    auto* child2 = scene->addVolatileChild<StaticActor>("Child1", jage::Tag::UNTAGGED);

    ASSERT_EQ(child1->getName(), "Child1");
    ASSERT_EQ(child2->getName(), "Child1");
    ASSERT_EQ(scene->getVolatileChildren().getSize(), 2);

    ASSERT_EQ(child1->getScene(), scene);
    ASSERT_EQ(child2->getScene(), scene);
}

TEST(Actor, volatileChildLifeCycle) {
    using namespace jage::node::actor;
    using jage::runtime::Time;

    auto* scene = new Scene();

    auto* child1 = scene->addVolatileChild<StaticActor>("", jage::Tag::UNTAGGED);
    auto* child2 = scene->addVolatileChild<StaticActor>("", jage::Tag::UNTAGGED);
    auto* child12 = scene->addVolatileChild<StaticActor>("", jage::Tag::UNTAGGED);

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

    scene->update();

    ASSERT_EQ(scene->getVolatileChildren().getSize(), 1);

    child1->kill(0.001f);

    Time::waitForNextFrame();
    Time::update();
    scene->update();

    ASSERT_EQ(scene->getVolatileChildren().getSize(), 0);
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

TEST(Actor, volatileRecursion) {
    using namespace jage::node::actor;

    auto* scene = new Scene();

    scene->addVolatileChild<RecursionTest>("Child1", jage::Tag::UNTAGGED);

    ASSERT_THROW(scene->update(), RecursionTestSuccess);
    ASSERT_THROW(scene->draw(), RecursionTestSuccess);
}