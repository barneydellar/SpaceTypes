#pragma once
#include "detail/Vector2Base.h"

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class Vector2 final : public Vector2Base<ThisSpace, Implementation>
    {
        using _base = Vector2Base<ThisSpace, Implementation>;
    public:

        Vector2() noexcept(false) : VectorBase<ThisSpace, Implementation>(), Vector2Base<ThisSpace, Implementation>() {}
        explicit Vector2(const Implementation& e) noexcept(false) : VectorBase<ThisSpace, Implementation>(e), Vector2Base<ThisSpace, Implementation>(e) {}
        explicit Vector2<ThisSpace, Implementation>(const double x, const double y) noexcept(false) : VectorBase<ThisSpace, Implementation>(x, y, 0), Vector2Base<ThisSpace, Implementation>(x, y) {}
        Vector2(const std::initializer_list<double> l) noexcept(false) : Vector2Base<ThisSpace, Implementation>(l) {}

        using _base::operator-=;
        Vector2<ThisSpace, Implementation> operator-=(const Vector2Base<ThisSpace, Implementation>& rhs) noexcept {
            _base::Sub(rhs);
            return *this;
        }

        using _base::operator+=;
        Vector2<ThisSpace, Implementation> operator+=(const Vector2Base<ThisSpace, Implementation>& rhs) noexcept {
            _base::Add(rhs);
            return *this;
        }

        using _base::operator*=;
        Vector2<ThisSpace, Implementation> operator*=(const double& d) noexcept {
            _base::Scale(d);
            return *this;
        }

        friend std::ostream& operator << (
            std::ostream& os,
            const Vector2<ThisSpace, Implementation>& item
        ) {
            const auto space = SpaceTypeNameMap<ThisSpace>::name;
            os << space << "::Vector2 (" << item.X() << ", " << item.Y() << ")";
            return os;
        }
    };

}
