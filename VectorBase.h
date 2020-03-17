#pragma once
#include "SpaceImpl.h"
#include "PointBase.h"
#include "Base.h"

namespace Space {

    template <typename Space, typename ExternalImplementation>
    class PointBase;


    template <typename Space, typename ExternalImplementation>
    class VectorBase : public Base<Space, ExternalImplementation>
    {

        friend class PointBase<Space, ExternalImplementation>;

        using VectorBaseInThisSpace = VectorBase<Space, ExternalImplementation>;
        using VectorInThisSpace = VectorInASpace<Space>;
        using NormalizedVectorInThisSpace = NormalizedVectorInASpace<Space>;

    public:

        using _base = Base<Space, ExternalImplementation>;
        using _base::_base;

        [[nodiscard]] bool operator == (const VectorBaseInThisSpace& other) const noexcept {
            return _base::m_impl.operator==(other._base::m_impl);
        }

        [[nodiscard]] bool operator != (const VectorBaseInThisSpace& other) const noexcept {
            return !(operator==(other));
        }

        template <typename OtherSpace, typename TransformManager>
        [[nodiscard]] VectorInASpace<OtherSpace> ConvertTo(const TransformManager& transform_manager) const noexcept {
            return VectorInASpace<OtherSpace>(transform_manager.template Transform33<Space, OtherSpace>(static_cast<ExternalImplementation>(*this)));
        }

        [[nodiscard]] friend VectorInThisSpace operator*(VectorBaseInThisSpace lhs, const double& d) noexcept {
            lhs *= d;
            return VectorInThisSpace(lhs._base::m_impl);
        }

        VectorInThisSpace operator*=(const double& d) noexcept {
            _base::m_impl = _base::m_impl * d;
            return VectorInThisSpace(_base::m_impl);
        }

        [[nodiscard]] VectorInThisSpace operator*(const VectorBaseInThisSpace& rhs) const noexcept {
            return this->Cross(rhs);
        }

        VectorInThisSpace operator*=(const VectorBaseInThisSpace& other) noexcept {
            *this = this->Cross(other);
            return VectorInThisSpace(_base::m_impl);
        }

        [[nodiscard]] VectorInThisSpace Cross(const VectorBaseInThisSpace& other) const noexcept {
            return VectorInThisSpace(_base::m_impl.Cross(other._base::m_impl));
        }

        [[nodiscard]] friend VectorInThisSpace operator-(VectorBaseInThisSpace lhs, const VectorBaseInThisSpace& rhs) noexcept {
            lhs -= rhs;
            return VectorInThisSpace(lhs._base::m_impl);
        }

        VectorInThisSpace operator-=(const VectorBaseInThisSpace& rhs) noexcept {
            _base::m_impl = _base::m_impl - rhs._base::m_impl;
            return VectorInThisSpace(_base::m_impl);
        }

        [[nodiscard]] friend VectorInThisSpace operator+(VectorBaseInThisSpace lhs, const VectorBaseInThisSpace& rhs) noexcept {
            lhs += rhs;
            return VectorInThisSpace(lhs.m_impl);
        }

        VectorInThisSpace operator+=(const VectorBaseInThisSpace& rhs) noexcept {
            _base::m_impl = _base::m_impl + rhs._base::m_impl;
            return VectorInThisSpace(_base::m_impl);
        }

        [[nodiscard]] typename Space::Unit Mag() const noexcept {
            return Space::Unit{ _base::m_impl.Mag() };
        }

        [[nodiscard]] double Mag_double() const noexcept {
            return _base::m_impl.Mag();
        }

        [[nodiscard]] double Dot(const VectorBaseInThisSpace& other) const noexcept {
            return _base::m_impl.Dot(other._base::m_impl);
        }

        [[nodiscard]] NormalizedVectorInThisSpace Norm() const {
            return NormalizedVectorInThisSpace(_base::m_impl);
        }

        //-------------------------------------------------------------------------------------
#ifndef IGNORE_SPACE_STATIC_ASSERT

        template <typename OtherSpace>
        StaticAssert::invalid_equality operator == (const VectorBase<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_equality{};
        }
        template <typename AnySpace>
        StaticAssert::invalid_point_vector_equality operator == (const PointBase<AnySpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_equality operator != (const VectorBase<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_equality{};
        }
        template <typename AnySpace>
        StaticAssert::invalid_point_vector_equality operator != (const PointBase<AnySpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_cross operator*(const VectorBase<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_vector_cross{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_cross Cross(const VectorBase<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_vector_cross{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_cross operator*=(const VectorBase<OtherSpace, ExternalImplementation>&) noexcept {
            return StaticAssert::invalid_vector_cross{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_to_vector_addition operator+(const VectorBase<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_vector_to_vector_addition{};
        }
        template <typename AnySpace>
        StaticAssert::invalid_point_to_vector_addition operator+(const PointBase<AnySpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_point_to_vector_addition{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_to_vector_addition operator+=(const VectorBase<OtherSpace, ExternalImplementation>&) noexcept {
            return StaticAssert::invalid_vector_to_vector_addition{};
        }
        template <typename AnySpace>
        StaticAssert::invalid_point_from_vector_subtraction operator-(const PointBase<AnySpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_point_from_vector_subtraction{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_to_vector_subtraction operator-(const VectorBase<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_vector_to_vector_subtraction{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_to_vector_subtraction operator-=(const VectorBase<OtherSpace, ExternalImplementation>&) noexcept {
            return StaticAssert::invalid_vector_to_vector_subtraction{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_dot Dot(const VectorBase<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_vector_dot{};
        }
#endif
    };
}
