#pragma once
#include "detail/NormalizedVector2Base.h"

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class NormalizedVector2 final : public NormalizedVector2Base<ThisSpace, Implementation>
    {
        using _base = NormalizedVector2Base<ThisSpace, Implementation>;

    public:

        NormalizedVector2() noexcept(false) : VectorBase<ThisSpace, Implementation>(), NormalizedVector2Base<ThisSpace, Implementation>() {}
        explicit NormalizedVector2(const Implementation& e) noexcept(false) : VectorBase<ThisSpace, Implementation>(e), NormalizedVector2Base<ThisSpace, Implementation>(e) {}
        explicit NormalizedVector2<ThisSpace, Implementation>(const double x, const double y) noexcept(false) : VectorBase<ThisSpace, Implementation>(x, y, 0), NormalizedVector2Base<ThisSpace, Implementation>(x, y) {}
        NormalizedVector2(const std::initializer_list<double> l) noexcept(false) : NormalizedVector2Base<ThisSpace, Implementation>(l) {}


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
