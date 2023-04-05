#include "engine/time.h"

#define GLFW_INCLUDE_NONE
#include <glfw3.h>

double Time::m_lastTime = 0.0;
double Time::m_delta = 0.0;

void Time::init() {
    m_lastTime = glfwGetTime();
    m_delta = 0;
}

void Time::update() {
    double newTime = glfwGetTime();
    m_delta = newTime - m_lastTime;
    m_lastTime = newTime;
}

float Time::getDeltaFloat() {
    return (float)m_delta;
}

double Time::getDeltaDouble() {
    return m_delta;
}
