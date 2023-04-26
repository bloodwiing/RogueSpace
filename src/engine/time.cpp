#include "engine/time.hpp"

#include <chrono>
#include <thread>

TTimePoint Time::m_frameStart = std::chrono::steady_clock::now();
TTimePoint Time::m_frameEnd = Time::m_frameStart;
TDoubleSec Time::m_delta = TDoubleSec(0.0);
std::chrono::microseconds Time::m_requiredFrameTime(0);

void Time::init() {
    m_frameStart = std::chrono::steady_clock::now();
    update();
}

void Time::update() {
    auto newTime = std::chrono::steady_clock::now();
    m_delta = newTime - m_frameStart;
    m_frameStart = newTime;
    m_frameEnd = m_frameStart + m_requiredFrameTime;
}

void Time::setMaxFramerate(int framerate) {
    if (framerate <= 0)
        m_requiredFrameTime = std::chrono::microseconds(0);
    else
        m_requiredFrameTime = std::chrono::microseconds(1'000'000 / framerate);
}

std::chrono::microseconds Time::getMinimumFrameTime() {
    return m_requiredFrameTime;
}

float Time::getDeltaFloat() {
    return (float)m_delta.count();
}

double Time::getDeltaDouble() {
    return m_delta.count();
}

void Time::setDelta(TDoubleSec delta) {
    m_delta = delta;
}

void Time::waitForNextFrame() {
    std::this_thread::sleep_until(m_frameEnd - std::chrono::milliseconds(50));
    while (std::chrono::steady_clock::now() < m_frameEnd);
}
