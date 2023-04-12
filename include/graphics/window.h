#ifndef WINDOW_CLASS_H
#define WINDOW_CLASS_H

#define GLFW_INCLUDE_NONE
#include <glfw3.h>

#define IS_KEY(key, state) Window::getActive()->isKey(key, state)
#define IS_MOUSE(button, state) Window::getActive()->isMouse(button, state)
#define RESET_MOUSE() Window::getActive()->resetMouse()
#define GET_RELATIVE_MOUSE(x, y) Window::getActive()->getRelativeMouse(x, y)
#define GET_ABSOLUTE_MOUSE(x, y) Window::getActive()->getAbsoluteMouse(x, y)

class Window {
public:
    Window(int width, int height);
    ~Window();

    void activate();
    static Window* getActive();

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
    GLFWwindow* m_glWindow;

    int m_width,
        m_height;

    static Window* m_active;

    static bool m_wasGLLoaded;
};

#endif //WINDOW_CLASS_H
