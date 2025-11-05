#pragma once

namespace Space::implementation {

template <typename ThisSpace, typename UnderlyingData>
class XYPoint final : public Base<ThisSpace, UnderlyingData, BaseType::XYPoint> {
    using _base = Base<ThisSpace, UnderlyingData, BaseType::XYPoint>;

  public:
    XYPoint() noexcept { std::fill(_base::begin(), _base::end(), 0); }
    explicit XYPoint(const UnderlyingData& v) noexcept {
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

    [[nodiscard]] operator Point<ThisSpace, UnderlyingData>() const noexcept {
        return Point<ThisSpace, UnderlyingData>(_base::X(), _base::Y(), 0);
    }

    template <BaseType BT> requires(IsPoint(BT))
    [[nodiscard]] bool operator==(const Base<ThisSpace, UnderlyingData, BT>& other) const noexcept {
        return std::equal(_base::cbegin(), _base::cend(), implementation::CBegin(UnderlyingDataFrom(other)), Equality);
    }

    template <BaseType BT> requires(IsPoint(BT))
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
        Point<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Sub(UnderlyingDataFrom(v), UnderlyingDataFrom(rhs));
        return v;
    }
    template <BaseType BT> requires(IsVector(BT) && IsXY(BT))
    [[nodiscard]] auto operator-(const Base<ThisSpace, UnderlyingData, BT>& rhs) const noexcept {
        XYPoint<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Sub(UnderlyingDataFrom(v), UnderlyingDataFrom(rhs));
        return v;
    }

    [[nodiscard]] auto operator-(const XYPoint<ThisSpace, UnderlyingData>& rhs) const noexcept {
        XYVector<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Sub(UnderlyingDataFrom(v), rhs._base::underlyingData);
        return v;
    }
    [[nodiscard]] auto operator-(const Point<ThisSpace, UnderlyingData>& rhs) const noexcept {
        Vector<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
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
        Point<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Add(UnderlyingDataFrom(v), UnderlyingDataFrom(rhs));
        return v;
    }
    template <BaseType BT> requires(IsVector(BT) && IsXY(BT))
    [[nodiscard]] auto operator+(const Base<ThisSpace, UnderlyingData, BT>& rhs) const noexcept {
        XYPoint<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Add(UnderlyingDataFrom(v), UnderlyingDataFrom(rhs));
        return v;
    }

    template <DifferentSpaceTo<ThisSpace> OtherSpace, typename TransformManager>
    [[nodiscard]] auto ConvertTo(const TransformManager& transform_manager) const {
        return Point<OtherSpace, UnderlyingData>(
            transform_manager.template TransformPoint<ThisSpace, OtherSpace>(static_cast<UnderlyingData>(*this))
        );
    }

    friend auto& operator<<(std::ostream& os, const XYPoint<ThisSpace, UnderlyingData>& p) {
        const auto space = SpaceTypeNameMap<ThisSpace>::name;
        return os << std::format("{}::XYPoint ({}, {})", space, p.X(), p.Y());
    }

#ifndef IGNORE_SPACE_STATIC_ASSERT

    using _base::operator==;
    using _base::operator!=;
    using _base::operator+=;
    using _base::operator+;
    using _base::operator-=;
    using _base::operator-;
    using _base::ConvertTo;

    template <BaseType BT> requires(IsVector(BT))
    StaticAssert::invalid_point_vector_equality operator==(const Base<ThisSpace, UnderlyingData, BT>&) const noexcept {
        return StaticAssert::invalid_point_vector_equality{};
    }

    template <BaseType BT> requires(IsVector(BT))
    StaticAssert::invalid_point_vector_equality operator!=(const Base<ThisSpace, UnderlyingData, BT>&) const noexcept {
        return StaticAssert::invalid_point_vector_equality{};
    }

    template <BaseType BT> requires(IsPoint(BT))
    StaticAssert::invalid_point_to_point_addition operator+=(const Base<ThisSpace, UnderlyingData, BT>&) const noexcept {
        return StaticAssert::invalid_point_to_point_addition{};
    }

    template <BaseType BT> requires(IsPoint(BT))
    StaticAssert::invalid_point_to_point_addition operator+(const Base<ThisSpace, UnderlyingData, BT>&) const {
        return StaticAssert::invalid_point_to_point_addition{};
    }

    template <BaseType BT> requires(IsVector(BT) && Is3D(BT))
    StaticAssert::invalid_vector3_to_xy_point_addition operator+=(const Base<ThisSpace, UnderlyingData, BT>&) noexcept {
        return StaticAssert::invalid_vector3_to_xy_point_addition{};
    }

    template <BaseType BT> requires(IsPoint(BT))
    StaticAssert::invalid_point_from_point_subtraction operator-=(const Base<ThisSpace, UnderlyingData, BT>&) const noexcept {
        return StaticAssert::invalid_point_from_point_subtraction{};
    }

    template <BaseType BT> requires(IsVector(BT) && Is3D(BT))
    StaticAssert::invalid_vector3_from_xy_point_subtraction operator-=(const Base<ThisSpace, UnderlyingData, BT>&) noexcept {
        return StaticAssert::invalid_vector3_from_xy_point_subtraction{};
    }
#endif
    // Hide functions from intellisense
    void Dot() = delete;
    void Cross() = delete;
    void operator*() = delete;
    void operator*=(double) = delete;
};
} // namespace Space::implementation
