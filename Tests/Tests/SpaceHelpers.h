#pragma once
#include "Space.h"
#include <array>

class Millimetres final
{
public:
    constexpr explicit Millimetres(const double d) : m_values{ d } {}
    constexpr double get() const { return m_values; }
private:
    double m_values;
};

class Pixels final
{
public:
    constexpr explicit Pixels(const double d) : m_values{ d } {}
    constexpr double get() const { return m_values; }
private:
    double m_values;
};

class Voxels final
{
public:
    constexpr explicit Voxels(const double d) : m_values{ d } {}
    constexpr double get() const { return m_values; }
private:
    double m_values;
};

namespace Space {
    struct Volume final : SpaceBase<Volume, Voxels> {};
    template <> const std::string SpaceTypeNameMap<Volume>::name = "Volume";

    struct Patient final : SpaceBase<Patient, Millimetres> {};
    template <> const std::string SpaceTypeNameMap<Patient>::name = "Patient";

    struct Image final : SpaceBase<Image, Millimetres> {};
    template <> const std::string SpaceTypeNameMap<Image>::name = "Image";

    struct View final : SpaceBase<View, Pixels> {};
    template <> const std::string SpaceTypeNameMap<View>::name = "View";

}

//-------------------------------------------------------------------------------------------------

class TransformManager final
{
public:

    template <typename From, typename To>
    static std::array<double, 3> Transform33(
        std::array<double, 3>
    ) {
        return {15, 16, 17};
    }

    template <typename From, typename To>
    static std::array<double, 3> Transform(
        std::array<double, 3>
    ) {
        return { -5, -6, -7 };
    }
};