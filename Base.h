#pragma once
#include "SpaceImpl.h"

namespace Space {

    template <typename Space, typename ExternalImplementation>
    class Base
    {
    public:
        Base(const detail::PointOrVector& v) noexcept : m_impl(v) {}
        constexpr Base() noexcept : m_impl(0, 0, 0) {}
        constexpr explicit Base(const ExternalImplementation& v) noexcept : m_impl(v.X(), v.Y(), v.Z()) {}
        constexpr explicit Base(const double x, const double y, const double z) noexcept : m_impl(x, y, z) {}
        constexpr explicit Base(const double x, const double y) noexcept : m_impl(x, y, 0) {}
        constexpr Base(const std::initializer_list<double> l) : m_impl(l) {}

        [[nodiscard]] explicit constexpr operator ExternalImplementation() const noexcept {
            return ExternalImplementation(m_impl.X(), m_impl.Y(), m_impl.Z());
        }

        [[nodiscard]] constexpr double X() const noexcept { return m_impl.X(); }
        [[nodiscard]] constexpr double Y() const noexcept { return m_impl.Y(); }
        [[nodiscard]] constexpr double Z() const noexcept { return m_impl.Z(); }

        [[nodiscard]] constexpr double operator[] (const unsigned int i) const {return m_impl[i];}

        template <int I>
        [[nodiscard]] typename std::enable_if<I == 0 || I == 1 || I == 2, double>::type at() const {
            return m_impl[I];
        }

        [[nodiscard]] constexpr double* begin() noexcept {
            return m_impl.begin();
        }
        [[nodiscard]] constexpr double* end() noexcept {
            return m_impl.end();
        }

        [[nodiscard]] constexpr const double* cbegin() const noexcept {
            return m_impl.cbegin();
        }
        [[nodiscard]] constexpr const double* cend() const noexcept {
            return m_impl.cend();
        }

        //------------------------------------------------------------------------------------

#ifndef IGNORE_SPACE_STATIC_ASSERT
        template <int I>
        typename std::enable_if<I != 0 && I != 1 && I != 2, StaticAssert::invalid_at_access>::type at() const {
            return StaticAssert::invalid_at_access{};
        }
#endif

    protected:
        detail::PointOrVector m_impl;
    };
}
