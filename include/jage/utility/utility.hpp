#ifndef UTILITY_FILE_H
#define UTILITY_FILE_H

#include <string>
#include <streambuf>
#include <ios>

namespace jage::utility {

    /// \brief          Loads any other required OpenGL libraries
    /// \details        Initialises glfw
    void initializeOpenGL();
}

#endif //UTILITY_FILE_H
