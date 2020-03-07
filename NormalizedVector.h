#pragma once
#include "SpaceImpl.h"

namespace Space {

    template <typename Space, typename ExternalImplementation>
    class NormalizedVector final
    {

        friend class Vector< Space, ExternalImplementation>;

        using VectorInThisSpace = VectorInASpace<Space>;
        using NormalizedVectorInThisSpace = NormalizedVectorInASpace<Space>;

    public:

        NormalizedVector(const detail::PointOrVector& v) noexcept(false) : m_impl(v) { m_impl.Normalize(); }
        constexpr NormalizedVector() noexcept(false) : m_impl(1, 0, 0) { m_impl.Normalize(); }
        constexpr explicit NormalizedVector(const ExternalImplementation& v) noexcept(false) : m_impl(v.X(), v.Y(), v.Z()) { m_impl.Normalize(); }
        constexpr explicit NormalizedVector(const double x, const double y, const double z) noexcept(false) : m_impl(x, y, z) { m_impl.Normalize();}
        constexpr explicit NormalizedVector(const double x, const double y) noexcept(false) : m_impl(x, y, 0) { m_impl.Normalize();}
        constexpr NormalizedVector(const std::initializer_list<double> l) noexcept(false) : m_impl(l) { m_impl.Normalize();}

        [[nodiscard]] explicit constexpr operator ExternalImplementation() const noexcept {
            return ExternalImplementation(m_impl.X(), m_impl.Y(), m_impl.Z());
        }

        [[nodiscard]] constexpr operator VectorInThisSpace() const noexcept {
            return VectorInThisSpace(m_impl);
        }

        [[nodiscard]] constexpr double X() const noexcept { return m_impl.X(); }
        [[nodiscard]] constexpr double Y() const noexcept { return m_impl.Y(); }
        [[nodiscard]] constexpr double Z() const noexcept { return m_impl.Z(); }

        [[nodiscard]] constexpr double operator[] (const unsigned int i) const {return m_impl[i];}

        template <int I>
        [[nodiscard]] typename std::enable_if<I == 0 || I == 1 || I == 2, double>::type at() const {
            return m_impl[I];
        }
        [[nodiscard]] constexpr bool operator == (const NormalizedVectorInThisSpace& other) const noexcept {
            return m_impl.operator==(other.m_impl);
        }
        [[nodiscard]] constexpr bool operator == (const VectorInThisSpace& other) const noexcept {
            return m_impl.operator==(other.m_impl);
        }
        [[nodiscard]] constexpr bool operator != (const NormalizedVectorInThisSpace& other) const noexcept {
            return !(operator==(other));
        }
        [[nodiscard]] constexpr bool operator != (const VectorInThisSpace& other) const noexcept {
            return !(operator==(other));
        }
        [[nodiscard]] constexpr VectorInThisSpace operator+(const NormalizedVectorInThisSpace& other) const noexcept {
            return VectorInThisSpace(m_impl + other.m_impl);
        }
        [[nodiscard]] constexpr VectorInThisSpace operator+(const VectorInThisSpace& other) const noexcept {
            return VectorInThisSpace(m_impl + other.m_impl);
        }
        [[nodiscard]] constexpr VectorInThisSpace operator-(const NormalizedVectorInThisSpace& other) const noexcept {
            return VectorInThisSpace(m_impl - other.m_impl);
        }
        [[nodiscard]] constexpr VectorInThisSpace operator-(const VectorInThisSpace& other) const noexcept {
            return VectorInThisSpace(m_impl - other.m_impl);
        }
        [[nodiscard]] constexpr VectorInThisSpace operator*(const double& d) const noexcept {
            return VectorInThisSpace(m_impl * d);
        }
        [[nodiscard]] constexpr double Dot(const NormalizedVectorInThisSpace& other) const noexcept {
            return m_impl.Dot(other.m_impl);
        }
        [[nodiscard]] constexpr double Dot(const VectorInThisSpace& other) const noexcept {
            return m_impl.Dot(other.m_impl);
        }
        [[nodiscard]] constexpr NormalizedVectorInThisSpace operator*(const NormalizedVectorInThisSpace& rhs) const noexcept {
            return this->Cross(rhs);
        }
        [[nodiscard]] constexpr VectorInThisSpace operator*(const VectorInThisSpace& rhs) const noexcept {
            return this->Cross(rhs);
        }
        [[nodiscard]] constexpr NormalizedVectorInThisSpace Cross(const NormalizedVectorInThisSpace& other) const noexcept {
            return NormalizedVectorInThisSpace(m_impl.Cross(other.m_impl));
        }
        [[nodiscard]] constexpr VectorInThisSpace Cross(const VectorInThisSpace& other) const noexcept {
            return VectorInThisSpace(m_impl.Cross(other.m_impl));
        }
        template <typename OtherSpace, typename TransformManager>
        [[nodiscard]] constexpr VectorInASpace<OtherSpace> ConvertTo(const TransformManager& transform_manager) const noexcept {
            return VectorInASpace<OtherSpace>(transform_manager.template Transform33<Space, OtherSpace>(static_cast<ExternalImplementation>(*this)));
        }

        //-------------------------------------------------------------------------------------

#ifndef IGNORE_SPACE_STATIC_ASSERT

        template <int I>
        typename std::enable_if<I != 0 && I != 1 && I != 2, StaticAssert::invalid_at_access>::type at() const {
            return StaticAssert::invalid_at_access{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_equality operator == (const NormalizedVector<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_equality{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_equality operator == (const Vector<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_equality{};
        }
        template <typename AnySpace>
        StaticAssert::invalid_point_vector_equality operator == (const Point<AnySpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_equality operator != (const NormalizedVector<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_equality{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_equality operator != (const Vector<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_equality{};
        }
        template <typename AnySpace>
        StaticAssert::invalid_point_vector_equality operator != (const Point<AnySpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_to_vector_addition operator+(const NormalizedVector<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_vector_to_vector_addition{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_to_vector_addition operator+(const Vector<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_vector_to_vector_addition{};
        }
        template <typename AnySpace>
        StaticAssert::invalid_point_to_vector_addition operator+(const Point<AnySpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_point_to_vector_addition{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_to_vector_subtraction operator-(const NormalizedVector<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_vector_to_vector_subtraction{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_to_vector_subtraction operator-(const Vector<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_vector_to_vector_subtraction{};
        }

        StaticAssert::invalid_normalized_vector_scale operator*=(const double&) const noexcept {
            return StaticAssert::invalid_normalized_vector_scale{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_normalized_vector_addition operator+=(const Vector<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_normalized_vector_addition{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_normalized_vector_addition operator+=(const NormalizedVector<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_normalized_vector_addition{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_normalized_vector_subtraction operator-=(const Vector<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_normalized_vector_subtraction{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_normalized_vector_subtraction operator-=(const NormalizedVector<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_normalized_vector_subtraction{};
        }

        template <typename OtherSpace>
        StaticAssert::invalid_vector_dot Dot(const NormalizedVector<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_vector_dot{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_dot Dot(const Vector<OtherSpace, ExternalImplementation>&) const noexcept {
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

        detail::PointOrVector m_impl;
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
