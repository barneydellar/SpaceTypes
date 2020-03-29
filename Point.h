#pragma once

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class Point final : public Base<ThisSpace, Implementation>
    {
        using _base = Base<ThisSpace, Implementation>;
        using _base::_base;
    public:

        Point() noexcept{std::fill(begin(), end(), 0);}
        explicit Point(const Implementation& v) noexcept
        {
            std::copy(
                reinterpret_cast<const double*>(&v),
                reinterpret_cast<const double*>(&v) + 3,
                begin()
            );
        }
        explicit Point(const double x, const double y, const double z) noexcept
        {
            auto iter = begin();
            *iter++ = x;
            *iter++ = y;
            *iter = z;
        }
        Point(const std::initializer_list<double>& l)
        {
            if (l.size() != 3)
            {
                throw std::invalid_argument("You can only initialise with three elements");
            }
            std::copy(
                std::cbegin(l),
                std::cend(l),
                begin()
            );
        }

        [[nodiscard]] explicit operator Implementation() const noexcept {
            return _base::m_impl;
        }

        [[nodiscard]] double X() const noexcept { return _base::X_internal(); }
        [[nodiscard]] double Y() const noexcept { return _base::Y_internal(); }
        [[nodiscard]] double Z() const noexcept { return _base::Z_internal(); }

        void SetX(const double d) noexcept { *(begin() + 0) = d; }
        void SetY(const double d) noexcept { *(begin() + 1) = d; }
        void SetZ(const double d) noexcept { *(begin() + 2) = d; }

        [[nodiscard]] double* begin() noexcept { return _base::begin(); }
        [[nodiscard]] double* end() noexcept { return _base::end(); }
        [[nodiscard]] const double* cbegin() const noexcept { return _base::cbegin(); }
        [[nodiscard]] const double* cend() const noexcept { return _base::cend(); }

        [[nodiscard]] double operator[] (const unsigned int i) const {
            if (i > 2) {
                throw std::invalid_argument("Index is out of range");
            }
            return *(_base::cbegin() + i);
        }

        template <int I>
        [[nodiscard]] typename std::enable_if<I == 0 || I == 1 || I == 2, double>::type at() const {
            return operator[](I);
        }

        [[nodiscard]] XYPoint<ThisSpace, Implementation> ToXY() const {
            return XYPoint<ThisSpace, Implementation>(X(), Y());
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

        Point<ThisSpace, Implementation> operator-=(const Vector<ThisSpace, Implementation>& rhs) noexcept {
            _base::Sub(*this, rhs);
            return *this;
        }
        Point<ThisSpace, Implementation> operator-=(const NormalizedVector<ThisSpace, Implementation>& rhs) noexcept {
            _base::Sub(*this, rhs);
            return *this;
        }
        Point<ThisSpace, Implementation> operator-=(const NormalizedXYVector<ThisSpace, Implementation>& rhs) noexcept {
            _base::Sub(*this, rhs);
            return *this;
        }
        Point<ThisSpace, Implementation> operator-=(const XYVector<ThisSpace, Implementation>& rhs) noexcept {
            _base::Sub(*this, rhs);
            return *this;
        }

        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator-(Point<ThisSpace, Implementation> lhs, const Point<ThisSpace, Implementation>& rhs) {
            _base::Sub(lhs, rhs);
            Vector<ThisSpace, Implementation> v(lhs.X(), lhs.Y(), lhs.Z());
            return v;
        }
        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator-(Point<ThisSpace, Implementation> lhs, const XYPoint<ThisSpace, Implementation>& rhs) {
            _base::Sub(lhs, rhs);
            Vector<ThisSpace, Implementation> v(lhs.X(), lhs.Y(), lhs.Z());
            return v;
        }

        [[nodiscard]] friend Point<ThisSpace, Implementation> operator-(Point<ThisSpace, Implementation> lhs, const Vector<ThisSpace, Implementation>& rhs) noexcept {
            lhs -= rhs;
            return lhs;
        }
        [[nodiscard]] friend Point<ThisSpace, Implementation> operator-(Point<ThisSpace, Implementation> lhs, const NormalizedVector<ThisSpace, Implementation>& rhs) noexcept {
            lhs -= rhs;
            return lhs;
        }
        [[nodiscard]] friend Point<ThisSpace, Implementation> operator-(Point<ThisSpace, Implementation> lhs, const NormalizedXYVector<ThisSpace, Implementation>& rhs) noexcept {
            lhs -= rhs;
            return lhs;
        }
        [[nodiscard]] friend Point<ThisSpace, Implementation> operator-(Point<ThisSpace, Implementation> lhs, const XYVector<ThisSpace, Implementation>& rhs) noexcept {
            lhs -= rhs;
            return lhs;
        }

        Point<ThisSpace, Implementation> operator+=(const Vector<ThisSpace, Implementation>& rhs) noexcept {
            _base::Add(*this, rhs);
            return *this;
        }
        Point<ThisSpace, Implementation> operator+=(const NormalizedVector<ThisSpace, Implementation>& rhs) noexcept {
            _base::Add(*this, rhs);
            return *this;
        }
        Point<ThisSpace, Implementation> operator+=(const NormalizedXYVector<ThisSpace, Implementation>& rhs) noexcept {
            _base::Add(*this, rhs);
            return *this;
        }
        Point<ThisSpace, Implementation> operator+=(const XYVector<ThisSpace, Implementation>& rhs) noexcept {
            _base::Add(*this, rhs);
            return *this;
        }

        [[nodiscard]] friend Point<ThisSpace, Implementation> operator+(Point<ThisSpace, Implementation> lhs, const Vector<ThisSpace, Implementation>& rhs) noexcept {
            lhs += rhs;
            return lhs;
        }
        [[nodiscard]] friend Point<ThisSpace, Implementation> operator+(Point<ThisSpace, Implementation> lhs, const NormalizedVector<ThisSpace, Implementation>& rhs) noexcept {
            lhs += rhs;
            return lhs;
        }
        [[nodiscard]] friend Point<ThisSpace, Implementation> operator+(Point<ThisSpace, Implementation> lhs, const NormalizedXYVector<ThisSpace, Implementation>& rhs) noexcept {
            lhs += rhs;
            return lhs;
        }
        [[nodiscard]] friend Point<ThisSpace, Implementation> operator+(Point<ThisSpace, Implementation> lhs, const XYVector<ThisSpace, Implementation>& rhs) noexcept {
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

        template <int I>
        typename std::enable_if<I != 0 && I != 1 && I != 2, StaticAssert::invalid_at_access>::type at() const {
            return StaticAssert::invalid_at_access{};
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

        StaticAssert::invalid_point_vector_equality operator!= (const Vector<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        StaticAssert::invalid_point_vector_equality operator!= (const NormalizedVector<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        StaticAssert::invalid_point_vector_equality operator!= (const NormalizedXYVector<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        StaticAssert::invalid_point_vector_equality operator!= (const XYVector<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }

        friend StaticAssert::invalid_point_to_point_addition operator+(Point<ThisSpace, Implementation>, const Point<ThisSpace, Implementation>&) {
            return StaticAssert::invalid_point_to_point_addition{};;
        }

        friend StaticAssert::invalid_point_to_point_addition operator+(Point<ThisSpace, Implementation>, const XYPoint<ThisSpace, Implementation>&) {
            return StaticAssert::invalid_point_to_point_addition{};;
        }
#endif
        // Hide functions from intellisense
        void Dot() = delete;
        void Cross() = delete;
        void operator*() = delete;
        void operator*=(double) = delete;
    };

}
