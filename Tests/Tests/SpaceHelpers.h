#pragma once
#include "Space.h"
#include <array>

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

    struct Volume final : SpaceBase<Volume, Voxels> {
        static inline constexpr SpaceIDs id = SpaceIDs::Volume;
    };
    template <> const std::string SpaceTypeNameMap<Volume>::name = "Volume";

    struct Patient final : SpaceBase<Patient, double> {
        static inline constexpr SpaceIDs id = SpaceIDs::Patient;
    };
    template <> const std::string SpaceTypeNameMap<Patient>::name = "Patient";

    struct Image final : SpaceBase<Image, Millimetres> {
        static inline constexpr SpaceIDs id = SpaceIDs::Image;
    };
    template <> const std::string SpaceTypeNameMap<Image>::name = "Image";

    struct View final : SpaceBase<View, Pixels> {
        static inline constexpr SpaceIDs id = SpaceIDs::View;
    };
    template <> const std::string SpaceTypeNameMap<View>::name = "View";

}

//-------------------------------------------------------------------------------------------------

class TransformManager final
{
public:

    //--------------------------------
    // Old

    template <typename From, typename To>
    [[nodiscard]] std::array<double, 3> Transform33(
        std::array<double, 3>
    ) const noexcept {
        using namespace Space;
        if constexpr (From::id == SpaceIDs::View) {
            return { 15, 16, 17 };
        } else {
            return { 1, 0, 0 };
        }
    }

    template <typename From, typename To>
    [[nodiscard]] std::array<double, 3> Transform(
        std::array<double, 3>
    ) const noexcept {
        using namespace Space;
        if constexpr (From::id == SpaceIDs::View) {
            return { -5, -6, -7 };
        } else {
            return { 0, 0, 0 };
        }
    }
};