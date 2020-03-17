#pragma once
#include "SpaceImpl.h"

namespace Space {

    template <typename Space, typename ExternalImplementation>
    class VectorBase
    {
        friend class Point<Space, ExternalImplementation>;

        using BaseInThisSpace = VectorBase<Space, ExternalImplementation>;
        using VectorInThisSpace = VectorInASpace<Space>;
        using NormalizedVectorInThisSpace = NormalizedVectorInASpace<Space>;

    public:

        VectorBase(const detail::PointOrVector& v) noexcept : m_impl(v) {}
        explicit VectorBase() noexcept : m_impl(0, 0, 0) {}
        explicit VectorBase(const ExternalImplementation& v) noexcept : m_impl(v.X(), v.Y(), v.Z()) {}
        explicit VectorBase(const double x, const double y, const double z) noexcept : m_impl(x, y, z) {}
        explicit VectorBase(const double x, const double y) noexcept : m_impl(x, y, 0) {}
        constexpr VectorBase(const std::initializer_list<double> l) : m_impl(l) {}

        [[nodiscard]] explicit operator ExternalImplementation() const noexcept {
            return ExternalImplementation(m_impl.X(), m_impl.Y(), m_impl.Z());
        }

        [[nodiscard]] double X() const noexcept { return m_impl.X(); }
        [[nodiscard]] double Y() const noexcept { return m_impl.Y(); }
        [[nodiscard]] double Z() const noexcept { return m_impl.Z(); }

        [[nodiscard]] double operator[] (const unsigned int i) const { return m_impl[i]; }

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

        [[nodiscard]] bool operator == (const BaseInThisSpace& other) const noexcept {
            return m_impl.operator==(other.m_impl);
        }

        [[nodiscard]] bool operator != (const BaseInThisSpace& other) const noexcept {
            return !(operator==(other));
        }

        template <typename OtherSpace, typename TransformManager>
        [[nodiscard]] VectorInASpace<OtherSpace> ConvertTo(const TransformManager& transform_manager) const noexcept {
            return VectorInASpace<OtherSpace>(transform_manager.template Transform33<Space, OtherSpace>(static_cast<ExternalImplementation>(*this)));
        }

        [[nodiscard]] friend VectorInThisSpace operator*(BaseInThisSpace lhs, const double& d) noexcept {
            lhs *= d;
            return VectorInThisSpace(lhs.m_impl);
        }

        VectorInThisSpace operator*=(const double& d) noexcept {
            m_impl = m_impl * d;
            return VectorInThisSpace(m_impl);
        }

        [[nodiscard]] VectorInThisSpace operator*(const BaseInThisSpace& rhs) const noexcept {
            return this->Cross(rhs);
        }

        VectorInThisSpace operator*=(const BaseInThisSpace& other) noexcept {
            *this = this->Cross(other);
            return VectorInThisSpace(m_impl);
        }

        [[nodiscard]] VectorInThisSpace Cross(const BaseInThisSpace& other) const noexcept {
            return VectorInThisSpace(m_impl.Cross(other.m_impl));
        }

        [[nodiscard]] friend VectorInThisSpace operator-(BaseInThisSpace lhs, const BaseInThisSpace& rhs) noexcept {
            lhs -= rhs;
            return VectorInThisSpace(lhs.m_impl);
        }

        VectorInThisSpace operator-=(const BaseInThisSpace& rhs) noexcept {
            m_impl = m_impl - rhs.m_impl;
            return VectorInThisSpace(m_impl);
        }

        [[nodiscard]] friend VectorInThisSpace operator+(BaseInThisSpace lhs, const BaseInThisSpace& rhs) noexcept {
            lhs += rhs;
            return VectorInThisSpace(lhs.m_impl);
        }

        VectorInThisSpace operator+=(const BaseInThisSpace& rhs) noexcept {
            m_impl = m_impl + rhs.m_impl;
            return VectorInThisSpace(m_impl);
        }

        [[nodiscard]] typename Space::Unit Mag() const noexcept {
            return Space::Unit{ m_impl.Mag() };
        }

        [[nodiscard]] double Mag_double() const noexcept {
            return m_impl.Mag();
        }

        [[nodiscard]] double Dot(const BaseInThisSpace& other) const noexcept {
            return m_impl.Dot(other.m_impl);
        }

        [[nodiscard]] NormalizedVectorInThisSpace Norm() const {
            return NormalizedVectorInThisSpace(m_impl);
        }

        //-------------------------------------------------------------------------------------
#ifndef IGNORE_SPACE_STATIC_ASSERT

        template <int I>
        typename std::enable_if<I != 0 && I != 1 && I != 2, StaticAssert::invalid_at_access>::type at() const {
            return StaticAssert::invalid_at_access{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_equality operator == (const VectorBase<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_equality{};
        }
        template <typename AnySpace>
        StaticAssert::invalid_point_vector_equality operator == (const Point<AnySpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_equality operator != (const VectorBase<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_equality{};
        }
        template <typename AnySpace>
        StaticAssert::invalid_point_vector_equality operator != (const Point<AnySpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_cross operator*(const VectorBase<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_vector_cross{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_cross Cross(const VectorBase<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_vector_cross{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_cross operator*=(const VectorBase<OtherSpace, ExternalImplementation>&) noexcept {
            return StaticAssert::invalid_vector_cross{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_to_vector_addition operator+(const VectorBase<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_vector_to_vector_addition{};
        }
        template <typename AnySpace>
        StaticAssert::invalid_point_to_vector_addition operator+(const Point<AnySpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_point_to_vector_addition{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_to_vector_addition operator+=(const VectorBase<OtherSpace, ExternalImplementation>&) noexcept {
            return StaticAssert::invalid_vector_to_vector_addition{};
        }
        template <typename AnySpace>
        StaticAssert::invalid_point_from_vector_subtraction operator-(const Point<AnySpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_point_from_vector_subtraction{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_to_vector_subtraction operator-(const VectorBase<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_vector_to_vector_subtraction{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_to_vector_subtraction operator-=(const VectorBase<OtherSpace, ExternalImplementation>&) noexcept {
            return StaticAssert::invalid_vector_to_vector_subtraction{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_dot Dot(const VectorBase<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_vector_dot{};
        }
#endif
    protected:
        detail::PointOrVector m_impl;
    };
}
