#pragma once
#include "BaseImpl.h"
#include "NormalizedVector.h"

namespace Space::detail {

    //--------------------------------------------------------------------------------------------

    template <typename Space>
    class Vector final : public ModifiableBaseImpl<Space>
    {
        friend class Space::NormalizedVector;
        friend class Space::Point;
        using _base = ModifiableBaseImpl<Space>;

    public:

        constexpr explicit Vector(const std::array<double, 3> value) noexcept : _base(value) {}
        constexpr explicit Vector(const double x, const double y, const double z) noexcept : _base(x, y, z) {}
        constexpr explicit Vector(const double x, const double y) noexcept : _base(x, y) {}
        constexpr explicit Vector(const typename Space::NormalizedVector nv) noexcept : _base(nv.X(), nv.Y(), nv.Z()) {}

        //------------------------------------------------------------------------------------

        [[nodiscard]] constexpr bool operator == (const typename Space::Vector& other) const noexcept {
            return std::equal(_base::m_values.cbegin(), _base::m_values.cend(), other.m_values.cbegin());
        }
        [[nodiscard]] constexpr bool operator == (const typename Space::NormalizedVector& other) const noexcept {
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

        [[nodiscard]] constexpr bool operator != (const typename Space::Vector& other) const noexcept {
            return !(operator==(other));
        }
        [[nodiscard]] constexpr bool operator != (const typename Space::NormalizedVector& other) const noexcept {
            return !(operator==(other));
        }
        template <typename WrongSpace>
        constexpr StaticAssert::invalid_equality operator != (const Vector<WrongSpace>&) const noexcept {
            return StaticAssert::invalid_equality{};
        }
        template <typename WrongSpace>
        constexpr StaticAssert::invalid_equality operator != (const NormalizedVector<WrongSpace>&) const noexcept {
            return StaticAssert::invalid_equality{};
        }
        template <typename AnySpace>
        constexpr StaticAssert::invalid_point_vector_equality operator != (const Point<AnySpace>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }

        //-------------------------------------------------------------------------------------

        template <typename OtherSpace, typename TransformManager>
        [[nodiscard]] constexpr typename OtherSpace::Vector ConvertTo(const TransformManager& transform_manager) const noexcept {
            return typename OtherSpace::Vector(transform_manager.template Transform33<Space, OtherSpace>(_base::m_values));
        }

        //------------------------------------------------------------------------------------

        // Operators
        [[nodiscard]] constexpr typename Space::Vector operator*(const double& d) const noexcept {
            return Space::Vector(_base::ScaleArray(_base::m_values, d));
        }
        constexpr typename Space::Vector& operator*=(const double& d) noexcept {
            _base::m_values = _base::ScaleArray(_base::m_values, d);
            return *this;
        }

        [[nodiscard]] constexpr typename Space::Vector operator*(const typename Space::Vector& rhs) const noexcept {
            return this->Cross(rhs);
        }
        template <typename WrongSpace>
        [[nodiscard]] constexpr StaticAssert::invalid_vector_cross operator*(const Vector<WrongSpace>&) const noexcept {
            return StaticAssert::invalid_vector_cross{};
        }

        constexpr typename Space::Vector operator*=(const typename Space::Vector& rhs) noexcept {
            return *this = this->Cross(rhs);
        }
        template <typename WrongSpace>
        constexpr StaticAssert::invalid_vector_cross operator*=(const Vector<WrongSpace>&) const noexcept {
            return StaticAssert::invalid_vector_cross{};
        }

        //-------------------------------------------------------------------------------------

        [[nodiscard]] constexpr typename Space::Vector operator+(const typename Space::Vector& rhs) const noexcept {
            return Space::Vector(_base::SumArrays(_base::m_values, rhs.m_values));
        }
        [[nodiscard]] constexpr typename Space::Vector operator+(const typename Space::NormalizedVector& rhs) const noexcept {
            return Space::Vector(_base::SumArrays(_base::m_values, rhs.m_values));
        }
        template <typename WrongSpace>
        constexpr StaticAssert::invalid_vector_to_vector_addition operator+(const Vector<WrongSpace>&) const noexcept {
            return StaticAssert::invalid_vector_to_vector_addition{};
        }
        template <typename WrongSpace>
        constexpr StaticAssert::invalid_vector_to_vector_addition operator+(const NormalizedVector<WrongSpace>&) const noexcept {
            return StaticAssert::invalid_vector_to_vector_addition{};
        }
        template <typename AnySpace>
        constexpr StaticAssert::invalid_point_to_vector_addition operator+(const Point<AnySpace>&) const noexcept {
            return StaticAssert::invalid_point_to_vector_addition{};
        }

        //-------------------------------------------------------------------------------------

        constexpr typename Space::Vector operator+=(const typename Space::Vector& rhs) noexcept {
            _base::m_values = _base::SumArrays(_base::m_values, rhs.m_values);
            return *this;
        }
        constexpr typename Space::Vector operator+=(const typename Space::NormalizedVector& rhs) noexcept {
            _base::m_values = _base::SumArrays(_base::m_values, rhs.m_values);
            return *this;
        }
        template <typename WrongSpace>
        constexpr StaticAssert::invalid_vector_to_vector_addition operator += (const Vector<WrongSpace>&) const noexcept {
            return StaticAssert::invalid_vector_to_vector_addition{};
        }
        template <typename WrongSpace>
        constexpr StaticAssert::invalid_vector_to_vector_addition operator += (const NormalizedVector<WrongSpace>&) const noexcept {
            return StaticAssert::invalid_vector_to_vector_addition{};
        }

        //-------------------------------------------------------------------------------------

        [[nodiscard]] constexpr typename Space::Unit Mag() const noexcept {
            return Space::Unit{ _base::MagHelper() };
        }

        [[nodiscard]] constexpr double Mag_double() const noexcept {
            return _base::MagHelper();
        }

        [[nodiscard]] constexpr typename Space::NormalizedVector Norm() const {
            return Space::NormalizedVector(_base::m_values);
        }

        [[nodiscard]] constexpr double Dot(const typename Space::Vector& other) const noexcept {
            return _base::DotArrays(_base::m_values, other.m_values);
        }

        [[nodiscard]] constexpr double Dot(const typename Space::NormalizedVector& other) const noexcept {
            return _base::DotArrays(_base::m_values, other.m_values);
        }
        template <typename WrongSpace>
        constexpr StaticAssert::invalid_vector_dot Dot(const Vector<WrongSpace>&) const noexcept {
            return StaticAssert::invalid_vector_dot{};
        }
        template <typename WrongSpace>
        constexpr StaticAssert::invalid_vector_dot Dot(const NormalizedVector<WrongSpace>&) const noexcept {
            return StaticAssert::invalid_vector_dot{};
        }

        [[nodiscard]] constexpr typename Space::Vector Cross(const typename Space::Vector& other) const noexcept {
            return Space::Vector(_base::CrossArrays(_base::m_values, other.m_values));
        }
        template <typename WrongSpace>
        constexpr StaticAssert::invalid_vector_cross Cross(const Vector<WrongSpace>&) const noexcept {
            return StaticAssert::invalid_vector_cross{};
        }
    };

    template <typename Space>
    constexpr std::ostream& operator << (
        std::ostream& os,
        const Vector<Space>& item
    ) {
        const auto space = SpaceTypeNameMap<Space>::name;
        os << space << "::Vector (" << item.X() << ", " << item.Y() << ", " << item.Z() << ")";
        return os;
    }
}
