#pragma once
#include "detail/XYVectorBase.h"

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class XYVector final : public XYVectorBase<ThisSpace, Implementation>
    {
        using _base = XYVectorBase<ThisSpace, Implementation>;
    public:

        XYVector() noexcept(false) : VectorBase<ThisSpace, Implementation>(), XYVectorBase<ThisSpace, Implementation>() {}
        explicit XYVector(const Implementation& e) noexcept(false) : VectorBase<ThisSpace, Implementation>(e), XYVectorBase<ThisSpace, Implementation>(e) {}
        explicit XYVector<ThisSpace, Implementation>(const double x, const double y) noexcept(false) : VectorBase<ThisSpace, Implementation>(x, y, 0), XYVectorBase<ThisSpace, Implementation>(x, y) {}
        XYVector(const std::initializer_list<double>& l) noexcept(false) : XYVectorBase<ThisSpace, Implementation>(l) {}

        [[nodiscard]] double* begin() noexcept { return _base::begin(); }
        [[nodiscard]] double* end() noexcept {return reinterpret_cast<double*>(std::prev(_base::end()));}

        XYVector<ThisSpace, Implementation> operator-=(const XYVectorBase<ThisSpace, Implementation>& rhs) noexcept {
            _base::Sub(rhs);
            return *this;
        }

        XYVector<ThisSpace, Implementation> operator+=(const XYVectorBase<ThisSpace, Implementation>& rhs) noexcept {
            _base::Add(rhs);
            return *this;
        }

        XYVector<ThisSpace, Implementation> operator*=(const double& d) noexcept {
            _base::Scale(d);
            return *this;
        }

        friend std::ostream& operator << (
            std::ostream& os,
            const XYVector<ThisSpace, Implementation>& item
        ) {
            const auto space = SpaceTypeNameMap<ThisSpace>::name;
            os << space << "::XYVector (" << item.X() << ", " << item.Y() << ")";
            return os;
        }
#ifndef IGNORE_SPACE_STATIC_ASSERT
        using _base::operator+=;
        using _base::operator-=;
        using _base::operator*=;
#endif
    };

}
