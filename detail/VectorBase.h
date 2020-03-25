#pragma once

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class VectorBase : public Base<ThisSpace, Implementation>
    {
        using VectorBaseInThisSpace = VectorBase<ThisSpace, Implementation>;

        using _base = Base<ThisSpace, Implementation>;
        using _base::_base;

    public:

        [[nodiscard]] bool operator== (const VectorBaseInThisSpace& other) const noexcept {
            return std::equal(_base::cbegin(), _base::cend(), other.cbegin(), _base::Equality);
        }

        [[nodiscard]] bool operator!= (const VectorBase<ThisSpace, Implementation>& other) const noexcept {
            return !(operator==(other));
        }

        template <typename OtherSpace, typename TransformManager>
        [[nodiscard]] Vector<OtherSpace, Implementation> ConvertTo(const TransformManager& transform_manager) const noexcept {
            return Vector < OtherSpace, Implementation>(transform_manager.template Transform33<ThisSpace, OtherSpace>(static_cast<Implementation>(*this)));
        }

        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator*(Vector<ThisSpace, Implementation> lhs, const double& d) noexcept {
            lhs *= d;
            return lhs;
        }

        [[nodiscard]] Vector<ThisSpace, Implementation> operator*(const VectorBaseInThisSpace& rhs) const noexcept {
            return this->Cross(rhs);
        }

        [[nodiscard]] Vector<ThisSpace, Implementation> Cross(const VectorBaseInThisSpace& other) const noexcept {

            return Vector<ThisSpace, Implementation>{
                _base::Y() * other.Z() - _base::Z() * other.Y(),
                _base::Z() * other.X() - _base::X() * other.Z(),
                _base::X() * other.Y() - _base::Y() * other.X()
            };
        }

        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator-(Vector<ThisSpace, Implementation> lhs, const VectorBaseInThisSpace& rhs) noexcept {
            lhs.Sub(rhs);
            return lhs;
        }

        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator+(Vector<ThisSpace, Implementation> lhs, const VectorBaseInThisSpace& rhs) noexcept {
            lhs.Add(rhs);
            return lhs;
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
            return NormalizedVector<ThisSpace, Implementation>(VectorBaseInThisSpace::X(), VectorBaseInThisSpace::Y(), VectorBaseInThisSpace::Z());
        }

        [[nodiscard]] XYVector<ThisSpace, Implementation> RemoveZ() const {
            return XYVector<ThisSpace, Implementation>(VectorBaseInThisSpace::X(), VectorBaseInThisSpace::Y());
        }

        //-------------------------------------------------------------------------------------
#ifndef IGNORE_SPACE_STATIC_ASSERT

        using _base::operator==;
        using _base::operator!=;
        using _base::operator+;
        using _base::operator+=;
        using _base::operator-;
        using _base::operator-=;
        using _base::operator*;
        using _base::operator*=;
        using _base::Cross;
        using _base::Dot;

        StaticAssert::invalid_point_vector_equality operator== (const PointBase<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        StaticAssert::invalid_point_vector_equality operator!= (const PointBase<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        StaticAssert::invalid_point_to_vector_addition operator+(const PointBase<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_to_vector_addition{};
        }
        StaticAssert::invalid_point_from_vector_subtraction operator-(const PointBase<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_from_vector_subtraction{};
        }
#endif
    };
}
