#pragma once

namespace Space::implementation {

template <typename ThisSpace, typename UnderlyingData>
class NormalizedXYVector final : public Base<ThisSpace, UnderlyingData, BaseType::NormalizedXYVector> {

    using _base = Base<ThisSpace, UnderlyingData, BaseType::NormalizedXYVector>;

  public:
    NormalizedXYVector() noexcept {
        auto iter = implementation::Begin(_base::underlyingData);
        *iter++ = 1;
        *iter++ = 0;
        *iter = 0;
    }
    explicit NormalizedXYVector(const UnderlyingData& v) noexcept(false) {
        auto iter = implementation::Begin(_base::underlyingData);
        auto in = implementation::CBegin(v);
        *iter++ = *in++;
        *iter++ = *in++;
        *iter = 0;
        Normalize();
    }
    NormalizedXYVector(const double x, const double y) noexcept(false) {
        auto iter = implementation::Begin(_base::underlyingData);
        *iter++ = x;
        *iter++ = y;
        *iter = 0;
        Normalize();
    }

    [[nodiscard]] operator Vector<ThisSpace, UnderlyingData>() const noexcept {
        return Vector<ThisSpace, UnderlyingData>(_base::X(), _base::Y(), 0);
    }

    [[nodiscard]] operator XYVector<ThisSpace, UnderlyingData>() const noexcept {
        return XYVector<ThisSpace, UnderlyingData>(_base::X(), _base::Y());
    }

    [[nodiscard]] operator NormalizedVector<ThisSpace, UnderlyingData>() const noexcept {
        return NormalizedVector<ThisSpace, UnderlyingData>(_base::X(), _base::Y(), 0);
    }

    template <BaseType BT> requires(IsVector(BT))
    [[nodiscard]] bool operator==(const Base<ThisSpace, UnderlyingData, BT>& other) const noexcept {
        return std::equal(_base::cbegin(), _base::cend(), implementation::CBegin(UnderlyingDataFrom(other)), Equality);
    }

    template <BaseType BT> requires(IsVector(BT))
    [[nodiscard]] bool operator!=(const Base<ThisSpace, UnderlyingData, BT>& other) const noexcept {
        return !(operator==(other));
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

    [[nodiscard]] auto operator*(const double& d) const noexcept {
        XYVector<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Scale(UnderlyingDataFrom(v), d);
        return v;
    }

    template <BaseType BT> requires(IsVector(BT))
    [[nodiscard]] auto operator*(const Base<ThisSpace, UnderlyingData, BT>& rhs) const noexcept {
        return this->Cross(rhs);
    }

    template <BaseType BT> requires(IsVector(BT) && IsNotNormalized(BT))
    [[nodiscard]] auto Cross(const Base<ThisSpace, UnderlyingData, BT>& other) const noexcept {
        const auto [x, y, z] = Cross_internal(_base::underlyingData, UnderlyingDataFrom(other));
        return Vector<ThisSpace, UnderlyingData>(x, y, z);
    }
    template <BaseType BT> requires(IsVector(BT) && IsNormalized(BT))
    [[nodiscard]] auto Cross(const Base<ThisSpace, UnderlyingData, BT>& other) const noexcept {
        const auto [x, y, z] = Cross_internal(_base::underlyingData, UnderlyingDataFrom(other));
        return NormalizedVector<ThisSpace, UnderlyingData>(x, y, z);
    }

    template <BaseType BT> requires(IsVector(BT))
    [[nodiscard]] double Dot(const Base<ThisSpace, UnderlyingData, BT>& other) const noexcept {
        return implementation::Dot(_base::underlyingData, UnderlyingDataFrom(other));
    }

    template <DifferentSpaceTo<ThisSpace> OtherSpace, typename TransformManager>
    [[nodiscard]] auto ConvertTo(const TransformManager& transform_manager) const noexcept {
        return Vector<OtherSpace, UnderlyingData>(
            transform_manager.template TransformVector<ThisSpace, OtherSpace>(static_cast<UnderlyingData>(*this))
        );
    }

    friend std::ostream& operator<<(std::ostream& os, const NormalizedXYVector<ThisSpace, UnderlyingData>& v) {
        const auto space = SpaceTypeNameMap<ThisSpace>::name;
        return os << std::format("{}::NormalizedXYVector ({}, {})", space, v.X(), v.Y());
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

    StaticAssert::invalid_normalized_vector_scale operator*=(const double&) const noexcept {
        return StaticAssert::invalid_normalized_vector_scale{};
    }

    template <BaseType BT> requires(IsVector(BT))
    StaticAssert::invalid_normalized_vector_in_place_cross operator*=(const Base<ThisSpace, UnderlyingData, BT>&) const noexcept {
        return StaticAssert::invalid_normalized_vector_in_place_cross{};
    }

    template <BaseType BT> requires(IsVector(BT))
    StaticAssert::invalid_normalized_vector_addition operator+=(const Base<ThisSpace, UnderlyingData, BT>&) const noexcept {
        return StaticAssert::invalid_normalized_vector_addition{};
    }

    template <BaseType BT> requires(IsVector(BT))
    StaticAssert::invalid_normalized_vector_subtraction operator-=(const Base<ThisSpace, UnderlyingData, BT>&) const noexcept {
        return StaticAssert::invalid_normalized_vector_subtraction{};
    }
#endif

  private:
    void Normalize() {
        const auto mag = Mag_internal(_base::underlyingData);
        if (std::abs(mag) < 1e-6) {
            throw std::invalid_argument("Zero-sized normal vectors are not allowed");
        }

        std::transform(_base::cbegin(), _base::cend(), Begin(_base::underlyingData), [mag](auto v) { return v / mag; });
    }
};
} // namespace Space::implementation
