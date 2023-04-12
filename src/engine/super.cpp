#include "engine/super.h"

Window* Super::m_window = nullptr;

void Super::init(int width, int height) {
    m_window = new Window(width, height);
    if (m_window != nullptr)
        m_window->activate();
}

Window* Super::getWindow() {
    return m_window;
}
