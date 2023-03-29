#ifndef SCREEN_CLASS_H
#define SCREEN_CLASS_H

class Screen {
public:
    static Screen* getInstance();

    int width,
        height;

private:
    static Screen* instance;
};

#endif //SCREEN_CLASS_H
