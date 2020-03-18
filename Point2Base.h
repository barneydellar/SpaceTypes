#pragma once
#include "SpaceImpl.h"
#include "PointBase.h"
#include "VectorBase.h"
#include "Vector2Base.h"

namespace Space {

    template <typename Space, typename ExternalImplementation>
    class Point2Base : public PointBase<Space, ExternalImplementation>
    {
        friend class NormalizedVector<Space, ExternalImplementation>;
        friend class Vector<Space, ExternalImplementation>;

        using Point2BaseInThisSpace = Point2Base<Space, ExternalImplementation>;
        using Vector2BaseInThisSpace = Vector2Base<Space, ExternalImplementation>;
        using VectorBaseInThisSpace = VectorBase<Space, ExternalImplementation>;

        using Point2InThisSpace = Point2<Space, ExternalImplementation>;
        using Vector2InThisSpace = Vector2<Space, ExternalImplementation>;
        using VectorInThisSpace = Vector<Space, ExternalImplementation>;

    public:

        using _base = PointBase<Space, ExternalImplementation>;

        Point2Base(const detail::PointOrVector& v) noexcept { _base::m_impl = { v.X(), v.Y(), 0 }; }
        constexpr Point2Base() noexcept { _base::m_impl = { 0, 0, 0 }; }
        constexpr explicit Point2Base(const ExternalImplementation& v) noexcept { _base::m_impl = { v.X(), v.Y(), 0 }; }
        constexpr explicit Point2Base(const double x, const double y) noexcept {_base::m_impl = { x, y, 0 };}
        constexpr Point2Base(const std::initializer_list<double> l)
        {
            if (l.size() != 2)
            {
                throw std::invalid_argument("You can only initialise with two elements");
            }
            _base::m_impl = l;
        }


        [[nodiscard]] operator Point<Space, ExternalImplementation>() const noexcept {
            return Point<Space, ExternalImplementation>(_base::m_impl.X(), _base::m_impl.Y(), _base::m_impl.Z());
        }

        [[nodiscard]] StaticAssert::z_not_supported Z() const noexcept { return StaticAssert::z_not_supported{}; }

        double operator[](const unsigned int i) const
        {
            if (i > 1) {
                throw std::invalid_argument("Index is out of range");
            }
            return _base::operator[](i);
        }

        template <int I>
        [[nodiscard]] typename std::enable_if<I == 0 || I == 1, double>::type at() const {
            return _base::m_impl[I];
        }

        [[nodiscard]] friend Vector2InThisSpace operator-(Point2BaseInThisSpace lhs, const Point2BaseInThisSpace& rhs) {
            return Vector2InThisSpace(lhs.m_impl - rhs.m_impl);
        }

        [[nodiscard]] friend Point2InThisSpace operator+(Point2BaseInThisSpace lhs, const Point2BaseInThisSpace& rhs) noexcept {
            lhs.m_impl += rhs.m_impl;
            return Point2InThisSpace(lhs.m_impl);
        }
/*
        Point2InThisSpace operator+=(const Vector2InThisSpace& rhs) noexcept {
            _base::m_impl = _base::m_impl + rhs.m_impl;
            return Point2InThisSpace(_base::m_impl);
        }*/

        [[nodiscard]] friend Point2InThisSpace operator-(Point2BaseInThisSpace lhs, const Vector2BaseInThisSpace& rhs) noexcept {
            return Point2InThisSpace(lhs.m_impl - rhs.m_impl);
        }
/*
        Point2InThisSpace operator-=(const Vector2InThisSpace& rhs) noexcept {
            _base::m_impl = _base::m_impl - rhs.m_impl;
            return Point2InThisSpace(_base::m_impl);
        }*/

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
