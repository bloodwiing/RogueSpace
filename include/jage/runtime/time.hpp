#ifndef TIME_CLASS_H
#define TIME_CLASS_H

#include <chrono>

namespace jage::runtime {

    /// \brief      Static Time tracker.
    /// \details    Tracks the time difference between each update call and limits frame rate to a maximum number
    class Time {
    public:

        using TDoubleSec = std::chrono::duration<double>;
        using TClock = std::chrono::steady_clock;
        using TTimePoint = std::chrono::time_point<TClock, TDoubleSec>;

        /// \brief      Initialises basic values
        static void init();

        /// \brief      Updates previous frame timestamps
        static void update();

        /// \brief      Sets the maximum game engine Frame rate
        /// \details    Any non-positive value will disable the Frame rate limit
        static void setMaxFramerate(int framerate);
        /// \return     The minimum time a frame must be shown before the next update
        /// \details    This is updated using the setMaxFramerate function
        /// \see        Time#setMaxFramerate
        static std::chrono::microseconds getMinimumFrameTime();

        /// \return     The delta of time between updates as a float
        static float getDeltaFloat();
        /// \return     The delta of time between updates as a double
        static double getDeltaDouble();
        /// \brief      Sets the Delta time for the current frame to a specific value
        /// \details    Only useful for testing, please do not call this function otherwise
        static void setDelta(TDoubleSec delta);

        /// \brief      Helpful function that halts the current thread until a new frame can begin
        static void waitForNextFrame();

    private:
        /// The calculated time delta
        static TDoubleSec m_delta;
        /// The expected time stamp when a frame should end
        static TTimePoint m_frameEnd;
        /// The timestamp when the current frame started
        static TTimePoint m_frameStart;
        /// Time to wait in microseconds for how short a frame should be
        static std::chrono::microseconds m_requiredFrameTime;
    };
}

#endif //TIME_CLASS_H
