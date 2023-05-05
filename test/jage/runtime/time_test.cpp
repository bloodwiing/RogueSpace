#include "jage/runtime/time.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gmock/gmock-matchers.h>
#include <thread>

using jage::runtime::Time;
using namespace testing;

TEST(Time, update) {
    Time::init();
    Time::update();

    ASSERT_LT(Time::getDeltaFloat(), 0.00001f);
    ASSERT_LT(Time::getDeltaDouble(), 0.00001);

    Time::update();
    auto sleepTill = std::chrono::steady_clock::now() + std::chrono::milliseconds(150);
    std::this_thread::sleep_until(sleepTill - std::chrono::milliseconds(10));
    while(std::chrono::steady_clock::now() < sleepTill);
    Time::update();

    ASSERT_GT(Time::getDeltaFloat(), 0.15f);
    ASSERT_GT(Time::getDeltaDouble(), 0.15f);

    ASSERT_LT(Time::getDeltaFloat(), 0.1501f);
    ASSERT_LT(Time::getDeltaDouble(), 0.1501f);
}

TEST(Time, setMaxFramerate) {
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
    Time::init();

    Time::setMaxFramerate(0);
    Time::update();
    Time::waitForNextFrame();
    Time::update();
    ASSERT_LT(Time::getDeltaFloat(), 0.0001f);

    Time::setMaxFramerate(1000);
    Time::update();
    Time::waitForNextFrame();
    Time::update();
    ASSERT_LT(Time::getDeltaFloat(), 0.0011f);
    ASSERT_GT(Time::getDeltaFloat(), 0.001f);

    Time::setMaxFramerate(144);
    Time::update();
    Time::waitForNextFrame();
    Time::update();
    ASSERT_LT(Time::getDeltaFloat(), 0.0071f);
    ASSERT_GT(Time::getDeltaFloat(), 0.0069f);

    Time::setMaxFramerate(60);
    Time::update();
    Time::waitForNextFrame();
    Time::update();
    ASSERT_LT(Time::getDeltaFloat(), 0.0167f);
    ASSERT_GT(Time::getDeltaFloat(), 0.0165f);

    Time::setMaxFramerate(0);
}