#pragma once

namespace Space::implementation {

template <typename ThisSpace, typename UnderlyingData>
class Vector final : public Base<ThisSpace, UnderlyingData, BaseType::Vector> {

    using _base = Base<ThisSpace, UnderlyingData, BaseType::Vector>;

  public:
    Vector() noexcept { std::fill(_base::begin(), _base::end(), 0); }
    explicit Vector(const UnderlyingData& v) noexcept {
        std::copy(implementation::CBegin(v), implementation::CEnd(v), _base::begin());
    }
    Vector(const double x, const double y, const double z) noexcept {
        auto iter = _base::begin();
        *iter++ = x;
        *iter++ = y;
        *iter = z;
    }

    template <BaseType BT> requires(IsVector(BT))
    [[nodiscard]] bool operator==(const Base<ThisSpace, UnderlyingData, BT>& other) const noexcept {
        return std::equal(_base::cbegin(), _base::cend(), implementation::CBegin(UnderlyingDataFrom(other)), Equality);
    }

    template <BaseType BT> requires(IsVector(BT))
    [[nodiscard]] bool operator!=(const Base<ThisSpace, UnderlyingData, BT>& other) const noexcept {
        return !(operator==(other));
    }

    template <BaseType BT> requires(IsVector(BT))
    auto operator-=(const Base<ThisSpace, UnderlyingData, BT>& rhs) noexcept {
        Sub(_base::underlyingData, UnderlyingDataFrom(rhs));
        return *this;
    }

    template <BaseType BT> requires(IsVector(BT))
    [[nodiscard]] auto operator-(const Base<ThisSpace, UnderlyingData, BT>& rhs) const noexcept {
        Vector<ThisSpace, UnderlyingData> v(_base::X(), _base::Y(), _base::Z());
        Sub(UnderlyingDataFrom(v), UnderlyingDataFrom(rhs));
        return v;
    }

    template <BaseType BT> requires(IsVector(BT))
    auto operator+=(const Base<ThisSpace, UnderlyingData, BT>& rhs) noexcept {
        Add(_base::underlyingData, UnderlyingDataFrom(rhs));
        return *this;
    }

    template <BaseType BT> requires(IsVector(BT))
    [[nodiscard]] auto operator+(const Base<ThisSpace, UnderlyingData, BT>& rhs) const noexcept {
        Vector<ThisSpace, UnderlyingData> v(_base::X(), _base::Y(), _base::Z());
        Add(UnderlyingDataFrom(v), UnderlyingDataFrom(rhs));
        return v;
    }

    auto operator*=(const double& d) noexcept {
        Scale(_base::underlyingData, d);
        return *this;
    }

    template <BaseType BT> requires(IsVector(BT))
    auto operator*=(const Base<ThisSpace, UnderlyingData, BT>& rhs) noexcept {
        *this = this->Cross(rhs);
        return *this;
    }

    [[nodiscard]] auto operator*(const double& d) const noexcept {
        Vector<ThisSpace, UnderlyingData> v(_base::X(), _base::Y(), _base::Z());
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

    [[nodiscard]] auto ToXY() const requires ThisSpace::supportsXY
    {
        return XYVector<ThisSpace, UnderlyingData>(_base::X(), _base::Y());
    }

    [[nodiscard]] auto Norm() const { return NormalizedVector<ThisSpace, UnderlyingData>(_base::X(), _base::Y(), _base::Z()); }

    template <DifferentSpaceTo<ThisSpace> OtherSpace, typename TransformManager>
    [[nodiscard]] auto ConvertTo(const TransformManager& transform_manager) const noexcept {
        return Vector<OtherSpace, UnderlyingData>(
            transform_manager.template TransformVector<ThisSpace, OtherSpace>(static_cast<UnderlyingData>(*this))
        );
    }

    [[nodiscard]] auto Mag() const noexcept { return typename ThisSpace::Unit{Mag_double()}; }

    [[nodiscard]] double Mag_double() const noexcept { return Mag_internal(_base::underlyingData); }

    friend std::ostream& operator<<(std::ostream& os, const Vector<ThisSpace, UnderlyingData>& item) {
        const auto space = SpaceTypeNameMap<ThisSpace>::name;
        os << space << "::Vector (" << item.X() << ", " << item.Y() << ", " << item.Z() << ")";
        return os;
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

    [[nodiscard]] StaticAssert::XYVector_not_supported ToXY() const noexcept requires ThisSpace::doesNotSupportXY
    {
        return StaticAssert::XYVector_not_supported{};
    }
#endif
};
} // namespace Space::implementation
