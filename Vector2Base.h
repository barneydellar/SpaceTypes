#pragma once
#include "SpaceImpl.h"
#include "PointBase.h"
#include "Base.h"
#include "NormalizedVector2Base.h"

namespace Space {

    template <typename Space, typename ExternalImplementation>
    class PointBase;


    template <typename Space, typename ExternalImplementation>
    class Vector2Base : public virtual VectorBase<Space, ExternalImplementation>
    {
        using Vector2BaseInThisSpace = Vector2Base<Space, ExternalImplementation>;
        using VectorBaseInThisSpace = VectorBase<Space, ExternalImplementation>;

    public:

        Vector2Base() noexcept { VectorBaseInThisSpace::m_impl = { 0, 0, 0 }; }
        explicit Vector2Base(const ExternalImplementation& v) noexcept { VectorBaseInThisSpace::m_impl = { v.X(), v.Y(), 0 }; }
        explicit Vector2Base(const double x, const double y) noexcept { VectorBaseInThisSpace::m_impl = { x, y, 0 }; }
        Vector2Base(const std::initializer_list<double> l)
        {
            if (l.size() != 2)
            {
                throw std::invalid_argument("You can only initialise with two elements");
            }
            VectorBaseInThisSpace::m_impl = l;
        }

        [[nodiscard]] operator Vector<Space, ExternalImplementation>() const noexcept {
            return Vector<Space, ExternalImplementation>(VectorBaseInThisSpace::m_impl.X(), VectorBaseInThisSpace::m_impl.Y(), VectorBaseInThisSpace::m_impl.Z());
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
            return reinterpret_cast<const double*>(std::prev(VectorBaseInThisSpace::m_impl.cend()));
        }

        [[nodiscard]] double* end() noexcept
        {
            return reinterpret_cast<double*>(std::prev(VectorBaseInThisSpace::m_impl.end()));
        }

        template <int I>
        [[nodiscard]] typename std::enable_if<I == 0 || I == 1, double>::type at() const {
            return VectorBaseInThisSpace::m_impl[I];
        }

        [[nodiscard]] friend Vector2<Space, ExternalImplementation> operator*(Vector2BaseInThisSpace lhs, const double& d) noexcept {
            lhs *= d;
            return Vector2<Space, ExternalImplementation>(lhs.VectorBaseInThisSpace::m_impl);
        }

        using VectorBaseInThisSpace::operator*=;
        Vector2<Space, ExternalImplementation> operator*=(const double& d) noexcept {
            VectorBaseInThisSpace::m_impl = VectorBaseInThisSpace::m_impl * d;
            return Vector2<Space, ExternalImplementation>(VectorBaseInThisSpace::m_impl);
        }

        using VectorBaseInThisSpace::operator*;
        [[nodiscard]] Vector<Space, ExternalImplementation> operator*(const Vector2BaseInThisSpace& rhs) const noexcept {
            return this->Cross(rhs);
        }

        using VectorBaseInThisSpace::Cross;
        [[nodiscard]] Vector<Space, ExternalImplementation> Cross(const Vector2BaseInThisSpace& other) const noexcept {
            return Vector<Space, ExternalImplementation>(VectorBaseInThisSpace::m_impl.Cross(other.VectorBaseInThisSpace::m_impl));
        }

        [[nodiscard]] friend Vector2<Space, ExternalImplementation> operator-(Vector2BaseInThisSpace lhs, const Vector2BaseInThisSpace& rhs) noexcept {
            lhs -= rhs;
            return Vector2<Space, ExternalImplementation>(lhs.VectorBaseInThisSpace::m_impl);
        }

        using VectorBaseInThisSpace::operator-=;
        Vector2<Space, ExternalImplementation> operator-=(const Vector2BaseInThisSpace& rhs) noexcept {
            VectorBaseInThisSpace::m_impl = VectorBaseInThisSpace::m_impl - rhs.VectorBaseInThisSpace::m_impl;
            return Vector2<Space, ExternalImplementation>(VectorBaseInThisSpace::m_impl);
        }

        [[nodiscard]] friend Vector2<Space, ExternalImplementation> operator+(Vector2BaseInThisSpace lhs, const Vector2BaseInThisSpace& rhs) noexcept {
            lhs += rhs;
            return Vector2<Space, ExternalImplementation>(lhs.m_impl);
        }

        using VectorBaseInThisSpace::operator+=;
        Vector2<Space, ExternalImplementation> operator+=(const Vector2BaseInThisSpace& rhs) noexcept {
            VectorBaseInThisSpace::m_impl = VectorBaseInThisSpace::m_impl + rhs.VectorBaseInThisSpace::m_impl;
            return Vector2<Space, ExternalImplementation>(VectorBaseInThisSpace::m_impl);
        }

        [[nodiscard]] NormalizedVector2<Space, ExternalImplementation> Norm() const {
            return NormalizedVector2<Space, ExternalImplementation>(VectorBaseInThisSpace::m_impl);
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

#endif
    };
}
