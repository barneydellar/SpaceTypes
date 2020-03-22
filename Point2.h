#pragma once
#include "detail/Point2Base.h"

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class Point2 final : public Point2Base<ThisSpace, Implementation>
    {
        using _base = Point2Base<ThisSpace, Implementation>;
        using _base::_base;
    public:

        [[nodiscard]] friend Point<ThisSpace, Implementation> operator+(Point2<ThisSpace, Implementation> lhs, const Vector<ThisSpace, Implementation>& rhs) noexcept {
            Point<ThisSpace, Implementation> point3(lhs.X(), lhs.Y(), 0);
            point3 += rhs;
            return point3;
        }

        [[nodiscard]] friend Point2<ThisSpace, Implementation> operator+(Point2<ThisSpace, Implementation> lhs, const Vector2<ThisSpace, Implementation>& rhs) noexcept {
            lhs += rhs;
            return lhs;
        }

        using _base::operator+=;
        Point2<ThisSpace, Implementation> operator+=(const Vector2<ThisSpace, Implementation>& rhs) noexcept {
            _base::Add(rhs);
            return *this;
        }

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
