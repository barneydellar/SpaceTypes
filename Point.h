#pragma once

namespace Space::implementation {

template <typename ThisSpace, typename UnderlyingData>
class Point final : public Base<ThisSpace, UnderlyingData, BaseType::Point> {
    using _base = Base<ThisSpace, UnderlyingData, BaseType::Point>;

  public:
    Point() noexcept { std::fill(_base::begin(), _base::end(), 0); }

    explicit Point(const UnderlyingData& v) noexcept {
        std::copy(implementation::CBegin(v), implementation::CEnd(v), _base::begin());
    }

    Point(const double x, const double y, const double z) noexcept {
        auto iter = _base::begin();
        *iter++ = x;
        *iter++ = y;
        *iter = z;
    }

    template <BaseType BT> requires(IsPoint(BT))
    [[nodiscard]] bool operator==(const Base<ThisSpace, UnderlyingData, BT>& other) const noexcept {
        return std::equal(_base::cbegin(), _base::cend(), implementation::CBegin(static_cast<UnderlyingData>(other)), Equality);
    }

    template <BaseType BT> requires(IsPoint(BT))
    [[nodiscard]] bool operator!=(const Base<ThisSpace, UnderlyingData, BT>& other) const noexcept {
        return !(operator==(other));
    }

    template <BaseType BT> requires(IsVector(BT))
    auto operator-=(const Base<ThisSpace, UnderlyingData, BT>& rhs) noexcept {
        Sub(_base::underlyingData, UnderlyingDataFrom(rhs));
        return *this;
    }

    template <BaseType BT> requires(IsPoint(BT))
    [[nodiscard]] auto operator-(const Base<ThisSpace, UnderlyingData, BT>& rhs) const noexcept {
        Vector<ThisSpace, UnderlyingData> v(_base::X(), _base::Y(), _base::Z());
        Sub(UnderlyingDataFrom(v), UnderlyingDataFrom(rhs));
        return v;
    }

    template <BaseType BT> requires(IsVector(BT))
    [[nodiscard]] auto operator-(const Base<ThisSpace, UnderlyingData, BT>& rhs) const noexcept {
        Point<ThisSpace, UnderlyingData> v(_base::X(), _base::Y(), _base::Z());
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
        Point<ThisSpace, UnderlyingData> p(_base::X(), _base::Y(), _base::Z());
        Add(UnderlyingDataFrom(p), UnderlyingDataFrom(rhs));
        return p;
    }

    template <typename OtherSpace, typename TransformManager> requires DifferentSpaces<OtherSpace, ThisSpace>
    [[nodiscard]] auto ConvertTo(const TransformManager& transform_manager) const {
        return Point<OtherSpace, UnderlyingData>(
            transform_manager.template TransformPoint<ThisSpace, OtherSpace>(static_cast<UnderlyingData>(*this))
        );
    }

    [[nodiscard]] auto ToXY() const requires ThisSpace::supportsXY
    {
        return XYPoint<ThisSpace, UnderlyingData>(_base::X(), _base::Y());
    }

    friend std::ostream& operator<<(std::ostream& os, const Point<ThisSpace, UnderlyingData>& item) {
        const auto space = SpaceTypeNameMap<ThisSpace>::name;
        os << space << "::Point (" << item.X() << ", " << item.Y() << ", " << item.Z() << ")";
        return os;
    }

#ifndef IGNORE_SPACE_STATIC_ASSERT

    using _base::operator==;
    using _base::operator!=;
    using _base::operator+=;
    using _base::operator-;
    using _base::operator+;
    using _base::operator-=;
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
    StaticAssert::invalid_point_to_point_addition operator+(const Base<ThisSpace, UnderlyingData, BT>&) const noexcept {
        return StaticAssert::invalid_point_to_point_addition{};
    }

    template <BaseType BT> requires(IsPoint(BT))
    StaticAssert::invalid_point_from_point_subtraction operator-=(const Base<ThisSpace, UnderlyingData, BT>&) const noexcept {
        return StaticAssert::invalid_point_from_point_subtraction{};
    }

    [[nodiscard]] StaticAssert::XYVector_not_supported ToXY() const noexcept requires ThisSpace::doesNotSupportXY
    {
        return StaticAssert::XYVector_not_supported{};
    }

#endif
    // Hide functions from intellisense
    void Dot() = delete;
    void Cross() = delete;
    void operator*() = delete;
    void operator*=(double) = delete;
};
} // namespace Space::implementation
