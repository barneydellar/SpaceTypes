#pragma once

#include "SpaceImpl.h"

namespace Space {

    template <typename Space, typename Implementation>
    class Vector;

    template <typename Space, typename Implementation>
    class NormalizedVector;

    //--------------------------------------------------------------------------------------------

    template <typename Space, typename Implementation>
    class Point final
    {
    public:
        constexpr explicit Point(const Implementation v) noexcept : m_impl(v) {}
        constexpr explicit Point(const double x, const double y, const double z) noexcept : m_impl(x, y, z) {}
        constexpr explicit Point(const double x, const double y) noexcept : m_impl(x, y) {}
        constexpr Point(const std::initializer_list<double> l) : m_impl(l) {}

        //------------------------------------------------------------------------------------

        explicit constexpr operator Implementation() const noexcept {
            return m_impl;
        }

        //------------------------------------------------------------------------------------

        [[nodiscard]] constexpr double X() const noexcept { return m_impl.X(); }
        [[nodiscard]] constexpr double Y() const noexcept { return m_impl.Y(); }
        [[nodiscard]] constexpr double Z() const noexcept { return m_impl.Z(); }

        //-------------------------------------------------------------------------------------

        [[nodiscard]] constexpr double operator[] (const unsigned int i) const {
            if (i > 2) {
                throw std::invalid_argument("Index is out of range");
            }
            return m_impl[i];
        }

        template <int I>
        [[nodiscard]] constexpr double at() const noexcept {
            if constexpr (I != 0 && I != 1 && I != 2) {
                StaticAssert::invalid_at_access{};
            }
            else {
                return m_impl[I];
            }
        }

        //------------------------------------------------------------------------------------

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

        [[nodiscard]] constexpr bool operator == (const Point<Space, Implementation>& other) const noexcept {
            return m_impl.operator==(other.m_impl);
        }

        template <typename OtherSpace>
        constexpr bool operator == (const Point<OtherSpace, Implementation>& other) const noexcept {
            StaticAssert::invalid_equality{};
        }
        template <typename AnySpace>
        constexpr bool operator == (const Vector<AnySpace, Implementation>&) const noexcept {
            StaticAssert::invalid_point_vector_equality{};
        }
        template <typename AnySpace>
        constexpr bool operator == (const NormalizedVector<AnySpace, Implementation>&) const noexcept {
            StaticAssert::invalid_point_vector_equality{};
        }

        //------------------------------------------------------------------------------------

        [[nodiscard]] constexpr bool operator != (const Point<Space, Implementation>& other) const noexcept {
            return !(operator==(other));
        }
        template <typename OtherSpace>
        constexpr bool operator != (const Point<OtherSpace, Implementation>& other) const noexcept {
            StaticAssert::invalid_equality{};
        }
        template <typename AnySpace>
        constexpr bool operator != (const Vector<AnySpace, Implementation>&) const noexcept {
            StaticAssert::invalid_point_vector_equality{};
        }

        //------------------------------------------------------------------------------------

        template <typename OtherSpace, typename TransformManager>
        [[nodiscard]] constexpr Point<OtherSpace, Implementation> ConvertTo(const TransformManager& transform_manager) const {
            return Point<OtherSpace, Implementation>(transform_manager.template Transform<Space, OtherSpace>(m_impl));
        }

        //------------------------------------------------------------------------------------

        [[nodiscard]] constexpr Vector<Space, Implementation> operator-(const Point<Space, Implementation>& other) const noexcept {
            return Vector<Space, Implementation>(m_impl - other.m_impl);
        }

        template <typename OtherSpace>
        constexpr Vector<Space, Implementation> operator-(const Point<OtherSpace, Implementation>& other) const noexcept {
            StaticAssert::invalid_subtraction{};
        }

        //------------------------------------------------------------------------------------

        friend Point<Space, Implementation> operator+(Point<Space, Implementation> lhs, const Vector<Space, Implementation>& rhs) noexcept {
            lhs += rhs;
            return lhs;
        }

        Point<Space, Implementation>& operator+=(const Vector<Space, Implementation>& rhs) noexcept {
            m_impl = m_impl + rhs.m_impl;
            return *this;
        }

        template <typename OtherSpace>
        constexpr Point<Space, Implementation> operator+(const Vector<OtherSpace, Implementation>& other) const noexcept {
            StaticAssert::invalid_vector_to_point_addition{};
        }

        template <typename OtherSpace>
        constexpr Point<Space, Implementation> operator+=(const Vector<OtherSpace, Implementation>& other) noexcept {
            StaticAssert::invalid_vector_to_point_addition{};
        }

    private:
        Implementation m_impl;
    };

    template <typename Space, typename Impl>
    constexpr std::ostream& operator << (
        std::ostream& os,
        const Point<Space, Impl>& item
    ) {
        const auto space = SpaceTypeNameMap<Space>::name;
        os << space << "::Point (" << item.X() << ", " << item.Y() << ", " << item.Z() << ")";
        return os;
    }
}