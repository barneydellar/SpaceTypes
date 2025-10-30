#pragma once

namespace Space::implementation {

template <typename SpaceA, typename SpaceB>
concept SameSpaceAs = std::is_same_v<SpaceA, SpaceB>;

template <int I>
concept ValidFor3dAt = (I >= 0 && I <= 2);

template <int I>
concept ValidFor2dAt = (I >= 0 && I <= 1);

template <typename SpaceA, typename SpaceB>
concept DifferentSpaces = !std::is_same_v<SpaceA, SpaceB>;

enum class BaseType { XYVector, XYPoint, Vector, Point, NormalizedVector, NormalizedXYVector };

static constexpr bool IsXY(BaseType BT) {
    return BT == BaseType::XYVector || BT == BaseType::XYPoint || BT == BaseType::NormalizedXYVector;
}
static constexpr bool Is3D(BaseType BT) { return !IsXY(BT); }
static constexpr bool IsPoint(BaseType BT) { return BT == BaseType::Point || BT == BaseType::XYPoint; }
static constexpr bool IsVector(BaseType BT) { return !IsPoint(BT); }
static constexpr bool IsNormalized(BaseType BT) { return BT == BaseType::NormalizedVector || BT == BaseType::NormalizedXYVector; }
static constexpr bool IsNotNormalized(BaseType BT) { return !IsNormalized(BT); }
static constexpr int Dimensions(BaseType BT) { return IsXY(BT) ? 2 : 3; }

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

    template <int I> requires(I >= 0 && I < Dimensions(BT))
    [[nodiscard]] double at() const {
        return operator[](I);
    }

#ifndef IGNORE_SPACE_STATIC_ASSERT

    template <int I> requires(I < 0 || I >= Dimensions(BT))
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

    template <typename OtherSpace, BaseType OtherBaseType> requires(DifferentSpaces<OtherSpace, ThisSpace>)
    StaticAssert::invalid_space operator!=(const Base<OtherSpace, UnderlyingData, OtherBaseType>&) const noexcept {
        return StaticAssert::invalid_space{};
    }

    template <typename OtherSpace, BaseType OtherBaseType> requires(DifferentSpaces<OtherSpace, ThisSpace>)
    StaticAssert::invalid_space operator==(const Base<OtherSpace, UnderlyingData, OtherBaseType>&) const noexcept {
        return StaticAssert::invalid_space{};
    }

    template <typename OtherSpace, BaseType OtherBaseType> requires DifferentSpaces<OtherSpace, ThisSpace>
    StaticAssert::invalid_space operator*(const Base<OtherSpace, UnderlyingData, OtherBaseType>&) const noexcept {
        return StaticAssert::invalid_space{};
    }
    template <typename OtherSpace, BaseType OtherBaseType>
    StaticAssert::invalid_space Cross(const Base<OtherSpace, UnderlyingData, OtherBaseType>&) const noexcept {
        return StaticAssert::invalid_space{};
    }
    template <typename OtherSpace, BaseType OtherBaseType> requires DifferentSpaces<OtherSpace, ThisSpace>
    StaticAssert::invalid_space operator*=(const Base<OtherSpace, UnderlyingData, OtherBaseType>&) noexcept {
        return StaticAssert::invalid_space{};
    }
    template <typename OtherSpace, BaseType OtherBaseType> requires DifferentSpaces<OtherSpace, ThisSpace>
    StaticAssert::invalid_space operator+(const Base<OtherSpace, UnderlyingData, OtherBaseType>&) const noexcept {
        return StaticAssert::invalid_space{};
    }
    template <typename OtherSpace, BaseType OtherBaseType> requires DifferentSpaces<OtherSpace, ThisSpace>
    StaticAssert::invalid_space operator+=(const Base<OtherSpace, UnderlyingData, OtherBaseType>&) noexcept {
        return StaticAssert::invalid_space{};
    }
    template <typename OtherSpace, BaseType OtherBaseType> requires DifferentSpaces<OtherSpace, ThisSpace>
    StaticAssert::invalid_space operator-(const Base<OtherSpace, UnderlyingData, OtherBaseType>&) const noexcept {
        return StaticAssert::invalid_space{};
    }
    template <typename OtherSpace, BaseType OtherBaseType> requires DifferentSpaces<OtherSpace, ThisSpace>
    StaticAssert::invalid_space operator-=(const Base<OtherSpace, UnderlyingData, OtherBaseType>&) noexcept {
        return StaticAssert::invalid_space{};
    }
    template <typename OtherSpace, BaseType OtherBaseType>
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
} // namespace Space::implementation
