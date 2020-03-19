#pragma once

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class NormalizedVectorBase : public virtual VectorBase<ThisSpace, Implementation>
    {
        using NormalizedVectorBaseInThisSpace = NormalizedVectorBase<ThisSpace, Implementation>;
        using VectorBaseInThisSpace = VectorBase<ThisSpace, Implementation>;

    public:

        NormalizedVectorBase() noexcept(false) { VectorBaseInThisSpace::m_impl = { 1, 0, 0 }; }
        explicit NormalizedVectorBase(const Implementation& e) noexcept(false) { VectorBaseInThisSpace::m_impl = { e.X(), e.Y(), e.Z() };  Normalize(); }
        explicit NormalizedVectorBase(const double x, const double y, const double z) noexcept(false) { VectorBaseInThisSpace::m_impl = { x, y, z }; Normalize(); }
        NormalizedVectorBase(const std::initializer_list<double> l) noexcept(false) {
            if (l.size() != 3)
            {
                throw std::invalid_argument("You can only initialise with three elements");
            }
            VectorBaseInThisSpace::m_impl = l;
            Normalize();
        }

        [[nodiscard]] operator Vector<ThisSpace, Implementation>() const noexcept {
            return Vector<ThisSpace, Implementation>(VectorBaseInThisSpace::m_impl.X(), VectorBaseInThisSpace::m_impl.Y(), VectorBaseInThisSpace::m_impl.Z());
        }

        using VectorBaseInThisSpace::operator*;
        [[nodiscard]] NormalizedVector<ThisSpace, Implementation> operator*(const NormalizedVectorBaseInThisSpace& rhs) const noexcept {
            return this->Cross(rhs);
        }

        using VectorBaseInThisSpace::Cross;
        [[nodiscard]] NormalizedVector<ThisSpace, Implementation> Cross(const NormalizedVectorBaseInThisSpace& other) const noexcept {
            return NormalizedVector<ThisSpace, Implementation>(VectorBaseInThisSpace::m_impl.Cross(other.m_impl));
        }

        [[nodiscard]] NormalizedVector2<ThisSpace, Implementation> RemoveZ() const {
            return NormalizedVector2<ThisSpace, Implementation>(VectorBaseInThisSpace::m_impl);
        }

        //-------------------------------------------------------------------------------------
#ifndef IGNORE_SPACE_STATIC_ASSERT
        StaticAssert::invalid_normalized_vector_scale operator*=(const double&) const noexcept {
            return StaticAssert::invalid_normalized_vector_scale{};
        }
        template <typename AnySpace>
        StaticAssert::invalid_normalized_vector_addition operator+=(const NormalizedVectorBase<AnySpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_normalized_vector_addition{};
        }

        template <typename AnySpace>
        StaticAssert::invalid_normalized_vector_subtraction operator-=(const NormalizedVectorBase<AnySpace, Implementation>&) const noexcept {
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

    protected:
        void Normalize() {
            if (std::abs(VectorBaseInThisSpace::Mag_double()) < 1e-6) {
                throw std::invalid_argument("Zero-sized normal vectors are not allowed");
            }
            VectorBaseInThisSpace::m_impl.Normalize();
        }
    };
}
