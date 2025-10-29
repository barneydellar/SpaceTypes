#pragma once

namespace Space::implementation {

template <typename ThisSpace, typename UnderlyingData> class Point final : public Base<ThisSpace, UnderlyingData> {
    friend class NormalizedVector<ThisSpace, UnderlyingData>;
    friend class NormalizedXYVector<ThisSpace, UnderlyingData>;
    friend class Vector<ThisSpace, UnderlyingData>;
    friend class XYPoint<ThisSpace, UnderlyingData>;
    friend class XYVector<ThisSpace, UnderlyingData>;
    using _base = Base<ThisSpace, UnderlyingData>;

  public:
    Point() noexcept { std::fill(_base::begin(), _base::end(), 0); }
    explicit Point(const UnderlyingData &v) noexcept {
        std::copy(implementation::CBegin(v), implementation::CEnd(v), _base::begin());
    }
    Point(const double x, const double y, const double z) noexcept {
        auto iter = _base::begin();
        *iter++ = x;
        *iter++ = y;
        *iter = z;
    }

    [[nodiscard]] bool operator==(const Point<ThisSpace, UnderlyingData> &other) const noexcept {
        return std::equal(_base::cbegin(), _base::cend(), implementation::CBegin(other.underlyingData), Equality);
    }
    [[nodiscard]] bool operator==(const XYPoint<ThisSpace, UnderlyingData> &other) const noexcept {
        return std::equal(_base::cbegin(), _base::cend(), implementation::CBegin(other.underlyingData), Equality);
    }

    [[nodiscard]] bool operator!=(const Point<ThisSpace, UnderlyingData> &other) const noexcept { return !(operator==(other)); }
    [[nodiscard]] bool operator!=(const XYPoint<ThisSpace, UnderlyingData> &other) const noexcept { return !(operator==(other)); }

    auto operator-=(const Vector<ThisSpace, UnderlyingData> &rhs) noexcept {
        Sub(_base::underlyingData, rhs.underlyingData);
        return *this;
    }
    auto operator-=(const NormalizedVector<ThisSpace, UnderlyingData> &rhs) noexcept {
        Sub(_base::underlyingData, rhs.underlyingData);
        return *this;
    }
    auto operator-=(const NormalizedXYVector<ThisSpace, UnderlyingData> &rhs) noexcept {
        Sub(_base::underlyingData, rhs.underlyingData);
        return *this;
    }
    auto operator-=(const XYVector<ThisSpace, UnderlyingData> &rhs) noexcept {
        Sub(_base::underlyingData, rhs.underlyingData);
        return *this;
    }

    [[nodiscard]] auto operator-(const Point<ThisSpace, UnderlyingData> &rhs) const noexcept {
        Vector<ThisSpace, UnderlyingData> v(_base::X(), _base::Y(), _base::Z());
        Sub(v.underlyingData, rhs.underlyingData);
        return v;
    }
    [[nodiscard]] auto operator-(const XYPoint<ThisSpace, UnderlyingData> &rhs) const noexcept {
        Vector<ThisSpace, UnderlyingData> v(_base::X(), _base::Y(), _base::Z());
        Sub(v.underlyingData, rhs.underlyingData);
        return v;
    }
    [[nodiscard]] auto operator-(const Vector<ThisSpace, UnderlyingData> &rhs) const noexcept {
        Point<ThisSpace, UnderlyingData> v(_base::X(), _base::Y(), _base::Z());
        Sub(v.underlyingData, rhs.underlyingData);
        return v;
    }
    [[nodiscard]] auto operator-(const NormalizedVector<ThisSpace, UnderlyingData> &rhs) const noexcept {
        Point<ThisSpace, UnderlyingData> v(_base::X(), _base::Y(), _base::Z());
        Sub(v.underlyingData, rhs.underlyingData);
        return v;
    }
    [[nodiscard]] auto operator-(const NormalizedXYVector<ThisSpace, UnderlyingData> &rhs) const noexcept {
        Point<ThisSpace, UnderlyingData> v(_base::X(), _base::Y(), _base::Z());
        Sub(v.underlyingData, rhs.underlyingData);
        return v;
    }
    [[nodiscard]] auto operator-(const XYVector<ThisSpace, UnderlyingData> &rhs) const noexcept {
        Point<ThisSpace, UnderlyingData> v(_base::X(), _base::Y(), _base::Z());
        Sub(v.underlyingData, rhs.underlyingData);
        return v;
    }

    auto operator+=(const Vector<ThisSpace, UnderlyingData> &rhs) noexcept {
        Add(_base::underlyingData, rhs.underlyingData);
        return *this;
    }
    auto operator+=(const NormalizedVector<ThisSpace, UnderlyingData> &rhs) noexcept {
        Add(_base::underlyingData, rhs.underlyingData);
        return *this;
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
        Point<ThisSpace, UnderlyingData> p(_base::X(), _base::Y(), _base::Z());
        Add(p.underlyingData, rhs.underlyingData);
        return p;
    }
    [[nodiscard]] auto operator+(const NormalizedVector<ThisSpace, UnderlyingData> &rhs) const noexcept {
        Point<ThisSpace, UnderlyingData> p(_base::X(), _base::Y(), _base::Z());
        Add(p.underlyingData, rhs.underlyingData);
        return p;
    }
    [[nodiscard]] auto operator+(const NormalizedXYVector<ThisSpace, UnderlyingData> &rhs) const noexcept {
        Point<ThisSpace, UnderlyingData> p(_base::X(), _base::Y(), _base::Z());
        Add(p.underlyingData, rhs.underlyingData);
        return p;
    }
    [[nodiscard]] auto operator+(const XYVector<ThisSpace, UnderlyingData> &rhs) const noexcept {
        Point<ThisSpace, UnderlyingData> p(_base::X(), _base::Y(), _base::Z());
        Add(p.underlyingData, rhs.underlyingData);
        return p;
    }

    template <typename OtherSpace, typename TransformManager> requires DifferentSpaces<OtherSpace, ThisSpace>
    [[nodiscard]] auto ConvertTo(const TransformManager &transform_manager) const {
        return Point<OtherSpace, UnderlyingData>(
            transform_manager.template TransformPoint<ThisSpace, OtherSpace>(static_cast<UnderlyingData>(*this))
        );
    }

    [[nodiscard]] auto ToXY() const requires ThisSpace::supportsXY
    {
        return XYPoint<ThisSpace, UnderlyingData>(_base::X(), _base::Y());
    }

    friend std::ostream &operator<<(std::ostream &os, const Point<ThisSpace, UnderlyingData> &item) {
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

    StaticAssert::invalid_point_to_point_addition operator+(const Point<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_point_to_point_addition{};
    }
    StaticAssert::invalid_point_to_point_addition operator+(const XYPoint<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_point_to_point_addition{};
    }

    StaticAssert::invalid_point_from_point_subtraction operator-=(const Point<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_point_from_point_subtraction{};
    }
    StaticAssert::invalid_point_from_point_subtraction operator-=(const XYPoint<ThisSpace, UnderlyingData> &) const noexcept {
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
