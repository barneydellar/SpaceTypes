#pragma once

namespace Space::implementation {

template <typename ThisSpace, typename UnderlyingData> class NormalizedXYVector final : public Base<ThisSpace, UnderlyingData> {

    friend class NormalizedVector<ThisSpace, UnderlyingData>;
    friend class Point<ThisSpace, UnderlyingData>;
    friend class Vector<ThisSpace, UnderlyingData>;
    friend class XYPoint<ThisSpace, UnderlyingData>;
    friend class XYVector<ThisSpace, UnderlyingData>;

  public:
    NormalizedXYVector() noexcept {
        auto iter = implementation::begin(_base::underlyingData);
        *iter++ = 1;
        *iter++ = 0;
        *iter = 0;
    }
    explicit NormalizedXYVector(const UnderlyingData &v) noexcept(false) {
        auto iter = implementation::begin(_base::underlyingData);
        auto in = implementation::cbegin(v);
        *iter++ = *in++;
        *iter++ = *in++;
        *iter = 0;
        Normalize();
    }
    NormalizedXYVector(const double x, const double y) noexcept(false) {
        auto iter = implementation::begin(_base::underlyingData);
        *iter++ = x;
        *iter++ = y;
        *iter = 0;
        Normalize();
    }

    [[nodiscard]] operator Vector<ThisSpace, UnderlyingData>() const noexcept {
        return Vector<ThisSpace, UnderlyingData>(X(), Y(), 0);
    }

    [[nodiscard]] operator XYVector<ThisSpace, UnderlyingData>() const noexcept {
        return XYVector<ThisSpace, UnderlyingData>(X(), Y());
    }

    [[nodiscard]] operator NormalizedVector<ThisSpace, UnderlyingData>() const noexcept {
        return NormalizedVector<ThisSpace, UnderlyingData>(X(), Y(), 0);
    }

    [[nodiscard]] double X() const noexcept { return *(cbegin() + 0); }
    [[nodiscard]] double Y() const noexcept { return *(cbegin() + 1); }

    [[nodiscard]] const double *cbegin() const noexcept { return reinterpret_cast<const double *>(&(_base::underlyingData)); }
    [[nodiscard]] const double *cend() const noexcept { return reinterpret_cast<const double *>(&(_base::underlyingData)) + 2; }

    double operator[](const unsigned int i) const {
        if (i > 1) {
            throw std::invalid_argument("Index is out of range");
        }
        return *(cbegin() + i);
    }

    template <int I> requires ValidFor2dAt<I>
    [[nodiscard]] double at() const {
        return operator[](I);
    }

    [[nodiscard]] bool operator==(const Vector<ThisSpace, UnderlyingData> &other) const noexcept {
        return std::equal(cbegin(), cend(), implementation::cbegin(other.underlyingData), Equality);
    }
    [[nodiscard]] bool operator==(const NormalizedVector<ThisSpace, UnderlyingData> &other) const noexcept {
        return std::equal(cbegin(), cend(), implementation::cbegin(other.underlyingData), Equality);
    }
    [[nodiscard]] bool operator==(const NormalizedXYVector<ThisSpace, UnderlyingData> &other) const noexcept {
        return std::equal(cbegin(), cend(), implementation::cbegin(other.underlyingData), Equality);
    }
    [[nodiscard]] bool operator==(const XYVector<ThisSpace, UnderlyingData> &other) const noexcept {
        return std::equal(cbegin(), cend(), implementation::cbegin(other.underlyingData), Equality);
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
        return NormalizedVector<ThisSpace, UnderlyingData>(x, y, z);
    }
    [[nodiscard]] auto Cross(const NormalizedXYVector<ThisSpace, UnderlyingData> &other) const noexcept {
        const auto [x, y, z] = Cross_internal(_base::underlyingData, other.underlyingData);
        return NormalizedVector<ThisSpace, UnderlyingData>(x, y, z);
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

    template <typename OtherSpace, typename TransformManager> requires DifferentSpaces<OtherSpace, ThisSpace>
    [[nodiscard]] auto ConvertTo(const TransformManager &transform_manager) const noexcept {
        return Vector<OtherSpace, UnderlyingData>(
            transform_manager.template TransformVector<ThisSpace, OtherSpace>(static_cast<UnderlyingData>(*this))
        );
    }

    friend std::ostream &operator<<(std::ostream &os, const NormalizedXYVector<ThisSpace, UnderlyingData> &item) {
        const auto space = SpaceTypeNameMap<ThisSpace>::name;
        os << space << "::NormalizedXYVector (" << item.X() << ", " << item.Y() << ")";
        return os;
    }
#ifndef IGNORE_SPACE_STATIC_ASSERT
    using _base = Base<ThisSpace, UnderlyingData>;
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

    StaticAssert::invalid_normalized_vector_scale operator*=(const double &) const noexcept {
        return StaticAssert::invalid_normalized_vector_scale{};
    }

    StaticAssert::invalid_normalized_vector_in_place_cross operator*=(const Vector<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_normalized_vector_in_place_cross{};
    }
    StaticAssert::invalid_normalized_vector_in_place_cross
    operator*=(const NormalizedVector<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_normalized_vector_in_place_cross{};
    }
    StaticAssert::invalid_normalized_vector_in_place_cross
    operator*=(const NormalizedXYVector<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_normalized_vector_in_place_cross{};
    }
    StaticAssert::invalid_normalized_vector_in_place_cross
    operator*=(const XYVector<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_normalized_vector_in_place_cross{};
    }

    StaticAssert::invalid_normalized_vector_addition operator+=(const Vector<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_normalized_vector_addition{};
    }
    StaticAssert::invalid_normalized_vector_addition
    operator+=(const NormalizedVector<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_normalized_vector_addition{};
    }
    StaticAssert::invalid_normalized_vector_addition
    operator+=(const NormalizedXYVector<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_normalized_vector_addition{};
    }
    StaticAssert::invalid_normalized_vector_addition operator+=(const XYVector<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_normalized_vector_addition{};
    }

    StaticAssert::invalid_normalized_vector_subtraction operator-=(const Vector<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_normalized_vector_subtraction{};
    }
    StaticAssert::invalid_normalized_vector_subtraction
    operator-=(const NormalizedVector<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_normalized_vector_subtraction{};
    }
    StaticAssert::invalid_normalized_vector_subtraction
    operator-=(const NormalizedXYVector<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_normalized_vector_subtraction{};
    }
    StaticAssert::invalid_normalized_vector_subtraction operator-=(const XYVector<ThisSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_normalized_vector_subtraction{};
    }
#endif

  private:
    void Normalize() {
        const auto mag = Mag_internal(_base::underlyingData);
        if (std::abs(mag) < 1e-6) {
            throw std::invalid_argument("Zero-sized normal vectors are not allowed");
        }

        std::transform(cbegin(), cend(), begin(_base::underlyingData), [mag](auto v) { return v / mag; });
    }
};
} // namespace Space::implementation
