#pragma once
#include "SpaceImpl.h"

namespace Space {

    template <typename Space, typename ExternalImplementation>
    class NormalizedVector final : public Base<Space, ExternalImplementation>
    {
        using NormalizedVectorInThisSpace = NormalizedVectorInASpace<Space>;
        using _base = Base<Space, ExternalImplementation>;

    public:

        NormalizedVector(const detail::PointOrVector& p) noexcept(false) : _base(p) { _base::m_impl.Normalize(); }
        constexpr NormalizedVector() noexcept(false) { _base::m_impl = { 1, 0, 0 }; }
        constexpr explicit NormalizedVector(const ExternalImplementation& e) noexcept(false) : _base(e) { _base::m_impl.Normalize(); }
        constexpr explicit NormalizedVector(const double x, const double y, const double z) noexcept(false) : _base(x, y, z) { _base::m_impl.Normalize();}
        constexpr explicit NormalizedVector(const double x, const double y) noexcept(false) : _base(x, y) { _base::m_impl.Normalize();}
        constexpr NormalizedVector(const std::initializer_list<double> l) noexcept(false) : _base(l) { _base::m_impl.Normalize();}


        [[nodiscard]] operator Vector<Space, ExternalImplementation>() const noexcept {
            return Vector<Space, ExternalImplementation>(_base::m_impl.X(), _base::m_impl.Y(), _base::m_impl.Z());
        }

        using _base::operator*;
        [[nodiscard]] constexpr NormalizedVectorInThisSpace operator*(const NormalizedVectorInThisSpace& rhs) const noexcept {
            return this->Cross(rhs);
        }

        using _base::Cross;
        [[nodiscard]] NormalizedVectorInThisSpace Cross(const NormalizedVectorInThisSpace& other) const noexcept {
            return NormalizedVectorInThisSpace(_base::m_impl.Cross(other.m_impl));
        }

        //-------------------------------------------------------------------------------------
#ifndef IGNORE_SPACE_STATIC_ASSERT
        StaticAssert::invalid_normalized_vector_scale operator*=(const double&) const noexcept {
            return StaticAssert::invalid_normalized_vector_scale{};
        }
        template <typename Anything>
        StaticAssert::invalid_normalized_vector_addition operator+=(const Anything&) const noexcept {
            return StaticAssert::invalid_normalized_vector_addition{};
        }

        template <typename Anything>
        StaticAssert::invalid_normalized_vector_subtraction operator-=(const Anything&) const noexcept {
            return StaticAssert::invalid_normalized_vector_subtraction{};
        }

        StaticAssert::normalized_vectors_do_not_support_non_const_iteration begin() const noexcept {
            return StaticAssert::normalized_vectors_do_not_support_non_const_iteration{};
        }
        StaticAssert::normalized_vectors_do_not_support_non_const_iteration end() const noexcept {
            return StaticAssert::normalized_vectors_do_not_support_non_const_iteration{};
        }

        StaticAssert::normalized_vectors_do_not_support_norm Norm() const noexcept{
            return StaticAssert::normalized_vectors_do_not_support_norm();
        }
#endif
    };

    template <typename Space, typename Impl>
    constexpr std::ostream& operator << (
        std::ostream& os,
        const NormalizedVector<Space, Impl>& item
    ) {
        const auto space = SpaceTypeNameMap<Space>::name;
        os << space << "::NormalizedVector (" << item.X() << ", " << item.Y() << ", " << item.Z() << ")";
        return os;
    }
}
