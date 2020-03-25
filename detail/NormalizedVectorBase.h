#pragma once

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class NormalizedVectorBase : public virtual VectorBase<ThisSpace, Implementation>
    {
        using NormalizedVectorBaseInThisSpace = NormalizedVectorBase<ThisSpace, Implementation>;
        using VectorBaseInThisSpace = VectorBase<ThisSpace, Implementation>;

    public:

        NormalizedVectorBase() noexcept(false) : VectorBaseInThisSpace() { *VectorBaseInThisSpace::begin() = 1; }
        explicit NormalizedVectorBase(const Implementation& e) noexcept(false): VectorBaseInThisSpace(e) {Normalize();}
        explicit NormalizedVectorBase(const double x, const double y, const double z) noexcept(false) : VectorBaseInThisSpace(x, y, z) { Normalize(); }
        NormalizedVectorBase(const std::initializer_list<double>& l) noexcept(false) : VectorBaseInThisSpace(l) {Normalize();}

        [[nodiscard]] operator Vector<ThisSpace, Implementation>() const noexcept {
            return Vector<ThisSpace, Implementation>(VectorBaseInThisSpace::X(), VectorBaseInThisSpace::Y(), VectorBaseInThisSpace::Z());
        }

        using VectorBaseInThisSpace::operator*;
        [[nodiscard]] NormalizedVector<ThisSpace, Implementation> operator*(const NormalizedVectorBaseInThisSpace& rhs) const noexcept {
            return this->Cross(rhs);
        }

        using VectorBaseInThisSpace::Cross;
        [[nodiscard]] NormalizedVector<ThisSpace, Implementation> Cross(const NormalizedVectorBaseInThisSpace& other) const noexcept {
            return NormalizedVector<ThisSpace, Implementation>(VectorBaseInThisSpace::Cross(other).Norm());
        }

        [[nodiscard]] NormalizedVector2<ThisSpace, Implementation> RemoveZ() const {
            return NormalizedVector2<ThisSpace, Implementation>(VectorBaseInThisSpace::m_impl);
        }

        using VectorBaseInThisSpace::operator-;
        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator-(NormalizedVector<ThisSpace, Implementation> lhs, const VectorBaseInThisSpace& rhs) noexcept {
            lhs.Sub(rhs);
            return lhs;
        }

        using VectorBaseInThisSpace::operator+;
        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator+(NormalizedVector<ThisSpace, Implementation> lhs, const VectorBaseInThisSpace& rhs) noexcept {
            lhs.Add(rhs);
            return lhs;
        }

        using VectorBaseInThisSpace::operator-=;
        using VectorBaseInThisSpace::operator*=;

        //-------------------------------------------------------------------------------------
#ifndef IGNORE_SPACE_STATIC_ASSERT
        StaticAssert::invalid_normalized_vector_scale operator*=(const double&) const noexcept {
            return StaticAssert::invalid_normalized_vector_scale{};
        }

        StaticAssert::invalid_normalized_vector_in_place_cross operator*=(const Vector<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_normalized_vector_in_place_cross{};
        }

        StaticAssert::invalid_normalized_vector_addition operator+=(const NormalizedVectorBase<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_normalized_vector_addition{};
        }

        StaticAssert::invalid_normalized_vector_subtraction operator-=(const NormalizedVectorBase<ThisSpace, Implementation>&) const noexcept {
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

            const auto mag = VectorBaseInThisSpace::Mag_double();
            if (std::abs(mag) < 1e-6) {
                throw std::invalid_argument("Zero-sized normal vectors are not allowed");
            }

            std::transform(
                VectorBaseInThisSpace::cbegin(),
                VectorBaseInThisSpace::cend(),
                VectorBaseInThisSpace::begin(),
                [mag](auto v) { return v / mag; }
            );
        }
    };
}
