#pragma once
#include "detail/VectorBase.h"

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class Vector final : public VectorBase<ThisSpace, Implementation>
    {
        using _base = VectorBase<ThisSpace, Implementation>;
        using _base::_base;
    public:

        [[nodiscard]] double* begin() noexcept { return _base::begin(); }
        [[nodiscard]] double* end() noexcept { return _base::end(); }

        [[nodiscard]] double Z() const noexcept { return *(_base::cbegin() + 2); }
        void SetX(const double d) noexcept { *(begin() + 0) = d; }
        void SetY(const double d) noexcept { *(begin() + 1) = d; }
        void SetZ(const double d) noexcept { *(begin() + 2) = d; }

        Vector<ThisSpace, Implementation> operator-=(const VectorBase<ThisSpace, Implementation>& rhs) noexcept {
            _base::Sub(rhs);
            return *this;
        }

        Vector<ThisSpace, Implementation> operator+=(const VectorBase<ThisSpace, Implementation>& rhs) noexcept {
            _base::Add(rhs);
            return *this;
        }

        Vector<ThisSpace, Implementation> operator*=(const double& d) noexcept {
            _base::Scale(d);
            return *this;
        }

        Vector<ThisSpace, Implementation> operator*=(const VectorBase<ThisSpace, Implementation>& rhs) noexcept {
            *this = this->Cross(rhs);
            return *this;
        }

        [[nodiscard]] XYVector<ThisSpace, Implementation> ToXY() const {
            return XYVector<ThisSpace, Implementation>(_base::X(), _base::Y());
        }

        [[nodiscard]] NormalizedVector<ThisSpace, Implementation> Norm() const {
            return NormalizedVector<ThisSpace, Implementation>(_base::X(), _base::Y(), _base::Z());
        }

        friend std::ostream& operator << (
            std::ostream& os,
            const Vector<ThisSpace, Implementation>& item
        ) {
            const auto space = SpaceTypeNameMap<ThisSpace>::name;
            os << space << "::Vector (" << item.X() << ", " << item.Y() << ", " << item.Z() << ")";
            return os;
        }
#ifndef IGNORE_SPACE_STATIC_ASSERT
        using _base::operator-=;
        using _base::operator+=;
        using _base::operator*=;
#endif

    };
}
