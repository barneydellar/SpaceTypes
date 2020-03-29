#pragma once
#include "Space.h"
#include "TestVector.h"
#include "ExampleTransformManager.h"

class Millimetres final
{
public:
    explicit Millimetres(const double d) : m_values{ d } {}
    [[nodiscard]] double get() const { return m_values; }
private:
    double m_values;
};

class Pixels final
{
public:
    explicit Pixels(const double d) : m_values{ d } {}
    [[nodiscard]] double get() const { return m_values; }
private:
    double m_values;
};

class Voxels final
{
public:
    explicit Voxels(const double d) : m_values{ d } {}
    [[nodiscard]] double get() const { return m_values; }
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

    struct Volume final : SpaceBase<Volume, TestVector, XY::IsNotUsed, Voxels> {
        static inline SpaceIDs id = SpaceIDs::Volume;
    };
    template <> const std::string SpaceTypeNameMap<Volume>::name = "Volume";

    struct Patient final : SpaceBase<Patient, TestVector, XY::IsNotUsed, double> {
        static inline SpaceIDs id = SpaceIDs::Patient;
    };
    template <> const std::string SpaceTypeNameMap<Patient>::name = "Patient";

    struct Image final : SpaceBase<Image, TestVector, XY::IsUsed, Millimetres> {
        static inline SpaceIDs id = SpaceIDs::Image;
    };
    template <> const std::string SpaceTypeNameMap<Image>::name = "Image";

    struct View final : SpaceBase<View, TestVector, XY::IsUsed, Pixels> {
        static inline SpaceIDs id = SpaceIDs::View;
    };
    template <> const std::string SpaceTypeNameMap<View>::name = "View";

}

