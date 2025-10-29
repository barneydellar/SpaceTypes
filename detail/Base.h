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

template <typename ThisSpace, typename UnderlyingData, int Dimensions = 3, bool IsNormalised = false>
requires(Dimensions == 2 || Dimensions == 3)
class Base {
  public:
    [[nodiscard]] explicit operator UnderlyingData() const noexcept { return underlyingData; }
    [[nodiscard]] const double* cbegin() const noexcept { return reinterpret_cast<const double*>(&underlyingData); }
    [[nodiscard]] const double* cend() const noexcept { return reinterpret_cast<const double*>(&underlyingData) + Dimensions; }

    [[nodiscard]] double* begin() noexcept requires(IsNormalised == false)
    {
        return reinterpret_cast<double*>(&underlyingData);
    }
    [[nodiscard]] double* end() noexcept requires(IsNormalised == false)
    {
        return reinterpret_cast<double*>(&underlyingData) + Dimensions;
    }

    [[nodiscard]] double X() const noexcept { return *(cbegin() + 0); }
    [[nodiscard]] double Y() const noexcept { return *(cbegin() + 1); }
    [[nodiscard]] double Z() const noexcept requires(Dimensions == 3)
    {
        return *(cbegin() + 2);
    }

    void SetX(const double d) noexcept requires(IsNormalised == false)
    {
        *(begin() + 0) = d;
    }
    void SetY(const double d) noexcept requires(IsNormalised == false)
    {
        *(begin() + 1) = d;
    }

    void SetZ(const double d) noexcept requires(IsNormalised == false && Dimensions == 3)
    {
        *(begin() + 2) = d;
    }

    [[nodiscard]] double operator[](const unsigned int i) const {
        if (i >= Dimensions) {
            throw std::invalid_argument("Index is out of range");
        }
        return *(cbegin() + i);
    }

    template <int I> requires(I >= 0 && I < Dimensions)
    [[nodiscard]] double at() const {
        return operator[](I);
    }

#ifndef IGNORE_SPACE_STATIC_ASSERT

    template <int I> requires(I < 0 || I >= Dimensions)
    StaticAssert::invalid_at_access at() const {
        return StaticAssert::invalid_at_access{};
    }

    StaticAssert::invalid_3D_access Z() const noexcept requires(Dimensions < 3)
    {
        return StaticAssert::invalid_3D_access{};
    }

    StaticAssert::invalid_3D_access SetZ(const double d) noexcept requires(IsNormalised == false && Dimensions < 3)
    {
        return StaticAssert::invalid_3D_access{};
    }

    StaticAssert::invalid_normalized_vector_modification SetX(const double d) noexcept requires(IsNormalised == true)
    {
        return StaticAssert::invalid_normalized_vector_modification{};
    }
        StaticAssert::invalid_normalized_vector_modification SetY(const double d) noexcept requires(IsNormalised == true)
    {
        return StaticAssert::invalid_normalized_vector_modification{};
    }
        StaticAssert::invalid_normalized_vector_modification SetZ(const double d) noexcept requires(IsNormalised == true)
    {
        return StaticAssert::invalid_normalized_vector_modification{};
    }

    StaticAssert::invalid_normalized_vector_modification begin() noexcept requires(IsNormalised == true)
    {
        return StaticAssert::invalid_normalized_vector_modification{};
    }
    StaticAssert::invalid_normalized_vector_modification end() noexcept requires(IsNormalised == true)
    {
        return StaticAssert::invalid_normalized_vector_modification{};
    }

    template <typename OtherSpace, int I, bool B> requires DifferentSpaces<OtherSpace, ThisSpace>
    StaticAssert::invalid_space operator*(const Base<OtherSpace, UnderlyingData, I, B>&) const noexcept {
        return StaticAssert::invalid_space{};
    }
    template <typename OtherSpace, int I, bool B>
    StaticAssert::invalid_space Cross(const Base<OtherSpace, UnderlyingData, I, B>&) const noexcept {
        return StaticAssert::invalid_space{};
    }
    template <typename OtherSpace, int I, bool B> requires DifferentSpaces<OtherSpace, ThisSpace>
    StaticAssert::invalid_space operator*=(const Base<OtherSpace, UnderlyingData, I, B>&) noexcept {
        return StaticAssert::invalid_space{};
    }
    template <typename OtherSpace, int I, bool B> requires DifferentSpaces<OtherSpace, ThisSpace>
    StaticAssert::invalid_space operator+(const Base<OtherSpace, UnderlyingData, I, B>&) const noexcept {
        return StaticAssert::invalid_space{};
    }
    template <typename OtherSpace, int I, bool B> requires DifferentSpaces<OtherSpace, ThisSpace>
    StaticAssert::invalid_space operator+=(const Base<OtherSpace, UnderlyingData, I, B>&) noexcept {
        return StaticAssert::invalid_space{};
    }
    template <typename OtherSpace, int I, bool B> requires DifferentSpaces<OtherSpace, ThisSpace>
    StaticAssert::invalid_space operator-(const Base<OtherSpace, UnderlyingData, I, B>&) const noexcept {
        return StaticAssert::invalid_space{};
    }
    template <typename OtherSpace, int I, bool B> requires DifferentSpaces<OtherSpace, ThisSpace>
    StaticAssert::invalid_space operator-=(const Base<OtherSpace, UnderlyingData, I, B>&) noexcept {
        return StaticAssert::invalid_space{};
    }
    template <typename OtherSpace, int I, bool B>
    StaticAssert::invalid_space Dot(const Base<OtherSpace, UnderlyingData, I, B>&) const noexcept {
        return StaticAssert::invalid_space{};
    }
    template <SameSpaceAs<ThisSpace> S, typename TransformManager>
    StaticAssert::invalid_same_space_conversion ConvertTo(const TransformManager& transform_manager) const noexcept {
        return StaticAssert::invalid_same_space_conversion{};
    }
#endif

  public:
    UnderlyingData underlyingData;
};

} // namespace Space::implementation
