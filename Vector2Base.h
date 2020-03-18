#pragma once
#include "SpaceImpl.h"
#include "PointBase.h"
#include "Base.h"

namespace Space {

    template <typename Space, typename ExternalImplementation>
    class PointBase;


    template <typename Space, typename ExternalImplementation>
    class Vector2Base : public VectorBase<Space, ExternalImplementation>
    {
        friend class PointBase<Space, ExternalImplementation>;

        using Vector2BaseInThisSpace = Vector2Base<Space, ExternalImplementation>;
        using Vector2InThisSpace = Vector2<Space, ExternalImplementation>;
        using VectorInThisSpace = VectorInASpace<Space>;
        using NormalizedVectorInThisSpace = NormalizedVectorInASpace<Space>;

    public:

        using _base = VectorBase<Space, ExternalImplementation>;

        Vector2Base(const detail::PointOrVector& v) noexcept { _base::m_impl = { v.X(), v.Y(), 0 }; }
        constexpr Vector2Base() noexcept { _base::m_impl = { 0, 0, 0 }; }
        constexpr explicit Vector2Base(const ExternalImplementation& v) noexcept { _base::m_impl = { v.X(), v.Y(), 0 }; }
        constexpr explicit Vector2Base(const double x, const double y) noexcept { _base::m_impl = { x, y, 0 }; }
        constexpr Vector2Base(const std::initializer_list<double> l)
        {
            if (l.size() != 2)
            {
                throw std::invalid_argument("You can only initialise with two elements");
            }
            _base::m_impl = l;
        }

        [[nodiscard]] operator Vector<Space, ExternalImplementation>() const noexcept {
            return Vector<Space, ExternalImplementation>(_base::m_impl.X(), _base::m_impl.Y(), _base::m_impl.Z());
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

        [[nodiscard]] friend Vector2InThisSpace operator*(Vector2BaseInThisSpace lhs, const double& d) noexcept {
            lhs *= d;
            return Vector2InThisSpace(lhs._base::m_impl);
        }

        using _base::operator*=;
        Vector2InThisSpace operator*=(const double& d) noexcept {
            _base::m_impl = _base::m_impl * d;
            return Vector2InThisSpace(_base::m_impl);
        }

        using _base::operator*;
        [[nodiscard]] VectorInThisSpace operator*(const Vector2BaseInThisSpace& rhs) const noexcept {
            return this->Cross(rhs);
        }

        using _base::Cross;
        [[nodiscard]] VectorInThisSpace Cross(const Vector2BaseInThisSpace& other) const noexcept {
            return VectorInThisSpace(_base::m_impl.Cross(other._base::m_impl));
        }

        using _base::operator-;
        [[nodiscard]] friend Vector2InThisSpace operator-(Vector2BaseInThisSpace lhs, const Vector2BaseInThisSpace& rhs) noexcept {
            lhs -= rhs;
            return Vector2InThisSpace(lhs._base::m_impl);
        }

        using _base::operator-=;
        Vector2InThisSpace operator-=(const Vector2BaseInThisSpace& rhs) noexcept {
            _base::m_impl = _base::m_impl - rhs._base::m_impl;
            return Vector2InThisSpace(_base::m_impl);
        }

        using _base::operator+;
        [[nodiscard]] friend Vector2InThisSpace operator+(Vector2BaseInThisSpace lhs, const Vector2BaseInThisSpace& rhs) noexcept {
            lhs += rhs;
            return Vector2InThisSpace(lhs.m_impl);
        }

        using _base::operator+=;
        Vector2InThisSpace operator+=(const Vector2BaseInThisSpace& rhs) noexcept {
            _base::m_impl = _base::m_impl + rhs._base::m_impl;
            return Vector2InThisSpace(_base::m_impl);
        }

        //[[nodiscard]] NormalizedVectorInThisSpace Norm() const {
        //    return NormalizedVectorInThisSpace(_base::m_impl);
        //}

        //-------------------------------------------------------------------------------------
#ifndef IGNORE_SPACE_STATIC_ASSERT

        template <int I>
        typename std::enable_if<I != 0 && I != 1, StaticAssert::invalid_at_access>::type at() const {
            return StaticAssert::invalid_at_access{};
        }

        StaticAssert::invalid_vector2_in_place_cross operator*=(const Vector2BaseInThisSpace& other) noexcept {
            return StaticAssert::invalid_vector2_in_place_cross{};
        }

#endif
    };
}
