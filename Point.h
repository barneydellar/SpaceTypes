#pragma once
#include "detail/PointBase.h"

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class Point final : public PointBase<ThisSpace, Implementation>
    {
        friend class Point2<ThisSpace, Implementation>;

        using _base = PointBase<ThisSpace, Implementation>;
        using _base::_base;
    public:

        [[nodiscard]] friend Point<ThisSpace, Implementation> operator+(Point<ThisSpace, Implementation> lhs, const Vector<ThisSpace, Implementation>& rhs) noexcept {
            lhs += rhs;
            return lhs;
        }

        using _base::operator+=;
        Point<ThisSpace, Implementation> operator+=(const Vector<ThisSpace, Implementation>& rhs) noexcept {
            _base::Add(rhs);
            return *this;
        }

        friend std::ostream& operator << (
            std::ostream& os,
            const Point<ThisSpace, Implementation>& item
        ) {
            const auto space = SpaceTypeNameMap<ThisSpace>::name;
            os << space << "::Point (" << item.X() << ", " << item.Y() << ", " << item.Z() << ")";
            return os;
        }
    };

}
