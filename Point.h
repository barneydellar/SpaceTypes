#pragma once

namespace Space::implementation {

template <typename ThisSpace, typename UnderlyingData> class Point final : public PointLike<ThisSpace, UnderlyingData> {
    friend class NormalizedVector<ThisSpace, UnderlyingData>;
    friend class NormalizedXYVector<ThisSpace, UnderlyingData>;
    friend class Vector<ThisSpace, UnderlyingData>;
    friend class XYPoint<ThisSpace, UnderlyingData>;
    friend class XYVector<ThisSpace, UnderlyingData>;
    using _base = Base<ThisSpace, UnderlyingData>;

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

    template <int I>
    [[nodiscard]] bool operator==(const PointLike<ThisSpace, UnderlyingData, I>& other) const noexcept {
        return std::equal(_base::cbegin(), _base::cend(), implementation::CBegin(other.underlyingData), Equality);
    }

    template <int I>
    [[nodiscard]] bool operator!=(const PointLike<ThisSpace, UnderlyingData, I>& other) const noexcept { return !(operator==(other)); }

    template <int I, bool B>
    auto operator-=(const VectorLike<ThisSpace, UnderlyingData, I, B>& rhs) noexcept {
        Sub(_base::underlyingData, rhs.underlyingData);
        return *this;
    }

    template <int I>
    [[nodiscard]] auto operator-(const PointLike<ThisSpace, UnderlyingData, I>& rhs) const noexcept {
        Vector<ThisSpace, UnderlyingData> v(_base::X(), _base::Y(), _base::Z());
        Sub(v.underlyingData, rhs.underlyingData);
        return v;
    }

    template <int I, bool B>
    [[nodiscard]] auto operator-(const VectorLike<ThisSpace, UnderlyingData, I, B>& rhs) const noexcept {
        Point<ThisSpace, UnderlyingData> v(_base::X(), _base::Y(), _base::Z());
        Sub(v.underlyingData, rhs.underlyingData);
        return v;
    }

    template <int I, bool B>
    auto operator+=(const VectorLike<ThisSpace, UnderlyingData, I, B>& rhs) noexcept {
        Add(_base::underlyingData, rhs.underlyingData);
        return *this;
    }

    template <int I, bool B>
    [[nodiscard]] auto operator+(const VectorLike<ThisSpace, UnderlyingData, I, B>& rhs) const noexcept {
        Point<ThisSpace, UnderlyingData> p(_base::X(), _base::Y(), _base::Z());
        Add(p.underlyingData, rhs.underlyingData);
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

    using _base::operator+=;
    using _base::operator-;
    using _base::operator+;
    using _base::operator-=;
    using _base::ConvertTo;

    template <typename OtherSpace, int I> requires DifferentSpaces<OtherSpace, ThisSpace>
    StaticAssert::invalid_space operator!=(const PointLike<OtherSpace, UnderlyingData, I>&) const noexcept {
        return StaticAssert::invalid_space{};
    }

    template <typename OtherSpace, int I> requires DifferentSpaces<OtherSpace, ThisSpace>
    StaticAssert::invalid_space operator==(const PointLike<OtherSpace, UnderlyingData, I>&) const noexcept {
        return StaticAssert::invalid_space{};
    }

    template <int I, bool B>
    StaticAssert::invalid_point_vector_equality operator==(const VectorLike<ThisSpace, UnderlyingData, I, B>&) const noexcept {
        return StaticAssert::invalid_point_vector_equality{};
    }

    template <int I, bool B>
    StaticAssert::invalid_point_vector_equality operator!=(const VectorLike<ThisSpace, UnderlyingData, I, B>&) const noexcept {
        return StaticAssert::invalid_point_vector_equality{};
    }

    template <int I>
    StaticAssert::invalid_point_to_point_addition operator+=(const PointLike<ThisSpace, UnderlyingData, I>&) const noexcept {
        return StaticAssert::invalid_point_to_point_addition{};
    }

    template <int I>
    StaticAssert::invalid_point_to_point_addition operator+(const PointLike<ThisSpace, UnderlyingData, I>&) const noexcept {
        return StaticAssert::invalid_point_to_point_addition{};
    }

    template <int I>
    StaticAssert::invalid_point_from_point_subtraction operator-=(const PointLike<ThisSpace, UnderlyingData, I>&) const noexcept {
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
