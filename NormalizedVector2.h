#pragma once
#include "NormalizedVector2Base.h"

namespace Space {

    template <typename Space, typename ExternalImplementation>
    class NormalizedVector2 final : public NormalizedVector2Base<Space, ExternalImplementation>
    {
        using _base = NormalizedVector2Base<Space, ExternalImplementation>;
        using _base::_base;

    public:

        friend std::ostream& operator << (
            std::ostream& os,
            const NormalizedVector2<Space, ExternalImplementation>& item
        ) {
            const auto space = SpaceTypeNameMap<Space>::name;
            os << space << "::NormalizedVector2 (" << item.X() << ", " << item.Y() << ")";
            return os;
        }
    };
}
