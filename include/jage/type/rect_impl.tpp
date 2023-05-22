template<typename T>
jage::type::Rect<T>::Rect()
    : x1(0.0)
    , y1(0.0)
    , x2(1.0)
    , y2(1.0)
{

}

template<typename T>
jage::type::Rect<T>::Rect(T width, T height)
        : x1(0.0)
        , y1(0.0)
        , x2(width)
        , y2(height)
{

}

template<typename T>
jage::type::Rect<T>::Rect(T x1, T y1, T x2, T y2)
    : x1(x1)
    , y1(y1)
    , x2(x2)
    , y2(y2)
{

}

template<typename T>
jage::type::Rect<T>::Rect(glm::vec2 corner, T width, T height)
    : x1(corner.x)
    , y1(corner.y)
    , x2(corner.x + width)
    , y2(corner.y + height)
{

}

template<typename T>
jage::type::Rect<T>::Rect(glm::vec2 corner1, glm::vec2 corner2)
    : x1(corner1.x)
    , y1(corner1.y)
    , x2(corner2.x)
    , y2(corner2.y)
{

}

template<typename T>
jage::type::Rect<T>::Rect(const Rect &ref)
        : x1(ref.x1)
        , y1(ref.y1)
        , x2(ref.x2)
        , y2(ref.y2)
{

}

template<typename T>
template<typename TNew>
jage::type::Rect<TNew> jage::type::Rect<T>::as() {
    return Rect<TNew>((TNew)x1, (TNew)y1, (TNew)x2, (TNew)y2);
}

template<typename T>
void jage::type::Rect<T>::moveX(T x) {
    x2 = x2 - x1 + x;
    x1 = x;
}

template<typename T>
void jage::type::Rect<T>::moveY(T y) {
    y2 = y2 - y1 + y;
    y1 = y;
}

template<typename T>
void jage::type::Rect<T>::setWidth(T width) {
    x2 = x1 + width;
}

template<typename T>
void jage::type::Rect<T>::setHeight(T height) {
    x2 = x1 + height;
}

template<typename T>
jage::type::Rect<T> jage::type::Rect<T>::scalePhysical(const Rect<T>& parentImaginary, const Rect<T>& parentPhysical, const Rect<float>& anchor) {
    const T diffX1 = parentPhysical.x1 - parentImaginary.x1;
    const T diffY1 = parentPhysical.y1 - parentImaginary.y1;
    const T diffX2 = parentPhysical.x2 - parentImaginary.x2;
    const T diffY2 = parentPhysical.y2 - parentImaginary.y2;

    const T newX1 = x1 + diffX1 * (1.0 - anchor.x1) + diffX2 * anchor.x1;
    const T newY1 = y1 + diffY1 * (1.0 - anchor.y1) + diffY2 * anchor.y1;
    const T newX2 = x2 + diffX2 * anchor.x2 - diffX1 * (1.0 - anchor.x2);
    const T newY2 = x2 + diffY2 * anchor.y2 - diffY1 * (1.0 - anchor.y2);

    return {newX1, newY1, newX2, newY2};
}

template<typename T>
jage::type::Rect<T> jage::type::Rect<T>::normalized() {
    return Rect();
}

template<typename T>
bool jage::type::Rect<T>::isContaining(const glm::vec2 &point) {
    return false;
}

template<typename T>
bool jage::type::Rect<T>::isIntersecting(const Rect &other) {
    return false;
}

template<typename T>
bool jage::type::Rect<T>::operator==(const Rect &other) const {
    return x1 == other.x1 and x2 == other.x2 and y1 == other.y1 and y2 == other.y2;
}

template<typename T>
bool jage::type::Rect<T>::operator!=(const Rect &other) const {
    return !this->operator==(other);
}

template<typename T>
jage::type::Rect<T>& jage::type::Rect<T>::operator=(const Rect &ref) {
    return *this;
}
