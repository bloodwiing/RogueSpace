#include "engine/super.h"

Screen* Super::m_screen = nullptr;

void Super::init(int width, int height) {
    m_screen = new Screen(width, height);
    if (m_screen != nullptr)
        m_screen->activate();
}

Screen* Super::getScreen() {
    return m_screen;
}
