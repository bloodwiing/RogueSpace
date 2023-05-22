#ifndef JAGE_TRANSFORMABLE_ABC_HPP
#define JAGE_TRANSFORMABLE_ABC_HPP

namespace jage::node::abc {

    template<typename TVec, typename TRot, typename TMat>
    class TransformableABC {
    public:
        typedef TVec VectorType;

        typedef TVec TranslateType;
        typedef TRot RotateType;
        typedef TMat MatrixType;

        [[nodiscard]] virtual TMat getWorldMatrix() const = 0;

        [[nodiscard]] virtual TVec getTranslation() const = 0;
        [[nodiscard]] virtual TRot getRotation() const = 0;
        [[nodiscard]] virtual TVec getScale() const = 0;

        [[nodiscard]] virtual TVec getWorldPosition() const = 0;

        virtual void setTranslation(const TVec& tra) = 0;
        virtual void setRotation(const TRot& rot) = 0;
        virtual void setScale(const TVec& sca) = 0;

        virtual void translate(const TVec& tra) = 0;
        virtual void rotate(const TRot& rot) = 0;
        virtual void scale(const TVec& sca) = 0;
    };
}

#include "transformable_abc_impl.tpp"

#endif //JAGE_TRANSFORMABLE_ABC_HPP
