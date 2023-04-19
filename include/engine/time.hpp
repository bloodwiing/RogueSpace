#ifndef TIME_CLASS_H
#define TIME_CLASS_H

#include <chrono>

/// \brief      Static Time tracker.
/// \details    Tracks the time difference between each update call and limits frame rate to a maximum number
class Time {
public:
    /// \brief      Initialises basic values
    static void init();

    /// \brief      Updates previous frame timestamps
    static void update();

    /// \brief      Sets the maximum game engine Frame rate
    /// \details    Any non-positive value will disable the Frame rate limit
    static void setMaxFramerate(int framerate);

    /// \return     The delta of time between updates as a float
    static float getDeltaFloat();
    /// \return     The delta of time between updates as a double
    static double getDeltaDouble();

    /// \brief      Helpful function that halts the current thread until a new frame can begin
    static void waitForNextFrame();

private:
    /// The calculated time delta
    static std::chrono::duration<double, std::ratio<1, 1>> m_delta;
    /// Current frame's timestamp
    static std::chrono::time_point<std::chrono::steady_clock> m_frameStartTime;
    /// Last frame's timestamp
    static std::chrono::time_point<std::chrono::steady_clock> m_lastTime;
    /// Time to wait in microseconds for how short a frame should be
    static std::chrono::microseconds m_requiredFrameTime;
};

#endif //TIME_CLASS_H
