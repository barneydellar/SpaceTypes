#pragma once
#include "SpaceImpl.h"
#include "PointBase.h"
#include "VectorBase.h"
#include "Vector2Base.h"

namespace Space {

    template <typename Space, typename ExternalImplementation>
    class Point2Base : public PointBase<Space, ExternalImplementation>
    {
        using Point2BaseInThisSpace = Point2Base<Space, ExternalImplementation>;
        using Vector2BaseInThisSpace = Vector2Base<Space, ExternalImplementation>;
        using VectorBaseInThisSpace = VectorBase<Space, ExternalImplementation>;
        using PointBaseInThisSpace = PointBase<Space, ExternalImplementation>;

    public:

        Point2Base() noexcept { PointBaseInThisSpace::m_impl = { 0, 0, 0 }; }
        explicit Point2Base(const ExternalImplementation& v) noexcept { PointBaseInThisSpace::m_impl = { v.X(), v.Y(), 0 }; }
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
            return reinterpret_cast<const double*>(std::prev(PointBaseInThisSpace::m_impl.cend()));
        }

        [[nodiscard]] double* end() noexcept
        {
            return reinterpret_cast<double*>(std::prev(PointBaseInThisSpace::m_impl.end()));
        }

        [[nodiscard]] operator Point<Space, ExternalImplementation>() const noexcept {
            return Point<Space, ExternalImplementation>(PointBaseInThisSpace::m_impl.X(), PointBaseInThisSpace::m_impl.Y(), PointBaseInThisSpace::m_impl.Z());
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
            return PointBaseInThisSpace::m_impl[I];
        }

        [[nodiscard]] friend Vector2<Space, ExternalImplementation> operator-(Point2BaseInThisSpace lhs, const Point2BaseInThisSpace& rhs) {
            return Vector2<Space, ExternalImplementation>(static_cast<ExternalImplementation>(lhs) - static_cast<ExternalImplementation>(rhs));
        }

        [[nodiscard]] friend Point2<Space, ExternalImplementation> operator+(Point2BaseInThisSpace lhs, const Point2BaseInThisSpace& rhs) noexcept {
            lhs.m_impl += rhs.m_impl;
            return Point2<Space, ExternalImplementation>(static_cast<ExternalImplementation>(lhs));
        }

        using PointBaseInThisSpace::operator+=;
        Point2<Space, ExternalImplementation> operator+=(const Vector2<Space, ExternalImplementation>& rhs) noexcept {
            PointBaseInThisSpace::m_impl = PointBaseInThisSpace::m_impl + static_cast<ExternalImplementation>(rhs);
            return Point2<Space, ExternalImplementation>(PointBaseInThisSpace::m_impl);
        }

        [[nodiscard]] friend Point2<Space, ExternalImplementation> operator-(Point2BaseInThisSpace lhs, const Vector2BaseInThisSpace& rhs) noexcept {
            return Point2<Space, ExternalImplementation>(static_cast<ExternalImplementation>(lhs) - static_cast<ExternalImplementation>(rhs));
        }

        using PointBaseInThisSpace::operator-=;
        Point2<Space, ExternalImplementation> operator-=(const Vector2<Space, ExternalImplementation>& rhs) noexcept {
            PointBaseInThisSpace::m_impl = PointBaseInThisSpace::m_impl - static_cast<ExternalImplementation>(rhs);
            return Point2<Space, ExternalImplementation>(PointBaseInThisSpace::m_impl);
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
