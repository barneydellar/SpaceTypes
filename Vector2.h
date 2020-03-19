#pragma once
#include "detail/Vector2Base.h"

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class Vector2 final : public Vector2Base<ThisSpace, Implementation>
    {
        using _base = Vector2Base<ThisSpace, Implementation>;
        using _base::_base;
    public:
        friend std::ostream& operator << (
            std::ostream& os,
            const Vector2<ThisSpace, Implementation>& item
        ) {
            const auto space = SpaceTypeNameMap<ThisSpace>::name;
            os << space << "::Vector2 (" << item.X() << ", " << item.Y() << ")";
            return os;
        }
    };

}
