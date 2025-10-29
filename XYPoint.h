#pragma once

namespace Space::implementation {

template <typename ThisSpace, typename UnderlyingData> class XYPoint final : public PointLike<ThisSpace, UnderlyingData, 2> {
    friend class NormalizedVector<ThisSpace, UnderlyingData>;
    friend class NormalizedXYVector<ThisSpace, UnderlyingData>;
    friend class Point<ThisSpace, UnderlyingData>;
    friend class Vector<ThisSpace, UnderlyingData>;
    friend class XYVector<ThisSpace, UnderlyingData>;
    using _base = Base<ThisSpace, UnderlyingData, 2>;

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

    template <int I>
    [[nodiscard]] bool operator==(const PointLike<ThisSpace, UnderlyingData, I>& other) const noexcept {
        return std::equal(_base::cbegin(), _base::cend(), implementation::CBegin(other.underlyingData), Equality);
    }

    template <int I>
    [[nodiscard]] bool operator!=(const PointLike<ThisSpace, UnderlyingData, I>& other) const noexcept { return !(operator==(other)); }

    // Todo why only xy vectors here?
    auto operator-=(const XYVector<ThisSpace, UnderlyingData>& rhs) noexcept {
        Sub(_base::underlyingData, rhs.underlyingData);
        return *this;
    }
    auto operator-=(const NormalizedXYVector<ThisSpace, UnderlyingData>& rhs) noexcept {
        Sub(_base::underlyingData, rhs.underlyingData);
        return *this;
    }

    [[nodiscard]] auto operator-(const Vector<ThisSpace, UnderlyingData>& rhs) const noexcept {
        Point<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Sub(v.underlyingData, rhs.underlyingData);
        return v;
    }
    [[nodiscard]] auto operator-(const NormalizedVector<ThisSpace, UnderlyingData>& rhs) const noexcept {
        Point<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Sub(v.underlyingData, rhs.underlyingData);
        return v;
    }
    [[nodiscard]] auto operator-(const NormalizedXYVector<ThisSpace, UnderlyingData>& rhs) const noexcept {
        XYPoint<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Sub(v.underlyingData, rhs.underlyingData);
        return v;
    }
    [[nodiscard]] auto operator-(const XYVector<ThisSpace, UnderlyingData>& rhs) const noexcept {
        XYPoint<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Sub(v.underlyingData, rhs.underlyingData);
        return v;
    }

    [[nodiscard]] auto operator-(const XYPoint<ThisSpace, UnderlyingData>& rhs) const noexcept {
        XYVector<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Sub(v.underlyingData, rhs._base::underlyingData);
        return v;
    }
    [[nodiscard]] auto operator-(const Point<ThisSpace, UnderlyingData>& rhs) const noexcept {
        Vector<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Sub(v.underlyingData, rhs.underlyingData);
        return v;
    }

    auto operator+=(const XYVector<ThisSpace, UnderlyingData>& rhs) noexcept {
        Add(_base::underlyingData, rhs.underlyingData);
        return *this;
    }
    auto operator+=(const NormalizedXYVector<ThisSpace, UnderlyingData>& rhs) noexcept {
        Add(_base::underlyingData, rhs.underlyingData);
        return *this;
    }

    [[nodiscard]] auto operator+(const Vector<ThisSpace, UnderlyingData>& rhs) const noexcept {
        Point<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Add(v.underlyingData, rhs.underlyingData);
        return v;
    }
    [[nodiscard]] auto operator+(const NormalizedVector<ThisSpace, UnderlyingData>& rhs) const noexcept {
        Point<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Add(v.underlyingData, rhs.underlyingData);
        return v;
    }
    [[nodiscard]] auto operator+(const NormalizedXYVector<ThisSpace, UnderlyingData>& rhs) const noexcept {
        XYPoint<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Add(v.underlyingData, rhs.underlyingData);
        return v;
    }
    [[nodiscard]] auto operator+(const XYVector<ThisSpace, UnderlyingData>& rhs) const noexcept {
        XYPoint<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
        Add(v.underlyingData, rhs.underlyingData);
        return v;
    }

    template <typename OtherSpace, typename TransformManager> requires DifferentSpaces<OtherSpace, ThisSpace>
    [[nodiscard]] auto ConvertTo(const TransformManager& transform_manager) const {
        return Point<OtherSpace, UnderlyingData>(
            transform_manager.template TransformPoint<ThisSpace, OtherSpace>(static_cast<UnderlyingData>(*this))
        );
    }

    friend std::ostream& operator<<(std::ostream& os, const XYPoint<ThisSpace, UnderlyingData>& item) {
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

    StaticAssert::invalid_vector3_to_xy_point_addition operator+=(const Vector<ThisSpace, UnderlyingData>&) noexcept {
        return StaticAssert::invalid_vector3_to_xy_point_addition{};
    }
    StaticAssert::invalid_vector3_to_xy_point_addition operator+=(const NormalizedVector<ThisSpace, UnderlyingData>&) noexcept {
        return StaticAssert::invalid_vector3_to_xy_point_addition{};
    }

    template <int I>
    StaticAssert::invalid_point_from_point_subtraction operator-=(const PointLike<ThisSpace, UnderlyingData, I>&) const noexcept {
        return StaticAssert::invalid_point_from_point_subtraction{};
    }

    StaticAssert::invalid_vector3_from_xy_point_subtraction operator-=(const Vector<ThisSpace, UnderlyingData>&) noexcept {
        return StaticAssert::invalid_vector3_from_xy_point_subtraction{};
    }
    StaticAssert::invalid_vector3_from_xy_point_subtraction operator-=(const NormalizedVector<ThisSpace, UnderlyingData>&) noexcept {
        return StaticAssert::invalid_vector3_from_xy_point_subtraction{};
    }

    template <int I>
    StaticAssert::invalid_point_to_point_addition operator+(const PointLike<ThisSpace, UnderlyingData, I>&) const {
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
