#include "jage/runtime/time.hpp"

#include <chrono>
#include <thread>

using jage::runtime::Time;

namespace chrono = std::chrono;

Time::TTimePoint Time::m_frameStart = chrono::steady_clock::now();
Time::TTimePoint Time::m_frameEnd = Time::m_frameStart;
Time::TDoubleSec Time::m_delta = TDoubleSec(0.0);
chrono::microseconds Time::m_requiredFrameTime(0);

void Time::init() {
    m_frameStart = chrono::steady_clock::now();
    update();
}

void Time::update() {
    auto newTime = chrono::steady_clock::now();
    m_delta = newTime - m_frameStart;
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
    std::this_thread::sleep_until(m_frameEnd - chrono::milliseconds(50));
    while (chrono::steady_clock::now() < m_frameEnd);
}
