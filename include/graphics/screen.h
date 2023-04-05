#ifndef SCREEN_CLASS_H
#define SCREEN_CLASS_H

#define GLFW_INCLUDE_NONE
#include <glfw3.h>

#define IS_KEY(key, state) Screen::getActive()->isKey(key, state)
#define IS_MOUSE(button, state) Screen::getActive()->isMouse(button, state)
#define RESET_MOUSE() Screen::getActive()->resetMouse()
#define GET_RELATIVE_MOUSE(x, y) Screen::getActive()->getRelativeMouse(x, y)
#define GET_ABSOLUTE_MOUSE(x, y) Screen::getActive()->getAbsoluteMouse(x, y)

class Screen {
public:
    Screen(int width, int height);
    ~Screen();

    void activate();
    static Screen* getActive();

    void updateSize(int width, int height);

    [[nodiscard]] int getWidth() const;
    [[nodiscard]] int getHeight() const;

    [[nodiscard]] GLFWwindow* getWindow() const;

    void swapBuffers() const;

    void close();
    [[nodiscard]] bool isClosing() const;

    [[nodiscard]] bool isKey(int key, int state) const;
    [[nodiscard]] bool isMouse(int button, int state) const;

    void resetMouse() const;
    void getAbsoluteMouse(int& x, int& y) const;
    void getRelativeMouse(double& x, double& y) const;

private:
    GLFWwindow* m_window;

    int m_width,
        m_height;

    static Screen* m_active;

    static bool m_wasGLLoaded;
};

#endif //SCREEN_CLASS_H
