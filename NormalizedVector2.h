#pragma once
#include "detail/NormalizedVector2Base.h"

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class NormalizedVector2 final : public NormalizedVector2Base<ThisSpace, Implementation>
    {
        using _base = NormalizedVector2Base<ThisSpace, Implementation>;
        using _base::_base;

    public:

        friend std::ostream& operator << (
            std::ostream& os,
            const NormalizedVector2<ThisSpace, Implementation>& item
        ) {
            const auto space = SpaceTypeNameMap<ThisSpace>::name;
            os << space << "::NormalizedVector2 (" << item.X() << ", " << item.Y() << ")";
            return os;
        }
    };
}
