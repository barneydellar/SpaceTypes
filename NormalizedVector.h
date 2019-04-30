#pragma once

#include "BaseImpl.h"

namespace Space::detail {

    template <typename Space>
    class NormalizedVector final : public BaseImpl<Space>
    {
        friend class Vector<Space>;

        using _base = BaseImpl<Space>;

        constexpr void Normalise() noexcept(false)
        {
            const auto mag = _base::MagHelper();
            if (mag == 0) {
                throw std::invalid_argument("Zero-sized normal vectors are not allowed");
            }
            std::transform(_base::m_values.cbegin(), _base::m_values.cend(), _base::m_values.begin(), [mag](auto v) {return v / mag;});
        }

    public:

        //-------------------------------------------------------------------------------------

        constexpr explicit NormalizedVector(const std::array<double, 3> value) noexcept(false) : _base(value) { Normalise();}
        constexpr explicit NormalizedVector(const double x, const double y, const double z) noexcept(false) : _base(x, y, z) { Normalise(); }
        constexpr explicit NormalizedVector(const double x, const double y) noexcept(false) : _base(x, y, 0) { Normalise(); }

        constexpr operator Vector<Space>() const noexcept {
            return Space::Vector(_base::m_values);
        }

        //-------------------------------------------------------------------------------------

        constexpr bool operator == (const NormalizedVector<Space>& other) const noexcept {
            return std::equal(_base::m_values.cbegin(), _base::m_values.cend(), other.m_values.cbegin());
        }
        constexpr bool operator == (const Vector<Space>& other) const noexcept {
            return std::equal(_base::m_values.cbegin(), _base::m_values.cend(), other.m_values.cbegin());
        }
        template <typename WrongSpace>
        constexpr StaticAssert::invalid_equality operator == (const NormalizedVector<WrongSpace>&) const noexcept {
            return StaticAssert::invalid_equality{};
        }
        template <typename WrongSpace>
        constexpr StaticAssert::invalid_equality operator == (const Vector<WrongSpace>&) const noexcept {
            return StaticAssert::invalid_equality{};
        }
        template <typename AnySpace>
        constexpr StaticAssert::invalid_point_vector_equality operator == (const Point<AnySpace>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        //------------------------------------------------------------------------------------

        constexpr bool operator != (const NormalizedVector<Space>& other) const noexcept {
            return !(operator==(other));
        }
        constexpr bool operator != (const Vector<Space>& other) const noexcept {
            return !(operator==(other));
        }
        template <typename WrongSpace>
        constexpr StaticAssert::invalid_equality operator != (const NormalizedVector<WrongSpace>&) const noexcept {
            return StaticAssert::invalid_equality{};
        }
        template <typename WrongSpace>
        constexpr StaticAssert::invalid_equality operator != (const Vector<WrongSpace>&) const noexcept {
            return StaticAssert::invalid_equality{};
        }
        template <typename AnySpace>
        constexpr StaticAssert::invalid_point_vector_equality operator != (const Point<AnySpace>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }

        //-------------------------------------------------------------------------------------

        constexpr typename Space::Vector operator+(const NormalizedVector<Space>& rhs) const noexcept {
            return Space::Vector(_base::SumArrays(_base::m_values, rhs.m_values));
        }
        constexpr typename Space::Vector operator+(const Vector<Space>& rhs) const noexcept {
            return Space::Vector(_base::SumArrays(_base::m_values, rhs.m_values));
        }
        template <typename WrongSpace>
        constexpr StaticAssert::invalid_vector_to_vector_addition operator+(const NormalizedVector<WrongSpace>&) const noexcept {
            return StaticAssert::invalid_vector_to_vector_addition{};
        }
        template <typename WrongSpace>
        constexpr StaticAssert::invalid_vector_to_vector_addition operator+(const Vector<WrongSpace>&) const noexcept {
            return StaticAssert::invalid_vector_to_vector_addition{};
        }
        template <typename AnySpace>
        constexpr StaticAssert::invalid_point_to_vector_addition operator+(const Point<AnySpace>&) const noexcept {
            return StaticAssert::invalid_point_to_vector_addition{};
        }

        //-------------------------------------------------------------------------------------

        // Prevent inline Scaling or Adding

        constexpr StaticAssert::invalid_normalized_vector_scale operator*=(const double&) const noexcept {
            return StaticAssert::invalid_normalized_vector_scale{};
        }

        template <typename OtherSpace>
        constexpr StaticAssert::invalid_normalized_vector_addition operator+=(const Vector<OtherSpace>&) const noexcept {
            return StaticAssert::invalid_normalized_vector_addition{};
        }

        template <typename OtherSpace>
        constexpr StaticAssert::invalid_normalized_vector_addition operator+=(const NormalizedVector<OtherSpace>&) const noexcept {
            return StaticAssert::invalid_normalized_vector_addition{};
        }

        //-------------------------------------------------------------------------------------

        // Allow immutable scaling

        constexpr typename Space::Vector operator*(const double& d) const noexcept {
            return Space::Vector(_base::ScaleArray(_base::m_values, d));
        }

        //-------------------------------------------------------------------------------------

        constexpr double Dot(const NormalizedVector<Space>& other) const noexcept {
            return _base::DotArrays(_base::m_values, other.m_values);
        }
        constexpr double Dot(const Vector<Space>& other) const noexcept {
            return _base::DotArrays(_base::m_values, other.m_values);
        }
        template <typename WrongSpace>
        constexpr StaticAssert::invalid_vector_dot Dot(const NormalizedVector<WrongSpace>&) const noexcept {
            return StaticAssert::invalid_vector_dot{};
        }
        template <typename WrongSpace>
        constexpr StaticAssert::invalid_vector_dot Dot(const Vector<WrongSpace>&) const noexcept {
            return StaticAssert::invalid_vector_dot{};
        }

        //-------------------------------------------------------------------------------------

        // Crossing
        constexpr typename Space::NormalizedVector operator*(const NormalizedVector<Space>& rhs) const noexcept {
            return this->Cross(rhs);
        }
        constexpr typename Space::Vector operator*(const Vector<Space>& rhs) const noexcept {
            return this->Cross(rhs);
        }

        constexpr typename Space::NormalizedVector Cross(const NormalizedVector<Space>& other) const noexcept {
            return Space::NormalizedVector(_base::CrossArrays(_base::m_values, other.m_values));
        }

        constexpr typename Space::Vector Cross(const Vector<Space>& other) const noexcept {
            return Space::Vector(_base::CrossArrays(_base::m_values, other.m_values));
        }

        //-------------------------------------------------------------------------------------

        constexpr StaticAssert::normalized_vectors_do_not_support_non_const_iteration begin() const noexcept {
            return StaticAssert::normalized_vectors_do_not_support_non_const_iteration{};
        }

        constexpr StaticAssert::normalized_vectors_do_not_support_non_const_iteration end() const noexcept {
            return StaticAssert::normalized_vectors_do_not_support_non_const_iteration{};
        }

        //-------------------------------------------------------------------------------------

        template <typename OtherSpace, typename TransformManager>
        constexpr typename OtherSpace::Vector ConvertTo(const TransformManager& transform_manager) const noexcept {
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
