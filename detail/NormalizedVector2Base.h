#pragma once

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class NormalizedVector2Base : public Vector2Base<ThisSpace, Implementation>, public NormalizedVectorBase<ThisSpace, Implementation>
    {
        using Vector2BaseInThisSpace = Vector2Base<ThisSpace, Implementation>;
        using NormalizedVector2BaseInThisSpace = NormalizedVector2Base<ThisSpace, Implementation>;
        using NormalizedVectorBaseInThisSpace = NormalizedVectorBase<ThisSpace, Implementation>;

    public:

        NormalizedVector2Base() noexcept(false) : Vector2BaseInThisSpace(), NormalizedVectorBaseInThisSpace() { }
        explicit NormalizedVector2Base(const Implementation& e) noexcept(false) : Vector2BaseInThisSpace(e), NormalizedVectorBaseInThisSpace(e) { }
        explicit NormalizedVector2Base(const double x, const double y) noexcept(false) : Vector2BaseInThisSpace(x, y), NormalizedVectorBaseInThisSpace(x, y, 0) {}
        NormalizedVector2Base(const std::initializer_list<double> l) noexcept(false) : Vector2BaseInThisSpace(l), NormalizedVectorBaseInThisSpace(l) { }

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
