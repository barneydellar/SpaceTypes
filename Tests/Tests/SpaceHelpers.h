#pragma once
#include "Space.h"
#include "ExampleImpl.h"
#include "ExampleTransformManager.h"

class Millimetres final
{
public:
    constexpr explicit Millimetres(const double d) : m_values{ d } {}
    [[nodiscard]] constexpr double get() const { return m_values; }
private:
    double m_values;
};

class Pixels final
{
public:
    constexpr explicit Pixels(const double d) : m_values{ d } {}
    [[nodiscard]] constexpr double get() const { return m_values; }
private:
    double m_values;
};

class Voxels final
{
public:
    constexpr explicit Voxels(const double d) : m_values{ d } {}
    [[nodiscard]] constexpr double get() const { return m_values; }
private:
    double m_values;
};

namespace Space {

    enum class SpaceIDs
    {
        Volume = 0,
        Patient,
        Image,
        View
    };

    struct Volume final : SpaceBase<Volume, ExampleImpl, Voxels> {
        static inline constexpr SpaceIDs id = SpaceIDs::Volume;
    };
    template <> const std::string SpaceTypeNameMap<Volume>::name = "Volume";

    struct Patient final : SpaceBase<Patient, ExampleImpl, double> {
        static inline constexpr SpaceIDs id = SpaceIDs::Patient;
    };
    template <> const std::string SpaceTypeNameMap<Patient>::name = "Patient";

    struct Image final : SpaceBase<Image, ExampleImpl, Millimetres> {
        static inline constexpr SpaceIDs id = SpaceIDs::Image;
    };
    template <> const std::string SpaceTypeNameMap<Image>::name = "Image";

    struct View final : SpaceBase<View, ExampleImpl, Pixels> {
        static inline constexpr SpaceIDs id = SpaceIDs::View;
    };
    template <> const std::string SpaceTypeNameMap<View>::name = "View";

}

//-------------------------------------------------------------------------------------------------
