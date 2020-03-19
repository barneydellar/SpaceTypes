#pragma once
#include "SpaceImpl.h"
#include "Vector2Base.h"
#include "NormalizedVectorBase.h"

namespace Space {


    template <typename Space, typename ExternalImplementation>
    class NormalizedVector2Base : public virtual NormalizedVectorBase<Space, ExternalImplementation>, public virtual Vector2Base<Space, ExternalImplementation>
    {
        using Vector2BaseInThisSpace = Vector2Base<Space, ExternalImplementation>;
        using NormalizedVector2BaseInThisSpace = NormalizedVector2Base<Space, ExternalImplementation>;
        using NormalizedVectorBaseInThisSpace = NormalizedVectorBase<Space, ExternalImplementation>;

    public:

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
            return Vector2<Space, ExternalImplementation>(static_cast<ExternalImplementation>(lhs) + static_cast<ExternalImplementation>(rhs));
        }
        [[nodiscard]] friend Vector2<Space, ExternalImplementation> operator+(Vector2BaseInThisSpace lhs, const NormalizedVector2BaseInThisSpace& rhs) noexcept {
            return Vector2<Space, ExternalImplementation>(static_cast<ExternalImplementation>(lhs) + static_cast<ExternalImplementation>(rhs));
        }
        [[nodiscard]] friend Vector2<Space, ExternalImplementation> operator+(NormalizedVector2BaseInThisSpace lhs, const Vector2BaseInThisSpace& rhs) noexcept {
            return Vector2<Space, ExternalImplementation>(static_cast<ExternalImplementation>(lhs) + static_cast<ExternalImplementation>(rhs));
        }

        using NormalizedVectorBaseInThisSpace::operator+=;

        [[nodiscard]] friend Vector2<Space, ExternalImplementation> operator-(NormalizedVector2BaseInThisSpace lhs, const NormalizedVector2BaseInThisSpace& rhs) noexcept {
            return Vector2<Space, ExternalImplementation>(static_cast<ExternalImplementation>(lhs) - static_cast<ExternalImplementation>(rhs));
        }
        [[nodiscard]] friend Vector2<Space, ExternalImplementation> operator-(Vector2BaseInThisSpace lhs, const NormalizedVector2BaseInThisSpace& rhs) noexcept {
            return Vector2<Space, ExternalImplementation>(static_cast<ExternalImplementation>(lhs) - static_cast<ExternalImplementation>(rhs));
        }
        [[nodiscard]] friend Vector2<Space, ExternalImplementation> operator-(NormalizedVector2BaseInThisSpace lhs, const Vector2BaseInThisSpace& rhs) noexcept {
            return Vector2<Space, ExternalImplementation>(static_cast<ExternalImplementation>(lhs) - static_cast<ExternalImplementation>(rhs));
        }

        using NormalizedVectorBaseInThisSpace::operator-=;

        using NormalizedVectorBaseInThisSpace::Cross;
        [[nodiscard]] NormalizedVector<Space, ExternalImplementation> Cross(const NormalizedVector2BaseInThisSpace& other) const noexcept {
            return NormalizedVector<Space, ExternalImplementation>(Vector2BaseInThisSpace::m_impl.Cross(other.m_impl));
        }

        using NormalizedVectorBaseInThisSpace::operator*;
        using NormalizedVectorBaseInThisSpace::end;
        using NormalizedVectorBaseInThisSpace::Norm;


    };
}
