#include "engine/time.hpp"

#include <chrono>
#include <thread>

std::chrono::time_point<std::chrono::steady_clock> Time::m_lastTime = std::chrono::steady_clock::now();
std::chrono::time_point<std::chrono::steady_clock> Time::m_frameStartTime = Time::m_lastTime;
std::chrono::duration<double, std::ratio<1, 1>> Time::m_delta = std::chrono::duration<double, std::ratio<1, 1>>(0.0);
std::chrono::microseconds Time::m_requiredFrameTime(0);

void Time::init() {
    m_lastTime = std::chrono::steady_clock::now();
}

void Time::update() {
    auto newTime = std::chrono::steady_clock::now();
    m_delta = newTime - m_lastTime;
    m_frameStartTime = m_lastTime;
    m_lastTime = newTime;
}

void Time::setMaxFramerate(int framerate) {
    if (framerate <= 0)
        m_requiredFrameTime = std::chrono::microseconds(0);
    else
        m_requiredFrameTime = std::chrono::microseconds(1'000'000 / framerate);
}

float Time::getDeltaFloat() {
    return (float)m_delta.count();
}

double Time::getDeltaDouble() {
    return m_delta.count();
}

void Time::waitForNextFrame() {
    if (m_requiredFrameTime.count() != 0) {
        std::this_thread::sleep_until(m_frameStartTime + m_requiredFrameTime);
    }
}
