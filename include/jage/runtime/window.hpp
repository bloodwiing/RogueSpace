#ifndef JAGE_WINDOW_HPP
#define JAGE_WINDOW_HPP

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#define JAGE_IS_KEY(key, state) (jage::runtime::Window::getActive() != nullptr and jage::runtime::Window::getActive()->isKey(key, state))
#define JAGE_IS_MOUSE(button, state) (jage::runtime::Window::getActive() != nullptr and jage::runtime::Window::getActive()->isMouse(button, state))
#define JAGE_RESET_MOUSE() (jage::runtime::Window::getActive() != nullptr ? jage::runtime::Window::getActive()->resetMouse() : void())
#define JAGE_GET_RELATIVE_MOUSE(x, y) (jage::runtime::Window::getActive() != nullptr ? jage::runtime::Window::getActive()->getRelativeMouse(x, y) : void())
#define JAGE_GET_ABSOLUTE_MOUSE(x, y) (jage::runtime::Window::getActive() != nullptr ? jage::runtime::Window::getActive()->getAbsoluteMouse(x, y) : void())

namespace jage::runtime {

    /// \brief      A game window, can support multiple, but preferred to be only 1
    /// \details    Manages a glfwWindow
    class Window {
    public:
        /// \brief          Creates a new glfwWindow of the given size
        /// \param width    The Width of the new Window
        /// \param height   The Height of the new Window
        Window(int width, int height);
        /// \brief          Destroys the glfwWindow
        ~Window();

        /// \brief          Sets the current Window as the active context for OpenGL events
        void activate();
        /// \brief          Returns the currently active Window used for drawing
        static Window* getActive();

        /// \brief          Updates the Physical size of the Window
        void updateSize(int width, int height);

        /// \return         The Width of the Window
        [[nodiscard]] int getWidth() const;
        /// \return         The Height of the Window
        [[nodiscard]] int getHeight() const;
        /// \return         The Aspect Ratio or Width/Height Ratio of the Window
        [[nodiscard]] float getAspectRatio() const;

        /// \return         The glfwWindow instance of this Window
        [[nodiscard]] GLFWwindow* getWindow() const;

        /// \brief          Swaps the Back and Front buffer
        void swapBuffers() const;

        /// \brief          Begin the shutdown of the glfwWindow
        void close();
        /// \return         The state if the glfwWindow has received a system call to be closed or has been shutdown
        ///                 from a function call
        /// \see            Window#close
        [[nodiscard]] bool isClosing() const;

        /// \brief          Checks if a Keyboard Button matches a Button state
        /// \param key      The glfw Key to check
        /// \param state    The glfw State to compare to
        /// \return         - true, if the key matches the state
        ///                 - false, if the key does not match the state
        [[nodiscard]] bool isKey(int key, int state) const;
        /// \brief          Checks if a Mouse Button matches a Button state
        /// \param key      The glfw Mouse Button to check
        /// \param state    The glfw State to compare to
        /// \return         - true, if the Mouse Button matches the state
        ///                 - false, if the Mouse Button does not match the state
        [[nodiscard]] bool isMouse(int button, int state) const;

        /// \brief          Helper function to move the mouse back to the centre of the glfwWindow
        void resetMouse() const;
        /// \brief          Reads the Cursor position and updates the coordinate parameters to match them
        /// \details        This function is in window space, within [0; width) and [0; height) values respectively
        ///                 for the x and y components
        /// \param[out] x   The absolute X position
        /// \param[out] y   The absolute Y position
        void getAbsoluteMouse(int& x, int& y) const;
        /// \brief          Reads the Cursor position and updates the coordinate parameters to match them
        /// \details        This function is in screen space, within the [-0.5; 0.5] range for the shorter component and aspect relative other
        /// \param[out] x   The relative X position
        /// \param[out] y   The relative Y position
        void getRelativeMouse(double& x, double& y) const;

    private:
        /// The glfwWindow or System window of this Window
        GLFWwindow* m_glWindow;

        /// The Width of this Window
        int m_width,
        /// The Height of this Window
        m_height;

        /// The currently active window used as the context for OpenGL calls
        static Window* m_active;

        /// A flag that stops OpenGL from loading multiple times
        static bool m_wasGLLoaded;
    };
}

#endif //JAGE_WINDOW_HPP
