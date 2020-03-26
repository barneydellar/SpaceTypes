#pragma once
#include "detail/PointBase.h"

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class Point final : public PointBase<ThisSpace, Implementation>
    {
        using _base = PointBase<ThisSpace, Implementation>;
        using _base::_base;
    public:

        [[nodiscard]] double* begin() noexcept {return _base::begin();}
        [[nodiscard]] double* end() noexcept {return _base::end();}

        [[nodiscard]] double Z() const noexcept { return *(_base::cbegin() + 2); }
        void SetX(const double d) noexcept { *(begin() + 0) = d; }
        void SetY(const double d) noexcept { *(begin() + 1) = d; }
        void SetZ(const double d) noexcept { *(begin() + 2) = d; }

        Point<ThisSpace, Implementation> operator+=(const VectorBase<ThisSpace, Implementation>& rhs) noexcept {
            _base::Add(rhs);
            return *this;
        }

        //---------------------------------------------------------------------

        Point<ThisSpace, Implementation> operator-=(const VectorBase<ThisSpace, Implementation>& rhs) noexcept {
            _base::Sub(rhs);
            return *this;
        }

        [[nodiscard]] XYPoint<ThisSpace, Implementation> ToXY() const {
            return XYPoint<ThisSpace, Implementation>(_base::X(), _base::Y());
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
