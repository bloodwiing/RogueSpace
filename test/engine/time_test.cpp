#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gmock/gmock-matchers.h>

#include "engine/time.hpp"

#include <thread>

using namespace testing;

TEST(Time, update) {
    using Engine::Time;

    Time::init();
    Time::update();

    ASSERT_LT(Time::getDeltaFloat(), 0.001f);
    ASSERT_LT(Time::getDeltaDouble(), 0.001);

    Time::update();
    std::this_thread::sleep_for(std::chrono::milliseconds(550));
    Time::update();

    ASSERT_GT(Time::getDeltaFloat(), 0.5f);
    ASSERT_GT(Time::getDeltaDouble(), 0.5f);

    ASSERT_LT(Time::getDeltaFloat(), 0.6f);
    ASSERT_LT(Time::getDeltaDouble(), 0.6f);
}

TEST(Time, setMaxFramerate) {
    using Engine::Time;

    Time::init();
    Time::update();

    Time::setMaxFramerate(0);
    ASSERT_EQ(Time::getMinimumFrameTime().count(), 0);

    Time::setMaxFramerate(60);
    ASSERT_EQ(Time::getMinimumFrameTime().count(), 16'666);

    Time::setMaxFramerate(144);
    ASSERT_EQ(Time::getMinimumFrameTime().count(), 6944);

    Time::setMaxFramerate(300);
    ASSERT_EQ(Time::getMinimumFrameTime().count(), 3333);

    Time::setMaxFramerate(0);
    ASSERT_EQ(Time::getMinimumFrameTime().count(), 0);
}

TEST(Time, waitForNextFrame) {
    using Engine::Time;

    Time::init();

    Time::setMaxFramerate(0);
    Time::update();
    Time::waitForNextFrame();
    Time::update();
    ASSERT_LT(Time::getDeltaFloat(), 0.001f);

    Time::setMaxFramerate(144);
    Time::update();
    Time::waitForNextFrame();
    Time::update();
    ASSERT_LT(Time::getDeltaFloat(), 0.0072f);
    ASSERT_GT(Time::getDeltaFloat(), 0.0062f);

    Time::setMaxFramerate(60);
    Time::update();
    Time::waitForNextFrame();
    Time::update();
    ASSERT_LT(Time::getDeltaFloat(), 0.02f);
    ASSERT_GT(Time::getDeltaFloat(), 0.012f);

    Time::setMaxFramerate(2);
    Time::update();
    Time::waitForNextFrame();
    Time::update();
    ASSERT_LT(Time::getDeltaFloat(), 0.55f);
    ASSERT_GT(Time::getDeltaFloat(), 0.45f);

    Time::setMaxFramerate(0);
}