#include "jage/actor/physicsactor.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gmock/gmock-matchers.h>
#include <thread>

#include "jage/runtime/time.hpp"

using jage::actor::PhysicsActor;
using jage::runtime::Time;
using namespace testing;

TEST(PhysicsActor, applyLinearVelocity) {
    Time::init();

    jage::actor::DynamicActor actor(nullptr, nullptr, "");

    // Get a 0.5s delta ready
    Time::setDelta(Time::TDoubleSec(0.5));

    glm::vec3 linearVelocity(10.0, -8.0, 4.0);

    ASSERT_EQ(actor.getTranslation(), glm::vec3(0.0, 0.0, 0.0));

    PhysicsActor::applyLinearVelocity(&actor, linearVelocity);
    ASSERT_EQ(actor.getTranslation(), glm::vec3(5.0, -4.0, 2.0));

    PhysicsActor::applyLinearVelocity(&actor, linearVelocity);
    ASSERT_EQ(actor.getTranslation(), glm::vec3(10.0, -8.0, 4.0));

    PhysicsActor::applyLinearVelocity(&actor, -linearVelocity);
    ASSERT_EQ(actor.getTranslation(), glm::vec3(5.0, -4.0, 2.0));
}

TEST(PhysicsActor, applyAngularVelocity) {
    Time::init();

    jage::actor::DynamicActor actor(nullptr, nullptr, "");

    // Get a 0.5s delta ready
    Time::setDelta(Time::TDoubleSec(0.5));

    glm::vec3 angularVelocity(glm::pi<float>(), 0.0, -glm::pi<float>());

    ASSERT_EQ(actor.getRotation(), glm::quat(glm::vec3(0.0, 0.0, 0.0)));

    PhysicsActor::applyAngularVelocity(&actor, angularVelocity);
    glm::quat expected = glm::normalize(glm::quat(angularVelocity * 0.5f) * glm::quat(1.0, 0.0, 0.0, 0.0));
    ASSERT_EQ(actor.getRotation(), expected);

    PhysicsActor::applyAngularVelocity(&actor, -angularVelocity);
    expected = glm::normalize(glm::quat(-angularVelocity * 0.5f) * expected);
    ASSERT_EQ(actor.getRotation(), expected);
}

TEST(PhysicsActor, diminishVelocity) {
    Time::init();

    jage::actor::DynamicActor actor(nullptr, nullptr, "");

    // Get a 0.5s delta ready
    Time::setDelta(Time::TDoubleSec(0.5));

    glm::vec3 linearVelocity(10.0, -8.0, 4.0);

    PhysicsActor::diminishVelocity(linearVelocity, 1.0f, 0.0f);
    ASSERT_EQ(linearVelocity, glm::vec3(5.0, -4.0, 2.0));

    PhysicsActor::diminishVelocity(linearVelocity, 0.0f, 0.0f);
    ASSERT_EQ(linearVelocity, glm::vec3(5.0, -4.0, 2.0));

    PhysicsActor::diminishVelocity(linearVelocity, 1.5f, 0.0f);
    ASSERT_EQ(linearVelocity, glm::vec3(1.25, -1.0, 0.5));

    PhysicsActor::diminishVelocity(linearVelocity, 0.0f, 10.0f);
    ASSERT_EQ(linearVelocity, glm::vec3(0.0, 0.0, 0.0));
}

TEST(PhysicsActor, isVectorZero) {
    ASSERT_TRUE(PhysicsActor::isVectorZero(glm::vec3(0.0, 0.0, 0.0)));

    ASSERT_FALSE(PhysicsActor::isVectorZero(glm::vec3(1.0, 0.0, 0.0)));
    ASSERT_FALSE(PhysicsActor::isVectorZero(glm::vec3(0.0, 1.0, 0.0)));
    ASSERT_FALSE(PhysicsActor::isVectorZero(glm::vec3(0.0, 0.0, 1.0)));

    ASSERT_FALSE(PhysicsActor::isVectorZero(glm::vec3(5.0, 9.0, -2.0)));
}
