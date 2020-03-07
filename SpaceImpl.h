#pragma once
namespace Space {

    template <typename T>
    struct SpaceTypeNameMap final { static const std::string name; };

    template <typename T>
    const std::string SpaceTypeNameMap <T>::name = "NoSpaceNameDefined";

    template<typename S>
    using VectorInASpace = typename S::Vector;

    template<typename S>
    using PointInASpace = typename S::Point;

    template<typename S>
    using NormalizedVectorInASpace = typename S::NormalizedVector;
}
