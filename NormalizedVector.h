#pragma once

namespace Space::implementation {

template <typename ThisSpace, typename UnderlyingData>
class NormalizedVector final : public Base<ThisSpace, UnderlyingData, BaseType::NormalizedVector> {
    using _base = Base<ThisSpace, UnderlyingData, BaseType::NormalizedVector>;

  public:
    NormalizedVector() {
        auto iter = implementation::Begin(_base::underlyingData);
        *iter++ = 1;
        *iter++ = 0;
        *iter = 0;
    }
    explicit NormalizedVector(const UnderlyingData& v) noexcept(false) {
        std::copy(implementation::CBegin(v), implementation::CEnd(v), implementation::Begin(_base::underlyingData));
        Normalize();
    }
    NormalizedVector(const double x, const double y, const double z) noexcept(false) {
        auto iter = implementation::Begin(_base::underlyingData);
        *iter++ = x;
        *iter++ = y;
        *iter = z;
        Normalize();
    }

    [[nodiscard]] operator Vector<ThisSpace, UnderlyingData>() const noexcept {
        return Vector<ThisSpace, UnderlyingData>(_base::X(), _base::Y(), _base::Z());
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
    [[nodiscard]] auto operator-(const Base<ThisSpace, UnderlyingData, BT>& rhs) const noexcept {
        Vector<ThisSpace, UnderlyingData> v(_base::X(), _base::Y(), _base::Z());
        Sub(UnderlyingDataFrom(v), UnderlyingDataFrom(rhs));
        return v;
    }

    template <BaseType BT> requires(IsVector(BT))
    [[nodiscard]] auto operator+(const Base<ThisSpace, UnderlyingData, BT>& rhs) const noexcept {
        Vector<ThisSpace, UnderlyingData> v(_base::X(), _base::Y(), _base::Z());
        Add(UnderlyingDataFrom(v), UnderlyingDataFrom(rhs));
        return v;
    }

    [[nodiscard]] auto operator*(const double& d) const noexcept {
        Vector<ThisSpace, UnderlyingData> v(_base::X(), _base::Y(), _base::Z());
        Scale(UnderlyingDataFrom(v), d);
        return v;
    }

    template <BaseType BT> requires(IsVector(BT) && IsNormalized(BT))
    auto operator*=(const Base<ThisSpace, UnderlyingData, BT>& rhs) noexcept {
        *this = this->Cross(rhs);
        return *this;
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

    [[nodiscard]] auto ToXY() const requires ThisSpace::supportsXY
    {
        return NormalizedXYVector<ThisSpace, UnderlyingData>(_base::X(), _base::Y());
    }

    template <DifferentSpaceTo<ThisSpace> OtherSpace, typename TransformManager>
    [[nodiscard]] auto ConvertTo(const TransformManager& transform_manager) const noexcept {
        return Vector<OtherSpace, UnderlyingData>(
            transform_manager.template TransformVector<ThisSpace, OtherSpace>(static_cast<UnderlyingData>(*this))
        );
    }

    friend auto& operator<<(std::ostream& os, const NormalizedVector<ThisSpace, UnderlyingData>& v) {
        return os << std::format("{}", v);
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
    StaticAssert::invalid_point_to_vector_addition operator+(const Base<ThisSpace, UnderlyingData, BT>&) const noexcept {
        return StaticAssert::invalid_point_to_vector_addition{};
    }

    template <BaseType BT> requires(IsPoint(BT))
    StaticAssert::invalid_point_from_vector_subtraction operator-(const Base<ThisSpace, UnderlyingData, BT>&) const noexcept {
        return StaticAssert::invalid_point_from_vector_subtraction{};
    }

    template <BaseType BT> requires(IsVector(BT))
    StaticAssert::invalid_normalized_vector_addition operator+=(const Base<ThisSpace, UnderlyingData, BT>&) const noexcept {
        return StaticAssert::invalid_normalized_vector_addition{};
    }

    template <BaseType BT> requires(IsVector(BT))
    StaticAssert::invalid_normalized_vector_subtraction operator-=(const Base<ThisSpace, UnderlyingData, BT>&) const noexcept {
        return StaticAssert::invalid_normalized_vector_subtraction{};
    }

    StaticAssert::invalid_normalized_vector_scale operator*=(const double&) const noexcept {
        return StaticAssert::invalid_normalized_vector_scale{};
    }

    template <BaseType BT> requires(IsVector(BT) && IsNotNormalized(BT))
    StaticAssert::invalid_normalized_vector_in_place_cross operator*=(const Base<ThisSpace, UnderlyingData, BT>&) const noexcept {
        return StaticAssert::invalid_normalized_vector_in_place_cross{};
    }

    [[nodiscard]] StaticAssert::XYVector_not_supported ToXY() const noexcept requires ThisSpace::doesNotSupportXY
    {
        return StaticAssert::XYVector_not_supported{};
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

template <typename S, typename U>
struct std::formatter<Space::implementation::NormalizedVector<S, U>>
    : Space::implementation::baseFormatter<S, Space::implementation::BaseType::NormalizedVector> {

    using _base = Space::implementation::baseFormatter<S, Space::implementation::BaseType::NormalizedVector>;

    constexpr auto parse(std::format_parse_context& ctx) { return _base::parse(ctx); }

    template <class FormatContext> auto format(const auto& v, FormatContext& fc) const { return _base::format(v, fc); }
};
