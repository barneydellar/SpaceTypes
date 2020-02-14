#pragma once

#include "BaseImpl.h"

namespace Space {

    template <typename Space>
    class NormalizedVector final : public detail::BaseImpl<Space>
    {
        friend class Vector<Space>;

        using _base = detail::BaseImpl<Space>;

        constexpr void Normalize() noexcept(false)
        {
            const auto mag = _base::MagHelper();
            if (mag == 0) {
                throw std::invalid_argument("Zero-sized normal vectors are not allowed");
            }
            std::transform(
                _base::m_values.cbegin(),
                _base::m_values.cend(),
                _base::m_values.begin(),
                [mag](auto v) {return v / mag;}
            );
        }

    public:

        //-------------------------------------------------------------------------------------

        constexpr explicit NormalizedVector(const std::array<double, 3> value) noexcept(false) : _base(value) { Normalize();}
        constexpr explicit NormalizedVector(const double x, const double y, const double z) noexcept(false) : _base(x, y, z) {Normalize();}
        constexpr explicit NormalizedVector(const double x, const double y) noexcept(false) : _base(x, y, 0) {Normalize();}
        constexpr NormalizedVector(const std::initializer_list<double> l) : _base(l) { Normalize(); }

        constexpr operator Vector<Space>() const noexcept {
            return Space::Vector(_base::m_values);
        }

        //-------------------------------------------------------------------------------------

        template <typename AnySpace>
        [[nodiscard]] constexpr bool operator == (const NormalizedVector<AnySpace>& other) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_equality{};
            }
            else {
                return std::equal(_base::m_values.cbegin(), _base::m_values.cend(), other.m_values.cbegin());
            }
        }

        template <typename AnySpace>
        [[nodiscard]] constexpr bool operator == (const Vector<AnySpace>& other) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_equality{};
            }
            else {
                return std::equal(_base::m_values.cbegin(), _base::m_values.cend(), other.m_values.cbegin());
            }
        }
        template <typename AnySpace>
        constexpr bool operator == (const Point<AnySpace>&) const noexcept {
            StaticAssert::invalid_point_vector_equality{};
        }
        //------------------------------------------------------------------------------------

        template <typename AnySpace>
        [[nodiscard]] constexpr bool operator != (const NormalizedVector<AnySpace>& other) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_equality{};
            }
            else {
                return !(operator==(other));
            }
        }

        template <typename AnySpace>
        [[nodiscard]] constexpr bool operator != (const Vector<AnySpace>& other) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_equality{};
            }
            else {
                return !(operator==(other));
            }
        }

        template <typename AnySpace>
        constexpr bool operator != (const Point<AnySpace>&) const noexcept {
            StaticAssert::invalid_point_vector_equality{};
        }

        //-------------------------------------------------------------------------------------

        template <typename AnySpace>
        [[nodiscard]] constexpr typename Space::Vector operator+(const NormalizedVector<AnySpace>& rhs) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_vector_to_vector_addition{};
            }
            else {
                return Space::Vector(_base::SumArrays(_base::m_values, rhs.m_values));
            }
        }

        template <typename AnySpace>
        [[nodiscard]] constexpr typename Space::Vector operator+(const Vector<AnySpace>& rhs) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_vector_to_vector_addition{};
            }
            else {
                return Space::Vector(_base::SumArrays(_base::m_values, rhs.m_values));
            }
        }

        template <typename AnySpace>
        constexpr typename AnySpace::Vector operator+(const Point<AnySpace>&) const noexcept {
            StaticAssert::invalid_point_to_vector_addition{};
        }

        //-------------------------------------------------------------------------------------

        // Prevent inline Scaling or Adding
        constexpr typename Space::Vector operator*=(const double&) const noexcept {
            StaticAssert::invalid_normalized_vector_scale{};
        }
        template <typename OtherSpace>
        constexpr typename OtherSpace::Vector operator+=(const Vector<OtherSpace>&) const noexcept {
            StaticAssert::invalid_normalized_vector_addition{};
        }
        template <typename OtherSpace>
        constexpr typename OtherSpace::Vector operator+=(const NormalizedVector<OtherSpace>&) const noexcept {
            StaticAssert::invalid_normalized_vector_addition{};
        }

        //-------------------------------------------------------------------------------------

        // Allow immutable scaling
        [[nodiscard]] constexpr typename Space::Vector operator*(const double& d) const noexcept {
            return Space::Vector(_base::ScaleArray(_base::m_values, d));
        }

        //-------------------------------------------------------------------------------------

        template <typename AnySpace>
        [[nodiscard]] constexpr double Dot(const NormalizedVector<AnySpace>& other) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_vector_dot{};
            }
            else {
                return _base::DotArrays(_base::m_values, other.m_values);
            }
        }

        template <typename AnySpace>
        [[nodiscard]] constexpr double Dot(const Vector<AnySpace>& other) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invainvalid_vector_dotlid_equality{};
            }
            else {
                return _base::DotArrays(_base::m_values, other.m_values);
            }
        }

        //-------------------------------------------------------------------------------------

        // Crossing
        [[nodiscard]] constexpr typename Space::NormalizedVector operator*(const NormalizedVector<Space>& rhs) const noexcept {
            return this->Cross(rhs);
        }
        [[nodiscard]] constexpr typename Space::Vector operator*(const Vector<Space>& rhs) const noexcept {
            return this->Cross(rhs);
        }
        [[nodiscard]] constexpr typename Space::NormalizedVector Cross(const NormalizedVector<Space>& other) const noexcept {
            return Space::NormalizedVector(_base::CrossArrays(_base::m_values, other.m_values));
        }
        [[nodiscard]] constexpr typename Space::Vector Cross(const Vector<Space>& other) const noexcept {
            return Space::Vector(_base::CrossArrays(_base::m_values, other.m_values));
        }

        //-------------------------------------------------------------------------------------

        constexpr double* begin() const noexcept {
            StaticAssert::normalized_vectors_do_not_support_non_const_iteration{};
        }
        constexpr double* end() const noexcept {
            StaticAssert::normalized_vectors_do_not_support_non_const_iteration{};
        }

        //-------------------------------------------------------------------------------------

        template <typename OtherSpace, typename TransformManager>
        [[nodiscard]] constexpr typename OtherSpace::Vector ConvertTo(const TransformManager& transform_manager) const noexcept {
            return typename OtherSpace::Vector(transform_manager.template Transform33<Space, OtherSpace>(_base::m_values));
        }

        //-------------------------------------------------------------------------------------
    };

    template <typename Space>
    constexpr std::ostream& operator << (
        std::ostream& os,
        const NormalizedVector<Space>& item
    ) {
        const auto space = SpaceTypeNameMap<Space>::name;
        os << space << "::NormalizedVector (" << item.X() << ", " << item.Y() << ", " << item.Z() << ")";
        return os;
    }
}
