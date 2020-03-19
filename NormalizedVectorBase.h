#pragma once
#include "SpaceImpl.h"

namespace Space {

    template <typename Space, typename ExternalImplementation>
    class NormalizedVectorBase : public virtual VectorBase<Space, ExternalImplementation>
    {
        using NormalizedVectorBaseInThisSpace = NormalizedVectorBase<Space, ExternalImplementation>;
        using VectorBaseInThisSpace = VectorBase<Space, ExternalImplementation>;

    public:

        NormalizedVectorBase() noexcept(false) { VectorBaseInThisSpace::m_impl = { 1, 0, 0 }; }
        explicit NormalizedVectorBase(const ExternalImplementation& e) noexcept(false) { VectorBaseInThisSpace::m_impl = { e.X(), e.Y(), e.Z() }; VectorBaseInThisSpace::m_impl.Normalize(); }
        explicit NormalizedVectorBase(const double x, const double y, const double z) noexcept(false) { VectorBaseInThisSpace::m_impl = {x, y, z}; VectorBaseInThisSpace::m_impl.Normalize();}
        NormalizedVectorBase(const std::initializer_list<double> l) noexcept(false) {
            if (l.size() != 3)
            {
                throw std::invalid_argument("You can only initialise with three elements");
            }
            VectorBaseInThisSpace::m_impl = l;
            VectorBaseInThisSpace::m_impl.Normalize();
        }

        [[nodiscard]] operator Vector<Space, ExternalImplementation>() const noexcept {
            return Vector<Space, ExternalImplementation>(VectorBaseInThisSpace::m_impl.X(), VectorBaseInThisSpace::m_impl.Y(), VectorBaseInThisSpace::m_impl.Z());
        }

        using VectorBaseInThisSpace::operator*;
        [[nodiscard]] NormalizedVector<Space, ExternalImplementation> operator*(const NormalizedVectorBaseInThisSpace& rhs) const noexcept {
            return this->Cross(rhs);
        }

        using VectorBaseInThisSpace::Cross;
        [[nodiscard]] NormalizedVector<Space, ExternalImplementation> Cross(const NormalizedVectorBaseInThisSpace& other) const noexcept {
            return NormalizedVector<Space, ExternalImplementation>(VectorBaseInThisSpace::m_impl.Cross(other.m_impl));
        }

        [[nodiscard]] NormalizedVector2<Space, ExternalImplementation> RemoveZ() const {
            return NormalizedVector2<Space, ExternalImplementation>(VectorBaseInThisSpace::m_impl);
        }

        //-------------------------------------------------------------------------------------
#ifndef IGNORE_SPACE_STATIC_ASSERT
        StaticAssert::invalid_normalized_vector_scale operator*=(const double&) const noexcept {
            return StaticAssert::invalid_normalized_vector_scale{};
        }
        template <typename AnySpace>
        StaticAssert::invalid_normalized_vector_addition operator+=(const NormalizedVectorBase<AnySpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_normalized_vector_addition{};
        }

        template <typename AnySpace>
        StaticAssert::invalid_normalized_vector_subtraction operator-=(const NormalizedVectorBase<AnySpace, ExternalImplementation>&) const noexcept {
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
}
