#include "jage/graphics/mesh2d/quad2d.hpp"

using jage::graphics::mesh2d::Quad2D;

Quad2D::Quad2D(const jage::type::RectF& rect, const jage::graphics::Material &material)
        : Mesh2D(createVertices(rect), createIndices(), material)
{

}

std::vector<jage::graphics::mesh2d::Vertex2D> jage::graphics::mesh2d::Quad2D::createVertices(const jage::type::RectF &rect) {
    std::vector<Vertex2D> result;

    result.emplace_back(Vertex2D {
            .position = glm::vec2(rect.x1, rect.y1),
            .colour = glm::vec3(1.0f),
            .texCoord = glm::vec2(0.0f, 0.0f)
    });

    result.emplace_back(Vertex2D {
            .position = glm::vec2(rect.x2, rect.y1),
            .colour = glm::vec3(1.0f),
            .texCoord = glm::vec2(1.0f, 0.0f)
    });

    result.emplace_back(Vertex2D {
            .position = glm::vec2(rect.x1, rect.y2),
            .colour = glm::vec3(1.0f),
            .texCoord = glm::vec2(0.0f, 1.0f)
    });

    result.emplace_back(Vertex2D {
            .position = glm::vec2(rect.x2, rect.y2),
            .colour = glm::vec3(1.0f),
            .texCoord = glm::vec2(1.0f, 1.0f)
    });

    return result;
}

std::vector<GLuint> jage::graphics::mesh2d::Quad2D::createIndices() {
    return {
        0, 3, 2,
        3, 0, 1
    };
}
