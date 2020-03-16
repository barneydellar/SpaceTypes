#pragma once
#include "SpaceImpl.h"

namespace Space {

    template <typename Space, typename ExternalImplementation>
    class Vector : public Base<Space, ExternalImplementation>
    {
        friend class Point<Space, ExternalImplementation>;

        using VectorInThisSpace = VectorInASpace<Space>;
        using NormalizedVectorInThisSpace = NormalizedVectorInASpace<Space>;
        using _base = Base<Space, ExternalImplementation>;

    public:

        Vector(const detail::PointOrVector& p) noexcept(false) : _base(p) {}
        constexpr Vector() noexcept(false) { _base::m_impl = { 0, 0, 0 }; }
        constexpr explicit Vector(const ExternalImplementation& e) noexcept(false) : _base(e) {}
        constexpr explicit Vector(const double x, const double y, const double z) noexcept(false) : _base(x, y, z) {  }
        constexpr explicit Vector(const double x, const double y) noexcept(false) : _base(x, y) {}
        constexpr Vector(const std::initializer_list<double> l) noexcept(false) : _base(l) {}


    };

    template <typename Space, typename Impl>
    std::ostream& operator << (
        std::ostream& os,
        const Vector<Space, Impl>& item
    ) {
        const auto space = SpaceTypeNameMap<Space>::name;
        os << space << "::Vector (" << item.X() << ", " << item.Y() << ", " << item.Z() << ")";
        return os;
    }
}
