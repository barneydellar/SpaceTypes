#pragma once

namespace Space
{

    template <typename T>
    struct SpaceTypeNameMap final
    {
        static const std::string name;
    };

    template <typename T>
    const std::string SpaceTypeNameMap<T>::name = "NoSpaceNameDefined";
}
