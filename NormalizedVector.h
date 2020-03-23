#pragma once
#include "detail/NormalizedVectorBase.h"

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class NormalizedVector final : public NormalizedVectorBase<ThisSpace, Implementation>
    {
        using _base = NormalizedVectorBase<ThisSpace, Implementation>;
        using _base::_base;

    public:

        using _base::operator*=;
        NormalizedVector<ThisSpace, Implementation> operator*=(const NormalizedVectorBase<ThisSpace, Implementation>& rhs) noexcept {
            *this = this->Cross(rhs);
            return *this;
        }

        friend std::ostream& operator << (
            std::ostream& os,
            const NormalizedVector<ThisSpace, Implementation>& item
        ) {
            const auto space = SpaceTypeNameMap<ThisSpace>::name;
            os << space << "::NormalizedVector (" << item.X() << ", " << item.Y() << ", " << item.Z() << ")";
            return os;
        }
    };
}
