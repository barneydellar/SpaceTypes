#pragma once

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class Point2Base : public PointBase<ThisSpace, Implementation>
    {
        using Point2BaseInThisSpace = Point2Base<ThisSpace, Implementation>;
        using XYVectorBaseInThisSpace = XYVectorBase<ThisSpace, Implementation>;
        using VectorBaseInThisSpace = VectorBase<ThisSpace, Implementation>;
        using PointBaseInThisSpace = PointBase<ThisSpace, Implementation>;

    public:

        Point2Base() noexcept : PointBaseInThisSpace() {}
        explicit Point2Base(const Implementation& v) noexcept : PointBaseInThisSpace(v) {*(std::prev(PointBaseInThisSpace::end())) = 0;}
        explicit Point2Base(const double x, const double y) noexcept
        {
            auto iter = PointBaseInThisSpace::begin();
            *iter++ = x;
            *iter++ = y;
            *iter = 0;
        }
        Point2Base(const std::initializer_list<double>& l)
        {
            if (l.size() != 2)
            {
                throw std::invalid_argument("You can only initialise with two elements");
            }
            std::copy(
                std::cbegin(l),
                std::cend(l),
                PointBaseInThisSpace::begin()
            );
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

        using PointBaseInThisSpace::operator-=;
        [[nodiscard]] friend XYVector<ThisSpace, Implementation> operator-(Point2BaseInThisSpace lhs, const Point2BaseInThisSpace& rhs) {
            lhs.Sub(rhs);
            XYVector<ThisSpace, Implementation> v(lhs.X(), lhs.Y());
            return v;
        }

        [[nodiscard]] friend Point2<ThisSpace, Implementation> operator-(Point2<ThisSpace, Implementation> lhs, const XYVectorBase<ThisSpace, Implementation>& rhs) noexcept {
            lhs.Sub(rhs);
            return lhs;
        }

        [[nodiscard]] friend Point<ThisSpace, Implementation> operator-(Point2<ThisSpace, Implementation> lhs, const VectorBase<ThisSpace, Implementation>& rhs) noexcept {
            lhs.Sub(rhs);
            Point<ThisSpace, Implementation> point3(lhs.X(), lhs.Y(), 0);
            return point3;
        }

        using PointBaseInThisSpace::operator+=;

        [[nodiscard]] friend Point<ThisSpace, Implementation> operator+(Point2<ThisSpace, Implementation> lhs, const VectorBase<ThisSpace, Implementation>& rhs) noexcept {
            Point<ThisSpace, Implementation> point3(lhs.X(), lhs.Y(), 0);
            point3 += rhs;
            return point3;
        }

        [[nodiscard]] friend Point2<ThisSpace, Implementation> operator+(Point2<ThisSpace, Implementation> lhs, const XYVectorBase<ThisSpace, Implementation>& rhs) noexcept {
            lhs += rhs;
            return lhs;
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
