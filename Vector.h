#pragma once
#include "BaseImpl.h"
#include "NormalizedVector.h"

namespace Space {

    //--------------------------------------------------------------------------------------------

    template <typename Space>
    class Vector final : public detail::ModifiableBaseImpl<Space>
    {
        friend class Space::NormalizedVector;
        friend class Space::Point;
        using _base = detail::ModifiableBaseImpl<Space>;

    public:

        constexpr explicit Vector(const std::array<double, 3> value) noexcept : _base(value) {}
        constexpr explicit Vector(const double x, const double y, const double z) noexcept : _base(x, y, z) {}
        constexpr explicit Vector(const double x, const double y) noexcept : _base(x, y) {}
        constexpr explicit Vector(const typename Space::NormalizedVector nv) noexcept : _base(nv.X(), nv.Y(), nv.Z()) {}
        constexpr Vector(const std::initializer_list<double> l) : _base(l) {}

        //------------------------------------------------------------------------------------

        template <typename AnySpace>[[nodiscard]] constexpr bool operator == (const Vector<AnySpace>& other) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_equality{};
            }
            else {
                return std::equal(_base::m_values.cbegin(), _base::m_values.cend(), other.m_values.cbegin());
            }
        }

        template <typename AnySpace>[[nodiscard]] constexpr bool operator == (const NormalizedVector<AnySpace>& other) const noexcept {
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

        template <typename AnySpace>[[nodiscard]] constexpr bool operator != (const Vector<AnySpace>& other) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_equality{};
            } else {
                return !(operator==(other));
            }
        }

        template <typename AnySpace>[[nodiscard]] constexpr bool operator != (const typename NormalizedVector<AnySpace>& other) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_equality{};
            } else {
                return !(operator==(other));
            }
        }

        template <typename AnySpace>
        constexpr bool operator != (const Point<AnySpace>&) const noexcept {
            StaticAssert::invalid_point_vector_equality{};
        }

        //-------------------------------------------------------------------------------------

        template <typename OtherSpace, typename TransformManager>
        [[nodiscard]] constexpr typename OtherSpace::Vector ConvertTo(const TransformManager& transform_manager) const noexcept {
            return typename OtherSpace::Vector(transform_manager.template Transform33<Space, OtherSpace>(_base::m_values));
        }

        //------------------------------------------------------------------------------------

        [[nodiscard]] constexpr typename Space::Vector operator*(const double& d) const noexcept {
            return Space::Vector(_base::ScaleArray(_base::m_values, d));
        }
        constexpr typename Space::Vector& operator*=(const double& d) noexcept {
            _base::m_values = _base::ScaleArray(_base::m_values, d);
            return *this;
        }

        template <typename AnySpace>
        [[nodiscard]] constexpr typename Space::Vector operator*(const Vector<AnySpace>& rhs) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_vector_cross{};
            } else {
                return this->Cross(rhs);
            }
        }

        template <typename AnySpace>
        [[nodiscard]] constexpr typename Space::Vector operator*(const NormalizedVector<AnySpace>& rhs) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_vector_cross{};
            } else {
                return this->Cross(rhs);
            }
        }

        template <typename AnySpace>
        [[nodiscard]] constexpr typename Space::Vector Cross(const Vector<AnySpace>& other) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_vector_cross{};
            }
            else {
                return Space::Vector(_base::CrossArrays(_base::m_values, other.m_values));
            }
        }

        template <typename AnySpace>
        [[nodiscard]] constexpr typename Space::Vector Cross(const NormalizedVector<AnySpace>& other) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_vector_cross{};
            } else {
                return Space::Vector(_base::CrossArrays(_base::m_values, other.m_values));
            }
        }

        template <typename AnySpace>
        constexpr typename Space::Vector operator*=(const Vector<AnySpace>& rhs) noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_vector_cross{};
            } else {
                return *this = this->Cross(rhs);
            }
        }

        template <typename AnySpace>constexpr typename Space::Vector operator*=(const NormalizedVector<AnySpace>& rhs) noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_vector_cross{};
            } else {
                return *this = this->Cross(rhs);
            }
        }

        //-------------------------------------------------------------------------------------

        template <typename AnySpace>
        [[nodiscard]] constexpr typename Space::Vector operator+(const Vector<AnySpace>& rhs) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_vector_to_vector_addition{};
            } else {
                return Space::Vector(_base::SumArrays(_base::m_values, rhs.m_values));
            }
        }

        template <typename AnySpace>
        [[nodiscard]] constexpr typename Space::Vector operator+(const NormalizedVector<AnySpace>& rhs) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_vector_to_vector_addition{};
            } else {
                return Space::Vector(_base::SumArrays(_base::m_values, rhs.m_values));
            }
        }
        template <typename AnySpace>
        constexpr typename AnySpace::Vector operator+(const Point<AnySpace>&) const noexcept {
            StaticAssert::invalid_point_to_vector_addition{};
        }

        //-------------------------------------------------------------------------------------

        template <typename AnySpace>
        constexpr typename Space::Vector operator+=(const Vector<AnySpace>& rhs) noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_vector_to_vector_addition{};
            } else {
                _base::m_values = _base::SumArrays(_base::m_values, rhs.m_values);
                return *this;
            }
        }

        template <typename AnySpace>
        constexpr typename Space::Vector operator+=(const NormalizedVector<AnySpace>& rhs) noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_vector_to_vector_addition{};
            } else {
                _base::m_values = _base::SumArrays(_base::m_values, rhs.m_values);
                return *this;
            }
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

        template <typename AnySpace>
        [[nodiscard]] constexpr double Dot(const Vector<AnySpace>& other) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_vector_dot{};
            } else {
                return _base::DotArrays(_base::m_values, other.m_values);
            }
        }

        template <typename AnySpace>
        [[nodiscard]] constexpr double Dot(const NormalizedVector<AnySpace>& other) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_vector_dot{};
            } else {
                return _base::DotArrays(_base::m_values, other.m_values);
            }
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
