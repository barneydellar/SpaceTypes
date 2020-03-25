#pragma once

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class NormalizedVector2Base : public Vector2Base<ThisSpace, Implementation>, public NormalizedVectorBase<ThisSpace, Implementation>
    {
        using Vector2BaseInThisSpace = Vector2Base<ThisSpace, Implementation>;
        using NormalizedVector2BaseInThisSpace = NormalizedVector2Base<ThisSpace, Implementation>;
        using NormalizedVectorBaseInThisSpace = NormalizedVectorBase<ThisSpace, Implementation>;

    public:

        NormalizedVector2Base() noexcept(false) : Vector2BaseInThisSpace() { *Vector2BaseInThisSpace::begin() = 1; }
        explicit NormalizedVector2Base(const Implementation& e) noexcept(false) : Vector2BaseInThisSpace(e), NormalizedVectorBaseInThisSpace(e) { }
        explicit NormalizedVector2Base(const double x, const double y) noexcept(false) { Vector2BaseInThisSpace::m_impl = { x, y, 0 }; NormalizedVector2BaseInThisSpace::Normalize(); }
        NormalizedVector2Base(const std::initializer_list<double> l) noexcept(false) {
            if (l.size() != 2)
            {
                throw std::invalid_argument("You can only initialise with two elements");
            }
            Vector2BaseInThisSpace::m_impl = l;
            NormalizedVector2BaseInThisSpace::Normalize();
        }

        [[nodiscard]] operator Vector<ThisSpace, Implementation>() const noexcept {
            return Vector<ThisSpace, Implementation>(Vector2BaseInThisSpace::X(), Vector2BaseInThisSpace::Y(), 0);
        }

        [[nodiscard]] operator Vector2<ThisSpace, Implementation>() const noexcept {
            return Vector2<ThisSpace, Implementation>(Vector2BaseInThisSpace::X(), Vector2BaseInThisSpace::Y());
        }

        [[nodiscard]] operator NormalizedVector<ThisSpace, Implementation>() const noexcept {
            return NormalizedVector<ThisSpace, Implementation>(Vector2BaseInThisSpace::X(), Vector2BaseInThisSpace::Y(), 0);
        }

        using NormalizedVectorBaseInThisSpace::operator*;
        using NormalizedVectorBaseInThisSpace::operator*=;
        [[nodiscard]] friend Vector2<ThisSpace, Implementation> operator*(NormalizedVector2<ThisSpace, Implementation> lhs, const double& d) noexcept {
            lhs.Scale(d);
            return lhs;
        }

        using NormalizedVectorBaseInThisSpace::operator-=;
        using NormalizedVectorBaseInThisSpace::operator-;
        // Is this needed? TODO
        [[nodiscard]] friend Vector2<ThisSpace, Implementation> operator-(NormalizedVector2<ThisSpace, Implementation> lhs, const NormalizedVector2BaseInThisSpace& rhs) noexcept {
            lhs.Sub(rhs);
            return lhs;
        }
        [[nodiscard]] friend Vector2<ThisSpace, Implementation> operator-(NormalizedVector2<ThisSpace, Implementation> lhs, const Vector2BaseInThisSpace& rhs) noexcept {
            lhs.Sub(rhs);
            return lhs;
        }
        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator-(NormalizedVector2<ThisSpace, Implementation> lhs, const VectorBase<ThisSpace, Implementation>& rhs) noexcept {
            lhs.Sub(rhs);
            return lhs;
        }

        using NormalizedVectorBaseInThisSpace::operator+=;
        using NormalizedVectorBaseInThisSpace::operator+;
        [[nodiscard]] friend Vector2<ThisSpace, Implementation> operator+(NormalizedVector2<ThisSpace, Implementation> lhs, const NormalizedVector2<ThisSpace, Implementation>& rhs) noexcept {
            lhs.Add(rhs);
            return lhs;
        }
        [[nodiscard]] friend Vector2<ThisSpace, Implementation> operator+(NormalizedVector2<ThisSpace, Implementation> lhs, const Vector2<ThisSpace, Implementation>& rhs) noexcept {
            lhs.Add(rhs);
            return lhs;
        }
        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator+(NormalizedVector2<ThisSpace, Implementation> lhs, const VectorBase<ThisSpace, Implementation>& rhs) noexcept {
            lhs.Add(rhs);
            return lhs;
        }

        using NormalizedVectorBaseInThisSpace::Cross;
        [[nodiscard]] NormalizedVector<ThisSpace, Implementation> Cross(const NormalizedVector2BaseInThisSpace& other) const noexcept {
            return NormalizedVector<ThisSpace, Implementation>(Vector2BaseInThisSpace::Cross(other).Norm());
        }

        using NormalizedVectorBaseInThisSpace::end;
        using NormalizedVectorBaseInThisSpace::Norm;
    };
}
