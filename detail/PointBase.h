#pragma once

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class PointBase : public Base<ThisSpace, Implementation>
    {
        using VectorBaseInThisSpace = VectorBase<ThisSpace, Implementation>;
        using PointBaseInThisSpace = PointBase<ThisSpace, Implementation>;

        using _base = Base<ThisSpace, Implementation>;
        using _base::_base;

        friend class PointBase<ThisSpace, Implementation>;
        friend class Point2Base<ThisSpace, Implementation>;
        friend class NormalizedVectorBase<ThisSpace, Implementation>;
        friend class NormalizedVector2Base<ThisSpace, Implementation>;
        friend class VectorBase<ThisSpace, Implementation>;
        friend class Vector2Base<ThisSpace, Implementation>;

        friend class Point<ThisSpace, Implementation>;
        friend class Point2<ThisSpace, Implementation>;
        friend class NormalizedVector<ThisSpace, Implementation>;
        friend class NormalizedVector2<ThisSpace, Implementation>;
        friend class Vector<ThisSpace, Implementation>;
        friend class Vector2<ThisSpace, Implementation>;

    public:

        [[nodiscard]] bool operator== (const PointBaseInThisSpace& other) const noexcept {
            return std::equal(_base::cbegin(), _base::cend(), other.cbegin(), _base::Equality);
        }

        [[nodiscard]] bool operator!= (const PointBaseInThisSpace& other) const noexcept {
            return !(operator==(other));
        }

        template <typename OtherSpace, typename TransformManager>
        [[nodiscard]] Point<OtherSpace, Implementation> ConvertTo(const TransformManager& transform_manager) const {
            return Point<OtherSpace, Implementation>(transform_manager.template Transform<ThisSpace, OtherSpace>(static_cast<Implementation>(*this)));
        }

        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator-(PointBaseInThisSpace lhs, const PointBaseInThisSpace& rhs) {
            lhs.Sub(rhs);
            Vector<ThisSpace, Implementation> v(lhs.X(), lhs.Y(), lhs.Z());
            return v;
        }

        [[nodiscard]] friend Point<ThisSpace, Implementation> operator+(Point<ThisSpace, Implementation> lhs, const VectorBase<ThisSpace, Implementation>& rhs) noexcept {
            lhs += rhs;
            return lhs;
        }

        [[nodiscard]] friend Point<ThisSpace, Implementation> operator-(Point<ThisSpace, Implementation> lhs, const VectorBase<ThisSpace, Implementation>& rhs) noexcept {
            lhs -= rhs;
            return lhs;
        }

        [[nodiscard]] Point2<ThisSpace, Implementation> RemoveZ() const {
            return Point2<ThisSpace, Implementation>(_base::X(), _base::Y());
        }

        //------------------------------------------------------------------------------------

#ifndef IGNORE_SPACE_STATIC_ASSERT

        template <typename OtherSpace>
        StaticAssert::invalid_equality operator== (const PointBase<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_equality{};
        }
        template <typename AnySpace>
        StaticAssert::invalid_point_vector_equality operator== (const VectorBase<AnySpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_equality operator!= (const PointBase<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_equality{};
        }
        template <typename AnySpace>
        StaticAssert::invalid_point_vector_equality operator!= (const VectorBase<AnySpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        template <typename OtherSpace>
        friend StaticAssert::invalid_subtraction operator-(PointBaseInThisSpace, const PointBase<OtherSpace, Implementation>&) {
            return StaticAssert::invalid_subtraction{};
        }
        template <typename OtherSpace>
        friend StaticAssert::invalid_point_to_point_addition operator+(PointBaseInThisSpace, const PointBase<OtherSpace, Implementation>&) {
            return StaticAssert::invalid_point_to_point_addition{};
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
