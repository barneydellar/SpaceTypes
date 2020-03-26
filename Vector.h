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
