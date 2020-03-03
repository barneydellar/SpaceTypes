#pragma once
#include "SpaceImpl.h"
#include "NormalizedVector.h"

namespace Space {

    //--------------------------------------------------------------------------------------------

    template <typename Space, typename Implementation>
    class Vector final
    {
        friend class NormalizedVector<Space, Implementation>;
        friend class Point<Space, Implementation>;

    public:

        constexpr explicit Vector(const Implementation v) noexcept : m_impl(v) {}
        constexpr explicit Vector(const double x, const double y, const double z) noexcept : m_impl(x, y, z) {}
        constexpr explicit Vector(const double x, const double y) noexcept : m_impl(x, y) {}
        constexpr explicit Vector(const NormalizedVector<Space, Implementation> nv) noexcept : m_impl(nv.X(), nv.Y(), nv.Z()) {}
        constexpr Vector(const std::initializer_list<double> l) : m_impl(l) {}

        //------------------------------------------------------------------------------------

        explicit constexpr operator Implementation() const noexcept {
            return m_impl;
        }

        //------------------------------------------------------------------------------------

        [[nodiscard]] constexpr double X() const noexcept { return m_impl.X(); }
        [[nodiscard]] constexpr double Y() const noexcept { return m_impl.Y(); }
        [[nodiscard]] constexpr double Z() const noexcept { return m_impl.Z(); }

        [[nodiscard]]
        constexpr double operator[] (const unsigned int i) const {
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

        [[nodiscard]] constexpr bool operator == (const Vector<Space, Implementation>& other) const noexcept {
            return m_impl.operator==(other.m_impl);
        }

        template <typename OtherSpace>
        constexpr bool operator == (const Vector<OtherSpace, Implementation>& other) const noexcept {
            StaticAssert::invalid_equality{};
        }

        [[nodiscard]] constexpr bool operator == (const NormalizedVector<Space, Implementation>& other) const noexcept {
            return m_impl.operator==(other.m_impl);
        }

        template <typename OtherSpace>
        constexpr bool operator == (const NormalizedVector<OtherSpace, Implementation>& other) const noexcept {
            StaticAssert::invalid_equality{};
        }

        template <typename AnySpace>
        constexpr bool operator == (const Point<AnySpace, Implementation>&) const noexcept {
            StaticAssert::invalid_point_vector_equality{};
        }

        //------------------------------------------------------------------------------------

        [[nodiscard]] constexpr bool operator != (const Vector<Space, Implementation>& other) const noexcept {
            return !(operator==(other));
        }

        template <typename OtherSpace>
        constexpr bool operator != (const Vector<OtherSpace, Implementation>& other) const noexcept {
            StaticAssert::invalid_equality{};
        }

        [[nodiscard]] constexpr bool operator != (const NormalizedVector<Space, Implementation>& other) const noexcept {
            return !(operator==(other));
        }

        template <typename OtherSpace>
        constexpr bool operator != (const NormalizedVector<OtherSpace, Implementation>& other) const noexcept {
            StaticAssert::invalid_equality{};
        }

        template <typename AnySpace>
        constexpr bool operator != (const Point<AnySpace, Implementation>&) const noexcept {
            StaticAssert::invalid_point_vector_equality{};
        }

        //-------------------------------------------------------------------------------------

        template <typename OtherSpace, typename TransformManager>
        [[nodiscard]] constexpr Vector<OtherSpace, Implementation> ConvertTo(const TransformManager& transform_manager) const noexcept {
            return Vector<OtherSpace, Implementation>(transform_manager.template Transform33<Space, OtherSpace>(m_impl));
        }

        //------------------------------------------------------------------------------------

        [[nodiscard]] friend Vector<Space, Implementation> operator*(Vector<Space, Implementation> lhs, const double& d) noexcept {
            lhs *= d;
            return lhs;
        }

        constexpr Vector<Space, Implementation>& operator*=(const double& d) noexcept {
            m_impl = m_impl * d;
            return *this;
        }

        [[nodiscard]] constexpr Vector<Space, Implementation> operator*(const Vector<Space, Implementation>& rhs) const noexcept {
            return this->Cross(rhs);
        }

        template <typename OtherSpace>
        constexpr Vector<Space, Implementation> operator*(const Vector<OtherSpace, Implementation>& rhs) const noexcept {
            StaticAssert::invalid_vector_cross{};
        }

        [[nodiscard]] constexpr typename Vector<Space, Implementation> operator*(const NormalizedVector<Space, Implementation>& rhs) const noexcept {
            return this->Cross(rhs);
        }

        template <typename OtherSpace>
        constexpr Vector<Space, Implementation> operator*(const NormalizedVector<OtherSpace, Implementation>& rhs) const noexcept {
            StaticAssert::invalid_vector_cross{};
        }

        [[nodiscard]] constexpr Vector<Space, Implementation> Cross(const Vector<Space, Implementation>& other) const noexcept {
            return Vector<Space, Implementation>(m_impl.Cross(other.m_impl));
        }

        template <typename OtherSpace>
        [[nodiscard]] constexpr Vector<Space, Implementation> Cross(const Vector<OtherSpace, Implementation>& other) const noexcept {
            StaticAssert::invalid_vector_cross{};
        }

        [[nodiscard]] constexpr Vector<Space, Implementation> Cross(const NormalizedVector<Space, Implementation>& other) const noexcept {
            return Vector<Space, Implementation>(m_impl.Cross(other.m_impl));
        }

        template <typename OtherSpace>
        constexpr Vector<Space, Implementation> Cross(const NormalizedVector<OtherSpace, Implementation>& other) const noexcept {
            StaticAssert::invalid_vector_cross{};
        }

        constexpr Vector<Space, Implementation> operator*=(const Vector<Space, Implementation>& other) noexcept {
            return *this = this->Cross(other);
        }

        template <typename OtherSpace>
        constexpr Vector<Space, Implementation> operator*=(const Vector<OtherSpace, Implementation>& other) noexcept {
            StaticAssert::invalid_vector_cross{};
        }

        constexpr Vector<Space, Implementation> operator*=(const NormalizedVector<Space, Implementation>& other) noexcept {
            return *this = this->Cross(other);
        }

        template <typename OtherSpace>
        constexpr Vector<Space, Implementation> operator*=(const NormalizedVector<OtherSpace, Implementation>& other) noexcept {
            StaticAssert::invalid_vector_cross{};
        }

        //-------------------------------------------------------------------------------------

        friend Vector<Space, Implementation> operator+(Vector<Space, Implementation> lhs, const Vector<Space, Implementation>& rhs) noexcept {
            lhs += rhs;
            return lhs;
        }

        Vector<Space, Implementation>& operator+=(const Vector<Space, Implementation>& rhs) noexcept {
            m_impl = m_impl + rhs.m_impl;
            return *this;
        }

        friend Vector<Space, Implementation> operator+(Vector<Space, Implementation> lhs, const NormalizedVector<Space, Implementation>& rhs) noexcept {
            lhs += rhs;
            return lhs;
        }

        Vector<Space, Implementation>& operator+=(const NormalizedVector<Space, Implementation>& rhs) noexcept {
            m_impl = m_impl + rhs.m_impl;
            return *this;
        }

        template <typename OtherSpace>
        constexpr Vector<Space, Implementation> operator+(const Vector<OtherSpace, Implementation>& other) const noexcept {
            StaticAssert::invalid_vector_to_vector_addition{};
        }

        template <typename OtherSpace>
        constexpr Vector<Space, Implementation> operator+(const NormalizedVector<OtherSpace, Implementation>& other) const noexcept {
            StaticAssert::invalid_vector_to_vector_addition{};
        }

        template <typename AnySpace>
        constexpr Vector<AnySpace, Implementation> operator+(const Point<AnySpace, Implementation>&) const noexcept {
            StaticAssert::invalid_point_to_vector_addition{};
        }

        template <typename OtherSpace>
        constexpr Vector<Space, Implementation> operator+=(const Vector<OtherSpace, Implementation>& other) noexcept {
            StaticAssert::invalid_vector_to_vector_addition{};
        }

        template <typename OtherSpace>
        constexpr Vector<Space, Implementation> operator+=(const NormalizedVector<OtherSpace, Implementation>& other) noexcept {
            StaticAssert::invalid_vector_to_vector_addition{};
        }

        //-------------------------------------------------------------------------------------

        [[nodiscard]] constexpr typename Space::Unit Mag() const noexcept {
            return Space::Unit{m_impl.Mag()};
        }

        [[nodiscard]] constexpr double Mag_double() const noexcept {
            return m_impl.Mag();
        }

        [[nodiscard]] constexpr NormalizedVector<Space, Implementation> Norm() const {
            return NormalizedVector<Space, Implementation>(m_impl);
        }

        [[nodiscard]] constexpr double Dot(const Vector<Space, Implementation>& other) const noexcept {
            return m_impl.Dot(other.m_impl);
        }

        template <typename OtherSpace>
        constexpr double Dot(const Vector<OtherSpace, Implementation>& other) const noexcept {
            StaticAssert::invalid_vector_dot{};
        }

        [[nodiscard]] constexpr double Dot(const NormalizedVector<Space, Implementation>& other) const noexcept {
            return m_impl.Dot(other.m_impl);
        }

        template <typename OtherSpace>
        [[nodiscard]] constexpr double Dot(const NormalizedVector<OtherSpace, Implementation>& other) const noexcept {
            StaticAssert::invalid_vector_dot{};
        }

    private:
        Implementation m_impl;
    };

    template <typename Space, typename Impl>
    constexpr std::ostream& operator << (
        std::ostream& os,
        const Vector<Space, Impl>& item
    ) {
        const auto space = SpaceTypeNameMap<Space>::name;
        os << space << "::Vector (" << item.X() << ", " << item.Y() << ", " << item.Z() << ")";
        return os;
    }
}
