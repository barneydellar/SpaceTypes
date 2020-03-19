#pragma once
#include "SpaceImpl.h"
#include "Vector2Base.h"
#include "NormalizedVectorBase.h"

namespace Space {


    template <typename Space, typename ExternalImplementation>
    class NormalizedVector2Base : public virtual NormalizedVectorBase<Space, ExternalImplementation>, public virtual Vector2Base<Space, ExternalImplementation>
    {
        friend class PointBase<Space, ExternalImplementation>;

        using Vector2BaseInThisSpace = Vector2Base<Space, ExternalImplementation>;
        using NormalizedVector2BaseInThisSpace = NormalizedVector2Base<Space, ExternalImplementation>;
        using NormalizedVectorBaseInThisSpace = NormalizedVectorBase<Space, ExternalImplementation>;

    public:

        NormalizedVector2Base(const detail::PointOrVector& p) noexcept(false) { Vector2BaseInThisSpace::m_impl = { p.X(), p.Y(), 0 }; Vector2BaseInThisSpace::m_impl.Normalize(); }
        NormalizedVector2Base() noexcept(false) { Vector2BaseInThisSpace::m_impl = { 1, 0, 0 }; }
        explicit NormalizedVector2Base(const ExternalImplementation& e) noexcept(false) { Vector2BaseInThisSpace::m_impl = { e.X(), e.Y(), 0 }; Vector2BaseInThisSpace::m_impl.Normalize(); }
        explicit NormalizedVector2Base(const double x, const double y) noexcept(false) { Vector2BaseInThisSpace::m_impl = { x, y, 0 }; Vector2BaseInThisSpace::m_impl.Normalize(); }
        NormalizedVector2Base(const std::initializer_list<double> l) noexcept(false) {
            if (l.size() != 2)
            {
                throw std::invalid_argument("You can only initialise with two elements");
            }
            Vector2BaseInThisSpace::m_impl = l;
            Vector2BaseInThisSpace::m_impl.Normalize();
        }

        [[nodiscard]] operator Vector<Space, ExternalImplementation>() const noexcept {
            return Vector<Space, ExternalImplementation>(Vector2BaseInThisSpace::m_impl.X(), Vector2BaseInThisSpace::m_impl.Y(), 0);
        }

        [[nodiscard]] operator Vector2<Space, ExternalImplementation>() const noexcept {
            return Vector2<Space, ExternalImplementation>(Vector2BaseInThisSpace::m_impl.X(), Vector2BaseInThisSpace::m_impl.Y());
        }

        [[nodiscard]] operator NormalizedVector<Space, ExternalImplementation>() const noexcept {
            return NormalizedVector<Space, ExternalImplementation>(Vector2BaseInThisSpace::m_impl.X(), Vector2BaseInThisSpace::m_impl.Y(), 0);
        }

        [[nodiscard]] friend Vector2<Space, ExternalImplementation> operator*(NormalizedVector2BaseInThisSpace lhs, const double& d) noexcept {
            return Vector2<Space, ExternalImplementation>(lhs.m_impl * d);
        }

        using NormalizedVectorBaseInThisSpace::operator*=;

        [[nodiscard]] friend Vector2<Space, ExternalImplementation> operator+(NormalizedVector2BaseInThisSpace lhs, const NormalizedVector2BaseInThisSpace& rhs) noexcept {
            return Vector2<Space, ExternalImplementation>(lhs.m_impl + rhs.m_impl);
        }
        [[nodiscard]] friend Vector2<Space, ExternalImplementation> operator+(Vector2BaseInThisSpace lhs, const NormalizedVector2BaseInThisSpace& rhs) noexcept {
            return Vector2<Space, ExternalImplementation>(lhs.m_impl + rhs.m_impl);
        }
        [[nodiscard]] friend Vector2<Space, ExternalImplementation> operator+(NormalizedVector2BaseInThisSpace lhs, const Vector2BaseInThisSpace& rhs) noexcept {
            return Vector2<Space, ExternalImplementation>(lhs.m_impl + rhs.m_impl);
        }

        using NormalizedVectorBaseInThisSpace::operator+=;

        [[nodiscard]] friend Vector2<Space, ExternalImplementation> operator-(NormalizedVector2BaseInThisSpace lhs, const NormalizedVector2BaseInThisSpace& rhs) noexcept {
            return Vector2<Space, ExternalImplementation>(lhs.m_impl - rhs.m_impl);
        }
        [[nodiscard]] friend Vector2<Space, ExternalImplementation> operator-(Vector2BaseInThisSpace lhs, const NormalizedVector2BaseInThisSpace& rhs) noexcept {
            return Vector2<Space, ExternalImplementation>(lhs.m_impl - rhs.m_impl);
        }
        [[nodiscard]] friend Vector2<Space, ExternalImplementation> operator-(NormalizedVector2BaseInThisSpace lhs, const Vector2BaseInThisSpace& rhs) noexcept {
            return Vector2<Space, ExternalImplementation>(lhs.m_impl - rhs.m_impl);
        }

        using NormalizedVectorBaseInThisSpace::operator-=;

        using NormalizedVectorBaseInThisSpace::Cross;
        [[nodiscard]] NormalizedVector<Space, ExternalImplementation> Cross(const NormalizedVector2BaseInThisSpace& other) const noexcept {
            return NormalizedVector<Space, ExternalImplementation>(Vector2BaseInThisSpace::m_impl.Cross(other.m_impl));
        }

        using NormalizedVectorBaseInThisSpace::operator*;
        using NormalizedVectorBaseInThisSpace::end;
        using NormalizedVectorBaseInThisSpace::Norm;

//        using Vector2BaseInThisSpace::Z;
//        using Vector2BaseInThisSpace::operator[];
//        using Vector2BaseInThisSpace::at;
//
//        [[nodiscard]] friend Vector2<Space, ExternalImplementation> operator*(Vector2BaseInThisSpace lhs, const double& d) noexcept {
//            lhs *= d;
//            return Vector2<Space, ExternalImplementation>(lhs.m_impl);
//        }
//
//        using _base::operator*=;
//        Vector2<Space, ExternalImplementation> operator*=(const double& d) noexcept {
//            _base::m_impl = _base::m_impl * d;
//            return Vector2<Space, ExternalImplementation>(_base::m_impl);
//        }
//
//        using _base::operator*;
//        [[nodiscard]] Vector<Space, ExternalImplementation> operator*(const Vector2BaseInThisSpace& rhs) const noexcept {
//            return this->Cross(rhs);
//        }
//
//        using _base::Cross;
//        [[nodiscard]] Vector<Space, ExternalImplementation> Cross(const Vector2BaseInThisSpace& other) const noexcept {
//            return Vector<Space, ExternalImplementation>(_base::m_impl.Cross(other._base::m_impl));
//        }
//
//        [[nodiscard]] friend Vector2<Space, ExternalImplementation> operator-(Vector2BaseInThisSpace lhs, const Vector2BaseInThisSpace& rhs) noexcept {
//            lhs -= rhs;
//            return Vector2<Space, ExternalImplementation>(lhs.m_impl);
//        }
//
//        using _base::operator-=;
//        Vector2<Space, ExternalImplementation> operator-=(const Vector2BaseInThisSpace& rhs) noexcept {
//            _base::m_impl = _base::m_impl - rhs.m_impl;
//            return Vector2<Space, ExternalImplementation>(_base::m_impl);
//        }
//
//        [[nodiscard]] friend Vector2<Space, ExternalImplementation> operator+(Vector2BaseInThisSpace lhs, const Vector2BaseInThisSpace& rhs) noexcept {
//            lhs += rhs;
//            return Vector2<Space, ExternalImplementation>(lhs.m_impl);
//        }
//
//        using _base::operator+=;
//        Vector2<Space, ExternalImplementation> operator+=(const Vector2BaseInThisSpace& rhs) noexcept {
//            _base::m_impl = _base::m_impl + rhs.m_impl;
//            return Vector2<Space, ExternalImplementation>(_base::m_impl);
//        }
//
//        //[[nodiscard]] NormalizedVector<Space, ExternalImplementation> Norm() const {
//        //    return NormalizedVector<Space, ExternalImplementation>(_base::m_impl);
//        //}
//
//        //-------------------------------------------------------------------------------------
//#ifndef IGNORE_SPACE_STATIC_ASSERT
//
//        template <int I>
//        typename std::enable_if<I != 0 && I != 1, StaticAssert::invalid_at_access>::type at() const {
//            return StaticAssert::invalid_at_access{};
//        }
//        StaticAssert::invalid_vector2_in_place_cross operator*=(const Vector2BaseInThisSpace& other) noexcept {
//            return StaticAssert::invalid_vector2_in_place_cross{};
//        }
//
//#endif
    };
}
