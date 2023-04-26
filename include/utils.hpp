#ifndef UTILS_FILE_H
#define UTILS_FILE_H

#include <string>
#include <streambuf>
#include <ios>

namespace Utility {

    /// \brief          Loads any other required OpenGL libraries
    /// \details        Initialises glfw
    void initializeOpenGL();

    /// \brief          Reads the file from the path in the filename and returns the data of it
    /// \details        Will automatically convert Windows style line endings (\r\n) to UNIX style (\n) if the mode is not std::ios::binary
    /// \param filename The path of the file to read
    /// \param mode     The mode which to use when reading the file. Can be used along with std::ios::binary, but then
    ///                 the resulting std::string is better to be converted to a C string
    /// \return         The string representing the file contents
    /// \see            unixifyLineEndings
    std::string readFileContents(std::string filename, std::ios::openmode mode = std::ios::in);

    /// \brief          Finds and creates a string representing the current process' directory
    /// \details        Useful for looking up files relative to the executable and not working directory
    /// \return         The string path to the directory
    std::string getProcessDirectory();

    /// \brief          Converts Windows style \r\n line endings to UNIX style \n new line endings
    void unixifyLineEndings(std::string& text);
}

#endif //UTILS_FILE_H
