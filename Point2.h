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

        [[nodiscard]] friend Point<ThisSpace, Implementation> operator+(Point2<ThisSpace, Implementation> lhs, const VectorBase<ThisSpace, Implementation>& rhs) noexcept {
            Point<ThisSpace, Implementation> point3(lhs.X(), lhs.Y(), 0);
            point3 += rhs;
            return point3;
        }

        [[nodiscard]] friend Point2<ThisSpace, Implementation> operator+(Point2<ThisSpace, Implementation> lhs, const Vector2Base<ThisSpace, Implementation>& rhs) noexcept {
            lhs += rhs;
            return lhs;
        }

        using _base::operator+=;
        Point2<ThisSpace, Implementation> operator+=(const Vector2<ThisSpace, Implementation>& rhs) noexcept {
            _base::Add(rhs);
            return *this;
        }

        //---------------------------------------------------------------------

        [[nodiscard]] friend Point2<ThisSpace, Implementation> operator-(Point2<ThisSpace, Implementation> lhs, const Vector2Base<ThisSpace, Implementation>& rhs) noexcept {
            lhs.Sub(rhs);
            return lhs;
        }

        [[nodiscard]] friend Point<ThisSpace, Implementation> operator-(Point2<ThisSpace, Implementation> lhs, const VectorBase<ThisSpace, Implementation>& rhs) noexcept {
            lhs.Sub(rhs);
            Point<ThisSpace, Implementation> point3(lhs.X(), lhs.Y(), 0);
            return point3;
        }

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
