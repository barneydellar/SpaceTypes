#pragma once

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class NormalizedXYVector final : public XYVectorBase<ThisSpace, Implementation>, public NormalizedVectorBase<ThisSpace, Implementation>
    {
        using XYVectorBaseInThisSpace = XYVectorBase<ThisSpace, Implementation>;
        using NormalizedVectorBaseInThisSpace = NormalizedVectorBase<ThisSpace, Implementation>;

    public:

        NormalizedXYVector() noexcept(false) : VectorBase<ThisSpace, Implementation>(), XYVectorBaseInThisSpace(), NormalizedVectorBaseInThisSpace() { }
        explicit NormalizedXYVector(const Implementation& e) noexcept(false) : VectorBase<ThisSpace, Implementation>(e), XYVectorBaseInThisSpace(e), NormalizedVectorBaseInThisSpace(e) { }
        explicit NormalizedXYVector(const double x, const double y) noexcept(false) : VectorBase<ThisSpace, Implementation>(x, y, 0), XYVectorBaseInThisSpace(x, y), NormalizedVectorBaseInThisSpace(x, y, 0) {}
        NormalizedXYVector(const std::initializer_list<double> l) noexcept(false) : XYVectorBaseInThisSpace(l), NormalizedVectorBaseInThisSpace(l) { }

        using NormalizedVectorBaseInThisSpace::end;
        [[nodiscard]] operator Vector<ThisSpace, Implementation>() const noexcept {
            return Vector<ThisSpace, Implementation>(NormalizedVectorBaseInThisSpace::X(), NormalizedVectorBaseInThisSpace::Y(), 0);
        }

        [[nodiscard]] operator XYVector<ThisSpace, Implementation>() const noexcept {
            return XYVector<ThisSpace, Implementation>(NormalizedVectorBaseInThisSpace::X(), NormalizedVectorBaseInThisSpace::Y());
        }

        [[nodiscard]] operator NormalizedVector<ThisSpace, Implementation>() const noexcept {
            return NormalizedVector<ThisSpace, Implementation>(NormalizedVectorBaseInThisSpace::X(), NormalizedVectorBaseInThisSpace::Y(), 0);
        }

        using NormalizedVectorBaseInThisSpace::operator*;
        [[nodiscard]] friend XYVector<ThisSpace, Implementation> operator*(NormalizedXYVector<ThisSpace, Implementation> lhs, const double& d) noexcept {
            lhs.Scale(d);
            return lhs;
        }

        [[nodiscard]] friend XYVector<ThisSpace, Implementation> operator-(NormalizedXYVector<ThisSpace, Implementation> lhs, const XYVectorBase<ThisSpace, Implementation>& rhs) noexcept {
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
        [[nodiscard]] NormalizedVector<ThisSpace, Implementation> Cross(const NormalizedXYVector<ThisSpace, Implementation>& other) const noexcept {
            return NormalizedVector<ThisSpace, Implementation>(XYVectorBase<ThisSpace, Implementation>::Cross(other).Norm());
        }

        friend std::ostream& operator << (
            std::ostream& os,
            const NormalizedXYVector<ThisSpace, Implementation>& item
        ) {
            const auto space = SpaceTypeNameMap<ThisSpace>::name;
            os << space << "::NormalizedXYVector (" << item.X() << ", " << item.Y() << ")";
            return os;
        }

#ifndef IGNORE_SPACE_STATIC_ASSERT

        using NormalizedVectorBaseInThisSpace::operator*=;
        using NormalizedVectorBaseInThisSpace::operator-=;
        using NormalizedVectorBaseInThisSpace::operator-;
        using NormalizedVectorBaseInThisSpace::operator+=;
        using NormalizedVectorBaseInThisSpace::operator+;

#endif
    };
}
