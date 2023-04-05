#ifndef TIME_CLASS_H
#define TIME_CLASS_H

class Time {
public:
    static void init();

    static void update();

    static float getDeltaFloat();
    static double getDeltaDouble();

private:
    static double m_delta;
    static double m_lastTime;
};

#endif //TIME_CLASS_H
