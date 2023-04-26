#include "engine/time.hpp"

#include <chrono>
#include <thread>

Engine::Time::TTimePoint Engine::Time::m_frameStart = std::chrono::steady_clock::now();
Engine::Time::TTimePoint Engine::Time::m_frameEnd = Time::m_frameStart;
Engine::Time::TDoubleSec Engine::Time::m_delta = TDoubleSec(0.0);
std::chrono::microseconds Engine::Time::m_requiredFrameTime(0);

void Engine::Time::init() {
    m_frameStart = std::chrono::steady_clock::now();
    update();
}

void Engine::Time::update() {
    auto newTime = std::chrono::steady_clock::now();
    m_delta = newTime - m_frameStart;
    m_frameStart = newTime;
    m_frameEnd = m_frameStart + m_requiredFrameTime;
}

void Engine::Time::setMaxFramerate(int framerate) {
    if (framerate <= 0)
        m_requiredFrameTime = std::chrono::microseconds(0);
    else
        m_requiredFrameTime = std::chrono::microseconds(1'000'000 / framerate);
}

std::chrono::microseconds Engine::Time::getMinimumFrameTime() {
    return m_requiredFrameTime;
}

float Engine::Time::getDeltaFloat() {
    return (float)m_delta.count();
}

double Engine::Time::getDeltaDouble() {
    return m_delta.count();
}

void Engine::Time::setDelta(TDoubleSec delta) {
    m_delta = delta;
}

void Engine::Time::waitForNextFrame() {
    std::this_thread::sleep_until(m_frameEnd - std::chrono::milliseconds(50));
    while (std::chrono::steady_clock::now() < m_frameEnd);
}
