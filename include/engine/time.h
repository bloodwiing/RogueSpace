#ifndef TIME_CLASS_H
#define TIME_CLASS_H

#include <chrono>

class Time {
public:
    static void init();

    static void update();

    static void setMaxFramerate(int framerate);

    static float getDeltaFloat();
    static double getDeltaDouble();

    static void waitForNextFrame();

private:
    static std::chrono::duration<double, std::ratio<1, 1>> m_delta;
    static std::chrono::time_point<std::chrono::steady_clock> m_frameStartTime;
    static std::chrono::time_point<std::chrono::steady_clock> m_lastTime;
    static std::chrono::microseconds m_requiredFrameTime;
};

#endif //TIME_CLASS_H
