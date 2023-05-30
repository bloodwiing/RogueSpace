#include "jage/graphics/mesh2d/quad2d.hpp"

#include "jage/runtime/window.hpp"

using jage::graphics::mesh2d::Quad2D;
using jage::graphics::mesh2d::Sprite;
using jage::runtime::Window;

Quad2D::Quad2D(const jage::type::RectF& rect, std::shared_ptr<Sprite> sprite)
        : Mesh2D(createVertices(rect), createIndices(), std::move(sprite))
{

}

std::vector<jage::graphics::mesh2d::Vertex2D> jage::graphics::mesh2d::Quad2D::createVertices(const jage::type::RectF &rect) {
    std::vector<Vertex2D> result;

    const auto size = Window::getActive()->getRect().as<type::RectF>().getSize();
    const auto newRect = rect * size;

    result.emplace_back(Vertex2D {
            .position = glm::vec2(newRect.x1, newRect.y1),
            .colour = glm::vec3(1.0f),
            .texCoord = glm::vec2(0.0f, 0.0f)
    });

    result.emplace_back(Vertex2D {
            .position = glm::vec2(newRect.x2, newRect.y1),
            .colour = glm::vec3(1.0f),
            .texCoord = glm::vec2(1.0f, 0.0f)
    });

    result.emplace_back(Vertex2D {
            .position = glm::vec2(newRect.x1, newRect.y2),
            .colour = glm::vec3(1.0f),
            .texCoord = glm::vec2(0.0f, 1.0f)
    });

    result.emplace_back(Vertex2D {
            .position = glm::vec2(newRect.x2, newRect.y2),
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
