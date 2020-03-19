#pragma once
#include "detail/Point2Base.h"

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class Point2 : public Point2Base<ThisSpace, Implementation>
    {
        using _base = Point2Base<ThisSpace, Implementation>;
        using _base::_base;
    public:

        friend std::ostream& operator << (
            std::ostream& os,
            const Point2<ThisSpace, Implementation>& item
        ) {
            const auto space = SpaceTypeNameMap<ThisSpace>::name;
            os << space << "::Point2 (" << item.X() << ", " << item.Y() << ")";
            return os;
        }
    };
}
