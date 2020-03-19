#pragma once
#include "SpaceImpl.h"
#include "Point2Base.h"

namespace Space {

    template <typename Space, typename ExternalImplementation>
    class Point2 : public Point2Base<Space, ExternalImplementation>
    {
        using _base = Point2Base<Space, ExternalImplementation>;
        using _base::_base;
    public:

        friend std::ostream& operator << (
            std::ostream& os,
            const Point2<Space, ExternalImplementation>& item
        ) {
            const auto space = SpaceTypeNameMap<Space>::name;
            os << space << "::Point2 (" << item.X() << ", " << item.Y() << ")";
            return os;
        }
    };
}
