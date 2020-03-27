#pragma once

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class Point final : public Base<ThisSpace, Implementation>
    {
        using _base = Base<ThisSpace, Implementation>;
        using _base::_base;
    public:

        [[nodiscard]] double* begin() noexcept {return _base::begin();}
        [[nodiscard]] double* end() noexcept {return _base::end();}

        [[nodiscard]] double Z() const noexcept { return *(_base::cbegin() + 2); }

        void SetX(const double d) noexcept { *(begin() + 0) = d; }
        void SetY(const double d) noexcept { *(begin() + 1) = d; }
        void SetZ(const double d) noexcept { *(begin() + 2) = d; }


        [[nodiscard]] XYPoint<ThisSpace, Implementation> ToXY() const {
            return XYPoint<ThisSpace, Implementation>(_base::X(), _base::Y());
        }

        [[nodiscard]] bool operator== (const Point<ThisSpace, Implementation>& other) const noexcept {
            return std::equal(_base::cbegin(), _base::cend(), other.cbegin(), _base::Equality);
        }
        [[nodiscard]] bool operator== (const XYPoint<ThisSpace, Implementation>& other) const noexcept {
            return std::equal(_base::cbegin(), _base::cend(), other.cbegin(), _base::Equality);
        }

        [[nodiscard]] bool operator!= (const Point<ThisSpace, Implementation>& other) const noexcept {
            return !(operator==(other));
        }

        [[nodiscard]] bool operator!= (const XYPoint<ThisSpace, Implementation>& other) const noexcept {
            return !(operator==(other));
        }

        Point<ThisSpace, Implementation> operator-=(const VectorBase<ThisSpace, Implementation>& rhs) noexcept {
            _base::Sub(rhs);
            return *this;
        }
        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator-(Point<ThisSpace, Implementation> lhs, const Point<ThisSpace, Implementation>& rhs) {
            lhs.Sub(rhs);
            Vector<ThisSpace, Implementation> v(lhs.X(), lhs.Y(), lhs.Z());
            return v;
        }
        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator-(Point<ThisSpace, Implementation> lhs, const XYPoint<ThisSpace, Implementation>& rhs) {
            lhs.Sub(rhs);
            Vector<ThisSpace, Implementation> v(lhs.X(), lhs.Y(), lhs.Z());
            return v;
        }
        [[nodiscard]] friend Point<ThisSpace, Implementation> operator-(Point<ThisSpace, Implementation> lhs, const VectorBase<ThisSpace, Implementation>& rhs) noexcept {
            lhs -= rhs;
            return lhs;
        }

        Point<ThisSpace, Implementation> operator+=(const VectorBase<ThisSpace, Implementation>& rhs) noexcept {
            _base::Add(rhs);
            return *this;
        }
        [[nodiscard]] friend Point<ThisSpace, Implementation> operator+(Point<ThisSpace, Implementation> lhs, const VectorBase<ThisSpace, Implementation>& rhs) noexcept {
            lhs += rhs;
            return lhs;
        }

        template <typename OtherSpace, typename TransformManager>
        [[nodiscard]] std::enable_if_t<!std::is_same_v<OtherSpace, ThisSpace>, Point<OtherSpace, Implementation>> ConvertTo(const TransformManager& transform_manager) const {
            return Point<OtherSpace, Implementation>(transform_manager.template Transform<ThisSpace, OtherSpace>(static_cast<Implementation>(*this)));
        }

        friend std::ostream& operator << (
            std::ostream& os,
            const Point<ThisSpace, Implementation>& item
        ) {
            const auto space = SpaceTypeNameMap<ThisSpace>::name;
            os << space << "::Point (" << item.X() << ", " << item.Y() << ", " << item.Z() << ")";
            return os;
        }

#ifndef IGNORE_SPACE_STATIC_ASSERT

        using _base::operator==;
        using _base::operator!=;
        using _base::operator+=;
        using _base::operator-;
        using _base::operator-=;
        using _base::ConvertTo;


        StaticAssert::invalid_point_vector_equality operator== (const VectorBase<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        StaticAssert::invalid_point_vector_equality operator!= (const VectorBase<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }

        friend StaticAssert::invalid_point_to_point_addition operator+(Point<ThisSpace, Implementation>, const Point<ThisSpace, Implementation>&) {
            return StaticAssert::invalid_point_to_point_addition{};;
        }

        friend StaticAssert::invalid_point_to_point_addition operator+(Point<ThisSpace, Implementation>, const XYPoint<ThisSpace, Implementation>&) {
            return StaticAssert::invalid_point_to_point_addition{};;
        }
#endif

    };

}
