#pragma once

#include "BaseImpl.h"

namespace Space {

    template <typename Space>
    class Vector;

    template <typename Space>
    class NormalizedVector;

    //--------------------------------------------------------------------------------------------

    template <typename Space>
    class Point final : public detail::ModifiableBaseImpl<Space>
    {
        using _base = detail::ModifiableBaseImpl<Space>;

    public:
        constexpr explicit Point(const std::array<double, 3> value) noexcept: _base(value) {}
        constexpr explicit Point(const double x, const double y, const double z) noexcept : _base(x, y, z) {}
        constexpr explicit Point(const double x, const double y) noexcept : _base(x, y) {}
        constexpr Point(const std::initializer_list<double> l) : _base(l) {}

        //------------------------------------------------------------------------------------

        template <typename AnySpace>
        [[nodiscard]] constexpr bool operator == (const Point<AnySpace>& other) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_equality{};
            }
            else {
                return std::equal(_base::m_values.cbegin(), _base::m_values.cend(), other.m_values.cbegin());
            }
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

        template <typename AnySpace>
        [[nodiscard]] constexpr bool operator != (const Point<AnySpace>& other) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_equality{};
            } else {
                return !(operator==(other));
            }
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

        template <typename AnySpace>
        [[nodiscard]] constexpr typename Space::Vector operator-(
            const Point<AnySpace>& rhs
        ) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_subtraction{};
            }
            else {
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
        }

        //------------------------------------------------------------------------------------

        template <typename AnySpace>
        [[nodiscard]] constexpr typename Space::Point operator+(const Vector<AnySpace>& rhs) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_vector_to_point_addition{};
            }
            else {
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
        }

        template <typename AnySpace>
        constexpr typename Space::Point operator+=(const Vector<AnySpace>& rhs) noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_vector_to_point_addition{};
            }
            else {
                std::transform(
                    _base::m_values.cbegin(),
                    _base::m_values.cend(),
                    rhs.m_values.cbegin(),
                    _base::m_values.begin(),
                    std::plus<>()
                );
                return *this;
            }
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