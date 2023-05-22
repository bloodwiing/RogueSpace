#ifndef JAGE_QUAD_2D_HPP
#define JAGE_QUAD_2D_HPP

#include "jage/graphics/mesh2d/mesh2d.hpp"
#include "jage/type/rect.hpp"

namespace jage::graphics::mesh2d {

    class Quad2D
            : public Mesh2D {
    public:
        Quad2D(const jage::type::RectF& rect, const Material& material);

    protected:
        static std::vector<Vertex2D> createVertices(const jage::type::RectF& rect);
        static std::vector<GLuint> createIndices();
    };
}

#endif //JAGE_QUAD_2D_HPP
