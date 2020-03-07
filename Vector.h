#pragma once
#include "SpaceImpl.h"

namespace Space {

    template <typename Space, typename ExternalImplementation>
    class Vector final
    {
        friend class NormalizedVector<Space, ExternalImplementation>;
        friend class Point<Space, ExternalImplementation>;

        using VectorInThisSpace = VectorInASpace<Space>;
        using NormalizedVectorInThisSpace = NormalizedVectorInASpace<Space>;

    public:

        Vector(const detail::PointOrVector& v) noexcept : m_impl(v) {}
        explicit Vector() noexcept : m_impl(0, 0, 0) {}
        explicit Vector(const ExternalImplementation& v) noexcept : m_impl(v.X(), v.Y(), v.Z()) {}
        explicit Vector(const double x, const double y, const double z) noexcept : m_impl(x, y, z) {}
        explicit Vector(const double x, const double y) noexcept : m_impl(x, y, 0) {}
        explicit Vector(const NormalizedVectorInThisSpace nv) noexcept : m_impl(nv.X(), nv.Y(), nv.Z()) {}
        constexpr Vector(const std::initializer_list<double> l) : m_impl(l){}

        [[nodiscard]] explicit operator ExternalImplementation() const noexcept {
            return ExternalImplementation(m_impl.X(), m_impl.Y(), m_impl.Z());
        }

        [[nodiscard]] double X() const noexcept { return m_impl.X(); }
        [[nodiscard]] double Y() const noexcept { return m_impl.Y(); }
        [[nodiscard]] double Z() const noexcept { return m_impl.Z(); }

        [[nodiscard]] double operator[] (const unsigned int i) const {return m_impl[i];}

        template <int I>
        [[nodiscard]] typename std::enable_if<I == 0 || I == 1 || I == 2, double>::type at() const {
            return m_impl[I];
        }

        [[nodiscard]] double* begin() noexcept {
            return m_impl.begin();
        }
        [[nodiscard]] double* end() noexcept {
            return m_impl.end();
        }
        [[nodiscard]] const double* cbegin() const noexcept {
            return m_impl.cbegin();
        }
        [[nodiscard]] const double* cend() const noexcept {
            return m_impl.cend();
        }

        [[nodiscard]] bool operator == (const VectorInThisSpace& other) const noexcept {
            return m_impl.operator==(other.m_impl);
        }

        [[nodiscard]] bool operator == (const NormalizedVectorInThisSpace& other) const noexcept {
            return m_impl.operator==(other.m_impl);
        }

        [[nodiscard]] bool operator != (const VectorInThisSpace& other) const noexcept {
            return !(operator==(other));
        }

        [[nodiscard]] bool operator != (const NormalizedVectorInThisSpace& other) const noexcept {
            return !(operator==(other));
        }

        template <typename OtherSpace, typename TransformManager>
        [[nodiscard]] VectorInASpace<OtherSpace> ConvertTo(const TransformManager& transform_manager) const noexcept {
            return VectorInASpace<OtherSpace>(transform_manager.template Transform33<Space, OtherSpace>(static_cast<ExternalImplementation>(*this)));
        }

        [[nodiscard]] friend VectorInThisSpace operator*(VectorInThisSpace lhs, const double& d) noexcept {
            lhs *= d;
            return lhs;
        }

         VectorInThisSpace& operator*=(const double& d) noexcept {
            m_impl = m_impl * d;
            return *this;
        }

        [[nodiscard]] VectorInThisSpace operator*(const VectorInThisSpace& rhs) const noexcept {
            return this->Cross(rhs);
        }

        [[nodiscard]] VectorInThisSpace operator*(const NormalizedVectorInThisSpace& rhs) const noexcept {
            return this->Cross(rhs);
        }
        [[nodiscard]] VectorInThisSpace Cross(const VectorInThisSpace& other) const noexcept {
            return VectorInThisSpace(m_impl.Cross(other.m_impl));
        }

        [[nodiscard]] VectorInThisSpace Cross(const NormalizedVectorInThisSpace& other) const noexcept {
            return VectorInThisSpace(m_impl.Cross(other.m_impl));
        }

        VectorInThisSpace operator*=(const VectorInThisSpace& other) noexcept {
            return *this = this->Cross(other);
        }

        VectorInThisSpace operator*=(const NormalizedVectorInThisSpace& other) noexcept {
            return *this = this->Cross(other);
        }

        [[nodiscard]] friend VectorInThisSpace operator-(VectorInThisSpace lhs, const VectorInThisSpace& rhs) noexcept {
            lhs -= rhs;
            return lhs;
        }

        VectorInThisSpace& operator-=(const VectorInThisSpace& rhs) noexcept {
            m_impl = m_impl - rhs.m_impl;
            return *this;
        }

        [[nodiscard]] friend VectorInThisSpace operator-(VectorInThisSpace lhs, const NormalizedVectorInThisSpace& rhs) noexcept {
            lhs -= rhs;
            return lhs;
        }

        VectorInThisSpace& operator-=(const NormalizedVectorInThisSpace& rhs) noexcept {
            m_impl = m_impl - rhs.m_impl;
            return *this;
        }

        [[nodiscard]] friend VectorInThisSpace operator+(VectorInThisSpace lhs, const VectorInThisSpace& rhs) noexcept {
            lhs += rhs;
            return lhs;
        }

        VectorInThisSpace& operator+=(const VectorInThisSpace& rhs) noexcept {
            m_impl = m_impl + rhs.m_impl;
            return *this;
        }

        [[nodiscard]] friend VectorInThisSpace operator+(VectorInThisSpace lhs, const NormalizedVectorInThisSpace& rhs) noexcept {
            lhs += rhs;
            return lhs;
        }

        VectorInThisSpace& operator+=(const NormalizedVectorInThisSpace& rhs) noexcept {
            m_impl = m_impl + rhs.m_impl;
            return *this;
        }

        [[nodiscard]] typename Space::Unit Mag() const noexcept {
            return Space::Unit{m_impl.Mag()};
        }

        [[nodiscard]] double Mag_double() const noexcept {
            return m_impl.Mag();
        }

        [[nodiscard]] NormalizedVectorInThisSpace Norm() const {
            return NormalizedVectorInThisSpace(m_impl);
        }

        [[nodiscard]] double Dot(const VectorInThisSpace& other) const noexcept {
            return m_impl.Dot(other.m_impl);
        }

        [[nodiscard]] double Dot(const NormalizedVectorInThisSpace& other) const noexcept {
            return m_impl.Dot(other.m_impl);
        }

        //-------------------------------------------------------------------------------------

#ifndef IGNORE_SPACE_STATIC_ASSERT

        template <int I>
        typename std::enable_if<I != 0 && I != 1 && I != 2, StaticAssert::invalid_at_access>::type at() const {
            return StaticAssert::invalid_at_access{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_equality operator == (const Vector<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_equality{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_equality operator == (const NormalizedVector<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_equality{};
        }
        template <typename AnySpace>
        StaticAssert::invalid_point_vector_equality operator == (const Point<AnySpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_equality operator != (const Vector<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_equality{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_equality operator != (const NormalizedVector<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_equality{};
        }
        template <typename AnySpace>
        StaticAssert::invalid_point_vector_equality operator != (const Point<AnySpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_cross operator*(const Vector<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_vector_cross{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_cross operator*(const NormalizedVector<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_vector_cross{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_cross Cross(const Vector<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_vector_cross{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_cross Cross(const NormalizedVector<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_vector_cross{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_cross operator*=(const Vector<OtherSpace, ExternalImplementation>&) noexcept {
            return StaticAssert::invalid_vector_cross{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_cross operator*=(const NormalizedVector<OtherSpace, ExternalImplementation>&) noexcept {
            return StaticAssert::invalid_vector_cross{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_to_vector_addition operator+(const Vector<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_vector_to_vector_addition{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_to_vector_addition operator+(const NormalizedVector<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_vector_to_vector_addition{};
        }
        template <typename AnySpace>
        StaticAssert::invalid_point_to_vector_addition operator+(const Point<AnySpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_point_to_vector_addition{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_to_vector_addition operator+=(const Vector<OtherSpace, ExternalImplementation>&) noexcept {
            return StaticAssert::invalid_vector_to_vector_addition{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_to_vector_addition operator+=(const NormalizedVector<OtherSpace, ExternalImplementation>&) noexcept {
            return StaticAssert::invalid_vector_to_vector_addition{};
        }

        template <typename AnySpace>
        StaticAssert::invalid_point_from_vector_subtraction operator-(const Point<AnySpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_point_from_vector_subtraction{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_to_vector_subtraction operator-(const Vector<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_vector_to_vector_subtraction{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_to_vector_subtraction operator-(const NormalizedVector<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_vector_to_vector_subtraction{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_to_vector_subtraction operator-=(const Vector<OtherSpace, ExternalImplementation>&) noexcept {
            return StaticAssert::invalid_vector_to_vector_subtraction{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_to_vector_subtraction operator-=(const NormalizedVector<OtherSpace, ExternalImplementation>&) noexcept {
            return StaticAssert::invalid_vector_to_vector_subtraction{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_dot Dot(const Vector<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_vector_dot{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_dot Dot(const NormalizedVector<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_vector_dot{};
        }

#endif

    private:
        detail::PointOrVector m_impl;
    };

    template <typename Space, typename Impl>
    std::ostream& operator << (
        std::ostream& os,
        const Vector<Space, Impl>& item
    ) {
        const auto space = SpaceTypeNameMap<Space>::name;
        os << space << "::Vector (" << item.X() << ", " << item.Y() << ", " << item.Z() << ")";
        return os;
    }
}
