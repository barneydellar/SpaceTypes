#pragma once

#include "SpaceImpl.h"
#include "StaticAsserts.h"

namespace Space {

    template <typename Space, typename Implementation>
    class NormalizedVector final
    {
        void Normalize() noexcept(false)
        {
            m_impl.Normalize();
        }

    public:

        //-------------------------------------------------------------------------------------

        constexpr explicit NormalizedVector(const Implementation v) noexcept(false) : m_impl(v) { Normalize(); }
        constexpr explicit NormalizedVector(const std::array<double, 3> value) noexcept(false) : m_impl(value) { Normalize();}
        constexpr explicit NormalizedVector(const double x, const double y, const double z) noexcept(false) : m_impl(x, y, z) {Normalize();}
        constexpr explicit NormalizedVector(const double x, const double y) noexcept(false) : m_impl(x, y, 0) {Normalize();}
        constexpr NormalizedVector(const std::initializer_list<double> l) : m_impl(l) { Normalize(); }

        //-------------------------------------------------------------------------------------

        explicit constexpr operator Implementation() const noexcept {
            return m_impl;
        }

        constexpr operator Vector<Space, Implementation>() const noexcept {
            return Vector<Space, Implementation>(m_impl);
        }

        //-------------------------------------------------------------------------------------

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

        //-------------------------------------------------------------------------------------

        [[nodiscard]] constexpr bool operator == (const NormalizedVector<Space, Implementation>& other) const noexcept {
            return m_impl.operator==(static_cast<Implementation>(other));
        }

        template <typename OtherSpace>
        constexpr bool operator == (const NormalizedVector<OtherSpace, Implementation>& other) const noexcept {
            StaticAssert::invalid_equality{};
        }

        [[nodiscard]] constexpr bool operator == (const Vector<Space, Implementation>& other) const noexcept {
            return m_impl.operator==(static_cast<Implementation>(other));
        }
        template <typename OtherSpace>
        constexpr bool operator == (const Vector<OtherSpace, Implementation>& other) const noexcept {
            StaticAssert::invalid_equality{};
        }
        template <typename AnySpace>
        constexpr bool operator == (const Point<AnySpace, Implementation>&) const noexcept {
            StaticAssert::invalid_point_vector_equality{};
        }

        //------------------------------------------------------------------------------------

        [[nodiscard]] constexpr bool operator != (const NormalizedVector<Space, Implementation>& other) const noexcept {
            return !(operator==(other));
        }

        template <typename OtherSpace>
        constexpr bool operator != (const NormalizedVector<OtherSpace, Implementation>& other) const noexcept {
            StaticAssert::invalid_equality{};
        }

        [[nodiscard]] constexpr bool operator != (const Vector<Space, Implementation>& other) const noexcept {
            return !(operator==(other));
        }

        template <typename OtherSpace>
        constexpr bool operator != (const Vector<OtherSpace, Implementation>& other) const noexcept {
            StaticAssert::invalid_equality{};
        }

        template <typename AnySpace>
        constexpr bool operator != (const Point<AnySpace, Implementation>&) const noexcept {
            StaticAssert::invalid_point_vector_equality{};
        }

        //-------------------------------------------------------------------------------------

        [[nodiscard]] constexpr Vector<Space, Implementation> operator+(const NormalizedVector<Space, Implementation>& other) const noexcept {
            return Vector<Space, Implementation>(m_impl.operator+(static_cast<Implementation>(other)));
        }

        template <typename OtherSpace>
        constexpr Vector<Space, Implementation> operator+(const NormalizedVector<OtherSpace, Implementation>& other) const noexcept {
            StaticAssert::invalid_vector_to_vector_addition{};
        }

        [[nodiscard]] constexpr Vector<Space, Implementation> operator+(const Vector<Space, Implementation>& other) const noexcept {
            return Vector<Space, Implementation>(m_impl.operator+(static_cast<Implementation>(other)));
        }

        template <typename OtherSpace>
        constexpr Vector<Space, Implementation> operator+(const Vector<OtherSpace, Implementation>& other) const noexcept {
            StaticAssert::invalid_vector_to_vector_addition{};
        }

        template <typename AnySpace>
        constexpr Vector<AnySpace, Implementation> operator+(const Point<AnySpace, Implementation>&) const noexcept {
            StaticAssert::invalid_point_to_vector_addition{};
        }

        //-------------------------------------------------------------------------------------

        // Prevent inline Scaling or Adding
        constexpr Vector<Space, Implementation> operator*=(const double&) const noexcept {
            StaticAssert::invalid_normalized_vector_scale{};
        }
        template <typename OtherSpace>
        constexpr Vector<OtherSpace, Implementation> operator+=(const Vector<OtherSpace, Implementation>&) const noexcept {
            StaticAssert::invalid_normalized_vector_addition{};
        }
        template <typename OtherSpace>
        constexpr Vector<OtherSpace, Implementation> operator+=(const NormalizedVector<OtherSpace, Implementation>&) const noexcept {
            StaticAssert::invalid_normalized_vector_addition{};
        }

        //-------------------------------------------------------------------------------------

        [[nodiscard]] constexpr Vector<Space, Implementation> operator*(const double& d) const noexcept {
            return Vector<Space, Implementation>(m_impl.operator*(d));
        }

        //-------------------------------------------------------------------------------------

        [[nodiscard]] constexpr double Dot(const NormalizedVector<Space, Implementation>& other) const noexcept {
            return m_impl.Dot(static_cast<Implementation>(other));
        }

        template <typename OtherSpace>
        double Dot(const NormalizedVector<OtherSpace, Implementation>& other) const noexcept {
            StaticAssert::invalid_vector_dot{};
        }

        [[nodiscard]] constexpr double Dot(const Vector<Space, Implementation>& other) const noexcept {
            return m_impl.Dot(static_cast<Implementation>(other));
        }

        template <typename OtherSpace>
        double Dot(const Vector<OtherSpace, Implementation>& other) const noexcept {
            StaticAssert::invalid_vector_dot{};
        }

        //-------------------------------------------------------------------------------------

        // Crossing
        [[nodiscard]] constexpr NormalizedVector<Space, Implementation> operator*(const NormalizedVector<Space, Implementation>& rhs) const noexcept {
            return this->Cross(rhs);
        }
        [[nodiscard]] constexpr Vector<Space, Implementation> operator*(const Vector<Space, Implementation>& rhs) const noexcept {
            return this->Cross(rhs);
        }
        [[nodiscard]] constexpr NormalizedVector<Space, Implementation> Cross(const NormalizedVector<Space, Implementation>& other) const noexcept {
            return NormalizedVector<Space, Implementation>(m_impl.Cross(static_cast<Implementation>(other)));
        }
        [[nodiscard]] constexpr Vector<Space, Implementation> Cross(const Vector<Space, Implementation>& other) const noexcept {
            return Vector<Space, Implementation>(m_impl.Cross(static_cast<Implementation>(other)));
        }

        //-------------------------------------------------------------------------------------

        [[nodiscard]] constexpr double* begin() const noexcept {
            StaticAssert::normalized_vectors_do_not_support_non_const_iteration{};
        }

        [[nodiscard]] constexpr double* end() const noexcept {
            StaticAssert::normalized_vectors_do_not_support_non_const_iteration{};
        }

        //-------------------------------------------------------------------------------------

        template <typename OtherSpace, typename TransformManager>
        [[nodiscard]] constexpr Vector<OtherSpace, Implementation> ConvertTo(const TransformManager& transform_manager) const noexcept {
            return Vector<OtherSpace, Implementation>(transform_manager.template Transform33<Space, OtherSpace>(m_impl));
        }

    private:
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
