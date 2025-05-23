#include "jage/runtime/time.hpp"

#include <chrono>
#include <thread>

using jage::runtime::Time;

namespace chrono = std::chrono;

Time::TTimePoint Time::m_gameStart = chrono::steady_clock::now();
Time::TTimePoint Time::m_frameStart = Time::m_gameStart;
Time::TTimePoint Time::m_frameEnd = Time::m_gameStart;
Time::TDoubleSec Time::m_delta = TDoubleSec(0.0);
chrono::microseconds Time::m_requiredFrameTime(0);
double Time::m_timeScale = 1.0;

void Time::init() {
    m_gameStart = chrono::steady_clock::now();
    m_frameStart = m_gameStart;
    update();
}

void Time::update() {
    auto newTime = chrono::steady_clock::now();
    m_delta = (newTime - m_frameStart) * m_timeScale;
    m_frameStart = newTime;
    m_frameEnd = m_frameStart + m_requiredFrameTime;
}

void Time::setMaxFramerate(int framerate) {
    if (framerate <= 0)
        m_requiredFrameTime = chrono::microseconds(0);
    else
        m_requiredFrameTime = chrono::microseconds(1'000'000 / framerate);
}

std::chrono::microseconds Time::getMinimumFrameTime() {
    return m_requiredFrameTime;
}

Time::TDoubleSec Time::getFrameTime() {
    return m_gameStart - m_frameStart;
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

void jage::runtime::Time::setTimeScale(double timeScale) {
    m_timeScale = timeScale;
}

double jage::runtime::Time::getTimeScale() {
    return m_timeScale;
}

void Time::waitForNextFrame() {
    std::this_thread::sleep_until(m_frameEnd - chrono::milliseconds(50));
    while (chrono::steady_clock::now() < m_frameEnd);
}
