#pragma once

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class PointBase : public Base<ThisSpace, Implementation>
    {
        using VectorBaseInThisSpace = VectorBase<ThisSpace, Implementation>;
        using PointBaseInThisSpace = PointBase<ThisSpace, Implementation>;

        using _base = Base<ThisSpace, Implementation>;
        using _base::_base;

    public:

        [[nodiscard]] bool operator == (const PointBaseInThisSpace& other) const noexcept {
            return _base::m_impl.operator==(other.m_impl);
        }

        [[nodiscard]] bool operator != (const PointBaseInThisSpace& other) const noexcept {
            return !(operator==(other));
        }

        template <typename OtherSpace, typename TransformManager>
        [[nodiscard]] Point<OtherSpace, Implementation> ConvertTo(const TransformManager& transform_manager) const {
            return Point<OtherSpace, Implementation>(transform_manager.template Transform<ThisSpace, OtherSpace>(static_cast<Implementation>(*this)));
        }

        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator-(PointBaseInThisSpace lhs, const PointBaseInThisSpace& rhs) {
            return Vector<ThisSpace, Implementation>(lhs.m_impl - rhs.m_impl);
        }

        [[nodiscard]] friend Point<ThisSpace, Implementation> operator+(PointBaseInThisSpace lhs, const VectorBaseInThisSpace& rhs) noexcept {
            lhs += rhs;
            return Point<ThisSpace, Implementation>(lhs.m_impl);
        }

        Point<ThisSpace, Implementation> operator+=(const VectorBaseInThisSpace& rhs) noexcept {
            _base::m_impl = _base::m_impl + rhs.m_impl;
            return Point<ThisSpace, Implementation>(_base::m_impl);
        }

        [[nodiscard]] friend Point<ThisSpace, Implementation> operator-(PointBaseInThisSpace lhs, const VectorBaseInThisSpace& rhs) noexcept {
            lhs -= rhs;
            return Point<ThisSpace, Implementation>(lhs.m_impl);
        }

        Point<ThisSpace, Implementation> operator-=(const VectorBaseInThisSpace& rhs) noexcept {
            _base::m_impl = _base::m_impl - rhs.m_impl;
            return Point<ThisSpace, Implementation>(_base::m_impl);
        }

        [[nodiscard]] Point2<ThisSpace, Implementation> RemoveZ() const {
            return Point2<ThisSpace, Implementation>(_base::m_impl);
        }

        //------------------------------------------------------------------------------------

#ifndef IGNORE_SPACE_STATIC_ASSERT

        template <typename OtherSpace>
        StaticAssert::invalid_equality operator == (const PointBase<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_equality{};
        }
        template <typename AnySpace>
        StaticAssert::invalid_point_vector_equality operator == (const VectorBase<AnySpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_equality operator != (const PointBase<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_equality{};
        }
        template <typename AnySpace>
        StaticAssert::invalid_point_vector_equality operator != (const VectorBase<AnySpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        template <typename OtherSpace>
        friend StaticAssert::invalid_subtraction operator-(PointBaseInThisSpace, const PointBase<OtherSpace, Implementation>&) {
            return StaticAssert::invalid_subtraction{};
        }

        template <typename OtherSpace>
        StaticAssert::invalid_vector_to_point_addition operator+(const VectorBase<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_vector_to_point_addition{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_to_point_addition operator+=(const VectorBase<OtherSpace, Implementation>&) noexcept {
            return StaticAssert::invalid_vector_to_point_addition{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_from_point_subtraction operator-(const VectorBase<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_vector_from_point_subtraction{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_from_point_subtraction operator-=(const VectorBase<OtherSpace, Implementation>&) noexcept {
            return StaticAssert::invalid_vector_from_point_subtraction{};
        }
#endif
    };
}
