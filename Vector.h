#pragma once
#include "VectorBase.h"

namespace Space {

    template <typename Space, typename ExternalImplementation>
    class Vector : public VectorBase<Space, ExternalImplementation>
    {
        using _base = VectorBase<Space, ExternalImplementation>;
        using _base::_base;
    public:

        friend std::ostream& operator << (
            std::ostream& os,
            const Vector<Space, ExternalImplementation>& item
        ) {
            const auto space = SpaceTypeNameMap<Space>::name;
            os << space << "::Vector (" << item.X() << ", " << item.Y() << ", " << item.Z() << ")";
            return os;
        }
    };
}
