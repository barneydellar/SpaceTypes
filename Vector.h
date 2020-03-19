#pragma once
#include "detail/VectorBase.h"

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class Vector : public VectorBase<ThisSpace, Implementation>
    {
        using _base = VectorBase<ThisSpace, Implementation>;
        using _base::_base;
    public:

        friend std::ostream& operator << (
            std::ostream& os,
            const Vector<ThisSpace, Implementation>& item
        ) {
            const auto space = SpaceTypeNameMap<ThisSpace>::name;
            os << space << "::Vector (" << item.X() << ", " << item.Y() << ", " << item.Z() << ")";
            return os;
        }
    };
}
