#pragma once

namespace Space::implementation {

template <typename ThisSpace, typename UnderlyingData> class XYVector final : public Base<ThisSpace, UnderlyingData, 2> {

    friend class NormalizedVector<ThisSpace, UnderlyingData>;
    friend class NormalizedXYVector<ThisSpace, UnderlyingData>;
    friend class Point<ThisSpace, UnderlyingData>;
    friend class Vector<ThisSpace, UnderlyingData>;
    friend class XYPoint<ThisSpace, UnderlyingData>;
    using _base = Base<ThisSpace, UnderlyingData, 2>;

  public:
    XYVector() noexcept { std::fill(_base::begin(), _base::end(), 0); }
    explicit XYVector(const UnderlyingData &v) noexcept {
        auto iter = _base::begin();
        auto in = implementation::CBegin(v);
        *iter++ = *in++;
        *iter++ = *in++;
        *iter = 0;
    }
    XYVector(const double x, const double y) noexcept {
        auto iter = _base::begin();
        *iter++ = x;
        *iter++ = y;
        *iter = 0;
    }
    
    [[nodiscard]] operator Vector<ThisSpace, UnderlyingData>() const noexcept {
        return Vector<ThisSpace, UnderlyingData>(X(), Y(), 0);
    }

    [[nodiscard]] double X() const noexcept { return *(_base::cbegin() + 0); }
    [[nodiscard]] double Y() const noexcept { return *(_base::cbegin() + 1); }

    void SetX(const double d) noexcept { *(_base::begin() + 0) = d; }
    void SetY(const double d) noexcept { *(_base::begin() + 1) = d; }

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

    [[nodiscard]] bool operator==(const Vector<ThisSpace, UnderlyingData> &other) const noexcept {
        return std::equal(_base::cbegin(), _base::cend(), implementation::CBegin(other.underlyingData), Equality);
    }
    [[nodiscard]] bool operator==(const NormalizedVector<ThisSpace, UnderlyingData> &other) const noexcept {
        return std::equal(_base::cbegin(), _base::cend(), implementation::CBegin(other.underlyingData), Equality);
    }
    [[nodiscard]] bool operator==(const NormalizedXYVector<ThisSpace, UnderlyingData> &other) const noexcept {
        return std::equal(_base::cbegin(), _base::cend(), implementation::CBegin(other.underlyingData), Equality);
    }
    [[nodiscard]] bool operator==(const XYVector<ThisSpace, UnderlyingData> &other) const noexcept {
        return std::equal(_base::cbegin(), _base::cend(), implementation::CBegin(other.underlyingData), Equality);
    }

    [[nodiscard]] bool operator!=(const Vector<ThisSpace, UnderlyingData> &other) const noexcept { return !(operator==(other)); }
    [[nodiscard]] bool operator!=(const NormalizedVector<ThisSpace, UnderlyingData> &other) const noexcept {
        return !(operator==(other));
    }
    [[nodiscard]] bool operator!=(const NormalizedXYVector<ThisSpace, UnderlyingData> &other) const noexcept {
        return !(operator==(other));
    }
    [[nodiscard]] bool operator!=(const XYVector<ThisSpace, UnderlyingData> &other) const noexcept {
        return !(operator==(other));
    }

    auto operator-=(const NormalizedXYVector<ThisSpace, UnderlyingData> &rhs) noexcept {
        Sub(_base::underlyingData, rhs.underlyingData);
        return *this;
    }
    auto operator-=(const XYVector<ThisSpace, UnderlyingData> &rhs) noexcept {
        Sub(_base::underlyingData, rhs.underlyingData);
        return *this;
    }

    [[nodiscard]] auto operator-(const Vector<ThisSpace, UnderlyingData> &rhs) const noexcept {
        Vector<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Sub(v.underlyingData, rhs.underlyingData);
        return v;
    }
    [[nodiscard]] auto operator-(const NormalizedVector<ThisSpace, UnderlyingData> &rhs) const noexcept {
        Vector<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Sub(v.underlyingData, rhs.underlyingData);
        return v;
    }
    [[nodiscard]] auto operator-(const NormalizedXYVector<ThisSpace, UnderlyingData> &rhs) const noexcept {
        XYVector<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Sub(v.underlyingData, rhs.underlyingData);
        return v;
    }
    [[nodiscard]] auto operator-(const XYVector<ThisSpace, UnderlyingData> &rhs) const noexcept {
        XYVector<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Sub(v.underlyingData, rhs.underlyingData);
        return v;
    }

    auto operator+=(const NormalizedXYVector<ThisSpace, UnderlyingData> &rhs) noexcept {
        Add(_base::underlyingData, rhs.underlyingData);
        return *this;
    }
    auto operator+=(const XYVector<ThisSpace, UnderlyingData> &rhs) noexcept {
        Add(_base::underlyingData, rhs.underlyingData);
        return *this;
    }

    [[nodiscard]] auto operator+(const Vector<ThisSpace, UnderlyingData> &rhs) const noexcept {
        Vector<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Add(v.underlyingData, rhs.underlyingData);
        return v;
    }
    [[nodiscard]] auto operator+(const NormalizedVector<ThisSpace, UnderlyingData> &rhs) const noexcept {
        Vector<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Add(v.underlyingData, rhs.underlyingData);
        return v;
    }
    [[nodiscard]] auto operator+(const NormalizedXYVector<ThisSpace, UnderlyingData> &rhs) const noexcept {
        XYVector<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Add(v.underlyingData, rhs.underlyingData);
        return v;
    }
    [[nodiscard]] auto operator+(const XYVector<ThisSpace, UnderlyingData> &rhs) const noexcept {
        XYVector<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Add(v.underlyingData, rhs.underlyingData);
        return v;
    }

    auto operator*=(const double &d) noexcept {
        Scale(_base::underlyingData, d);
        return *this;
    }

    [[nodiscard]] auto operator*(const double &d) const noexcept {
        XYVector<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Scale(v.underlyingData, d);
        return v;
    }

    [[nodiscard]] auto operator*(const Vector<ThisSpace, UnderlyingData> &rhs) const noexcept { return this->Cross(rhs); }
    [[nodiscard]] auto operator*(const NormalizedXYVector<ThisSpace, UnderlyingData> &rhs) const noexcept {
        return this->Cross(rhs);
    }
    [[nodiscard]] auto operator*(const NormalizedVector<ThisSpace, UnderlyingData> &rhs) const noexcept {
        return this->Cross(rhs);
    }
    [[nodiscard]] auto operator*(const XYVector<ThisSpace, UnderlyingData> &rhs) const noexcept { return this->Cross(rhs); }

    [[nodiscard]] auto Cross(const Vector<ThisSpace, UnderlyingData> &other) const noexcept {
        const auto [x, y, z] = Cross_internal(_base::underlyingData, other.underlyingData);
        return Vector<ThisSpace, UnderlyingData>(x, y, z);
    }
    [[nodiscard]] auto Cross(const NormalizedVector<ThisSpace, UnderlyingData> &other) const noexcept {
        const auto [x, y, z] = Cross_internal(_base::underlyingData, other.underlyingData);
        return Vector<ThisSpace, UnderlyingData>(x, y, z);
    }
    [[nodiscard]] auto Cross(const NormalizedXYVector<ThisSpace, UnderlyingData> &other) const noexcept {
        const auto [x, y, z] = Cross_internal(_base::underlyingData, other.underlyingData);
        return Vector<ThisSpace, UnderlyingData>(x, y, z);
    }
    [[nodiscard]] auto Cross(const XYVector<ThisSpace, UnderlyingData> &other) const noexcept {
        const auto [x, y, z] = Cross_internal(_base::underlyingData, other.underlyingData);
        return Vector<ThisSpace, UnderlyingData>(x, y, z);
    }

    [[nodiscard]] double Dot(const Vector<ThisSpace, UnderlyingData> &other) const noexcept {
        return implementation::Dot(_base::underlyingData, other.underlyingData);
    }
    [[nodiscard]] double Dot(const NormalizedVector<ThisSpace, UnderlyingData> &other) const noexcept {
        return implementation::Dot(_base::underlyingData, other.underlyingData);
    }
    [[nodiscard]] double Dot(const NormalizedXYVector<ThisSpace, UnderlyingData> &other) const noexcept {
        return implementation::Dot(_base::underlyingData, other.underlyingData);
    }
    [[nodiscard]] double Dot(const XYVector<ThisSpace, UnderlyingData> &other) const noexcept {
        return implementation::Dot(_base::underlyingData, other.underlyingData);
    }

    [[nodiscard]] auto Norm() const { return NormalizedXYVector<ThisSpace, UnderlyingData>(X(), Y()); }

    template <typename OtherSpace, typename TransformManager> requires DifferentSpaces<OtherSpace, ThisSpace>
    [[nodiscard]] auto ConvertTo(const TransformManager &transform_manager) const noexcept {
        return Vector<OtherSpace, UnderlyingData>(
            transform_manager.template TransformVector<ThisSpace, OtherSpace>(static_cast<UnderlyingData>(*this))
        );
    }

    [[nodiscard]] auto Mag() const noexcept { return typename ThisSpace::Unit{Mag_double()}; }

    [[nodiscard]] double Mag_double() const noexcept { return Mag_internal(_base::underlyingData); }

    friend std::ostream &operator<<(std::ostream &os, const XYVector<ThisSpace, UnderlyingData> &item) {
        const auto space = SpaceTypeNameMap<ThisSpace>::name;
        os << space << "::XYVector (" << item.X() << ", " << item.Y() << ")";
        return os;
    }

#ifndef IGNORE_SPACE_STATIC_ASSERT
    using _base::operator-=;
    using _base::operator-;
    using _base::operator+=;
    using _base::operator+;
    using _base::operator*=;
    using _base::operator*;
    using _base::ConvertTo;
    using _base::Cross;
    using _base::Dot;

    template <int I> requires(!ValidFor2dAt<I>)
    StaticAssert::invalid_at_access at() const {
        return StaticAssert::invalid_at_access{};
    }

    template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
    StaticAssert::invalid_space operator!=(const Vector<OtherSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_space{};
    }
    template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
    StaticAssert::invalid_space operator!=(const NormalizedVector<OtherSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_space{};
    }
    template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
    StaticAssert::invalid_space operator!=(const NormalizedXYVector<OtherSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_space{};
    }
    template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
    StaticAssert::invalid_space operator!=(const XYVector<OtherSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_space{};
    }

    template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
    StaticAssert::invalid_space operator==(const Vector<OtherSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_space{};
    }
    template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
    StaticAssert::invalid_space operator==(const NormalizedVector<OtherSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_space{};
    }
    template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
    StaticAssert::invalid_space operator==(const NormalizedXYVector<OtherSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_space{};
    }
    template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
    StaticAssert::invalid_space operator==(const XYVector<OtherSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_space{};
    }

    StaticAssert::invalid_point_vector_equality operator==(const Point<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_point_vector_equality{};
    }
    StaticAssert::invalid_point_vector_equality operator==(const XYPoint<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_point_vector_equality{};
    }
    StaticAssert::invalid_point_vector_equality operator!=(const Point<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_point_vector_equality{};
    }
    StaticAssert::invalid_point_vector_equality operator!=(const XYPoint<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_point_vector_equality{};
    }

    StaticAssert::invalid_point_from_vector_subtraction operator-(const Point<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_point_from_vector_subtraction{};
    }

    StaticAssert::invalid_point_to_vector_addition operator+(const Point<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_point_to_vector_addition{};
    }

    StaticAssert::invalid_XYVector_in_place_cross operator*=(const Vector<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_XYVector_in_place_cross{};
    }
    StaticAssert::invalid_XYVector_in_place_cross operator*=(const NormalizedVector<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_XYVector_in_place_cross{};
    }
    StaticAssert::invalid_XYVector_in_place_cross
    operator*=(const NormalizedXYVector<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_XYVector_in_place_cross{};
    }
    StaticAssert::invalid_XYVector_in_place_cross operator*=(const XYVector<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_XYVector_in_place_cross{};
    }

    StaticAssert::invalid_vector_to_vector_addition operator+=(const Vector<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_vector_to_vector_addition{};
    }
    StaticAssert::invalid_vector_to_vector_addition
    operator+=(const NormalizedVector<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_vector_to_vector_addition{};
    }

    StaticAssert::invalid_vector_from_vector_subtraction operator-=(const Vector<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_vector_from_vector_subtraction{};
    }
    StaticAssert::invalid_vector_from_vector_subtraction
    operator-=(const NormalizedVector<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_vector_from_vector_subtraction{};
    }
#endif
};
} // namespace Space::implementation
