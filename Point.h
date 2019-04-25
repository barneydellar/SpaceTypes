#pragma once

#include "BaseImpl.h"

namespace Space::detail {

    template <typename Space>
    class Vector;

    template <typename Space>
    class NormalizedVector;

    //--------------------------------------------------------------------------------------------

    template <typename Space>
    class Point final : public ModifiableBaseImpl<Space>
    {
        using _base = ModifiableBaseImpl<Space>;

    public:
        constexpr explicit Point(const std::array<double, 3> value) : _base(value) {}
        constexpr explicit Point(const double x, const double y, const double z) : _base(x, y, z) {}
        constexpr explicit Point(const double x, const double y) : _base(x, y) {}

        //------------------------------------------------------------------------------------

        constexpr bool operator == (const Point<Space>& other) const {
            return std::equal(_base::m_values.cbegin(), _base::m_values.cend(), other.m_values.cbegin());
        }
        template <typename WrongSpace>
        constexpr StaticAssert::invalid_equality operator == (const Point<WrongSpace>&) const {
            return StaticAssert::invalid_equality{};
        }
        template <typename AnySpace>
        constexpr StaticAssert::invalid_point_vector_equality operator == (const Vector<AnySpace>&) const {
            return StaticAssert::invalid_point_vector_equality{};
        }
        template <typename AnySpace>
        constexpr StaticAssert::invalid_point_vector_equality operator == (const NormalizedVector<AnySpace>&) const {
            return StaticAssert::invalid_point_vector_equality{};
        }

        //------------------------------------------------------------------------------------

        constexpr bool operator != (const Point<Space>& other) const {
            return !(operator==(other));
        }
        template <typename WrongSpace>
        constexpr StaticAssert::invalid_equality operator != (const Point<WrongSpace>&) const {
            return StaticAssert::invalid_equality{};
        }
        template <typename AnySpace>
        constexpr StaticAssert::invalid_point_vector_equality operator != (const Vector<AnySpace>&) const {
            return StaticAssert::invalid_point_vector_equality{};
        }

        //------------------------------------------------------------------------------------

        template <typename OtherSpace, typename TransformManager>
        constexpr typename OtherSpace::Point ConvertTo(const TransformManager& transform_manager) const {
            return typename OtherSpace::Point(transform_manager.template Transform<Space, OtherSpace>(_base::m_values));
        }

        //------------------------------------------------------------------------------------

        constexpr typename Space::Vector operator-(
            const Point<Space>& rhs
        ) const {
            std::array<double, 3> result{};
            std::transform(_base::m_values.cbegin(), _base::m_values.cend(), rhs.m_values.cbegin(), result.begin(), std::minus<double>());
            return Space::Vector(result);
        }
        template <typename WrongSpace>
        constexpr StaticAssert::invalid_subtraction operator-(const Point<WrongSpace>&) const {
            return StaticAssert::invalid_subtraction{};
        }

        //------------------------------------------------------------------------------------

        // Operators:
        constexpr typename Space::Point operator+(const Vector<Space>& rhs) const {
            std::array<double, 3> result;
            std::transform(_base::m_values.cbegin(), _base::m_values.cend(), rhs.m_values.cbegin(), result.begin(), std::plus<double>());
            return Space::Point(result);
        }
        template <typename WrongSpace>
        constexpr StaticAssert::invalid_vector_to_point_addition operator+(const Vector<WrongSpace>&) const {
            return StaticAssert::invalid_vector_to_point_addition{};
        }

        constexpr typename Space::Point operator+=(const Vector<Space>& rhs) {
            std::transform(_base::m_values.cbegin(), _base::m_values.cend(), rhs.m_values.cbegin(), _base::m_values.begin(), std::plus<double>());
            return *this;
        }
        template <typename WrongSpace>
        constexpr StaticAssert::invalid_vector_to_point_addition operator+=(const Vector<WrongSpace>&) const {
            return StaticAssert::invalid_vector_to_point_addition{};
        }
    };

    template <typename Space>
    constexpr std::ostream& operator << (
        std::ostream& os,
        const Point<Space>& item
    ) {
        const auto space = SpaceTypeNameMap<Space>::name;
        os << space << "::Point (" << item.X() << ", " << item.Y() << ", " << item.Z() << ")";
        return os;
    }
}