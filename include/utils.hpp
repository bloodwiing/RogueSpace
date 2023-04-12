#ifndef UTILS_FILE_H
#define UTILS_FILE_H

#include <string>
#include <streambuf>
#include <ios>

std::string readFileContents(const std::string &filename, std::ios::openmode mode = std::ios::in);

#endif //UTILS_FILE_H
