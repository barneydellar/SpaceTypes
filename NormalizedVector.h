#pragma once
/**************************************************************************************************

Copyright (C) 2018 Canon Medical Systems Corporation. All rights reserved.

**************************************************************************************************/

// This is an implementation header. DO NOT include it directly. Just include Space.h

#include "BaseImpl.h"

namespace Space::detail {

    template <typename Space>
    class NormalizedVector final : public BaseImpl<Space>
    {
        friend class Vector<Space>;

        using _base = BaseImpl<Space>;

        void Normalise()
        {
            const auto mag = _base::MagHelper();
            if (mag == 0) {
                throw std::invalid_argument("Zero-sized normal vectors are not allowed");
            }
            std::transform(_base::m_values.cbegin(), _base::m_values.cend(), _base::m_values.begin(), [mag](auto v) {return v / mag;});
        }

    public:

        //-------------------------------------------------------------------------------------

        explicit NormalizedVector(const std::array<double, 3> value) : _base(value) { Normalise();}
        explicit NormalizedVector(const double x, const double y, const double z) : _base(x, y, z) { Normalise(); }
        explicit NormalizedVector(const double x, const double y) : _base(x, y, 0) { Normalise(); }

        operator Vector<Space>() const {
            return Space::Vector(_base::m_values);
        }

        //-------------------------------------------------------------------------------------

        bool operator == (const NormalizedVector<Space>& other) const {
            return std::equal(_base::m_values.cbegin(), _base::m_values.cend(), other.m_values.cbegin());
        }
        bool operator == (const Vector<Space>& other) const {
            return std::equal(_base::m_values.cbegin(), _base::m_values.cend(), other.m_values.cbegin());
        }
        template <typename WrongSpace>
        StaticAssert::invalid_equality operator == (const NormalizedVector<WrongSpace>&) const {
            return StaticAssert::invalid_equality{};
        }
        template <typename WrongSpace>
        StaticAssert::invalid_equality operator == (const Vector<WrongSpace>&) const {
            return StaticAssert::invalid_equality{};
        }
        template <typename AnySpace>
        StaticAssert::invalid_point_vector_equality operator == (const Point<AnySpace>&) const {
            return StaticAssert::invalid_point_vector_equality{};
        }
        //------------------------------------------------------------------------------------

        bool operator != (const NormalizedVector<Space>& other) const {
            return !(operator==(other));
        }
        bool operator != (const Vector<Space>& other) const {
            return !(operator==(other));
        }
        template <typename WrongSpace>
        StaticAssert::invalid_equality operator != (const NormalizedVector<WrongSpace>&) const {
            return StaticAssert::invalid_equality{};
        }
        template <typename WrongSpace>
        StaticAssert::invalid_equality operator != (const Vector<WrongSpace>&) const {
            return StaticAssert::invalid_equality{};
        }
        template <typename AnySpace>
        StaticAssert::invalid_point_vector_equality operator != (const Point<AnySpace>&) const {
            return StaticAssert::invalid_point_vector_equality{};
        }

        //-------------------------------------------------------------------------------------

        typename Space::Vector operator+(const NormalizedVector<Space>& rhs) const {
            return Space::Vector(_base::SumArrays(_base::m_values, rhs.m_values));
        }
        typename Space::Vector operator+(const Vector<Space>& rhs) const {
            return Space::Vector(_base::SumArrays(_base::m_values, rhs.m_values));
        }
        template <typename WrongSpace>
        StaticAssert::invalid_vector_to_vector_addition operator+(const NormalizedVector<WrongSpace>&) const {
            return StaticAssert::invalid_vector_to_vector_addition{};
        }
        template <typename WrongSpace>
        StaticAssert::invalid_vector_to_vector_addition operator+(const Vector<WrongSpace>&) const {
            return StaticAssert::invalid_vector_to_vector_addition{};
        }
        template <typename AnySpace>
        StaticAssert::invalid_point_to_vector_addition operator+(const Point<AnySpace>&) const {
            return StaticAssert::invalid_point_to_vector_addition{};
        }

        //-------------------------------------------------------------------------------------

        // Prevent inline Scaling or Adding

        StaticAssert::invalid_normalized_vector_scale operator*=(const double&) const {
            return StaticAssert::invalid_normalized_vector_scale{};
        }

        template <typename OtherSpace>
        StaticAssert::invalid_normalized_vector_addition operator+=(const Vector<OtherSpace>&) const {
            return StaticAssert::invalid_normalized_vector_addition{};
        }

        template <typename OtherSpace>
        StaticAssert::invalid_normalized_vector_addition operator+=(const NormalizedVector<OtherSpace>&) const {
            return StaticAssert::invalid_normalized_vector_addition{};
        }

        //-------------------------------------------------------------------------------------

        // Allow immutable scaling

        typename Space::Vector operator*(const double& d) const {
            return Space::Vector(_base::ScaleArray(_base::m_values, d));
        }

        //-------------------------------------------------------------------------------------

        double Dot(const NormalizedVector<Space>& other) const {
            return _base::DotArrays(_base::m_values, other.m_values);
        }
        double Dot(const Vector<Space>& other) const {
            return _base::DotArrays(_base::m_values, other.m_values);
        }
        template <typename WrongSpace>
        StaticAssert::invalid_vector_dot Dot(const NormalizedVector<WrongSpace>&) const {
            return StaticAssert::invalid_vector_dot{};
        }
        template <typename WrongSpace>
        StaticAssert::invalid_vector_dot Dot(const Vector<WrongSpace>&) const {
            return StaticAssert::invalid_vector_dot{};
        }

        //-------------------------------------------------------------------------------------

        // Crossing
        typename Space::NormalizedVector operator*(const NormalizedVector<Space>& rhs) const {
            return this->Cross(rhs);
        }
        typename Space::Vector operator*(const Vector<Space>& rhs) const {
            return this->Cross(rhs);
        }

        typename Space::NormalizedVector Cross(const NormalizedVector<Space>& other) const {
            return Space::NormalizedVector(_base::CrossArrays(_base::m_values, other.m_values));
        }

        typename Space::Vector Cross(const Vector<Space>& other) const {
            return Space::Vector(_base::CrossArrays(_base::m_values, other.m_values));
        }

        //-------------------------------------------------------------------------------------

        StaticAssert::normalized_vectors_do_not_support_non_const_iteration begin() const {
            return StaticAssert::normalized_vectors_do_not_support_non_const_iteration{};
        }

        StaticAssert::normalized_vectors_do_not_support_non_const_iteration end() const {
            return StaticAssert::normalized_vectors_do_not_support_non_const_iteration{};
        }

        //-------------------------------------------------------------------------------------

        template <typename OtherSpace, typename TransformManager>
        typename OtherSpace::Vector ConvertTo(const TransformManager& transform_manager) const {
            return typename OtherSpace::Vector(transform_manager.template Transform33<Space, OtherSpace>(_base::m_values));
        }

        //-------------------------------------------------------------------------------------
    };

    template <typename Space>
    std::ostream& operator << (
        std::ostream& os,
        const NormalizedVector<Space>& item
    ) {
        const auto space = SpaceTypeNameMap<Space>::name;
        os << space << "::NormalizedVector (" << item.X() << ", " << item.Y() << ", " << item.Z() << ")";
        return os;
    }
}
