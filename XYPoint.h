#pragma once

namespace Space::implementation {

template <typename ThisSpace, typename UnderlyingData> class XYPoint final : public Base<ThisSpace, UnderlyingData, 2> {
    friend class NormalizedVector<ThisSpace, UnderlyingData>;
    friend class NormalizedXYVector<ThisSpace, UnderlyingData>;
    friend class Point<ThisSpace, UnderlyingData>;
    friend class Vector<ThisSpace, UnderlyingData>;
    friend class XYVector<ThisSpace, UnderlyingData>;
    using _base = Base<ThisSpace, UnderlyingData, 2>;

  public:
    XYPoint() noexcept { std::fill(_base::begin(), _base::end(), 0); }
    explicit XYPoint(const UnderlyingData &v) noexcept {
        auto iter = _base::begin();
        auto in = implementation::CBegin(v);
        *iter++ = *in++;
        *iter++ = *in++;
        *iter = 0;
    }
    XYPoint(const double x, const double y) noexcept {
        auto iter = _base::begin();
        *iter++ = x;
        *iter++ = y;
        *iter = 0;
    }

    [[nodiscard]] double X() const noexcept { return *(_base::cbegin() + 0); }
    [[nodiscard]] double Y() const noexcept { return *(_base::cbegin() + 1); }

    void SetX(const double d) noexcept { *(_base::begin() + 0) = d; }
    void SetY(const double d) noexcept { *(_base::begin() + 1) = d; }

    [[nodiscard]] operator Point<ThisSpace, UnderlyingData>() const noexcept {
        return Point<ThisSpace, UnderlyingData>(X(), Y(), 0);
    }

    [[nodiscard]] bool operator==(const Point<ThisSpace, UnderlyingData> &other) const noexcept {
        return std::equal(_base::cbegin(), _base::cend(), implementation::CBegin(other.underlyingData), Equality);
    }
    [[nodiscard]] bool operator==(const XYPoint<ThisSpace, UnderlyingData> &other) const noexcept {
        return std::equal(_base::cbegin(), _base::cend(), implementation::CBegin(other.underlyingData), Equality);
    }

    [[nodiscard]] bool operator!=(const Point<ThisSpace, UnderlyingData> &other) const noexcept { return !(operator==(other)); }

    [[nodiscard]] bool operator!=(const XYPoint<ThisSpace, UnderlyingData> &other) const noexcept { return !(operator==(other)); }

    double operator[](const unsigned int i) const {
        if (i > 1) {
            throw std::invalid_argument("Index is out of range");
        }
        return *(_base::cbegin() + i);
    }

    template <int I> requires ValidFor2dAt<I>
    [[nodiscard]] double at() const {
        return operator[](I);
    }

    auto operator-=(const XYVector<ThisSpace, UnderlyingData> &rhs) noexcept {
        Sub(_base::underlyingData, rhs.underlyingData);
        return *this;
    }
    auto operator-=(const NormalizedXYVector<ThisSpace, UnderlyingData> &rhs) noexcept {
        Sub(_base::underlyingData, rhs.underlyingData);
        return *this;
    }

    [[nodiscard]] auto operator-(const Vector<ThisSpace, UnderlyingData> &rhs) const noexcept {
        Point<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Sub(v.underlyingData, rhs.underlyingData);
        return v;
    }
    [[nodiscard]] auto operator-(const NormalizedVector<ThisSpace, UnderlyingData> &rhs) const noexcept {
        Point<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Sub(v.underlyingData, rhs.underlyingData);
        return v;
    }
    [[nodiscard]] auto operator-(const NormalizedXYVector<ThisSpace, UnderlyingData> &rhs) const noexcept {
        XYPoint<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Sub(v.underlyingData, rhs.underlyingData);
        return v;
    }
    [[nodiscard]] auto operator-(const XYVector<ThisSpace, UnderlyingData> &rhs) const noexcept {
        XYPoint<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Sub(v.underlyingData, rhs.underlyingData);
        return v;
    }

    [[nodiscard]] auto operator-(const XYPoint<ThisSpace, UnderlyingData> &rhs) const noexcept {
        XYVector<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Sub(v.underlyingData, rhs._base::underlyingData);
        return v;
    }
    [[nodiscard]] auto operator-(const Point<ThisSpace, UnderlyingData> &rhs) const noexcept {
        Vector<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Sub(v.underlyingData, rhs.underlyingData);
        return v;
    }

    auto operator+=(const XYVector<ThisSpace, UnderlyingData> &rhs) noexcept {
        Add(_base::underlyingData, rhs.underlyingData);
        return *this;
    }
    auto operator+=(const NormalizedXYVector<ThisSpace, UnderlyingData> &rhs) noexcept {
        Add(_base::underlyingData, rhs.underlyingData);
        return *this;
    }

    [[nodiscard]] auto operator+(const Vector<ThisSpace, UnderlyingData> &rhs) const noexcept {
        Point<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Add(v.underlyingData, rhs.underlyingData);
        return v;
    }
    [[nodiscard]] auto operator+(const NormalizedVector<ThisSpace, UnderlyingData> &rhs) const noexcept {
        Point<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Add(v.underlyingData, rhs.underlyingData);
        return v;
    }
    [[nodiscard]] auto operator+(const NormalizedXYVector<ThisSpace, UnderlyingData> &rhs) const noexcept {
        XYPoint<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Add(v.underlyingData, rhs.underlyingData);
        return v;
    }
    [[nodiscard]] auto operator+(const XYVector<ThisSpace, UnderlyingData> &rhs) const noexcept {
        XYPoint<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Add(v.underlyingData, rhs.underlyingData);
        return v;
    }

    template <typename OtherSpace, typename TransformManager> requires DifferentSpaces<OtherSpace, ThisSpace>
    [[nodiscard]] auto ConvertTo(const TransformManager &transform_manager) const {
        return Point<OtherSpace, UnderlyingData>(
            transform_manager.template TransformPoint<ThisSpace, OtherSpace>(static_cast<UnderlyingData>(*this))
        );
    }

    friend std::ostream &operator<<(std::ostream &os, const XYPoint<ThisSpace, UnderlyingData> &item) {
        const auto space = SpaceTypeNameMap<ThisSpace>::name;
        os << space << "::XYPoint (" << item.X() << ", " << item.Y() << ")";
        return os;
    }

#ifndef IGNORE_SPACE_STATIC_ASSERT
    using _base::operator+=;
    using _base::operator+;
    using _base::operator-=;
    using _base::operator-;
    using _base::ConvertTo;

    template <int I> requires(!ValidFor2dAt<I>)
    typename StaticAssert::invalid_at_access at() const {
        return StaticAssert::invalid_at_access{};
    }

    template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
    StaticAssert::invalid_space operator!=(const Point<OtherSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_space{};
    }
    template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
    StaticAssert::invalid_space operator!=(const XYPoint<OtherSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_space{};
    }

    template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
    StaticAssert::invalid_space operator==(const Point<OtherSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_space{};
    }
    template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
    StaticAssert::invalid_space operator==(const XYPoint<OtherSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_space{};
    }

    StaticAssert::invalid_point_vector_equality operator==(const Vector<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_point_vector_equality{};
    }
    StaticAssert::invalid_point_vector_equality operator==(const NormalizedVector<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_point_vector_equality{};
    }
    StaticAssert::invalid_point_vector_equality operator==(const NormalizedXYVector<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_point_vector_equality{};
    }
    StaticAssert::invalid_point_vector_equality operator==(const XYVector<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_point_vector_equality{};
    }

    StaticAssert::invalid_point_vector_equality operator!=(const Vector<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_point_vector_equality{};
    }
    StaticAssert::invalid_point_vector_equality operator!=(const NormalizedVector<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_point_vector_equality{};
    }
    StaticAssert::invalid_point_vector_equality operator!=(const NormalizedXYVector<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_point_vector_equality{};
    }
    StaticAssert::invalid_point_vector_equality operator!=(const XYVector<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_point_vector_equality{};
    }

    StaticAssert::invalid_point_to_point_addition operator+=(const Point<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_point_to_point_addition{};
    }
    StaticAssert::invalid_point_to_point_addition operator+=(const XYPoint<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_point_to_point_addition{};
    }

    StaticAssert::invalid_vector3_to_xy_point_addition operator+=(const Vector<ThisSpace, UnderlyingData> &) noexcept {
        return StaticAssert::invalid_vector3_to_xy_point_addition{};
    }
    StaticAssert::invalid_vector3_to_xy_point_addition operator+=(const NormalizedVector<ThisSpace, UnderlyingData> &) noexcept {
        return StaticAssert::invalid_vector3_to_xy_point_addition{};
    }

    StaticAssert::invalid_point_from_point_subtraction operator-=(const Point<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_point_from_point_subtraction{};
    }
    StaticAssert::invalid_point_from_point_subtraction operator-=(const XYPoint<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_point_from_point_subtraction{};
    }

    StaticAssert::invalid_vector3_from_xy_point_subtraction operator-=(const Vector<ThisSpace, UnderlyingData> &) noexcept {
        return StaticAssert::invalid_vector3_from_xy_point_subtraction{};
    }
    StaticAssert::invalid_vector3_from_xy_point_subtraction
    operator-=(const NormalizedVector<ThisSpace, UnderlyingData> &) noexcept {
        return StaticAssert::invalid_vector3_from_xy_point_subtraction{};
    }

    StaticAssert::invalid_point_to_point_addition operator+(const Point<ThisSpace, UnderlyingData> &) const {
        return StaticAssert::invalid_point_to_point_addition{};
    }
    StaticAssert::invalid_point_to_point_addition operator+(const XYPoint<ThisSpace, UnderlyingData> &) const {
        return StaticAssert::invalid_point_to_point_addition{};
    }
#endif
    // Hide functions from intellisense
    void Dot() = delete;
    void Cross() = delete;
    void operator*() = delete;
    void operator*=(double) = delete;
};
} // namespace Space::implementation
