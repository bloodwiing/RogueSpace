#include "jage/actor/scene.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gmock/gmock-matchers.h>
#include <thread>

#include "jage/runtime/time.hpp"
#include "jage/actor/abc/actor_abc.hpp"

using jage::actor::Scene;
using namespace testing;

TEST(Scene, actorInstantiation) {
    using namespace jage::actor;

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
    using namespace jage::actor;

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
    using namespace jage::actor;
    using jage::runtime::Time;

    auto* scene = new Scene();

    auto* child1 = scene->addVolatileChild<StaticActor>("", jage::Tag::UNTAGGED);
    auto* child2 = scene->addVolatileChild<StaticActor>("", jage::Tag::UNTAGGED);
    auto* child12 = scene->addVolatileChild<StaticActor>("", jage::Tag::UNTAGGED);

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

class RecursionTest : public jage::actor::StaticActor {
public:
    RecursionTest(Scene* scene, jage::actor::abc::ActorABC* actor, std::string name, jage::Tag tag, bool isVolatile)
            : StaticActor(scene, actor, std::move(name), tag, isVolatile)
    { }

    void update() override {
        throw RecursionTestSuccess();
    }

    void draw(jage::graphics::Shader &shader) override {
        throw RecursionTestSuccess();
    }
};

TEST(Actor, volatileRecursion) {
    using namespace jage::actor;

    auto* scene = new Scene();

    scene->addVolatileChild<RecursionTest>("Child1", jage::Tag::UNTAGGED);

    jage::graphics::Shader shader;

    ASSERT_THROW(scene->update(), RecursionTestSuccess);
    ASSERT_THROW(scene->draw(shader), RecursionTestSuccess);
}