#pragma once

#include "SpaceImpl.h"
#include "StaticAsserts.h"

namespace Space {

    template <typename Space, typename Implementation>
    class NormalizedVector final
    {
    public:

        friend class Vector< Space, Implementation>;

        //-------------------------------------------------------------------------------------

        constexpr explicit NormalizedVector(const Implementation v) noexcept(false) : m_impl(v) { Normalize(); }
        constexpr explicit NormalizedVector(const double x, const double y, const double z) noexcept(false) : m_impl(x, y, z) {Normalize();}
        constexpr explicit NormalizedVector(const double x, const double y) noexcept(false) : m_impl(x, y, 0) {Normalize();}
        constexpr NormalizedVector(const std::initializer_list<double> l) : m_impl(l) { Normalize(); }

        [[nodiscard]] explicit constexpr operator Implementation() const noexcept {
            return m_impl;
        }

        [[nodiscard]] constexpr operator Vector<Space, Implementation>() const noexcept {
            return Vector<Space, Implementation>(m_impl);
        }

        [[nodiscard]] constexpr double X() const noexcept { return m_impl.X(); }
        [[nodiscard]] constexpr double Y() const noexcept { return m_impl.Y(); }
        [[nodiscard]] constexpr double Z() const noexcept { return m_impl.Z(); }

        [[nodiscard]] constexpr double operator[] (const unsigned int i) const {
            if (i > 2) {
                throw std::invalid_argument("Index is out of range");
            }
            return m_impl[i];
        }
        template <int I>
        [[nodiscard]] typename std::enable_if<I == 0 || I == 1 || I == 2, double>::type at() const {
            return m_impl[I];
        }
        [[nodiscard]] constexpr bool operator == (const NormalizedVector<Space, Implementation>& other) const noexcept {
            return m_impl.operator==(other.m_impl);
        }
        [[nodiscard]] constexpr bool operator == (const Vector<Space, Implementation>& other) const noexcept {
            return m_impl.operator==(other.m_impl);
        }
        [[nodiscard]] constexpr bool operator != (const NormalizedVector<Space, Implementation>& other) const noexcept {
            return !(operator==(other));
        }
        [[nodiscard]] constexpr bool operator != (const Vector<Space, Implementation>& other) const noexcept {
            return !(operator==(other));
        }
        [[nodiscard]] constexpr Vector<Space, Implementation> operator+(const NormalizedVector<Space, Implementation>& other) const noexcept {
            return Vector<Space, Implementation>(m_impl + other.m_impl);
        }
        [[nodiscard]] constexpr Vector<Space, Implementation> operator+(const Vector<Space, Implementation>& other) const noexcept {
            return Vector<Space, Implementation>(m_impl + other.m_impl);
        }
        [[nodiscard]] constexpr Vector<Space, Implementation> operator*(const double& d) const noexcept {
            return Vector<Space, Implementation>(m_impl * d);
        }
        [[nodiscard]] constexpr double Dot(const NormalizedVector<Space, Implementation>& other) const noexcept {
            return m_impl.Dot(other.m_impl);
        }
        [[nodiscard]] constexpr double Dot(const Vector<Space, Implementation>& other) const noexcept {
            return m_impl.Dot(other.m_impl);
        }
        [[nodiscard]] constexpr NormalizedVector<Space, Implementation> operator*(const NormalizedVector<Space, Implementation>& rhs) const noexcept {
            return this->Cross(rhs);
        }
        [[nodiscard]] constexpr Vector<Space, Implementation> operator*(const Vector<Space, Implementation>& rhs) const noexcept {
            return this->Cross(rhs);
        }
        [[nodiscard]] constexpr NormalizedVector<Space, Implementation> Cross(const NormalizedVector<Space, Implementation>& other) const noexcept {
            return NormalizedVector<Space, Implementation>(m_impl.Cross(other.m_impl));
        }
        [[nodiscard]] constexpr Vector<Space, Implementation> Cross(const Vector<Space, Implementation>& other) const noexcept {
            return Vector<Space, Implementation>(m_impl.Cross(other.m_impl));
        }
        template <typename OtherSpace, typename TransformManager>
        [[nodiscard]] constexpr Vector<OtherSpace, Implementation> ConvertTo(const TransformManager& transform_manager) const noexcept {
            return Vector<OtherSpace, Implementation>(transform_manager.template Transform33<Space, OtherSpace>(m_impl));
        }

        //-------------------------------------------------------------------------------------

#ifndef IGNORE_SPACE_STATIC_ASSERT

        template <int I>
        typename std::enable_if<I != 0 && I != 1 && I != 2, StaticAssert::invalid_at_access>::type at() const {
            return StaticAssert::invalid_at_access{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_equality operator == (const NormalizedVector<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_equality{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_equality operator == (const Vector<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_equality{};
        }
        template <typename AnySpace>
        StaticAssert::invalid_point_vector_equality operator == (const Point<AnySpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_equality operator != (const NormalizedVector<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_equality{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_equality operator != (const Vector<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_equality{};
        }
        template <typename AnySpace>
        StaticAssert::invalid_point_vector_equality operator != (const Point<AnySpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_to_vector_addition operator+(const NormalizedVector<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_vector_to_vector_addition{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_to_vector_addition operator+(const Vector<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_vector_to_vector_addition{};
        }
        template <typename AnySpace>
        StaticAssert::invalid_point_to_vector_addition operator+(const Point<AnySpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_to_vector_addition{};
        }
        StaticAssert::invalid_normalized_vector_scale operator*=(const double&) const noexcept {
            return StaticAssert::invalid_normalized_vector_scale{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_normalized_vector_addition operator+=(const Vector<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_normalized_vector_addition{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_normalized_vector_addition operator+=(const NormalizedVector<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_normalized_vector_addition{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_dot Dot(const NormalizedVector<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_vector_dot{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_dot Dot(const Vector<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_vector_dot{};
        }
        StaticAssert::normalized_vectors_do_not_support_non_const_iteration begin() const noexcept {
            return StaticAssert::normalized_vectors_do_not_support_non_const_iteration{};
        }
        StaticAssert::normalized_vectors_do_not_support_non_const_iteration end() const noexcept {
            return StaticAssert::normalized_vectors_do_not_support_non_const_iteration{};
        }
#endif

    private:

        void Normalize() noexcept(false)
        {
            const auto mag = m_impl.Mag();
            if (mag == 0) {
                throw std::invalid_argument("Zero-sized normal vectors are not allowed");
            }
            m_impl.Normalize();
        }


        Implementation m_impl;
    };

    template <typename Space, typename Impl>
    constexpr std::ostream& operator << (
        std::ostream& os,
        const NormalizedVector<Space, Impl>& item
    ) {
        const auto space = SpaceTypeNameMap<Space>::name;
        os << space << "::NormalizedVector (" << item.X() << ", " << item.Y() << ", " << item.Z() << ")";
        return os;
    }
}
