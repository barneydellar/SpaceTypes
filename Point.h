#pragma once
#include "SpaceImpl.h"

namespace Space {

    template <typename Space, typename ExternalImplementation>
    class Point final
    {
        friend class Vector<Space, ExternalImplementation>;

        using PointInThisSpace = PointInASpace<Space>;
        using VectorInThisSpace = VectorInASpace<Space>;

    public:
        Point(const detail::PointOrVector& v) noexcept : m_impl(v) {}
        constexpr Point() noexcept : m_impl(0, 0, 0) {}
        constexpr explicit Point(const ExternalImplementation& v) noexcept : m_impl(v.X(), v.Y(), v.Z()) {}
        constexpr explicit Point(const double x, const double y, const double z) noexcept : m_impl(x, y, z) {}
        constexpr explicit Point(const double x, const double y) noexcept : m_impl(x, y, 0) {}
        constexpr Point(const std::initializer_list<double> l) : m_impl(l) {}

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

        [[nodiscard]] constexpr bool operator == (const PointInThisSpace& other) const noexcept {
            return m_impl.operator==(other.m_impl);
        }

        [[nodiscard]] constexpr bool operator != (const PointInThisSpace& other) const noexcept {
            return !(operator==(other));
        }

        template <typename OtherSpace, typename TransformManager>
        [[nodiscard]] constexpr PointInASpace<OtherSpace> ConvertTo(const TransformManager& transform_manager) const {
            return PointInASpace<OtherSpace>(transform_manager.template Transform<Space, OtherSpace>(static_cast<ExternalImplementation>(*this)));
        }

        [[nodiscard]] friend VectorInThisSpace operator-(PointInThisSpace lhs, const PointInThisSpace& rhs) {
            return VectorInThisSpace(lhs.m_impl - rhs.m_impl);
        }

        [[nodiscard]] friend PointInThisSpace operator+(PointInThisSpace lhs, const VectorInThisSpace& rhs) noexcept {
            lhs += rhs;
            return lhs;
        }

        PointInThisSpace& operator+=(const VectorInThisSpace& rhs) noexcept {
            m_impl = m_impl + rhs.m_impl;
            return *this;
        }

        [[nodiscard]] friend PointInThisSpace operator-(PointInThisSpace lhs, const VectorInThisSpace& rhs) noexcept {
            lhs -= rhs;
            return lhs;
        }

        PointInThisSpace& operator-=(const VectorInThisSpace& rhs) noexcept {
            m_impl = m_impl - rhs.m_impl;
            return *this;
        }


        //------------------------------------------------------------------------------------

#ifndef IGNORE_SPACE_STATIC_ASSERT

        template <int I>
        typename std::enable_if<I != 0 && I != 1 && I != 2, StaticAssert::invalid_at_access>::type at() const {
            return StaticAssert::invalid_at_access{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_equality operator == (const Point<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_equality{};
        }
        template <typename AnySpace>
        StaticAssert::invalid_point_vector_equality operator == (const Vector<AnySpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_equality operator != (const Point<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_equality{};
        }
        template <typename AnySpace>
        StaticAssert::invalid_point_vector_equality operator != (const Vector<AnySpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_subtraction operator-(const Point<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_subtraction{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_to_point_addition operator+(const Vector<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_vector_to_point_addition{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_to_point_addition operator+=(const Vector<OtherSpace, ExternalImplementation>&) noexcept {
            return StaticAssert::invalid_vector_to_point_addition{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_from_point_subtraction operator-(const Vector<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_vector_from_point_subtraction{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_from_point_subtraction operator-=(const Vector<OtherSpace, ExternalImplementation>&) noexcept {
            return StaticAssert::invalid_vector_from_point_subtraction{};
        }

#endif

    private:

        detail::PointOrVector m_impl;
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
