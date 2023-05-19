#ifndef JAGE_RECT_HPP
#define JAGE_RECT_HPP

#include <glm/glm.hpp>

namespace jage::type {

    template<typename T>
    struct Rect {
        T x1, y1;
        T x2, y2;

        Rect();
        Rect(T width, T height);
        Rect(T x1, T y1, T x2, T y2);
        Rect(glm::vec2 corner, T width, T height);
        Rect(glm::vec2 corner1, glm::vec2 corner2);
        Rect(const Rect& ref);
        ~Rect() = default;

        template<typename TNew>
        Rect<TNew> as();

        void moveX(T x);
        void moveY(T y);

        void setWidth(T width);
        void setHeight(T height);

        Rect scalePhysical(const Rect& parentImaginary, const Rect& parentPhysical, const Rect& anchor);

        Rect normalized();

        bool isContaining(const glm::vec2& point);
        bool isIntersecting(const Rect& other);

        bool operator==(const Rect& other) const;
        bool operator!=(const Rect& other) const;

        Rect& operator=(const Rect& ref);
    };
}

#include "rect_impl.tpp"

#endif //JAGE_RECT_HPP
