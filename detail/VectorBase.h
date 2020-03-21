#pragma once

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class VectorBase : public Base<ThisSpace, Implementation>
    {
        using VectorBaseInThisSpace = VectorBase<ThisSpace, Implementation>;

        using _base = Base<ThisSpace, Implementation>;
        using _base::_base;

    public:

        [[nodiscard]] bool operator == (const VectorBaseInThisSpace& other) const noexcept {
            return std::equal(_base::cbegin(), _base::cend(), other.cbegin(), _base::Equality);
        }

        [[nodiscard]] bool operator != (const VectorBaseInThisSpace& other) const noexcept {
            return !(operator==(other));
        }

        template <typename OtherSpace, typename TransformManager>
        [[nodiscard]] Vector<OtherSpace, Implementation> ConvertTo(const TransformManager& transform_manager) const noexcept {
            return Vector < OtherSpace, Implementation>(transform_manager.template Transform33<ThisSpace, OtherSpace>(static_cast<Implementation>(*this)));
        }

        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator*(VectorBaseInThisSpace lhs, const double& d) noexcept {
            lhs *= d;
            return Vector<ThisSpace, Implementation>(lhs._base::m_impl);
        }

        Vector<ThisSpace, Implementation> operator*=(const double& d) noexcept {
            _base::m_impl = _base::m_impl * d;
            return Vector<ThisSpace, Implementation>(_base::m_impl);
        }

        [[nodiscard]] Vector<ThisSpace, Implementation> operator*(const VectorBaseInThisSpace& rhs) const noexcept {
            return this->Cross(rhs);
        }

        Vector<ThisSpace, Implementation> operator*=(const VectorBaseInThisSpace& other) noexcept {
            *this = this->Cross(other);
            return Vector<ThisSpace, Implementation>(_base::m_impl);
        }

        [[nodiscard]] Vector<ThisSpace, Implementation> Cross(const VectorBaseInThisSpace& other) const noexcept {

            return Vector<ThisSpace, Implementation>{
                _base::Y() * other.Z() - _base::Z() * other.Y(),
                _base::Z() * other.X() - _base::X() * other.Z(),
                _base::X() * other.Y() - _base::Y() * other.X()
            };
        }

        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator-(VectorBaseInThisSpace lhs, const VectorBaseInThisSpace& rhs) noexcept {
            lhs -= rhs;
            return Vector<ThisSpace, Implementation>(lhs._base::m_impl);
        }

        Vector<ThisSpace, Implementation> operator-=(const VectorBaseInThisSpace& rhs) noexcept {
            _base::m_impl = _base::m_impl - rhs._base::m_impl;
            return Vector<ThisSpace, Implementation>(_base::m_impl);
        }

        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator+(VectorBaseInThisSpace lhs, const VectorBaseInThisSpace& rhs) noexcept {
            lhs += rhs;
            return Vector<ThisSpace, Implementation>(lhs.m_impl);
        }

        Vector<ThisSpace, Implementation> operator+=(const VectorBaseInThisSpace& rhs) noexcept {
            _base::m_impl = _base::m_impl + rhs._base::m_impl;
            return Vector<ThisSpace, Implementation>(_base::m_impl);
        }

        [[nodiscard]] typename ThisSpace::Unit Mag() const noexcept {
            return ThisSpace::Unit{ Mag_double() };
        }

        [[nodiscard]] double Mag_double() const noexcept {

            return std::sqrt(
                std::accumulate(
                    _base::cbegin(),
                    _base::cend(),
                    0.0,
                    [](const auto accumulation, const auto v) { return accumulation + v * v; }
                )
            );
        }

        [[nodiscard]] double Dot(const VectorBaseInThisSpace& other) const noexcept {

            return std::transform_reduce(
                _base::cbegin(),
                _base::cend(),
                other.cbegin(),
                0.0,
                [](auto accumulation, auto v) { return accumulation + v; },
                [](auto v1, auto v2) { return v1 * v2; }
            );
        }

        [[nodiscard]] NormalizedVector<ThisSpace, Implementation> Norm() const {
            return NormalizedVector<ThisSpace, Implementation>(_base::m_impl);
        }

        [[nodiscard]] Vector2<ThisSpace, Implementation> RemoveZ() const {
            return Vector2<ThisSpace, Implementation>(_base::m_impl);
        }

        //-------------------------------------------------------------------------------------
#ifndef IGNORE_SPACE_STATIC_ASSERT

        template <typename OtherSpace>
        StaticAssert::invalid_equality operator == (const VectorBase<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_equality{};
        }
        template <typename AnySpace>
        StaticAssert::invalid_point_vector_equality operator == (const PointBase<AnySpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_equality operator != (const VectorBase<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_equality{};
        }
        template <typename AnySpace>
        StaticAssert::invalid_point_vector_equality operator != (const PointBase<AnySpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_cross operator*(const VectorBase<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_vector_cross{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_cross Cross(const VectorBase<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_vector_cross{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_cross operator*=(const VectorBase<OtherSpace, Implementation>&) noexcept {
            return StaticAssert::invalid_vector_cross{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_to_vector_addition operator+(const VectorBase<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_vector_to_vector_addition{};
        }
        template <typename AnySpace>
        StaticAssert::invalid_point_to_vector_addition operator+(const PointBase<AnySpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_to_vector_addition{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_to_vector_addition operator+=(const VectorBase<OtherSpace, Implementation>&) noexcept {
            return StaticAssert::invalid_vector_to_vector_addition{};
        }
        template <typename AnySpace>
        StaticAssert::invalid_point_from_vector_subtraction operator-(const PointBase<AnySpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_from_vector_subtraction{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_to_vector_subtraction operator-(const VectorBase<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_vector_to_vector_subtraction{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_to_vector_subtraction operator-=(const VectorBase<OtherSpace, Implementation>&) noexcept {
            return StaticAssert::invalid_vector_to_vector_subtraction{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_vector_dot Dot(const VectorBase<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_vector_dot{};
        }
#endif
    };
}
