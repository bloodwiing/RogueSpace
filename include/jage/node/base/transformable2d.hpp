#ifndef JAGE_TRANSFORMABLE_2D_HPP
#define JAGE_TRANSFORMABLE_2D_HPP

#include <glm/glm.hpp>

#include "jage/node/abc/transformable_abc.hpp"

namespace jage::node::base {

    class Transformable2D : public abc::TransformableABC<glm::vec2, float, glm::mat3> {
    public:
        [[nodiscard]] glm::vec2 getWorldPosition() const override;

        void translate(const glm::vec2& tra) override;
        void rotate(const float& rot) override;
        void scale(const glm::vec2& sca) override;
    };
}

#endif //JAGE_TRANSFORMABLE_2D_HPP
