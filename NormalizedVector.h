#pragma once
#include "detail/NormalizedVectorBase.h"

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class NormalizedVector final : public NormalizedVectorBase<ThisSpace, Implementation>
    {
        using _base = NormalizedVectorBase<ThisSpace, Implementation>;

    public:

        NormalizedVector() noexcept(false) : VectorBase<ThisSpace, Implementation>(), NormalizedVectorBase<ThisSpace, Implementation>() {}
        explicit NormalizedVector(const Implementation& e) noexcept(false) : VectorBase<ThisSpace, Implementation>(e), NormalizedVectorBase<ThisSpace, Implementation>(e) {}
        explicit NormalizedVector<ThisSpace, Implementation>(const double x, const double y, const double z) noexcept(false) : VectorBase<ThisSpace, Implementation>(x, y, z), NormalizedVectorBase<ThisSpace, Implementation>(x, y, z) {}
        NormalizedVector(const std::initializer_list<double>& l) noexcept(false) : VectorBase<ThisSpace, Implementation>(l), NormalizedVectorBase<ThisSpace, Implementation>(l) {}

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
