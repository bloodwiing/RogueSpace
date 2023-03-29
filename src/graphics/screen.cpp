#include "graphics/screen.h"

Screen* Screen::instance = nullptr;

Screen *Screen::getInstance() {
    if (instance == nullptr)
        instance = new Screen();
    return instance;
}
