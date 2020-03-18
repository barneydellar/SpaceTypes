#pragma once
#include "NormalizedVectorBase.h"

namespace Space {

    template <typename Space, typename ExternalImplementation>
    class NormalizedVector final : public NormalizedVectorBase<Space, ExternalImplementation>
    {
    public:
        using _base = NormalizedVectorBase<Space, ExternalImplementation>;
        using _base::_base;

        friend std::ostream& operator << (
            std::ostream& os,
            const NormalizedVector<Space, ExternalImplementation>& item
        ) {
            const auto space = SpaceTypeNameMap<Space>::name;
            os << space << "::NormalizedVector (" << item.X() << ", " << item.Y() << ", " << item.Z() << ")";
            return os;
        }
    };
}
