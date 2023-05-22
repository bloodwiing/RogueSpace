#ifndef JAGE_VAO_2D_HPP
#define JAGE_VAO_2D_HPP

#include <glad/glad.h>

#include "jage/graphics/abc/vao_abc.hpp"
#include "jage/graphics/mesh2d/vbo2d.hpp"

namespace jage::graphics::mesh2d {

    typedef abc::VAObjectABC<VBO2D> VAO2D;
}

#endif //JAGE_VAO_2D_HPP
