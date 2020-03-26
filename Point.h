#pragma once
#include "detail/PointBase.h"

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class Point final : public PointBase<ThisSpace, Implementation>
    {
        using _base = PointBase<ThisSpace, Implementation>;
        using _base::_base;
    public:

        Point<ThisSpace, Implementation> operator+=(const VectorBase<ThisSpace, Implementation>& rhs) noexcept {
            _base::Add(rhs);
            return *this;
        }

        //---------------------------------------------------------------------

        Point<ThisSpace, Implementation> operator-=(const VectorBase<ThisSpace, Implementation>& rhs) noexcept {
            _base::Sub(rhs);
            return *this;
        }

        //---------------------------------------------------------------------

        friend std::ostream& operator << (
            std::ostream& os,
            const Point<ThisSpace, Implementation>& item
        ) {
            const auto space = SpaceTypeNameMap<ThisSpace>::name;
            os << space << "::Point (" << item.X() << ", " << item.Y() << ", " << item.Z() << ")";
            return os;
        }


#ifndef IGNORE_SPACE_STATIC_ASSERT
        using _base::operator+=;
        using _base::operator-=;
#endif

    };

}
