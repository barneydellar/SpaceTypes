#pragma once

#include "BaseImpl.h"

namespace Space {

    template <typename Space>
    class NormalizedVector final
    {
        void Normalize() noexcept(false)
        {
            m_impl.Normalize();
        }

    public:

        //-------------------------------------------------------------------------------------

        constexpr explicit NormalizedVector(const detail::BaseImpl v) noexcept(false) : m_impl(v) { Normalize(); }
        constexpr explicit NormalizedVector(const std::array<double, 3> value) noexcept(false) : m_impl(value) { Normalize();}
        constexpr explicit NormalizedVector(const double x, const double y, const double z) noexcept(false) : m_impl(x, y, z) {Normalize();}
        constexpr explicit NormalizedVector(const double x, const double y) noexcept(false) : m_impl(x, y, 0) {Normalize();}
        constexpr NormalizedVector(const std::initializer_list<double> l) : m_impl(l) { Normalize(); }

        //-------------------------------------------------------------------------------------

        explicit constexpr operator detail::BaseImpl() const noexcept {
            return m_impl;
        }

        constexpr operator Vector<Space>() const noexcept {
            return Space::Vector(m_impl);
        }

        //-------------------------------------------------------------------------------------

        [[nodiscard]] constexpr double X() const noexcept { return m_impl.X(); }
        [[nodiscard]] constexpr double Y() const noexcept { return m_impl.Y(); }
        [[nodiscard]] constexpr double Z() const noexcept { return m_impl.Z(); }

        [[nodiscard]] constexpr double operator[] (const unsigned int i) const {
            if (i > 2) {
                throw std::invalid_argument("Index is out of range");
            }
            return m_impl[i];
        }

        template <int I>
        [[nodiscard]] constexpr double at(
        ) const noexcept {
            if constexpr (I != 0 && I != 1 && I != 2) {
                StaticAssert::invalid_at_access{};
            }
            else {
                return m_impl[I];
            }
        }

        //-------------------------------------------------------------------------------------

        template <typename AnySpace>
        [[nodiscard]] constexpr bool operator == (const NormalizedVector<AnySpace>& other) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_equality{};
            }
            return m_impl.operator==(static_cast<detail::BaseImpl>(other));
        }

        template <typename AnySpace>
        [[nodiscard]] constexpr bool operator == (const Vector<AnySpace>& other) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_equality{};
            }
            return m_impl.operator==(static_cast<detail::BaseImpl>(other));
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
            return !(operator==(other));
        }

        template <typename AnySpace>
        [[nodiscard]] constexpr bool operator != (const Vector<AnySpace>& other) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_equality{};
            }
            return !(operator==(other));
        }

        template <typename AnySpace>
        constexpr bool operator != (const Point<AnySpace>&) const noexcept {
            StaticAssert::invalid_point_vector_equality{};
        }

        //-------------------------------------------------------------------------------------

        template <typename AnySpace>
        [[nodiscard]] constexpr typename Space::Vector operator+(const NormalizedVector<AnySpace>& other) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_vector_to_vector_addition{};
            }
            return Space::Vector(m_impl.operator+(static_cast<detail::BaseImpl>(other)));
        }

        template <typename AnySpace>
        [[nodiscard]] constexpr typename Space::Vector operator+(const Vector<AnySpace>& other) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_vector_to_vector_addition{};
            }
            return Space::Vector(m_impl.operator+(static_cast<detail::BaseImpl>(other)));
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

        [[nodiscard]] constexpr typename Space::Vector operator*(const double& d) const noexcept {
            return Space::Vector(m_impl.operator*(d));
        }

        //-------------------------------------------------------------------------------------

        template <typename AnySpace>
        [[nodiscard]] constexpr double Dot(const NormalizedVector<AnySpace>& other) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_vector_dot{};
            }
            return m_impl.Dot(static_cast<detail::BaseImpl>(other));
        }

        template <typename AnySpace>
        [[nodiscard]] constexpr double Dot(const Vector<AnySpace>& other) const noexcept {
            if constexpr (!std::is_same_v<AnySpace, Space>) {
                StaticAssert::invalid_vector_dot{};
            }
            return m_impl.Dot(static_cast<detail::BaseImpl>(other));
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
            return Space::NormalizedVector(m_impl.Cross(static_cast<detail::BaseImpl>(other)));
        }
        [[nodiscard]] constexpr typename Space::Vector Cross(const Vector<Space>& other) const noexcept {
            return Space::Vector(m_impl.Cross(static_cast<detail::BaseImpl>(other)));
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
            return OtherSpace::Vector(m_impl.ConvertVectorTo<Space, OtherSpace, TransformManager>(transform_manager));
        }

    private:
        detail::BaseImpl m_impl;
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
