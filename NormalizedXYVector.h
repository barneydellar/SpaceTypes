#pragma once
#include "detail/NormalizedXYVectorBase.h"

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class NormalizedXYVector final : public NormalizedXYVectorBase<ThisSpace, Implementation>
    {
        using _base = NormalizedXYVectorBase<ThisSpace, Implementation>;
        using NormalizedVectorBaseInThisSpace = NormalizedVectorBase<ThisSpace, Implementation>;

    public:

        NormalizedXYVector() noexcept(false) : VectorBase<ThisSpace, Implementation>(), NormalizedXYVectorBase<ThisSpace, Implementation>() {}
        explicit NormalizedXYVector(const Implementation& e) noexcept(false) : VectorBase<ThisSpace, Implementation>(e), NormalizedXYVectorBase<ThisSpace, Implementation>(e) {}
        explicit NormalizedXYVector<ThisSpace, Implementation>(const double x, const double y) noexcept(false) : VectorBase<ThisSpace, Implementation>(x, y, 0), NormalizedXYVectorBase<ThisSpace, Implementation>(x, y) {}
        NormalizedXYVector(const std::initializer_list<double>& l) noexcept(false) : NormalizedXYVectorBase<ThisSpace, Implementation>(l) {}

        using NormalizedVectorBaseInThisSpace::end;
        [[nodiscard]] operator Vector<ThisSpace, Implementation>() const noexcept {
            return Vector<ThisSpace, Implementation>(_base::X(), _base::Y(), 0);
        }

        [[nodiscard]] operator XYVector<ThisSpace, Implementation>() const noexcept {
            return XYVector<ThisSpace, Implementation>(_base::X(), _base::Y());
        }

        [[nodiscard]] operator NormalizedVector<ThisSpace, Implementation>() const noexcept {
            return NormalizedVector<ThisSpace, Implementation>(_base::X(), _base::Y(), 0);
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
