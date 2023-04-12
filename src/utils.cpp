#include "utils.hpp"

#include <fstream>
#include <limits>

std::string readFileContents(const std::string &filename, std::ios_base::openmode mode /* = std::ios_base::in */) {
    std::ifstream stream(filename, mode);

    stream.ignore(std::numeric_limits<std::streamsize>::max());
    auto size = stream.gcount();
    stream.seekg(0, std::ios::beg);
    stream.clear();

    std::string result(size, '\0');
    stream.read(&result[0], size);

    return result;
}
