#pragma once
#include "detail/XYPointBase.h"

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class XYPoint final : public XYPointBase<ThisSpace, Implementation>
    {
        using _base = XYPointBase<ThisSpace, Implementation>;
        using _base::_base;
    public:

        using _base::operator+=;
        XYPoint<ThisSpace, Implementation> operator+=(const XYVector<ThisSpace, Implementation>& rhs) noexcept {
            _base::Add(rhs);
            return *this;
        }

        //---------------------------------------------------------------------


        using _base::operator-=;
        XYPoint<ThisSpace, Implementation> operator-=(const XYVector<ThisSpace, Implementation>& rhs) noexcept {
            _base::Sub(rhs);
            return *this;
        }

        //---------------------------------------------------------------------

        friend std::ostream& operator << (
            std::ostream& os,
            const XYPoint<ThisSpace, Implementation>& item
        ) {
            const auto space = SpaceTypeNameMap<ThisSpace>::name;
            os << space << "::XYPoint (" << item.X() << ", " << item.Y() << ")";
            return os;
        }
    };
}
