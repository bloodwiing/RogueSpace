template<typename T, typename TPair>
jage::type::Rect<T, TPair>::Rect()
    : x1(0.0)
    , y1(0.0)
    , x2(1.0)
    , y2(1.0)
{

}

template<typename T, typename TPair>
jage::type::Rect<T, TPair>::Rect(T width, T height)
        : x1(0.0)
        , y1(0.0)
        , x2(width)
        , y2(height)
{

}

template<typename T, typename TPair>
jage::type::Rect<T, TPair>::Rect(T x1, T y1, T x2, T y2)
    : x1(x1)
    , y1(y1)
    , x2(x2)
    , y2(y2)
{

}

template<typename T, typename TPair>
jage::type::Rect<T, TPair>::Rect(TPair corner, T width, T height)
    : x1(corner.x)
    , y1(corner.y)
    , x2(corner.x + width)
    , y2(corner.y + height)
{

}

template<typename T, typename TPair>
jage::type::Rect<T, TPair>::Rect(TPair corner1, TPair corner2)
    : x1(corner1.x)
    , y1(corner1.y)
    , x2(corner2.x)
    , y2(corner2.y)
{

}

template<typename T, typename TPair>
jage::type::Rect<T, TPair>::Rect(const Rect &ref)
        : x1(ref.x1)
        , y1(ref.y1)
        , x2(ref.x2)
        , y2(ref.y2)
{

}

template<typename T, typename TPair>
template<typename TNew, typename TNewPair>
jage::type::Rect<TNew, TNewPair> jage::type::Rect<T, TPair>::as() const {
    return Rect<TNew, TNewPair>((TNew)x1, (TNew)y1, (TNew)x2, (TNew)y2);
}

template<typename T, typename TPair>
template<class TRect>
jage::type::Rect<typename TRect::ValueType, typename TRect::PairType> jage::type::Rect<T, TPair>::as() const {
    using TNew = typename TRect::ValueType;
    return jage::type::Rect<TNew, typename TRect::PairType>((TNew)x1, (TNew)y1, (TNew)x2, (TNew)y2);
}

template<typename T, typename TPair>
void jage::type::Rect<T, TPair>::moveX(T x) {
    x2 = x2 - x1 + x;
    x1 = x;
}

template<typename T, typename TPair>
void jage::type::Rect<T, TPair>::moveY(T y) {
    y2 = y2 - y1 + y;
    y1 = y;
}

template<typename T, typename TPair>
void jage::type::Rect<T, TPair>::setWidth(T width) {
    x2 = x1 + width;
}

template<typename T, typename TPair>
void jage::type::Rect<T, TPair>::setHeight(T height) {
    x2 = x1 + height;
}

template<typename T, typename TPair>
template<class TRect>
jage::type::Rect<T, TPair> jage::type::Rect<T, TPair>::scalePhysical(const Rect<T, TPair>& parentImaginary, const TRect& parentPhysical, const TRect& anchor) {
    const T diffX1 = parentPhysical.x1 - parentImaginary.x1;
    const T diffY1 = parentPhysical.y1 - parentImaginary.y1;
    const T diffX2 = parentPhysical.x2 - parentImaginary.x2 - diffX1;
    const T diffY2 = parentPhysical.y2 - parentImaginary.y2 - diffY1;

    const T newX1 = x1 + diffX2 * anchor.x1 + parentPhysical.x1;
    const T newY1 = y1 + diffY2 * anchor.y1 + parentPhysical.y1;
    const T newX2 = x2 + diffX2 * anchor.x2 + parentPhysical.x1;
    const T newY2 = y2 + diffY2 * anchor.y2 + parentPhysical.y1;

    return {newX1, newY1, newX2, newY2};
}

template<typename T, typename TPair>
jage::type::Rect<T, TPair> jage::type::Rect<T, TPair>::normalized() {
    return Rect();
}

template<typename T, typename TPair>
bool jage::type::Rect<T, TPair>::isContaining(const TPair& point) {
    return false;
}

template<typename T, typename TPair>
bool jage::type::Rect<T, TPair>::isIntersecting(const Rect& other) {
    return false;
}

template<typename T, typename TPair>
TPair jage::type::Rect<T, TPair>::getSize() const {
    return TPair(x2 - x1, y2 - y1);
}

template<typename T, typename TPair>
jage::type::Rect<T, TPair>& jage::type::Rect<T, TPair>::operator+=(const T& val) {
    x1 += val;
    y1 += val;
    x2 += val;
    y2 += val;
    return *this;
}

template<typename T, typename TPair>
jage::type::Rect<T, TPair>& jage::type::Rect<T, TPair>::operator+=(const TPair& val) {
    x1 += val.x;
    y1 += val.y;
    x2 += val.x;
    y2 += val.y;
    return *this;
}

template<typename T, typename TPair>
jage::type::Rect<T, TPair> jage::type::Rect<T, TPair>::operator+(const T& val) const {
    Rect<T, TPair> copy(*this);
    copy += val;
    return copy;
}

template<typename T, typename TPair>
jage::type::Rect<T, TPair> jage::type::Rect<T, TPair>::operator+(const TPair& val) const {
    Rect<T, TPair> copy(*this);
    copy += val;
    return copy;
}

template<typename T, typename TPair>
jage::type::Rect<T, TPair>& jage::type::Rect<T, TPair>::operator-=(const T& val) {
    x1 -= val;
    y1 -= val;
    x2 -= val;
    y2 -= val;
    return *this;
}

template<typename T, typename TPair>
jage::type::Rect<T, TPair>& jage::type::Rect<T, TPair>::operator-=(const TPair& val) {
    x1 -= val.x;
    y1 -= val.y;
    x2 -= val.x;
    y2 -= val.y;
    return *this;
}

template<typename T, typename TPair>
jage::type::Rect<T, TPair> jage::type::Rect<T, TPair>::operator-(const T& val) const {
    Rect<T, TPair> copy(*this);
    copy -= val;
    return copy;
}

template<typename T, typename TPair>
jage::type::Rect<T, TPair> jage::type::Rect<T, TPair>::operator-(const TPair& val) const {
    Rect<T, TPair> copy(*this);
    copy -= val;
    return copy;
}

template<typename T, typename TPair>
jage::type::Rect<T, TPair>& jage::type::Rect<T, TPair>::operator*=(const T& val) {
    x1 *= val;
    y1 *= val;
    x2 *= val;
    y2 *= val;
    return *this;
}

template<typename T, typename TPair>
jage::type::Rect<T, TPair>& jage::type::Rect<T, TPair>::operator*=(const TPair& val) {
    x1 *= val.x;
    y1 *= val.y;
    x2 *= val.x;
    y2 *= val.y;
    return *this;
}

template<typename T, typename TPair>
jage::type::Rect<T, TPair> jage::type::Rect<T, TPair>::operator*(const T& val) const {
    Rect<T, TPair> copy(*this);
    copy *= val;
    return copy;
}

template<typename T, typename TPair>
jage::type::Rect<T, TPair> jage::type::Rect<T, TPair>::operator*(const TPair& val) const {
    Rect<T, TPair> copy(*this);
    copy *= val;
    return copy;
}

template<typename T, typename TPair>
jage::type::Rect<T, TPair>& jage::type::Rect<T, TPair>::operator/=(const T& val) {
    x1 /= val;
    y1 /= val;
    x2 /= val;
    y2 /= val;
    return *this;
}

template<typename T, typename TPair>
jage::type::Rect<T, TPair>& jage::type::Rect<T, TPair>::operator/=(const TPair& val) {
    x1 /= val.x;
    y1 /= val.y;
    x2 /= val.x;
    y2 /= val.y;
    return *this;
}

template<typename T, typename TPair>
jage::type::Rect<T, TPair> jage::type::Rect<T, TPair>::operator/(const T& val) const {
    Rect<T, TPair> copy(*this);
    copy /= val;
    return copy;
}

template<typename T, typename TPair>
jage::type::Rect<T, TPair> jage::type::Rect<T, TPair>::operator/(const TPair& val) const {
    Rect<T, TPair> copy(*this);
    copy /= val;
    return copy;
}

template<typename T, typename TPair>
bool jage::type::Rect<T, TPair>::operator==(const Rect &other) const {
    return x1 == other.x1 and x2 == other.x2 and y1 == other.y1 and y2 == other.y2;
}

template<typename T, typename TPair>
bool jage::type::Rect<T, TPair>::operator!=(const Rect &other) const {
    return !this->operator==(other);
}

template<typename T, typename TPair>
jage::type::Rect<T, TPair>& jage::type::Rect<T, TPair>::operator=(const Rect &ref) {
    x1 = ref.x1;
    y1 = ref.y1;
    x2 = ref.x2;
    y2 = ref.y2;
    return *this;
}

template<typename T, typename TPair>
jage::type::Rect<T, TPair> operator+(const T& val, const jage::type::Rect<T, TPair>& rect) {
    return rect + val;
}

template<typename T, typename TPair>
jage::type::Rect<T, TPair> operator+(const TPair& val, const jage::type::Rect<T, TPair>& rect) {
    return rect + val;
}

template<typename T, typename TPair>
jage::type::Rect<T, TPair> operator-(const T& val, const jage::type::Rect<T, TPair>& rect) {
    return rect * T(-1) + val;
}

template<typename T, typename TPair>
jage::type::Rect<T, TPair> operator-(const TPair& val, const jage::type::Rect<T, TPair>& rect) {
    return rect * T(-1) + val;
}

template<typename T, typename TPair>
jage::type::Rect<T, TPair> operator*(const T& val, const jage::type::Rect<T, TPair>& rect) {
    return rect * val;
}

template<typename T, typename TPair>
jage::type::Rect<T, TPair> operator*(const TPair& val, const jage::type::Rect<T, TPair>& rect) {
    return rect * val;
}

template<typename T, typename TPair>
jage::type::Rect<T, TPair> operator/(const T& val, const jage::type::Rect<T, TPair>& rect) {
    return jage::type::Rect<T, TPair> {
            .x1 = val / rect.x1,
            .y1 = val / rect.y1,
            .x2 = val / rect.x2,
            .y2 = val / rect.y2
    };
}

template<typename T, typename TPair>
jage::type::Rect<T, TPair> operator/(const TPair& val, const jage::type::Rect<T, TPair>& rect) {
    return jage::type::Rect<T, TPair> {
            .x1 = val.x / rect.x1,
            .y1 = val.y / rect.y1,
            .x2 = val.x / rect.x2,
            .y2 = val.y / rect.y2
    };
}
