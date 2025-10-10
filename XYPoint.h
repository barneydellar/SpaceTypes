#pragma once

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class XYPoint final
#ifndef IGNORE_SPACE_STATIC_ASSERT
        : public detail::Base<ThisSpace, Implementation>
#endif
    {
        using _base = detail::Base<ThisSpace, Implementation>;

        friend class NormalizedVector<ThisSpace, Implementation>;
        friend class NormalizedXYVector<ThisSpace, Implementation>;
        friend class Point<ThisSpace, Implementation>;
        friend class Vector<ThisSpace, Implementation>;
        friend class XYVector<ThisSpace, Implementation>;
    public:

        XYPoint() noexcept {
            std::fill(begin(), end(), 0);
        }
        explicit XYPoint(const Implementation& v) noexcept {
            auto iter = begin();
            auto in = detail::cbegin(v);
            *iter++ = *in++;
            *iter++ = *in++;
            *iter = 0;
        }
        XYPoint(const double x, const double y) noexcept
        {
            auto iter = begin();
            *iter++ = x;
            *iter++ = y;
            *iter = 0;
        }

        [[nodiscard]] explicit operator Implementation() const noexcept {
            return m_impl;
        }

        [[nodiscard]] double X() const noexcept { return *(cbegin() + 0); }
        [[nodiscard]] double Y() const noexcept { return *(cbegin() + 1); }

        void SetX(const double d) noexcept { *(begin() + 0) = d; }
        void SetY(const double d) noexcept { *(begin() + 1) = d; }

        [[nodiscard]] operator Point<ThisSpace, Implementation>() const noexcept {
            return Point<ThisSpace, Implementation>(X(), Y(), 0);
        }

        [[nodiscard]] double* begin() noexcept { return reinterpret_cast<double*>(&m_impl); }
        [[nodiscard]] double* end() noexcept { return reinterpret_cast<double*>(&m_impl) + 2; }
        [[nodiscard]] const double* cbegin() const noexcept { return reinterpret_cast<const double*>(&m_impl); }
        [[nodiscard]] const double* cend() const noexcept { return reinterpret_cast<const double*>(&m_impl) + 2; }

        [[nodiscard]] bool operator== (const Point<ThisSpace, Implementation>& other) const noexcept {
            return std::equal(cbegin(), cend(), detail::cbegin(other.m_impl), detail::Equality);
        }
        [[nodiscard]] bool operator== (const XYPoint<ThisSpace, Implementation>& other) const noexcept {
            return std::equal(cbegin(), cend(), detail::cbegin(other.m_impl), detail::Equality);
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
            return *(cbegin() + i);
        }

        template <int I> requires ValidFor2dAt<I>
        [[nodiscard]] double at() const {
            return operator[](I);
        }

        XYPoint<ThisSpace, Implementation> operator-=(const XYVector<ThisSpace, Implementation>& rhs) noexcept {
            detail::Sub(m_impl, rhs.m_impl);
            return *this;
        }
        XYPoint<ThisSpace, Implementation> operator-=(const NormalizedXYVector<ThisSpace, Implementation>& rhs) noexcept {
            detail::Sub(m_impl, rhs.m_impl);
            return *this;
        }

        [[nodiscard]] Point<ThisSpace, Implementation> operator-(const Vector<ThisSpace, Implementation>& rhs) const noexcept {
            Point<ThisSpace, Implementation> v(static_cast<Implementation>(*this));
            detail::Sub(v.m_impl, rhs.m_impl);
            return v;
        }
        [[nodiscard]] Point<ThisSpace, Implementation> operator-(const NormalizedVector<ThisSpace, Implementation>& rhs) const noexcept {
            Point<ThisSpace, Implementation> v(static_cast<Implementation>(*this));
            detail::Sub(v.m_impl, rhs.m_impl);
            return v;
        }
        [[nodiscard]] XYPoint<ThisSpace, Implementation> operator-(const NormalizedXYVector<ThisSpace, Implementation>& rhs) const noexcept {
            XYPoint<ThisSpace, Implementation> v(static_cast<Implementation>(*this));
            detail::Sub(v.m_impl, rhs.m_impl);
            return v;
        }
        [[nodiscard]] XYPoint<ThisSpace, Implementation> operator-(const XYVector<ThisSpace, Implementation>& rhs) const noexcept {
            XYPoint<ThisSpace, Implementation> v(static_cast<Implementation>(*this));
            detail::Sub(v.m_impl, rhs.m_impl);
            return v;
        }

        [[nodiscard]] XYVector<ThisSpace, Implementation> operator-(const XYPoint<ThisSpace, Implementation>& rhs) const noexcept {
            XYVector<ThisSpace, Implementation> v(static_cast<Implementation>(*this));
            detail::Sub(v.m_impl, rhs.m_impl);
            return v;
        }
        [[nodiscard]] Vector<ThisSpace, Implementation> operator-(const Point<ThisSpace, Implementation>& rhs) const noexcept {
            Vector<ThisSpace, Implementation> v(static_cast<Implementation>(*this));
            detail::Sub(v.m_impl, rhs.m_impl);
            return v;
        }

        XYPoint<ThisSpace, Implementation> operator+=(const XYVector<ThisSpace, Implementation>& rhs) noexcept {
            detail::Add(m_impl, rhs.m_impl);
            return *this;
        }
        XYPoint<ThisSpace, Implementation> operator+=(const NormalizedXYVector<ThisSpace, Implementation>& rhs) noexcept {
            detail::Add(m_impl, rhs.m_impl);
            return *this;
        }

        [[nodiscard]] Point<ThisSpace, Implementation> operator+(const Vector<ThisSpace, Implementation>& rhs) const noexcept {
            Point<ThisSpace, Implementation> v(static_cast<Implementation>(*this));
            detail::Add(v.m_impl, rhs.m_impl);
            return v;
        }
        [[nodiscard]] Point<ThisSpace, Implementation> operator+(const NormalizedVector<ThisSpace, Implementation>& rhs) const noexcept {
            Point<ThisSpace, Implementation> v(static_cast<Implementation>(*this));
            detail::Add(v.m_impl, rhs.m_impl);
            return v;
        }
        [[nodiscard]] XYPoint<ThisSpace, Implementation> operator+(const NormalizedXYVector<ThisSpace, Implementation>& rhs) const noexcept {
            XYPoint<ThisSpace, Implementation> v(static_cast<Implementation>(*this));
            detail::Add(v.m_impl, rhs.m_impl);
            return v;
        }
        [[nodiscard]] XYPoint<ThisSpace, Implementation> operator+(const XYVector<ThisSpace, Implementation>& rhs) const noexcept {
            XYPoint<ThisSpace, Implementation> v(static_cast<Implementation>(*this));
            detail::Add(v.m_impl, rhs.m_impl);
            return v;
        }

        template <typename OtherSpace, typename TransformManager> requires DifferentSpaces<OtherSpace, ThisSpace>
        [[nodiscard]] Point<OtherSpace, Implementation> ConvertTo(const TransformManager& transform_manager) const {
            return Point<OtherSpace, Implementation>(transform_manager.template TransformPoint<ThisSpace, OtherSpace>(static_cast<Implementation>(*this)));
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

        using _base::operator+=;
        using _base::operator+;
        using _base::operator-=;
        using _base::operator-;
        using _base::ConvertTo;

        template <int I> requires !ValidFor2dAt<I>
        typename StaticAssert::invalid_at_access at() const {
            return StaticAssert::invalid_at_access{};
        }

        template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
        StaticAssert::invalid_space operator!= (const Point<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
        StaticAssert::invalid_space operator!= (const XYPoint<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_space{};
        }

        template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
        StaticAssert::invalid_space operator== (const Point<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
        StaticAssert::invalid_space operator== (const XYPoint<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_space{};
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

        StaticAssert::invalid_point_to_point_addition operator+=(const Point<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_to_point_addition{};
        }
        StaticAssert::invalid_point_to_point_addition operator+=(const XYPoint<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_to_point_addition{};
        }

        StaticAssert::invalid_vector3_to_xy_point_addition operator+=(const Vector<ThisSpace, Implementation>&) noexcept {
            return StaticAssert::invalid_vector3_to_xy_point_addition{};
        }
        StaticAssert::invalid_vector3_to_xy_point_addition operator+=(const NormalizedVector<ThisSpace, Implementation>&) noexcept {
            return StaticAssert::invalid_vector3_to_xy_point_addition{};
        }

        StaticAssert::invalid_point_from_vector_subtraction operator-=(const Point<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_from_vector_subtraction{};
        }
        StaticAssert::invalid_point_from_vector_subtraction operator-=(const XYPoint<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_from_vector_subtraction{};
        }

        StaticAssert::invalid_vector3_from_xy_point_subtraction operator-=(const Vector<ThisSpace, Implementation>&) noexcept {
            return StaticAssert::invalid_vector3_from_xy_point_subtraction{};
        }
        StaticAssert::invalid_vector3_from_xy_point_subtraction operator-=(const NormalizedVector<ThisSpace, Implementation>&) noexcept {
            return StaticAssert::invalid_vector3_from_xy_point_subtraction{};
        }

        StaticAssert::invalid_point_to_point_addition operator+(const Point<ThisSpace, Implementation>&) const {
            return StaticAssert::invalid_point_to_point_addition{};
        }
        StaticAssert::invalid_point_to_point_addition operator+(const XYPoint<ThisSpace, Implementation>&) const {
            return StaticAssert::invalid_point_to_point_addition{};
        }
#endif
        // Hide functions from intellisense
        void Dot() = delete;
        void Cross() = delete;
        void operator*() = delete;
        void operator*=(double) = delete;

    private:
        Implementation m_impl;
    };
}
