#pragma once

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class NormalizedXYVectorBase : public XYVectorBase<ThisSpace, Implementation>, public NormalizedVectorBase<ThisSpace, Implementation>
    {
        using XYVectorBaseInThisSpace = XYVectorBase<ThisSpace, Implementation>;
        using NormalizedXYVectorBaseInThisSpace = NormalizedXYVectorBase<ThisSpace, Implementation>;
        using NormalizedVectorBaseInThisSpace = NormalizedVectorBase<ThisSpace, Implementation>;

    public:

        NormalizedXYVectorBase() noexcept(false) : XYVectorBaseInThisSpace(), NormalizedVectorBaseInThisSpace() { }
        explicit NormalizedXYVectorBase(const Implementation& e) noexcept(false) : XYVectorBaseInThisSpace(e), NormalizedVectorBaseInThisSpace(e) { }
        explicit NormalizedXYVectorBase(const double x, const double y) noexcept(false) : XYVectorBaseInThisSpace(x, y), NormalizedVectorBaseInThisSpace(x, y, 0) {}
        NormalizedXYVectorBase(const std::initializer_list<double> l) noexcept(false) : XYVectorBaseInThisSpace(l), NormalizedVectorBaseInThisSpace(l) { }

        [[nodiscard]] operator Vector<ThisSpace, Implementation>() const noexcept {
            return Vector<ThisSpace, Implementation>(XYVectorBaseInThisSpace::X(), XYVectorBaseInThisSpace::Y(), 0);
        }

        [[nodiscard]] operator XYVector<ThisSpace, Implementation>() const noexcept {
            return XYVector<ThisSpace, Implementation>(XYVectorBaseInThisSpace::X(), XYVectorBaseInThisSpace::Y());
        }

        [[nodiscard]] operator NormalizedVector<ThisSpace, Implementation>() const noexcept {
            return NormalizedVector<ThisSpace, Implementation>(XYVectorBaseInThisSpace::X(), XYVectorBaseInThisSpace::Y(), 0);
        }

        using NormalizedVectorBaseInThisSpace::operator*;
        [[nodiscard]] friend XYVector<ThisSpace, Implementation> operator*(NormalizedXYVector<ThisSpace, Implementation> lhs, const double& d) noexcept {
            lhs.Scale(d);
            return lhs;
        }

        [[nodiscard]] friend XYVector<ThisSpace, Implementation> operator-(NormalizedXYVector<ThisSpace, Implementation> lhs, const XYVectorBaseInThisSpace& rhs) noexcept {
            lhs.Sub(rhs);
            return lhs;
        }
        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator-(NormalizedXYVector<ThisSpace, Implementation> lhs, const VectorBase<ThisSpace, Implementation>& rhs) noexcept {
            lhs.Sub(rhs);
            return lhs;
        }

        [[nodiscard]] friend XYVector<ThisSpace, Implementation> operator+(NormalizedXYVector<ThisSpace, Implementation> lhs, const NormalizedXYVector<ThisSpace, Implementation>& rhs) noexcept {
            lhs.Add(rhs);
            return lhs;
        }
        [[nodiscard]] friend XYVector<ThisSpace, Implementation> operator+(NormalizedXYVector<ThisSpace, Implementation> lhs, const XYVector<ThisSpace, Implementation>& rhs) noexcept {
            lhs.Add(rhs);
            return lhs;
        }
        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator+(NormalizedXYVector<ThisSpace, Implementation> lhs, const VectorBase<ThisSpace, Implementation>& rhs) noexcept {
            lhs.Add(rhs);
            return lhs;
        }

        using NormalizedVectorBaseInThisSpace::Cross;
        [[nodiscard]] NormalizedVector<ThisSpace, Implementation> Cross(const NormalizedXYVectorBaseInThisSpace& other) const noexcept {
            return NormalizedVector<ThisSpace, Implementation>(XYVectorBaseInThisSpace::Cross(other).Norm());
        }

        using NormalizedVectorBaseInThisSpace::end;

#ifndef IGNORE_SPACE_STATIC_ASSERT

        using NormalizedVectorBaseInThisSpace::operator*=;
        using NormalizedVectorBaseInThisSpace::operator-=;
        using NormalizedVectorBaseInThisSpace::operator-;
        using NormalizedVectorBaseInThisSpace::operator+=;
        using NormalizedVectorBaseInThisSpace::operator+;

#endif
    };
}
