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

template <typename ThisSpace, typename UnderlyingData, int Dimensions=3, bool IsNormalised=false> 
requires(Dimensions == 2 || Dimensions == 3)
class Base {
  public:
    [[nodiscard]] explicit operator UnderlyingData() const noexcept { return underlyingData; }
    [[nodiscard]] const double *cbegin() const noexcept { return reinterpret_cast<const double *>(&underlyingData); }
    [[nodiscard]] const double *cend() const noexcept { return reinterpret_cast<const double *>(&underlyingData) + Dimensions; }

    [[nodiscard]] double *begin() noexcept requires(IsNormalised == false) { return reinterpret_cast<double *>(&underlyingData);}
    [[nodiscard]] double *end() noexcept requires(IsNormalised == false) { return reinterpret_cast<double *>(&underlyingData) + Dimensions; }

#ifndef IGNORE_SPACE_STATIC_ASSERT

    StaticAssert::invalid_normalized_vector_access begin() noexcept requires(IsNormalised == true) { return StaticAssert::invalid_normalized_vector_access{}; }
    StaticAssert::invalid_normalized_vector_access end() noexcept requires(IsNormalised == true) { return StaticAssert::invalid_normalized_vector_access{}; }

    template <typename OtherSpace, int I, bool B> requires DifferentSpaces<OtherSpace, ThisSpace>
    StaticAssert::invalid_space operator*(const Base<OtherSpace, UnderlyingData, I, B> &) const noexcept {
        return StaticAssert::invalid_space{};
    }
    template <typename OtherSpace, int I, bool B> StaticAssert::invalid_space Cross(const Base<OtherSpace, UnderlyingData, I, B> &) const noexcept {
        return StaticAssert::invalid_space{};
    }
    template <typename OtherSpace, int I, bool B> requires DifferentSpaces<OtherSpace, ThisSpace>
    StaticAssert::invalid_space operator*=(const Base<OtherSpace, UnderlyingData, I, B> &) noexcept {
        return StaticAssert::invalid_space{};
    }
    template <typename OtherSpace, int I, bool B> requires DifferentSpaces<OtherSpace, ThisSpace>
    StaticAssert::invalid_space operator+(const Base<OtherSpace, UnderlyingData, I, B> &) const noexcept {
        return StaticAssert::invalid_space{};
    }
    template <typename OtherSpace, int I, bool B> requires DifferentSpaces<OtherSpace, ThisSpace>
    StaticAssert::invalid_space operator+=(const Base<OtherSpace, UnderlyingData, I, B> &) noexcept {
        return StaticAssert::invalid_space{};
    }
    template <typename OtherSpace, int I, bool B> requires DifferentSpaces<OtherSpace, ThisSpace>
    StaticAssert::invalid_space operator-(const Base<OtherSpace, UnderlyingData, I, B> &) const noexcept {
        return StaticAssert::invalid_space{};
    }
    template <typename OtherSpace, int I, bool B> requires DifferentSpaces<OtherSpace, ThisSpace>
    StaticAssert::invalid_space operator-=(const Base<OtherSpace, UnderlyingData, I, B> &) noexcept {
        return StaticAssert::invalid_space{};
    }
    template <typename OtherSpace, int I, bool B> StaticAssert::invalid_space Dot(const Base<OtherSpace, UnderlyingData, I, B> &) const noexcept {
        return StaticAssert::invalid_space{};
    }
    template <SameSpaceAs<ThisSpace> S, typename TransformManager>
    StaticAssert::invalid_same_space_conversion ConvertTo(const TransformManager &transform_manager) const noexcept {
        return StaticAssert::invalid_same_space_conversion{};
    }
#endif

  public:
    UnderlyingData underlyingData;
};

} // namespace Space::implementation
