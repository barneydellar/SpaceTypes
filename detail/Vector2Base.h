#pragma once

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class Vector2Base : public virtual VectorBase<ThisSpace, Implementation>
    {
        using Vector2BaseInThisSpace = Vector2Base<ThisSpace, Implementation>;
        using VectorBaseInThisSpace = VectorBase<ThisSpace, Implementation>;

    public:

        Vector2Base() noexcept : VectorBaseInThisSpace() {}
        explicit Vector2Base(const Implementation& v) noexcept : VectorBaseInThisSpace(v) {*std::prev(VectorBaseInThisSpace::end()) = 0;}
        explicit Vector2Base(const double x, const double y) noexcept : VectorBaseInThisSpace(x, y, 0) {}
        Vector2Base(const std::initializer_list<double> l)
        {
            if (l.size() != 2)
            {
                throw std::invalid_argument("You can only initialise with two elements");
            }
            std::copy(
                std::cbegin(l),
                std::cend(l),
                VectorBaseInThisSpace::begin()
            );
        }

        [[nodiscard]] operator Vector<ThisSpace, Implementation>() const noexcept {
            return Vector<ThisSpace, Implementation>(VectorBaseInThisSpace::X(), VectorBaseInThisSpace::Y(), VectorBaseInThisSpace::Z());
        }

        [[nodiscard]] StaticAssert::z_not_supported Z() const noexcept { return StaticAssert::z_not_supported{}; }

        double operator[](const unsigned int i) const
        {
            if (i > 1) {
                throw std::invalid_argument("Index is out of range");
            }
            return VectorBaseInThisSpace::operator[](i);
        }

        [[nodiscard]] const double* cend() const noexcept
        {
            return reinterpret_cast<const double*>(std::prev(VectorBaseInThisSpace::cend()));
        }

        [[nodiscard]] double* end() noexcept
        {
            return reinterpret_cast<double*>(std::prev(VectorBaseInThisSpace::end()));
        }

        template <int I>
        [[nodiscard]] typename std::enable_if<I == 0 || I == 1, double>::type at() const {
            return VectorBaseInThisSpace::operator[](I);
        }

        [[nodiscard]] friend Vector2<ThisSpace, Implementation> operator*(Vector2<ThisSpace, Implementation> lhs, const double& d) noexcept {
            lhs *= d;
            return lhs;
        }

        using VectorBaseInThisSpace::operator*=;

        using VectorBaseInThisSpace::operator*;
        [[nodiscard]] Vector<ThisSpace, Implementation> operator*(const Vector2BaseInThisSpace& rhs) const noexcept {
            return this->Cross(rhs);
        }

        using VectorBaseInThisSpace::Cross;
        [[nodiscard]] Vector<ThisSpace, Implementation> Cross(const Vector2BaseInThisSpace& other) const noexcept {
            return Vector<ThisSpace, Implementation>(VectorBaseInThisSpace::Cross(other));
        }

        using VectorBaseInThisSpace::operator-;
        [[nodiscard]] friend Vector2<ThisSpace, Implementation> operator-(Vector2<ThisSpace, Implementation> lhs, const Vector2BaseInThisSpace& rhs) noexcept {
            lhs -= rhs;
            return lhs;
        }

        using VectorBaseInThisSpace::operator+=;
        using VectorBaseInThisSpace::operator-=;

        [[nodiscard]] friend Vector2<ThisSpace, Implementation> operator+(Vector2<ThisSpace, Implementation> lhs, const Vector2BaseInThisSpace& rhs) noexcept {
            lhs += rhs;
            return lhs;
        }

        [[nodiscard]] NormalizedVector2<ThisSpace, Implementation> Norm() const {
            return NormalizedVector2<ThisSpace, Implementation>(VectorBaseInThisSpace::m_impl);
        }

        //-------------------------------------------------------------------------------------
#ifndef IGNORE_SPACE_STATIC_ASSERT

        template <int I>
        typename std::enable_if<I != 0 && I != 1, StaticAssert::invalid_at_access>::type at() const {
            return StaticAssert::invalid_at_access{};
        }
        StaticAssert::invalid_vector2_in_place_cross operator*=(const Vector2BaseInThisSpace& other) noexcept {
            return StaticAssert::invalid_vector2_in_place_cross{};
        }

        StaticAssert::invalid_vector_to_vector_addition operator+=(const VectorBase<ThisSpace, Implementation>&) noexcept {
            return StaticAssert::invalid_vector_to_vector_addition{};
        }

#endif
    };
}
