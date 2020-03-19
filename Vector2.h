#pragma once
#include "detail/Vector2Base.h"

namespace Space {

    template <typename Space, typename ExternalImplementation>
    class Vector2 final : public Vector2Base<Space, ExternalImplementation>
    {
        using _base = Vector2Base<Space, ExternalImplementation>;
        using _base::_base;
    public:
        friend std::ostream& operator << (
            std::ostream& os,
            const Vector2<Space, ExternalImplementation>& item
        ) {
            const auto space = SpaceTypeNameMap<Space>::name;
            os << space << "::Vector2 (" << item.X() << ", " << item.Y() << ")";
            return os;
        }
    };

}
