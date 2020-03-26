#pragma once

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class XYVectorBase : public virtual VectorBase<ThisSpace, Implementation>
    {
        using XYVectorBaseInThisSpace = XYVectorBase<ThisSpace, Implementation>;
        using VectorBaseInThisSpace = VectorBase<ThisSpace, Implementation>;

    public:

        XYVectorBase() noexcept : VectorBaseInThisSpace() {}
        explicit XYVectorBase(const Implementation& v) noexcept : VectorBaseInThisSpace(v) {*std::prev(VectorBaseInThisSpace::end()) = 0;}
        explicit XYVectorBase(const double x, const double y) noexcept : VectorBaseInThisSpace(x, y, 0) {}
        XYVectorBase(const std::initializer_list<double>& l)
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

        [[nodiscard]] friend XYVector<ThisSpace, Implementation> operator*(XYVector<ThisSpace, Implementation> lhs, const double& d) noexcept {
            lhs *= d;
            return lhs;
        }

        using VectorBaseInThisSpace::operator*;
        [[nodiscard]] Vector<ThisSpace, Implementation> operator*(const XYVectorBaseInThisSpace& rhs) const noexcept {
            return this->Cross(rhs);
        }

        using VectorBaseInThisSpace::Cross;
        [[nodiscard]] Vector<ThisSpace, Implementation> Cross(const XYVectorBaseInThisSpace& other) const noexcept {
            return Vector<ThisSpace, Implementation>(VectorBaseInThisSpace::Cross(other));
        }

        [[nodiscard]] friend XYVector<ThisSpace, Implementation> operator-(XYVector<ThisSpace, Implementation> lhs, const XYVectorBaseInThisSpace& rhs) noexcept {
            lhs -= rhs;
            return lhs;
        }

        [[nodiscard]] friend XYVector<ThisSpace, Implementation> operator+(XYVector<ThisSpace, Implementation> lhs, const XYVectorBaseInThisSpace& rhs) noexcept {
            lhs += rhs;
            return lhs;
        }

        [[nodiscard]] NormalizedXYVector<ThisSpace, Implementation> Norm() const {
            return NormalizedXYVector<ThisSpace, Implementation>(VectorBaseInThisSpace::X(), VectorBaseInThisSpace::Y());
        }

        [[nodiscard]] StaticAssert::z_not_supported Z() const noexcept { return StaticAssert::z_not_supported{}; }
        StaticAssert::z_not_supported SetZ(double) const noexcept { return StaticAssert::z_not_supported{}; }

        //-------------------------------------------------------------------------------------
#ifndef IGNORE_SPACE_STATIC_ASSERT
        using VectorBaseInThisSpace::operator*=;
        using VectorBaseInThisSpace::operator-;
        using VectorBaseInThisSpace::operator+=;
        using VectorBaseInThisSpace::operator-=;

        template <int I>
        typename std::enable_if<I != 0 && I != 1, StaticAssert::invalid_at_access>::type at() const {
            return StaticAssert::invalid_at_access{};
        }
        StaticAssert::invalid_XYVector_in_place_cross operator*=(const XYVectorBaseInThisSpace&) noexcept {
            return StaticAssert::invalid_XYVector_in_place_cross{};
        }

        StaticAssert::invalid_vector_to_vector_addition operator+=(const VectorBase<ThisSpace, Implementation>&) noexcept {
            return StaticAssert::invalid_vector_to_vector_addition{};
        }

#endif
    };
}
