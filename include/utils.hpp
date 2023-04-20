#ifndef UTILS_FILE_H
#define UTILS_FILE_H

#include <string>
#include <streambuf>
#include <ios>

/// \brief          Loads any other required OpenGL libraries
/// \details        Initialises glfw
void initializeOpenGL();

/// \brief          Reads the file from the path in the filename and returns the data of it
/// \param filename The path of the file to read
/// \param mode     The mode which to use when reading the file. Can be used along with std::ios::binary, but then
///                 the resulting std::string is better to be converted to a C string
/// \return         The string representing the file contents
std::string readFileContents(const std::string &filename, std::ios::openmode mode = std::ios::in);

#endif //UTILS_FILE_H
