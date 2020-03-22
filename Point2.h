#pragma once
#include "detail/Point2Base.h"

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class Point2 final : public Point2Base<ThisSpace, Implementation>
    {
        using _base = Point2Base<ThisSpace, Implementation>;
        using _base::_base;

        friend class PointBase<ThisSpace, Implementation>;
        friend class Point2Base<ThisSpace, Implementation>;
        friend class NormalizedVectorBase<ThisSpace, Implementation>;
        friend class NormalizedVector2Base<ThisSpace, Implementation>;
        friend class VectorBase<ThisSpace, Implementation>;
        friend class Vector2Base<ThisSpace, Implementation>;

        friend class Point<ThisSpace, Implementation>;
        friend class Point2<ThisSpace, Implementation>;
        friend class NormalizedVector<ThisSpace, Implementation>;
        friend class NormalizedVector2<ThisSpace, Implementation>;
        friend class Vector<ThisSpace, Implementation>;
        friend class Vector2<ThisSpace, Implementation>;
    public:

        using _base::operator+=;
        Point2<ThisSpace, Implementation> operator+=(const Vector2<ThisSpace, Implementation>& rhs) noexcept {
            _base::Add(rhs);
            return *this;
        }

        //---------------------------------------------------------------------


        using _base::operator-=;
        Point2<ThisSpace, Implementation> operator-=(const Vector2<ThisSpace, Implementation>& rhs) noexcept {
            _base::Sub(rhs);
            return *this;
        }

        //---------------------------------------------------------------------

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
