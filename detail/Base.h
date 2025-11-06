#pragma once

namespace Space::implementation {

template <typename SpaceA, typename SpaceB>
concept SameSpaceAs = std::is_same_v<SpaceA, SpaceB>;

template <typename SpaceA, typename SpaceB>
concept DifferentSpaceTo = !std::is_same_v<SpaceA, SpaceB>;

static consteval bool ValidForDimensions(int I, int D) { return I >= 0 && I < D; }
static consteval bool InvalidForDimensions(int I, int D) { return !ValidForDimensions(I, D); }

enum class BaseType { XYVector, XYPoint, Vector, Point, NormalizedVector, NormalizedXYVector };

static consteval bool IsXY(BaseType BT) {
    return BT == BaseType::XYVector || BT == BaseType::XYPoint || BT == BaseType::NormalizedXYVector;
}
static consteval bool Is3D(BaseType BT) { return !IsXY(BT); }
static consteval bool IsPoint(BaseType BT) { return BT == BaseType::Point || BT == BaseType::XYPoint; }
static consteval bool IsVector(BaseType BT) { return !IsPoint(BT); }
static consteval bool IsNormalized(BaseType BT) { return BT == BaseType::NormalizedVector || BT == BaseType::NormalizedXYVector; }
static consteval bool IsNotNormalized(BaseType BT) { return !IsNormalized(BT); }
static consteval int Dimensions(BaseType BT) { return IsXY(BT) ? 2 : 3; }

static consteval auto Name(BaseType BT) {
    switch (BT) {
    case BaseType::XYVector:
        return "XYVector";
    case BaseType::XYPoint:
        return "XYPoint";
    case BaseType::Vector:
        return "Vector";
    case BaseType::Point:
        return "Point";
    case BaseType::NormalizedVector:
        return "NormalizedVector";
    case BaseType::NormalizedXYVector:
        return "NormalizedXYVector";
    }
}

template <typename ThisSpace, typename UnderlyingData, BaseType BT> class Base {

  public:
    [[nodiscard]] explicit operator UnderlyingData() const noexcept { return underlyingData; }
    [[nodiscard]] const double* cbegin() const noexcept { return reinterpret_cast<const double*>(&underlyingData); }
    [[nodiscard]] const double* cend() const noexcept {
        return reinterpret_cast<const double*>(&underlyingData) + Dimensions(BT);
    }

    [[nodiscard]] double* begin() noexcept requires(IsNotNormalized(BT))
    {
        return reinterpret_cast<double*>(&underlyingData);
    }
    [[nodiscard]] double* end() noexcept requires(IsNotNormalized(BT))
    {
        return reinterpret_cast<double*>(&underlyingData) + Dimensions(BT);
    }

    [[nodiscard]] double X() const noexcept { return *(cbegin() + 0); }
    [[nodiscard]] double Y() const noexcept { return *(cbegin() + 1); }
    [[nodiscard]] double Z() const noexcept requires(Is3D(BT))
    {
        return *(cbegin() + 2);
    }

    void SetX(const double d) noexcept requires(IsNotNormalized(BT))
    {
        *(begin() + 0) = d;
    }
    void SetY(const double d) noexcept requires(IsNotNormalized(BT))
    {
        *(begin() + 1) = d;
    }

    void SetZ(const double d) noexcept requires(IsNotNormalized(BT) && Is3D(BT))
    {
        *(begin() + 2) = d;
    }

    [[nodiscard]] double operator[](const unsigned int i) const {
        if (i >= Dimensions(BT)) {
            throw std::invalid_argument("Index is out of range");
        }
        return *(cbegin() + i);
    }

    [[nodiscard]] double& operator[](const unsigned int i) requires(IsNotNormalized(BT))
    {
        if (i >= Dimensions(BT)) {
            throw std::invalid_argument("Index is out of range");
        }
        return *(reinterpret_cast<double*>(&underlyingData) + i);
    }

    template <int I> requires(ValidForDimensions(I, Dimensions(BT)))
    [[nodiscard]] double at() const {
        return operator[](I);
    }

    template <int I> requires(ValidForDimensions(I, Dimensions(BT)) && IsNotNormalized(BT))
    [[nodiscard]] double& at() {
        return operator[](I);
    }

#ifndef IGNORE_SPACE_STATIC_ASSERT

    template <int I> requires(InvalidForDimensions(I, Dimensions(BT)))
    StaticAssert::invalid_at_access at() const {
        return StaticAssert::invalid_at_access{};
    }

    StaticAssert::invalid_3D_access Z() const noexcept requires(IsXY(BT))
    {
        return StaticAssert::invalid_3D_access{};
    }

    StaticAssert::invalid_3D_access SetZ(const double d) noexcept requires(IsNotNormalized(BT) && IsXY(BT))
    {
        return StaticAssert::invalid_3D_access{};
    }

    StaticAssert::invalid_normalized_vector_modification SetX(const double d) noexcept requires(IsNormalized(BT))
    {
        return StaticAssert::invalid_normalized_vector_modification{};
    }
    StaticAssert::invalid_normalized_vector_modification SetY(const double d) noexcept requires(IsNormalized(BT))
    {
        return StaticAssert::invalid_normalized_vector_modification{};
    }
    StaticAssert::invalid_normalized_vector_modification SetZ(const double d) noexcept requires(IsNormalized(BT))
    {
        return StaticAssert::invalid_normalized_vector_modification{};
    }

    StaticAssert::invalid_normalized_vector_modification begin() noexcept requires(IsNormalized(BT))
    {
        return StaticAssert::invalid_normalized_vector_modification{};
    }
    StaticAssert::invalid_normalized_vector_modification end() noexcept requires(IsNormalized(BT))
    {
        return StaticAssert::invalid_normalized_vector_modification{};
    }

    template <DifferentSpaceTo<ThisSpace> OtherSpace, BaseType OtherBaseType>
    StaticAssert::invalid_space operator!=(const Base<OtherSpace, UnderlyingData, OtherBaseType>&) const noexcept {
        return StaticAssert::invalid_space{};
    }

    template <DifferentSpaceTo<ThisSpace> OtherSpace, BaseType OtherBaseType>
    StaticAssert::invalid_space operator==(const Base<OtherSpace, UnderlyingData, OtherBaseType>&) const noexcept {
        return StaticAssert::invalid_space{};
    }

    template <DifferentSpaceTo<ThisSpace> OtherSpace, BaseType OtherBaseType>
    StaticAssert::invalid_space operator*(const Base<OtherSpace, UnderlyingData, OtherBaseType>&) const noexcept {
        return StaticAssert::invalid_space{};
    }
    template <DifferentSpaceTo<ThisSpace> OtherSpace, BaseType OtherBaseType>
    StaticAssert::invalid_space Cross(const Base<OtherSpace, UnderlyingData, OtherBaseType>&) const noexcept {
        return StaticAssert::invalid_space{};
    }
    template <DifferentSpaceTo<ThisSpace> OtherSpace, BaseType OtherBaseType>
    StaticAssert::invalid_space operator*=(const Base<OtherSpace, UnderlyingData, OtherBaseType>&) noexcept {
        return StaticAssert::invalid_space{};
    }
    template <DifferentSpaceTo<ThisSpace> OtherSpace, BaseType OtherBaseType>
    StaticAssert::invalid_space operator+(const Base<OtherSpace, UnderlyingData, OtherBaseType>&) const noexcept {
        return StaticAssert::invalid_space{};
    }
    template <DifferentSpaceTo<ThisSpace> OtherSpace, BaseType OtherBaseType>
    StaticAssert::invalid_space operator+=(const Base<OtherSpace, UnderlyingData, OtherBaseType>&) noexcept {
        return StaticAssert::invalid_space{};
    }
    template <DifferentSpaceTo<ThisSpace> OtherSpace, BaseType OtherBaseType>
    StaticAssert::invalid_space operator-(const Base<OtherSpace, UnderlyingData, OtherBaseType>&) const noexcept {
        return StaticAssert::invalid_space{};
    }
    template <DifferentSpaceTo<ThisSpace> OtherSpace, BaseType OtherBaseType>
    StaticAssert::invalid_space operator-=(const Base<OtherSpace, UnderlyingData, OtherBaseType>&) noexcept {
        return StaticAssert::invalid_space{};
    }

    template <DifferentSpaceTo<ThisSpace> OtherSpace, BaseType OtherBaseType>
    StaticAssert::invalid_space Dot(const Base<OtherSpace, UnderlyingData, OtherBaseType>&) const noexcept {
        return StaticAssert::invalid_space{};
    }
    template <SameSpaceAs<ThisSpace> S, typename TransformManager>
    StaticAssert::invalid_same_space_conversion ConvertTo(const TransformManager& transform_manager) const noexcept {
        return StaticAssert::invalid_same_space_conversion{};
    }
#endif

  protected:
    template <typename S, typename U, BaseType B> friend const U& UnderlyingDataFrom(const Base<S, U, B>& a);

    template <typename S, typename U, BaseType B> friend U& UnderlyingDataFrom(Base<S, U, B>& a);

    UnderlyingData underlyingData;
};

template <typename S, typename U, BaseType B> const U& UnderlyingDataFrom(const Base<S, U, B>& a) { return a.underlyingData; }

template <typename S, typename U, BaseType B> U& UnderlyingDataFrom(Base<S, U, B>& a) { return a.underlyingData; }

template <typename S, BaseType BT> struct baseFormatter : std::formatter<std::string> {

    constexpr auto parse(std::format_parse_context& ctx) {
        auto pos = ctx.begin();
        if (pos == ctx.end() || *pos == '}') {
            _format_type = format_type::full;
            return pos;
        }

        if (*pos == 's') {
            _format_type = format_type::space_only;
        } else if (*pos == 't') {
            _format_type = format_type::type_only;
        } else if (*pos == 'x') {
            _format_type = format_type::x_only;
        } else if (*pos == 'y') {
            _format_type = format_type::y_only;
        } else if (*pos == 'z' && Is3D(BT)) {
            _format_type = format_type::z_only;
        } else {
            unexpected_format_specification();
        }

        return ++pos;
    }

    template <class FormatContext> auto format(const auto& v, FormatContext& fc) const {
        switch (_format_type) {
        case format_type::type_only:
            return formatter<std::string>::format(Name(BT), fc);
        case format_type::space_only:
            return formatter<std::string>::format(Space::SpaceTypeNameMap<S>::name, fc);
        case format_type::x_only:
            return formatter<std::string>::format(std::format("{}", v.X()), fc);
        case format_type::y_only:
            return formatter<std::string>::format(std::format("{}", v.Y()), fc);
        case format_type::z_only:
            if constexpr (Is3D(BT)) {
                return formatter<std::string>::format(std::format("{}", v.Z()), fc);
            }
            throw std::format_error("Invalid format type");
        case format_type::full:
            if constexpr (Is3D(BT)) {
                return formatter<std::string>::format(
                    std::format("{}::{} ({}, {}, {})", Space::SpaceTypeNameMap<S>::name, Name(BT), v.X(), v.Y(), v.Z()), fc
                );
            } else {
                return formatter<std::string>::format(
                    std::format("{}::{} ({}, {})", Space::SpaceTypeNameMap<S>::name, Name(BT), v.X(), v.Y()), fc
                );
            }
        default:
            throw std::format_error("Invalid format type");
        }
    }

  private:
    void unexpected_format_specification() {}

    enum class format_type { full, space_only, type_only, x_only, y_only, z_only };
    format_type _format_type = format_type::full;
};

} // namespace Space::implementation
