#ifndef JAGE_UTILITY_HPP
#define JAGE_UTILITY_HPP

#include <string>
#include <streambuf>
#include <ios>

namespace jage::utility {

    /// \brief          Loads any other required OpenGL libraries
    /// \details        Initialises glfw
    void initializeOpenGL();

    template<class T>
    struct EnumSize;
}

#endif //JAGE_UTILITY_HPP
