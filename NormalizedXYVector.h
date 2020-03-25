#pragma once
#include "detail/NormalizedXYVectorBase.h"

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class NormalizedXYVector final : public NormalizedXYVectorBase<ThisSpace, Implementation>
    {
        using _base = NormalizedXYVectorBase<ThisSpace, Implementation>;

    public:

        NormalizedXYVector() noexcept(false) : VectorBase<ThisSpace, Implementation>(), NormalizedXYVectorBase<ThisSpace, Implementation>() {}
        explicit NormalizedXYVector(const Implementation& e) noexcept(false) : VectorBase<ThisSpace, Implementation>(e), NormalizedXYVectorBase<ThisSpace, Implementation>(e) {}
        explicit NormalizedXYVector<ThisSpace, Implementation>(const double x, const double y) noexcept(false) : VectorBase<ThisSpace, Implementation>(x, y, 0), NormalizedXYVectorBase<ThisSpace, Implementation>(x, y) {}
        NormalizedXYVector(const std::initializer_list<double>& l) noexcept(false) : NormalizedXYVectorBase<ThisSpace, Implementation>(l) {}


        friend std::ostream& operator << (
            std::ostream& os,
            const NormalizedXYVector<ThisSpace, Implementation>& item
        ) {
            const auto space = SpaceTypeNameMap<ThisSpace>::name;
            os << space << "::NormalizedXYVector (" << item.X() << ", " << item.Y() << ")";
            return os;
        }
    };
}
