#pragma once
#include "PointBase.h"

namespace Space {

    template <typename Space, typename ExternalImplementation>
    class Point : public PointBase<Space, ExternalImplementation>
    {
    public:
        using _base = PointBase<Space, ExternalImplementation>;
        using _base::_base;

        friend std::ostream& operator << (
            std::ostream& os,
            const Point<Space, ExternalImplementation>& item
        ) {
            const auto space = SpaceTypeNameMap<Space>::name;
            os << space << "::Point (" << item.X() << ", " << item.Y() << ", " << item.Z() << ")";
            return os;
        }
    };

}
