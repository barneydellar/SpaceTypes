#pragma once
#include "SpaceImpl.h"
#include "VectorBase.h"
#include "Base.h"

namespace Space {


    template <typename Space, typename ExternalImplementation>
    class VectorBase;

    template <typename Space, typename ExternalImplementation>
    class PointBase : public Base<Space, ExternalImplementation>
    {
        friend class Vector<Space, ExternalImplementation>;

        using VectorBaseInThisSpace = VectorBase<Space, ExternalImplementation>;
        using PointBaseInThisSpace = PointBase<Space, ExternalImplementation>;
        using PointInThisSpace = PointInASpace<Space>;
        using VectorInThisSpace = VectorInASpace<Space>;

    public:

        using _base = Base<Space, ExternalImplementation>;
        using _base::_base;

        [[nodiscard]] constexpr bool operator == (const PointBaseInThisSpace& other) const noexcept {
            return _base::m_impl.operator==(other.m_impl);
        }

        [[nodiscard]] constexpr bool operator != (const PointBaseInThisSpace& other) const noexcept {
            return !(operator==(other));
        }

        template <typename OtherSpace, typename TransformManager>
        [[nodiscard]] constexpr PointInASpace<OtherSpace> ConvertTo(const TransformManager& transform_manager) const {
            return PointInASpace<OtherSpace>(transform_manager.template Transform<Space, OtherSpace>(static_cast<ExternalImplementation>(*this)));
        }

        [[nodiscard]] friend VectorInThisSpace operator-(PointBaseInThisSpace lhs, const PointBaseInThisSpace& rhs) {
            return VectorInThisSpace(lhs.m_impl - rhs.m_impl);
        }

        [[nodiscard]] friend Point<Space, ExternalImplementation> operator+(PointBaseInThisSpace lhs, const VectorBaseInThisSpace& rhs) noexcept {
            lhs += rhs;
            return Point<Space, ExternalImplementation>(lhs.m_impl);
        }

        PointInThisSpace operator+=(const VectorBaseInThisSpace& rhs) noexcept {
            _base::m_impl = _base::m_impl + rhs.m_impl;
            return PointInThisSpace(_base::m_impl);
        }

        [[nodiscard]] friend PointInThisSpace operator-(PointBaseInThisSpace lhs, const VectorBaseInThisSpace& rhs) noexcept {
            lhs -= rhs;
            return PointInThisSpace(lhs.m_impl);
        }

        PointInThisSpace operator-=(const VectorBaseInThisSpace& rhs) noexcept {
            _base::m_impl = _base::m_impl - rhs.m_impl;
            return PointInThisSpace(_base::m_impl);
        }


        //------------------------------------------------------------------------------------

#ifndef IGNORE_SPACE_STATIC_ASSERT

        template <typename OtherSpace>
        StaticAssert::invalid_equality operator == (const PointBase<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_equality{};
        }
        template <typename AnySpace>
        StaticAssert::invalid_point_vector_equality operator == (const VectorBase<AnySpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_equality operator != (const PointBase<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_equality{};
        }
        template <typename AnySpace>
        StaticAssert::invalid_point_vector_equality operator != (const VectorBase<AnySpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        template <typename OtherSpace>
        friend StaticAssert::invalid_subtraction operator-(PointBaseInThisSpace, const PointBase<OtherSpace, ExternalImplementation>&) {
            return StaticAssert::invalid_subtraction{};
        }

        template <typename OtherSpace>
        StaticAssert::invalid_vector_to_point_addition operator+(const VectorBase<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_vector_to_point_addition{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_to_point_addition operator+=(const VectorBase<OtherSpace, ExternalImplementation>&) noexcept {
            return StaticAssert::invalid_vector_to_point_addition{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_from_point_subtraction operator-(const VectorBase<OtherSpace, ExternalImplementation>&) const noexcept {
            return StaticAssert::invalid_vector_from_point_subtraction{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_from_point_subtraction operator-=(const VectorBase<OtherSpace, ExternalImplementation>&) noexcept {
            return StaticAssert::invalid_vector_from_point_subtraction{};
        }

#endif
    };
}
