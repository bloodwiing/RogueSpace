#ifndef JAGE_TRANSFORMABLE_3D_ABC_HPP
#define JAGE_TRANSFORMABLE_3D_ABC_HPP

#include <glm/glm.hpp>

#include "jage/node/abc/transformable_abc.hpp"

namespace jage::node::abc {

    class Transformable3DABC : public abc::TransformableABC<glm::vec3, glm::quat, glm::mat4> {
    public:
        [[nodiscard]] glm::vec3 getWorldPosition() const override;

        void translate(const glm::vec3& tra) override;
        void rotate(const glm::quat& rot) override;
        void scale(const glm::vec3& sca) override;
    };
}

#endif //JAGE_TRANSFORMABLE_3D_ABC_HPP
