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

template <typename ThisSpace, typename UnderlyingData> class Base {
public:

    [[nodiscard]] explicit operator UnderlyingData() const noexcept { return underlyingData; }

#ifndef IGNORE_SPACE_STATIC_ASSERT
    template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
    StaticAssert::invalid_space operator*(const Base<OtherSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_space{};
    }
    template <typename OtherSpace> StaticAssert::invalid_space Cross(const Base<OtherSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_space{};
    }
    template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
    StaticAssert::invalid_space operator*=(const Base<OtherSpace, UnderlyingData> &) noexcept {
        return StaticAssert::invalid_space{};
    }
    template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
    StaticAssert::invalid_space operator+(const Base<OtherSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_space{};
    }
    template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
    StaticAssert::invalid_space operator+=(const Base<OtherSpace, UnderlyingData> &) noexcept {
        return StaticAssert::invalid_space{};
    }
    template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
    StaticAssert::invalid_space operator-(const Base<OtherSpace, UnderlyingData> &) const noexcept {
        return StaticAssert::invalid_space{};
    }
    template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
    StaticAssert::invalid_space operator-=(const Base<OtherSpace, UnderlyingData> &) noexcept {
        return StaticAssert::invalid_space{};
    }
    template <typename OtherSpace> StaticAssert::invalid_space Dot(const Base<OtherSpace, UnderlyingData> &) const noexcept {
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
