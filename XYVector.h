#pragma once

namespace Space::implementation {

template <typename ThisSpace, typename UnderlyingData>
class XYVector final : public Base<ThisSpace, UnderlyingData, BaseType::XYVector> {

    using _base = Base<ThisSpace, UnderlyingData, BaseType::XYVector>;

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

    template <BaseType BT> requires(IsVector(BT))
    [[nodiscard]] bool operator==(const Base<ThisSpace, UnderlyingData, BT>& other) const noexcept {
        return std::equal(_base::cbegin(), _base::cend(), implementation::CBegin(UnderlyingDataFrom(other)), Equality);
    }

    template <BaseType BT> requires(IsVector(BT))
    [[nodiscard]] bool operator!=(const Base<ThisSpace, UnderlyingData, BT>& other) const noexcept {
        return !(operator==(other));
    }

    template <BaseType BT> requires(IsVector(BT) && IsXY(BT))
    auto operator-=(const Base<ThisSpace, UnderlyingData, BT>& rhs) noexcept {
        Sub(_base::underlyingData, UnderlyingDataFrom(rhs));
        return *this;
    }

    template <BaseType BT> requires(IsVector(BT) && Is3D(BT))
    [[nodiscard]] auto operator-(const Base<ThisSpace, UnderlyingData, BT>& rhs) const noexcept {
        Vector<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Sub(UnderlyingDataFrom(v), UnderlyingDataFrom(rhs));
        return v;
    }
    template <BaseType BT> requires(IsVector(BT) && IsXY(BT))
    [[nodiscard]] auto operator-(const Base<ThisSpace, UnderlyingData, BT>& rhs) const noexcept {
        XYVector<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Sub(UnderlyingDataFrom(v), UnderlyingDataFrom(rhs));
        return v;
    }

    template <BaseType BT> requires(IsVector(BT) && IsXY(BT))
    auto operator+=(const Base<ThisSpace, UnderlyingData, BT>& rhs) noexcept {
        Add(_base::underlyingData, UnderlyingDataFrom(rhs));
        return *this;
    }

    template <BaseType BT> requires(IsVector(BT) && Is3D(BT))
    [[nodiscard]] auto operator+(const Base<ThisSpace, UnderlyingData, BT>& rhs) const noexcept {
        Vector<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Add(UnderlyingDataFrom(v), UnderlyingDataFrom(rhs));
        return v;
    }

    template <BaseType BT> requires(IsVector(BT) && IsXY(BT))
    [[nodiscard]] auto operator+(const Base<ThisSpace, UnderlyingData, BT>& rhs) const noexcept {
        XYVector<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Add(UnderlyingDataFrom(v), UnderlyingDataFrom(rhs));
        return v;
    }

    auto operator*=(const double& d) noexcept {
        Scale(_base::underlyingData, d);
        return *this;
    }

    [[nodiscard]] auto operator*(const double& d) const noexcept {
        XYVector<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Scale(UnderlyingDataFrom(v), d);
        return v;
    }

    template <BaseType BT> requires(IsVector(BT))
    [[nodiscard]] auto operator*(const Base<ThisSpace, UnderlyingData, BT>& rhs) const noexcept {
        return this->Cross(rhs);
    }

    template <BaseType BT> requires(IsVector(BT))
    [[nodiscard]] auto Cross(const Base<ThisSpace, UnderlyingData, BT>& other) const noexcept {
        const auto [x, y, z] = Cross_internal(_base::underlyingData, UnderlyingDataFrom(other));
        return Vector<ThisSpace, UnderlyingData>(x, y, z);
    }

    template <BaseType BT> requires(IsVector(BT))
    [[nodiscard]] double Dot(const Base<ThisSpace, UnderlyingData, BT>& other) const noexcept {
        return implementation::Dot(_base::underlyingData, UnderlyingDataFrom(other));
    }

    [[nodiscard]] auto Norm() const { return NormalizedXYVector<ThisSpace, UnderlyingData>(_base::X(), _base::Y()); }

    template <DifferentSpaceTo<ThisSpace> OtherSpace, typename TransformManager>
    [[nodiscard]] auto ConvertTo(const TransformManager& transform_manager) const noexcept {
        return Vector<OtherSpace, UnderlyingData>(
            transform_manager.template TransformVector<ThisSpace, OtherSpace>(static_cast<UnderlyingData>(*this))
        );
    }

    [[nodiscard]] auto Mag() const noexcept { return typename ThisSpace::Unit{Mag_double()}; }

    [[nodiscard]] double Mag_double() const noexcept { return Mag_internal(_base::underlyingData); }

    friend auto& operator<<(std::ostream& os, const XYVector<ThisSpace, UnderlyingData>& v) {
        const auto space = SpaceTypeNameMap<ThisSpace>::name;
        return os << std::format("{}::XYVector ({}, {})", space, v.X(), v.Y());
    }

#ifndef IGNORE_SPACE_STATIC_ASSERT

    using _base::operator==;
    using _base::operator!=;
    using _base::operator-=;
    using _base::operator-;
    using _base::operator+=;
    using _base::operator+;
    using _base::operator*=;
    using _base::operator*;
    using _base::ConvertTo;
    using _base::Cross;
    using _base::Dot;

    template <BaseType BT> requires(IsPoint(BT))
    StaticAssert::invalid_point_vector_equality operator==(const Base<ThisSpace, UnderlyingData, BT>&) const noexcept {
        return StaticAssert::invalid_point_vector_equality{};
    }
    template <BaseType BT> requires(IsPoint(BT))
    StaticAssert::invalid_point_vector_equality operator!=(const Base<ThisSpace, UnderlyingData, BT>&) const noexcept {
        return StaticAssert::invalid_point_vector_equality{};
    }

    template <BaseType BT> requires(IsPoint(BT))
    StaticAssert::invalid_point_from_vector_subtraction operator-(const Base<ThisSpace, UnderlyingData, BT>&) const noexcept {
        return StaticAssert::invalid_point_from_vector_subtraction{};
    }

    template <BaseType BT> requires(IsPoint(BT))
    StaticAssert::invalid_point_to_vector_addition operator+(const Base<ThisSpace, UnderlyingData, BT>&) const noexcept {
        return StaticAssert::invalid_point_to_vector_addition{};
    }

    template <BaseType BT> requires(IsVector(BT) && Is3D(BT))
    StaticAssert::invalid_XYVector_in_place_cross operator*=(const Base<ThisSpace, UnderlyingData, BT>&) const noexcept {
        return StaticAssert::invalid_XYVector_in_place_cross{};
    }

    template <BaseType BT> requires(IsVector(BT) && IsXY(BT))
    StaticAssert::invalid_XYVector_in_place_cross operator*=(const Base<ThisSpace, UnderlyingData, BT>&) const noexcept {
        return StaticAssert::invalid_XYVector_in_place_cross{};
    }

    template <BaseType BT> requires(IsVector(BT) && Is3D(BT))
    StaticAssert::invalid_vector_to_vector_addition operator+=(const Base<ThisSpace, UnderlyingData, BT>&) const noexcept {
        return StaticAssert::invalid_vector_to_vector_addition{};
    }

    template <BaseType BT> requires(IsVector(BT) && Is3D(BT))
    StaticAssert::invalid_vector_from_vector_subtraction operator-=(const Base<ThisSpace, UnderlyingData, BT>&) const noexcept {
        return StaticAssert::invalid_vector_from_vector_subtraction{};
    }
#endif
};
} // namespace Space::implementation
