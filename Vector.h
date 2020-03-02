#pragma once
#include "SpaceImpl.h"
#include "NormalizedVector.h"

namespace Space {

    //--------------------------------------------------------------------------------------------

    template <typename Space, typename Implementation>
    class Vector final
    {
    public:

        constexpr explicit Vector(const Implementation v) noexcept : m_impl(v) {}
        constexpr explicit Vector(const std::array<double, 3> value) noexcept : m_impl(value) {}
        constexpr explicit Vector(const double x, const double y, const double z) noexcept : m_impl(x, y, z) {}
        constexpr explicit Vector(const double x, const double y) noexcept : m_impl(x, y) {}
        constexpr explicit Vector(const typename Space::NormalizedVector nv) noexcept : m_impl(nv.X(), nv.Y(), nv.Z()) {}
        constexpr Vector(const std::initializer_list<double> l) : m_impl(l) {}

        //------------------------------------------------------------------------------------

        explicit constexpr operator Implementation() const noexcept {
            return m_impl;
        }

        //------------------------------------------------------------------------------------

        [[nodiscard]] constexpr double X() const noexcept { return m_impl.X(); }
        [[nodiscard]] constexpr double Y() const noexcept { return m_impl.Y(); }
        [[nodiscard]] constexpr double Z() const noexcept { return m_impl.Z(); }

            if (i > 2) {
                throw std::invalid_argument("Index is out of range");
            }
            return m_impl[i];
        }

        template <int I>
        [[nodiscard]] constexpr double at() const noexcept {
            if constexpr (I != 0 && I != 1 && I != 2) {
                StaticAssert::invalid_at_access{};
            }
            else {
                return m_impl[I];
            }
        }

        //------------------------------------------------------------------------------------

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

        //------------------------------------------------------------------------------------

        template <typename AnySpace>
        [[nodiscard]] constexpr bool operator == (const Vector<AnySpace, Implementation>& other) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_equality{};
            }
            return m_impl.operator==(static_cast<Implementation>(other));
        }

        template <typename AnySpace>
        [[nodiscard]] constexpr bool operator == (const NormalizedVector<AnySpace, Implementation>& other) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_equality{};
            }
            return m_impl.operator==(static_cast<Implementation>(other));
        }

        template <typename AnySpace>
        constexpr bool operator == (const Point<AnySpace, Implementation>&) const noexcept {
            StaticAssert::invalid_point_vector_equality{};
        }

        //------------------------------------------------------------------------------------

        template <typename AnySpace>
        [[nodiscard]] constexpr bool operator != (const Vector<AnySpace, Implementation>& other) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_equality{};
            }
            return !(operator==(other));
        }

        template <typename AnySpace>
        [[nodiscard]] constexpr bool operator != (const NormalizedVector<AnySpace, Implementation>& other) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_equality{};
            }
            return !(operator==(other));
        }

        template <typename AnySpace>
        constexpr bool operator != (const Point<AnySpace, Implementation>&) const noexcept {
            StaticAssert::invalid_point_vector_equality{};
        }

        //-------------------------------------------------------------------------------------

        template <typename OtherSpace, typename TransformManager>
        [[nodiscard]] constexpr typename OtherSpace::Vector ConvertTo(const TransformManager& transform_manager) const noexcept {
            return OtherSpace::Vector(transform_manager.template Transform33<Space, OtherSpace>(m_impl));
        }

        //------------------------------------------------------------------------------------

        [[nodiscard]] constexpr typename Space::Vector operator*(const double& d) const noexcept {
            return Space::Vector(m_impl.operator*(d));
        }
        constexpr typename Space::Vector& operator*=(const double& d) noexcept {
            m_impl.operator*=(d);
            return *this;
        }

        template <typename AnySpace>
        [[nodiscard]] constexpr typename Space::Vector operator*(const Vector<AnySpace, Implementation>& rhs) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_vector_cross{};
            }
            return this->Cross(rhs);
        }

        template <typename AnySpace>
        [[nodiscard]] constexpr typename Space::Vector operator*(const NormalizedVector<AnySpace, Implementation>& rhs) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_vector_cross{};
            }
            return this->Cross(rhs);
        }

        template <typename AnySpace>
        [[nodiscard]] constexpr typename Space::Vector Cross(const Vector<AnySpace, Implementation>& other) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_vector_cross{};
            }
            return Space::Vector(m_impl.Cross(static_cast<Implementation>(other)));
        }

        template <typename AnySpace>
        [[nodiscard]] constexpr typename Space::Vector Cross(const NormalizedVector<AnySpace, Implementation>& other) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_vector_cross{};
            }
            return Space::Vector(m_impl.Cross(static_cast<Implementation>(other)));
        }

        template <typename AnySpace>
        constexpr typename Space::Vector operator*=(const Vector<AnySpace, Implementation>& other) noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_vector_cross{};
            }
            return *this = this->Cross(other);
        }

        template <typename AnySpace>
        constexpr typename Space::Vector operator*=(const NormalizedVector<AnySpace, Implementation>& other) noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_vector_cross{};
            }
            return *this = this->Cross(other);
        }

        //-------------------------------------------------------------------------------------

        template <typename AnySpace>
        [[nodiscard]] constexpr typename Space::Vector operator+(const Vector<AnySpace, Implementation>& other) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_vector_to_vector_addition{};
            }
            return Space::Vector(m_impl.operator+(static_cast<Implementation>(other)));
        }

        template <typename AnySpace>
        [[nodiscard]] constexpr typename Space::Vector operator+(const NormalizedVector<AnySpace, Implementation>& other) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_vector_to_vector_addition{};
            }
            return Space::Vector(m_impl.operator+(static_cast<Implementation>(other)));
        }
        template <typename AnySpace>
        constexpr typename AnySpace::Vector operator+(const Point<AnySpace, Implementation>&) const noexcept {
            StaticAssert::invalid_point_to_vector_addition{};
        }

        //-------------------------------------------------------------------------------------

        template <typename AnySpace>
        constexpr typename Space::Vector operator+=(const Vector<AnySpace, Implementation>& other) noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_vector_to_vector_addition{};
            }
            m_impl.operator+=(static_cast<Implementation>(other));
            return *this;
        }

        template <typename AnySpace>
        constexpr typename Space::Vector operator+=(const NormalizedVector<AnySpace, Implementation>& other) noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_vector_to_vector_addition{};
            }
            m_impl.operator+=(static_cast<Implementation>(other));
            return *this;
        }

        //-------------------------------------------------------------------------------------

        [[nodiscard]] constexpr typename Space::Unit Mag() const noexcept {
            return Space::Unit{m_impl.Mag()};
        }

        [[nodiscard]] constexpr double Mag_double() const noexcept {
            return m_impl.Mag();
        }

        [[nodiscard]] constexpr typename Space::NormalizedVector Norm() const {
            return Space::NormalizedVector(m_impl);
        }

        template <typename AnySpace>
        [[nodiscard]] constexpr double Dot(const Vector<AnySpace, Implementation>& other) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_vector_dot{};
            }
            return m_impl.Dot(static_cast<Implementation>(other));
        }

        template <typename AnySpace>
        [[nodiscard]] constexpr double Dot(const NormalizedVector<AnySpace, Implementation>& other) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_vector_dot{};
            }
            return m_impl.Dot(static_cast<Implementation>(other));
        }

    private:
        Implementation m_impl;
    };

    template <typename Space, typename Impl>
    constexpr std::ostream& operator << (
        std::ostream& os,
        const Vector<Space, Impl>& item
    ) {
        const auto space = SpaceTypeNameMap<Space>::name;
        os << space << "::Vector (" << item.X() << ", " << item.Y() << ", " << item.Z() << ")";
        return os;
    }
}
