#pragma once

namespace Space::implementation {

template <typename ThisSpace, typename UnderlyingData> class XYVector final : public VectorLike<ThisSpace, UnderlyingData, 2> {

    friend class NormalizedVector<ThisSpace, UnderlyingData>;
    friend class NormalizedXYVector<ThisSpace, UnderlyingData>;
    friend class Point<ThisSpace, UnderlyingData>;
    friend class Vector<ThisSpace, UnderlyingData>;
    friend class XYPoint<ThisSpace, UnderlyingData>;
    using _base = Base<ThisSpace, UnderlyingData, 2>;

  public:
    XYVector() noexcept { std::fill(_base::begin(), _base::end(), 0); }
    explicit XYVector(const UnderlyingData& v) noexcept {
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
        return Vector<ThisSpace, UnderlyingData>(_base::X(), _base::Y(), 0);
    }

    template <int I, bool B>
    [[nodiscard]] bool operator==(const VectorLike<ThisSpace, UnderlyingData, I, B>& other) const noexcept {
        return std::equal(_base::cbegin(), _base::cend(), implementation::CBegin(other.underlyingData), Equality);
    }

    template <int I, bool B>
    [[nodiscard]] bool operator!=(const VectorLike<ThisSpace, UnderlyingData, I, B>& other) const noexcept {
        return !(operator==(other));
    }

    auto operator-=(const NormalizedXYVector<ThisSpace, UnderlyingData>& rhs) noexcept {
        Sub(_base::underlyingData, rhs.underlyingData);
        return *this;
    }
    auto operator-=(const XYVector<ThisSpace, UnderlyingData>& rhs) noexcept {
        Sub(_base::underlyingData, rhs.underlyingData);
        return *this;
    }

    [[nodiscard]] auto operator-(const Vector<ThisSpace, UnderlyingData>& rhs) const noexcept {
        Vector<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Sub(v.underlyingData, rhs.underlyingData);
        return v;
    }
    [[nodiscard]] auto operator-(const NormalizedVector<ThisSpace, UnderlyingData>& rhs) const noexcept {
        Vector<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Sub(v.underlyingData, rhs.underlyingData);
        return v;
    }
    [[nodiscard]] auto operator-(const NormalizedXYVector<ThisSpace, UnderlyingData>& rhs) const noexcept {
        XYVector<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Sub(v.underlyingData, rhs.underlyingData);
        return v;
    }
    [[nodiscard]] auto operator-(const XYVector<ThisSpace, UnderlyingData>& rhs) const noexcept {
        XYVector<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Sub(v.underlyingData, rhs.underlyingData);
        return v;
    }

    auto operator+=(const NormalizedXYVector<ThisSpace, UnderlyingData>& rhs) noexcept {
        Add(_base::underlyingData, rhs.underlyingData);
        return *this;
    }
    auto operator+=(const XYVector<ThisSpace, UnderlyingData>& rhs) noexcept {
        Add(_base::underlyingData, rhs.underlyingData);
        return *this;
    }

    [[nodiscard]] auto operator+(const Vector<ThisSpace, UnderlyingData>& rhs) const noexcept {
        Vector<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Add(v.underlyingData, rhs.underlyingData);
        return v;
    }
    [[nodiscard]] auto operator+(const NormalizedVector<ThisSpace, UnderlyingData>& rhs) const noexcept {
        Vector<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Add(v.underlyingData, rhs.underlyingData);
        return v;
    }
    [[nodiscard]] auto operator+(const NormalizedXYVector<ThisSpace, UnderlyingData>& rhs) const noexcept {
        XYVector<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Add(v.underlyingData, rhs.underlyingData);
        return v;
    }
    [[nodiscard]] auto operator+(const XYVector<ThisSpace, UnderlyingData>& rhs) const noexcept {
        XYVector<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Add(v.underlyingData, rhs.underlyingData);
        return v;
    }

    auto operator*=(const double& d) noexcept {
        Scale(_base::underlyingData, d);
        return *this;
    }

    [[nodiscard]] auto operator*(const double& d) const noexcept {
        XYVector<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Scale(v.underlyingData, d);
        return v;
    }

    [[nodiscard]] auto operator*(const Vector<ThisSpace, UnderlyingData>& rhs) const noexcept { return this->Cross(rhs); }
    [[nodiscard]] auto operator*(const NormalizedXYVector<ThisSpace, UnderlyingData>& rhs) const noexcept {
        return this->Cross(rhs);
    }
    [[nodiscard]] auto operator*(const NormalizedVector<ThisSpace, UnderlyingData>& rhs) const noexcept {
        return this->Cross(rhs);
    }
    [[nodiscard]] auto operator*(const XYVector<ThisSpace, UnderlyingData>& rhs) const noexcept { return this->Cross(rhs); }

    [[nodiscard]] auto Cross(const Vector<ThisSpace, UnderlyingData>& other) const noexcept {
        const auto [x, y, z] = Cross_internal(_base::underlyingData, other.underlyingData);
        return Vector<ThisSpace, UnderlyingData>(x, y, z);
    }
    [[nodiscard]] auto Cross(const NormalizedVector<ThisSpace, UnderlyingData>& other) const noexcept {
        const auto [x, y, z] = Cross_internal(_base::underlyingData, other.underlyingData);
        return Vector<ThisSpace, UnderlyingData>(x, y, z);
    }
    [[nodiscard]] auto Cross(const NormalizedXYVector<ThisSpace, UnderlyingData>& other) const noexcept {
        const auto [x, y, z] = Cross_internal(_base::underlyingData, other.underlyingData);
        return Vector<ThisSpace, UnderlyingData>(x, y, z);
    }
    [[nodiscard]] auto Cross(const XYVector<ThisSpace, UnderlyingData>& other) const noexcept {
        const auto [x, y, z] = Cross_internal(_base::underlyingData, other.underlyingData);
        return Vector<ThisSpace, UnderlyingData>(x, y, z);
    }

    [[nodiscard]] double Dot(const Vector<ThisSpace, UnderlyingData>& other) const noexcept {
        return implementation::Dot(_base::underlyingData, other.underlyingData);
    }
    [[nodiscard]] double Dot(const NormalizedVector<ThisSpace, UnderlyingData>& other) const noexcept {
        return implementation::Dot(_base::underlyingData, other.underlyingData);
    }
    [[nodiscard]] double Dot(const NormalizedXYVector<ThisSpace, UnderlyingData>& other) const noexcept {
        return implementation::Dot(_base::underlyingData, other.underlyingData);
    }
    [[nodiscard]] double Dot(const XYVector<ThisSpace, UnderlyingData>& other) const noexcept {
        return implementation::Dot(_base::underlyingData, other.underlyingData);
    }

    [[nodiscard]] auto Norm() const { return NormalizedXYVector<ThisSpace, UnderlyingData>(_base::X(), _base::Y()); }

    template <typename OtherSpace, typename TransformManager> requires DifferentSpaces<OtherSpace, ThisSpace>
    [[nodiscard]] auto ConvertTo(const TransformManager& transform_manager) const noexcept {
        return Vector<OtherSpace, UnderlyingData>(
            transform_manager.template TransformVector<ThisSpace, OtherSpace>(static_cast<UnderlyingData>(*this))
        );
    }

    [[nodiscard]] auto Mag() const noexcept { return typename ThisSpace::Unit{Mag_double()}; }

    [[nodiscard]] double Mag_double() const noexcept { return Mag_internal(_base::underlyingData); }

    friend std::ostream& operator<<(std::ostream& os, const XYVector<ThisSpace, UnderlyingData>& item) {
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

    template <typename OtherSpace, int I, bool B> requires DifferentSpaces<OtherSpace, ThisSpace>
    StaticAssert::invalid_space operator!=(const VectorLike<OtherSpace, UnderlyingData, I, B>&) const noexcept {
        return StaticAssert::invalid_space{};
    }

    template <typename OtherSpace, int I, bool B> requires DifferentSpaces<OtherSpace, ThisSpace>
    StaticAssert::invalid_space operator==(const VectorLike<OtherSpace, UnderlyingData, I, B>&) const noexcept {
        return StaticAssert::invalid_space{};
    }

    template <int I>
    StaticAssert::invalid_point_vector_equality operator==(const PointLike<ThisSpace, UnderlyingData, I>&) const noexcept {
        return StaticAssert::invalid_point_vector_equality{};
    }
    template <int I>
    StaticAssert::invalid_point_vector_equality operator!=(const PointLike<ThisSpace, UnderlyingData, I>&) const noexcept {
        return StaticAssert::invalid_point_vector_equality{};
    }

    // Todo tests for xypoint
    template <int I>
    StaticAssert::invalid_point_from_vector_subtraction operator-(const PointLike<ThisSpace, UnderlyingData, I>&) const noexcept {
        return StaticAssert::invalid_point_from_vector_subtraction{};
    }

    // Todo tests for xypoint
    template <int I>
    StaticAssert::invalid_point_to_vector_addition operator+(const PointLike<ThisSpace, UnderlyingData, I>&) const noexcept {
        return StaticAssert::invalid_point_to_vector_addition{};
    }

    StaticAssert::invalid_XYVector_in_place_cross operator*=(const Vector<ThisSpace, UnderlyingData>&) const noexcept {
        return StaticAssert::invalid_XYVector_in_place_cross{};
    }
    StaticAssert::invalid_XYVector_in_place_cross operator*=(const NormalizedVector<ThisSpace, UnderlyingData>&) const noexcept {
        return StaticAssert::invalid_XYVector_in_place_cross{};
    }
    StaticAssert::invalid_XYVector_in_place_cross
    operator*=(const NormalizedXYVector<ThisSpace, UnderlyingData>&) const noexcept {
        return StaticAssert::invalid_XYVector_in_place_cross{};
    }
    StaticAssert::invalid_XYVector_in_place_cross operator*=(const XYVector<ThisSpace, UnderlyingData>&) const noexcept {
        return StaticAssert::invalid_XYVector_in_place_cross{};
    }

    StaticAssert::invalid_vector_to_vector_addition operator+=(const Vector<ThisSpace, UnderlyingData>&) const noexcept {
        return StaticAssert::invalid_vector_to_vector_addition{};
    }
    StaticAssert::invalid_vector_to_vector_addition
    operator+=(const NormalizedVector<ThisSpace, UnderlyingData>&) const noexcept {
        return StaticAssert::invalid_vector_to_vector_addition{};
    }

    StaticAssert::invalid_vector_from_vector_subtraction operator-=(const Vector<ThisSpace, UnderlyingData>&) const noexcept {
        return StaticAssert::invalid_vector_from_vector_subtraction{};
    }
    StaticAssert::invalid_vector_from_vector_subtraction
    operator-=(const NormalizedVector<ThisSpace, UnderlyingData>&) const noexcept {
        return StaticAssert::invalid_vector_from_vector_subtraction{};
    }
#endif
};
} // namespace Space::implementation
