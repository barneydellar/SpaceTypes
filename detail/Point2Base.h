#pragma once

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class Point2Base : public PointBase<ThisSpace, Implementation>
    {
        using Point2BaseInThisSpace = Point2Base<ThisSpace, Implementation>;
        using Vector2BaseInThisSpace = Vector2Base<ThisSpace, Implementation>;
        using VectorBaseInThisSpace = VectorBase<ThisSpace, Implementation>;
        using PointBaseInThisSpace = PointBase<ThisSpace, Implementation>;

    public:

        Point2Base() noexcept { PointBaseInThisSpace::m_impl = { 0, 0, 0 }; }
        explicit Point2Base(const Implementation& v) noexcept { PointBaseInThisSpace::m_impl = { v.m_values[0], v.m_values[1], 0 }; }
        explicit Point2Base(const double x, const double y) noexcept {PointBaseInThisSpace::m_impl = { x, y, 0 };}
        Point2Base(const std::initializer_list<double> l)
        {
            if (l.size() != 2)
            {
                throw std::invalid_argument("You can only initialise with two elements");
            }
            PointBaseInThisSpace::m_impl = l;
        }

        [[nodiscard]] const double* cend() const noexcept
        {
            return reinterpret_cast<const double*>(std::prev(PointBaseInThisSpace::cend()));
        }

        [[nodiscard]] double* end() noexcept
        {
            return reinterpret_cast<double*>(std::prev(PointBaseInThisSpace::end()));
        }

        [[nodiscard]] operator Point<ThisSpace, Implementation>() const noexcept {
            return Point<ThisSpace, Implementation>(PointBaseInThisSpace::X(), PointBaseInThisSpace::Y(), PointBaseInThisSpace::Z());
        }

        [[nodiscard]] StaticAssert::z_not_supported Z() const noexcept { return StaticAssert::z_not_supported{}; }

        double operator[](const unsigned int i) const
        {
            if (i > 1) {
                throw std::invalid_argument("Index is out of range");
            }
            return PointBaseInThisSpace::operator[](i);
        }

        template <int I>
        [[nodiscard]] typename std::enable_if<I == 0 || I == 1, double>::type at() const {
            return PointBaseInThisSpace::operator[](I);
        }

        [[nodiscard]] friend Vector2<ThisSpace, Implementation> operator-(Point2BaseInThisSpace lhs, const Point2BaseInThisSpace& rhs) {
            return Vector2<ThisSpace, Implementation>(static_cast<Implementation>(lhs) - static_cast<Implementation>(rhs));
        }

        using PointBaseInThisSpace::operator+=;

        [[nodiscard]] friend Point2<ThisSpace, Implementation> operator-(Point2BaseInThisSpace lhs, const Vector2BaseInThisSpace& rhs) noexcept {
            return Point2<ThisSpace, Implementation>(static_cast<Implementation>(lhs) - static_cast<Implementation>(rhs));
        }

        using PointBaseInThisSpace::operator-=;
        Point2<ThisSpace, Implementation> operator-=(const Vector2<ThisSpace, Implementation>& rhs) noexcept {
            PointBaseInThisSpace::m_impl = PointBaseInThisSpace::m_impl - static_cast<Implementation>(rhs);
            return Point2<ThisSpace, Implementation>(PointBaseInThisSpace::m_impl);
        }

        //------------------------------------------------------------------------------------

#ifndef IGNORE_SPACE_STATIC_ASSERT

        template <int I>
        typename std::enable_if<I != 0 && I != 1, StaticAssert::invalid_at_access>::type at() const {
            return StaticAssert::invalid_at_access{};
        }

        StaticAssert::invalid_vector3_to_point2_addition operator+=(const VectorBaseInThisSpace&) noexcept {
            return StaticAssert::invalid_vector3_to_point2_addition{};
        }

        StaticAssert::invalid_vector3_from_point2_subtraction operator-=(const VectorBaseInThisSpace&) noexcept {
            return StaticAssert::invalid_vector3_from_point2_subtraction{};
        }
#endif

    };

}
