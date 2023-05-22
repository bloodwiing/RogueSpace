#ifndef JAGE_TRANSFORMABLE_2D_ABC_HPP
#define JAGE_TRANSFORMABLE_2D_ABC_HPP

#include <glm/glm.hpp>

#include "jage/node/abc/transformable_abc.hpp"

namespace jage::node::abc {

    class Transformable2DABC : public abc::TransformableABC<glm::vec2, float, glm::mat3> {
    public:
        [[nodiscard]] glm::vec2 getWorldPosition() const override;

        void translate(const glm::vec2& tra) override;
        void rotate(const float& rot) override;
        void scale(const glm::vec2& sca) override;

        void updateTransformations(const glm::mat3& parentMatrix) override;
    };
}

#endif //JAGE_TRANSFORMABLE_2D_ABC_HPP
