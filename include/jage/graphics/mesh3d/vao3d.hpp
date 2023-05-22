#ifndef JAGE_VAO_3D_HPP
#define JAGE_VAO_3D_HPP

#include <glad/glad.h>

#include "jage/graphics/abc/vao_abc.hpp"
#include "jage/graphics/mesh3d/vbo3d.hpp"

namespace jage::graphics::mesh3d {

    typedef abc::VAObjectABC<VBO3D> VAO3D;
}

#endif //JAGE_VAO_3D_HPP
