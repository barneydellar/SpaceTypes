#pragma once

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class XYPoint final : public Base<ThisSpace, Implementation>
    {
        using _base = Base<ThisSpace, Implementation>;

    public:

        XYPoint() noexcept : _base() {}
        explicit XYPoint(const Implementation& v) noexcept : _base(v) { *(std::prev(_base::end())) = 0; }
        explicit XYPoint(const double x, const double y) noexcept
        {
            auto iter = _base::begin();
            *iter++ = x;
            *iter++ = y;
            *iter = 0;
        }
        XYPoint(const std::initializer_list<double>& l)
        {
            if (l.size() != 2)
            {
                throw std::invalid_argument("You can only initialise with two elements");
            }
            std::copy(
                std::cbegin(l),
                std::cend(l),
                _base::begin()
            );
        }

        [[nodiscard]] double X() const noexcept { return _base::X_internal(); }
        [[nodiscard]] double Y() const noexcept { return _base::Y_internal(); }

        void SetX(const double d) noexcept { *(begin() + 0) = d; }
        void SetY(const double d) noexcept { *(begin() + 1) = d; }

        [[nodiscard]] operator Point<ThisSpace, Implementation>() const noexcept {
            return Point<ThisSpace, Implementation>(X(), Y(), _base::Z_internal());
        }

        [[nodiscard]] double* begin() noexcept { return _base::begin(); }
        [[nodiscard]] double* end() noexcept { return reinterpret_cast<double*>(std::prev(_base::end())); }
        [[nodiscard]] const double* cbegin() const noexcept { return _base::cbegin(); }
        [[nodiscard]] const double* cend() const noexcept { return reinterpret_cast<const double*>(std::prev(_base::cend())); }

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

        double operator[](const unsigned int i) const
        {
            if (i > 1) {
                throw std::invalid_argument("Index is out of range");
            }
            return *(_base::cbegin() + i);
        }

        template <int I>
        [[nodiscard]] typename std::enable_if<I == 0 || I == 1, double>::type at() const {
            return operator[](I);
        }

        XYPoint<ThisSpace, Implementation> operator-=(const XYVector<ThisSpace, Implementation>& rhs) noexcept {
            _base::Sub(rhs);
            return *this;
        }
        XYPoint<ThisSpace, Implementation> operator-=(const NormalizedXYVector<ThisSpace, Implementation>& rhs) noexcept {
            _base::Sub(rhs);
            return *this;
        }

        [[nodiscard]] friend Point<ThisSpace, Implementation> operator-(XYPoint<ThisSpace, Implementation> lhs, const Vector<ThisSpace, Implementation>& rhs) noexcept {
            lhs.Sub(rhs);
            Point<ThisSpace, Implementation> point3(lhs.X(), lhs.Y(), 0);
            return point3;
        }
        [[nodiscard]] friend Point<ThisSpace, Implementation> operator-(XYPoint<ThisSpace, Implementation> lhs, const NormalizedVector<ThisSpace, Implementation>& rhs) noexcept {
            lhs.Sub(rhs);
            Point<ThisSpace, Implementation> point3(lhs.X(), lhs.Y(), 0);
            return point3;
        }
        [[nodiscard]] friend XYPoint<ThisSpace, Implementation> operator-(XYPoint<ThisSpace, Implementation> lhs, const NormalizedXYVector<ThisSpace, Implementation>& rhs) noexcept {
            lhs.Sub(rhs);
            return lhs;
        }
        [[nodiscard]] friend XYPoint<ThisSpace, Implementation> operator-(XYPoint<ThisSpace, Implementation> lhs, const XYVector<ThisSpace, Implementation>& rhs) noexcept {
            lhs.Sub(rhs);
            return lhs;
        }

        [[nodiscard]] friend XYVector<ThisSpace, Implementation> operator-(XYPoint<ThisSpace, Implementation> lhs, const XYPoint<ThisSpace, Implementation>& rhs) {
            lhs.Sub(rhs);
            XYVector<ThisSpace, Implementation> v(lhs.X(), lhs.Y());
            return v;
        }
        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator-(XYPoint<ThisSpace, Implementation> lhs, const Point<ThisSpace, Implementation>& rhs) {
            lhs.Sub(rhs);
            Vector<ThisSpace, Implementation> v(lhs.X_internal(), lhs.Y_internal(), lhs.Z_internal());
            return v;
        }

        XYPoint<ThisSpace, Implementation> operator+=(const XYVector<ThisSpace, Implementation>& rhs) noexcept {
            _base::Add(rhs);
            return *this;
        }
        XYPoint<ThisSpace, Implementation> operator+=(const NormalizedXYVector<ThisSpace, Implementation>& rhs) noexcept {
            _base::Add(rhs);
            return *this;
        }

        [[nodiscard]] friend Point<ThisSpace, Implementation> operator+(XYPoint<ThisSpace, Implementation> lhs, const Vector<ThisSpace, Implementation>& rhs) noexcept {
            Point<ThisSpace, Implementation> point3(lhs.X(), lhs.Y(), 0);
            point3 += rhs;
            return point3;
        }
        [[nodiscard]] friend Point<ThisSpace, Implementation> operator+(XYPoint<ThisSpace, Implementation> lhs, const NormalizedVector<ThisSpace, Implementation>& rhs) noexcept {
            Point<ThisSpace, Implementation> point3(lhs.X(), lhs.Y(), 0);
            point3 += rhs;
            return point3;
        }
        [[nodiscard]] friend XYPoint<ThisSpace, Implementation> operator+(XYPoint<ThisSpace, Implementation> lhs, const NormalizedXYVector<ThisSpace, Implementation>& rhs) noexcept {
            lhs += rhs;
            return lhs;
        }
        [[nodiscard]] friend XYPoint<ThisSpace, Implementation> operator+(XYPoint<ThisSpace, Implementation> lhs, const XYVectorBase<ThisSpace, Implementation>& rhs) noexcept {
            lhs += rhs;
            return lhs;
        }

        template <typename OtherSpace, typename TransformManager>
        [[nodiscard]] std::enable_if_t<!std::is_same_v<OtherSpace, ThisSpace>, Point<OtherSpace, Implementation>> ConvertTo(const TransformManager& transform_manager) const {
            return Point<OtherSpace, Implementation>(transform_manager.template Transform<ThisSpace, OtherSpace>(static_cast<Implementation>(*this)));
        }

        friend std::ostream& operator << (
            std::ostream& os,
            const XYPoint<ThisSpace, Implementation>& item
        ) {
            const auto space = SpaceTypeNameMap<ThisSpace>::name;
            os << space << "::XYPoint (" << item.X() << ", " << item.Y() << ")";
            return os;
        }

#ifndef IGNORE_SPACE_STATIC_ASSERT

        using _base::operator==;
        using _base::operator!=;
        using _base::operator+=;
        using _base::operator-=;
        using _base::ConvertTo;

        template <int I>
        typename std::enable_if<I != 0 && I != 1, StaticAssert::invalid_at_access>::type at() const {
            return StaticAssert::invalid_at_access{};
        }

        StaticAssert::invalid_vector3_to_xy_point_addition operator+=(const Vector<ThisSpace, Implementation>&) noexcept {
            return StaticAssert::invalid_vector3_to_xy_point_addition{};
        }
        StaticAssert::invalid_vector3_to_xy_point_addition operator+=(const NormalizedVector<ThisSpace, Implementation>&) noexcept {
            return StaticAssert::invalid_vector3_to_xy_point_addition{};
        }

        StaticAssert::invalid_vector3_from_xy_point_subtraction operator-=(const Vector<ThisSpace, Implementation>&) noexcept {
            return StaticAssert::invalid_vector3_from_xy_point_subtraction{};
        }
        StaticAssert::invalid_vector3_from_xy_point_subtraction operator-=(const NormalizedVector<ThisSpace, Implementation>&) noexcept {
            return StaticAssert::invalid_vector3_from_xy_point_subtraction{};
        }

        StaticAssert::invalid_point_vector_equality operator== (const Vector<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        StaticAssert::invalid_point_vector_equality operator== (const NormalizedVector<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        StaticAssert::invalid_point_vector_equality operator== (const NormalizedXYVector<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        StaticAssert::invalid_point_vector_equality operator== (const XYVector<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }

        friend StaticAssert::invalid_point_to_point_addition operator+(XYPoint<ThisSpace, Implementation>, const Point<ThisSpace, Implementation>&) {
            return StaticAssert::invalid_point_to_point_addition{};
        }

        friend StaticAssert::invalid_point_to_point_addition operator+(XYPoint<ThisSpace, Implementation>, const XYPoint<ThisSpace, Implementation>&) {
            return StaticAssert::invalid_point_to_point_addition{};
        }
#endif
        // Hide functions from intellisense
        void Dot() = delete;
        void Cross() = delete;
        void operator*() = delete;
        void operator*=(double) = delete;
    };
}
