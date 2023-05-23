#ifndef JAGE_RECT_HPP
#define JAGE_RECT_HPP

#include <glm/glm.hpp>

namespace jage::type {

    template<typename T, typename TPair>
    struct Rect;

    typedef Rect<float, glm::vec2> RectF;
    typedef Rect<double, glm::vec<2, double>> RectD;
    typedef Rect<int, glm::vec<2, int>> RectI32;

    template<typename T, typename TPair>
    struct Rect {
        typedef T ValueType;
        typedef TPair PairType;

        T x1, y1;
        T x2, y2;

        Rect();
        Rect(T width, T height);
        Rect(T x1, T y1, T x2, T y2);
        Rect(TPair corner, T width, T height);
        Rect(TPair corner1, TPair corner2);
        Rect(const Rect& ref);
        ~Rect() = default;

        template<typename TNew, typename TPairNew>
        Rect<TNew, TPairNew> as();
        template<typename TRect>
        jage::type::Rect<typename TRect::ValueType, typename TRect::PairType> as();

        void moveX(T x);
        void moveY(T y);

        void setWidth(T width);
        void setHeight(T height);

        template<class TRect>
        Rect scalePhysical(const Rect<T, TPair>& parentImaginary, const TRect& parentPhysical, const TRect& anchor);

        Rect normalized();

        bool isContaining(const TPair& point);
        bool isIntersecting(const Rect& other);

        [[nodiscard]] TPair getSize() const;

        Rect<T, TPair>& operator+=(const T& val);
        Rect<T, TPair>& operator+=(const TPair& val);
        Rect<T, TPair> operator+(const T& val) const;
        Rect<T, TPair> operator+(const TPair& val) const;

        Rect<T, TPair>& operator-=(const T& val);
        Rect<T, TPair>& operator-=(const TPair& val);
        Rect<T, TPair> operator-(const T& val) const;
        Rect<T, TPair> operator-(const TPair& val) const;

        Rect<T, TPair>& operator*=(const T& val);
        Rect<T, TPair>& operator*=(const TPair& val);
        Rect<T, TPair> operator*(const T& val) const;
        Rect<T, TPair> operator*(const TPair& val) const;

        Rect<T, TPair>& operator/=(const T& val);
        Rect<T, TPair>& operator/=(const TPair& val);
        Rect<T, TPair> operator/(const T& val) const;
        Rect<T, TPair> operator/(const TPair& val) const;

        bool operator==(const Rect& other) const;
        bool operator!=(const Rect& other) const;

        Rect& operator=(const Rect& ref);
    };
}

template<typename T, typename TPair>
jage::type::Rect<T, TPair> operator+(const T& val, const jage::type::Rect<T, TPair>& rect);
template<typename T, typename TPair>
jage::type::Rect<T, TPair> operator+(const TPair& val, const jage::type::Rect<T, TPair>& rect);

template<typename T, typename TPair>
jage::type::Rect<T, TPair> operator-(const T& val, const jage::type::Rect<T, TPair>& rect);
template<typename T, typename TPair>
jage::type::Rect<T, TPair> operator-(const TPair& val, const jage::type::Rect<T, TPair>& rect);

template<typename T, typename TPair>
jage::type::Rect<T, TPair> operator*(const T& val, const jage::type::Rect<T, TPair>& rect);
template<typename T, typename TPair>
jage::type::Rect<T, TPair> operator*(const TPair& val, const jage::type::Rect<T, TPair>& rect);

template<typename T, typename TPair>
jage::type::Rect<T, TPair> operator/(const T& val, const jage::type::Rect<T, TPair>& rect);
template<typename T, typename TPair>
jage::type::Rect<T, TPair> operator/(const TPair& val, const jage::type::Rect<T, TPair>& rect);

#include "rect_impl.tpp"

#endif //JAGE_RECT_HPP
