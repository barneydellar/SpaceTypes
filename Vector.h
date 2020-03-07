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

        using VectorInThisSpace = VectorInASpace<Space>;
        using NormalizedVectorInThisSpace = NormalizedVectorInASpace<Space>;

    public:

        constexpr explicit Vector(const Implementation v) noexcept : m_impl(v) {}
        constexpr explicit Vector(const double x, const double y, const double z) noexcept : m_impl(x, y, z) {}
        constexpr explicit Vector(const double x, const double y) noexcept : m_impl(x, y) {}
        constexpr explicit Vector(const NormalizedVectorInThisSpace nv) noexcept : m_impl(nv.X(), nv.Y(), nv.Z()) {}
        constexpr Vector(const std::initializer_list<double> l) : m_impl(l) {}

        [[nodiscard]] explicit constexpr operator Implementation() const noexcept {
            return m_impl;
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
        [[nodiscard]] constexpr typename std::enable_if<I == 0 || I == 1 || I == 2, double>::type at() const {
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

        [[nodiscard]] constexpr bool operator == (const VectorInThisSpace& other) const noexcept {
            return m_impl.operator==(other.m_impl);
        }

        [[nodiscard]] constexpr bool operator == (const NormalizedVectorInThisSpace& other) const noexcept {
            return m_impl.operator==(other.m_impl);
        }

        [[nodiscard]] constexpr bool operator != (const VectorInThisSpace& other) const noexcept {
            return !(operator==(other));
        }

        [[nodiscard]] constexpr bool operator != (const NormalizedVectorInThisSpace& other) const noexcept {
            return !(operator==(other));
        }

        template <typename OtherSpace, typename TransformManager>
        [[nodiscard]] constexpr VectorInASpace<OtherSpace> ConvertTo(const TransformManager& transform_manager) const noexcept {
            return VectorInASpace<OtherSpace>(transform_manager.template Transform33<Space, OtherSpace>(m_impl));
        }

        [[nodiscard]] friend VectorInThisSpace operator*(VectorInThisSpace lhs, const double& d) noexcept {
            lhs *= d;
            return lhs;
        }

        constexpr  VectorInThisSpace& operator*=(const double& d) noexcept {
            m_impl = m_impl * d;
            return *this;
        }

        [[nodiscard]] constexpr VectorInThisSpace operator*(const VectorInThisSpace& rhs) const noexcept {
            return this->Cross(rhs);
        }

        [[nodiscard]] constexpr VectorInThisSpace operator*(const NormalizedVectorInThisSpace& rhs) const noexcept {
            return this->Cross(rhs);
        }
        [[nodiscard]] constexpr VectorInThisSpace Cross(const VectorInThisSpace& other) const noexcept {
            return VectorInThisSpace(m_impl.Cross(other.m_impl));
        }

        [[nodiscard]] constexpr VectorInThisSpace Cross(const NormalizedVectorInThisSpace& other) const noexcept {
            return VectorInThisSpace(m_impl.Cross(other.m_impl));
        }

        constexpr VectorInThisSpace operator*=(const VectorInThisSpace& other) noexcept {
            return *this = this->Cross(other);
        }

        constexpr VectorInThisSpace operator*=(const NormalizedVectorInThisSpace& other) noexcept {
            return *this = this->Cross(other);
        }

        [[nodiscard]] constexpr friend VectorInThisSpace operator+(VectorInThisSpace lhs, const VectorInThisSpace& rhs) noexcept {
            lhs += rhs;
            return lhs;
        }

        constexpr VectorInThisSpace& operator+=(const VectorInThisSpace& rhs) noexcept {
            m_impl = m_impl + rhs.m_impl;
            return *this;
        }

        [[nodiscard]] constexpr friend VectorInThisSpace operator+(VectorInThisSpace lhs, const NormalizedVectorInThisSpace& rhs) noexcept {
            lhs += rhs;
            return lhs;
        }

        constexpr VectorInThisSpace& operator+=(const NormalizedVectorInThisSpace& rhs) noexcept {
            m_impl = m_impl + rhs.m_impl;
            return *this;
        }

        [[nodiscard]] constexpr typename Space::Unit Mag() const noexcept {
            return Space::Unit{m_impl.Mag()};
        }

        [[nodiscard]] constexpr double Mag_double() const noexcept {
            return m_impl.Mag();
        }

        [[nodiscard]] constexpr NormalizedVectorInThisSpace Norm() const {
            return NormalizedVectorInThisSpace(m_impl);
        }

        [[nodiscard]] constexpr double Dot(const VectorInThisSpace& other) const noexcept {
            return m_impl.Dot(other.m_impl);
        }

        [[nodiscard]] constexpr double Dot(const NormalizedVectorInThisSpace& other) const noexcept {
            return m_impl.Dot(other.m_impl);
        }

        //-------------------------------------------------------------------------------------

#ifndef IGNORE_SPACE_STATIC_ASSERT

        template <int I>
        typename std::enable_if<I != 0 && I != 1 && I != 2, StaticAssert::invalid_at_access>::type at() const {
            return StaticAssert::invalid_at_access{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_equality operator == (const Vector<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_equality{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_equality operator == (const NormalizedVector<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_equality{};
        }
        template <typename AnySpace>
        StaticAssert::invalid_point_vector_equality operator == (const Point<AnySpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_equality operator != (const Vector<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_equality{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_equality operator != (const NormalizedVector<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_equality{};
        }
        template <typename AnySpace>
        StaticAssert::invalid_point_vector_equality operator != (const Point<AnySpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_cross operator*(const Vector<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_vector_cross{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_cross operator*(const NormalizedVector<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_vector_cross{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_cross Cross(const Vector<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_vector_cross{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_cross Cross(const NormalizedVector<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_vector_cross{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_cross operator*=(const Vector<OtherSpace, Implementation>&) noexcept {
            return StaticAssert::invalid_vector_cross{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_cross operator*=(const NormalizedVector<OtherSpace, Implementation>&) noexcept {
            return StaticAssert::invalid_vector_cross{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_to_vector_addition operator+(const Vector<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_vector_to_vector_addition{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_to_vector_addition operator+(const NormalizedVector<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_vector_to_vector_addition{};
        }
        template <typename AnySpace>
        StaticAssert::invalid_point_to_vector_addition operator+(const Point<AnySpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_to_vector_addition{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_to_vector_addition operator+=(const Vector<OtherSpace, Implementation>&) noexcept {
            return StaticAssert::invalid_vector_to_vector_addition{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_to_vector_addition operator+=(const NormalizedVector<OtherSpace, Implementation>&) noexcept {
            return StaticAssert::invalid_vector_to_vector_addition{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_dot Dot(const Vector<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_vector_dot{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_dot Dot(const NormalizedVector<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_vector_dot{};
        }

#endif

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
