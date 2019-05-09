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
        constexpr explicit Point(const std::array<double, 3> value) noexcept: _base(value) {}
        constexpr explicit Point(const double x, const double y, const double z) noexcept : _base(x, y, z) {}
        constexpr explicit Point(const double x, const double y) noexcept : _base(x, y) {}

        //------------------------------------------------------------------------------------

        [[nodiscard]] constexpr bool operator == (const Point<Space>& other) const noexcept {
            return std::equal(_base::m_values.cbegin(), _base::m_values.cend(), other.m_values.cbegin());
        }
        template <typename WrongSpace>
        constexpr bool operator == (const Point<WrongSpace>&) const noexcept {

            static_assert(false, "It is not valid to compare items from different spaces");

        }
        template <typename AnySpace>
        constexpr bool operator == (const Vector<AnySpace>&) const noexcept {
            StaticAssert::invalid_point_vector_equality{};
        }
        template <typename AnySpace>
        constexpr bool operator == (const NormalizedVector<AnySpace>&) const noexcept {
            StaticAssert::invalid_point_vector_equality{};
        }

        //------------------------------------------------------------------------------------

        [[nodiscard]] constexpr bool operator != (const Point<Space>& other) const noexcept {
            return !(operator==(other));
        }
        template <typename WrongSpace>
        constexpr bool operator != (const Point<WrongSpace>&) const noexcept {
            StaticAssert::invalid_equality{};
        }
        template <typename AnySpace>
        constexpr bool operator != (const Vector<AnySpace>&) const noexcept {
            StaticAssert::invalid_point_vector_equality{};
        }

        //------------------------------------------------------------------------------------

        template <typename OtherSpace, typename TransformManager>
        [[nodiscard]] constexpr typename OtherSpace::Point ConvertTo(const TransformManager& transform_manager) const {
            return typename OtherSpace::Point(transform_manager.template Transform<Space, OtherSpace>(_base::m_values));
        }

        //------------------------------------------------------------------------------------

        [[nodiscard]] constexpr typename Space::Vector operator-(
            const Point<Space>& rhs
        ) const noexcept {
            std::array<double, 3> result{};
            std::transform(
                _base::m_values.cbegin(), 
                _base::m_values.cend(), 
                rhs.m_values.cbegin(), 
                result.begin(), 
                std::minus<>()
            );
            return Space::Vector(result);
        }
        template <typename WrongSpace>
        constexpr typename WrongSpace::Vector operator-(const Point<WrongSpace>&) const noexcept {
            StaticAssert::invalid_subtraction{};
        }

        //------------------------------------------------------------------------------------

        // Operators:
        [[nodiscard]] constexpr typename Space::Point operator+(const Vector<Space>& rhs) const noexcept {
            std::array<double, 3> result{};
            std::transform(
                _base::m_values.cbegin(), 
                _base::m_values.cend(), 
                rhs.m_values.cbegin(), 
                result.begin(),
                std::plus<>()
            );
            return Space::Point(result);
        }
        template <typename WrongSpace>
        constexpr typename WrongSpace::Point operator+(const Vector<WrongSpace>&) const noexcept {
            StaticAssert::invalid_vector_to_point_addition{};
        }

        constexpr typename Space::Point operator+=(const Vector<Space>& rhs) noexcept {
            std::transform(
                _base::m_values.cbegin(), 
                _base::m_values.cend(), 
                rhs.m_values.cbegin(), 
                _base::m_values.begin(), 
                std::plus<>()
            );
            return *this;
        }
        template <typename WrongSpace>
        constexpr typename WrongSpace::Vector operator+=(const Vector<WrongSpace>&) const noexcept {
            StaticAssert::invalid_vector_to_point_addition{};
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