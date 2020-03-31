#pragma once

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class Point final
#ifndef IGNORE_SPACE_STATIC_ASSERT
        : public detail::Base<ThisSpace, Implementation>
#endif
    {
        using _base = detail::Base<ThisSpace, Implementation>;

        friend class NormalizedVector<ThisSpace, Implementation>;
        friend class NormalizedXYVector<ThisSpace, Implementation>;
        friend class Vector<ThisSpace, Implementation>;
        friend class XYPoint<ThisSpace, Implementation>;
        friend class XYVector<ThisSpace, Implementation>;
    public:

        Point() noexcept{std::fill(begin(), end(), 0);}
        explicit Point(const Implementation& v) noexcept
        {
            std::copy(
                detail::cbegin(v),
                detail::cend(v),
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
            return m_impl;
        }

        [[nodiscard]] double X() const noexcept { return *(cbegin() + 0); }
        [[nodiscard]] double Y() const noexcept { return *(cbegin() + 1); }
        [[nodiscard]] double Z() const noexcept { return *(cbegin() + 2); }

        void SetX(const double d) noexcept { *(begin() + 0) = d; }
        void SetY(const double d) noexcept { *(begin() + 1) = d; }
        void SetZ(const double d) noexcept { *(begin() + 2) = d; }

        [[nodiscard]] double* begin() noexcept {return reinterpret_cast<double*>(&m_impl);}
        [[nodiscard]] double* end() noexcept {return reinterpret_cast<double*>(&m_impl) + 3;}
        [[nodiscard]] const double* cbegin() const noexcept {return reinterpret_cast<const double*>(&m_impl);}
        [[nodiscard]] const double* cend() const noexcept {return reinterpret_cast<const double*>(&m_impl) + 3;}

        [[nodiscard]] double operator[] (const unsigned int i) const {
            if (i > 2) {
                throw std::invalid_argument("Index is out of range");
            }
            return *(cbegin() + i);
        }

        template <int I>
        [[nodiscard]] typename std::enable_if<I == 0 || I == 1 || I == 2, double>::type at() const {
            return operator[](I);
        }

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

        Point<ThisSpace, Implementation> operator-=(const Vector<ThisSpace, Implementation>& rhs) noexcept {
            detail::Sub(m_impl, rhs.m_impl);
            return *this;
        }
        Point<ThisSpace, Implementation> operator-=(const NormalizedVector<ThisSpace, Implementation>& rhs) noexcept {
            detail::Sub(m_impl, rhs.m_impl);
            return *this;
        }
        Point<ThisSpace, Implementation> operator-=(const NormalizedXYVector<ThisSpace, Implementation>& rhs) noexcept {
            detail::Sub(m_impl, rhs.m_impl);
            return *this;
        }
        Point<ThisSpace, Implementation> operator-=(const XYVector<ThisSpace, Implementation>& rhs) noexcept {
            detail::Sub(m_impl, rhs.m_impl);
            return *this;
        }

        [[nodiscard]] Vector<ThisSpace, Implementation> operator-(const Point<ThisSpace, Implementation>& rhs) const noexcept {
            Vector<ThisSpace, Implementation> v(X(), Y(), Z());
            detail::Sub(v.m_impl, rhs.m_impl);
            return v;
        }
        [[nodiscard]] Vector<ThisSpace, Implementation> operator-(const XYPoint<ThisSpace, Implementation>& rhs) const noexcept {
            Vector<ThisSpace, Implementation> v(X(), Y(), Z());
            detail::Sub(v.m_impl, rhs.m_impl);
            return v;
        }
        [[nodiscard]] Point<ThisSpace, Implementation> operator-(const Vector<ThisSpace, Implementation>& rhs) const noexcept {
            Point<ThisSpace, Implementation> v(X(), Y(), Z());
            detail::Sub(v.m_impl, rhs.m_impl);
            return v;
        }
        [[nodiscard]] Point<ThisSpace, Implementation> operator-(const NormalizedVector<ThisSpace, Implementation>& rhs) const noexcept {
            Point<ThisSpace, Implementation> v(X(), Y(), Z());
            detail::Sub(v.m_impl, rhs.m_impl);
            return v;
        }
        [[nodiscard]] Point<ThisSpace, Implementation> operator-(const NormalizedXYVector<ThisSpace, Implementation>& rhs) const noexcept {
            Point<ThisSpace, Implementation> v(X(), Y(), Z());
            detail::Sub(v.m_impl, rhs.m_impl);
            return v;
        }
        [[nodiscard]] Point<ThisSpace, Implementation> operator-(const XYVector<ThisSpace, Implementation>& rhs) const noexcept {
            Point<ThisSpace, Implementation> v(X(), Y(), Z());
            detail::Sub(v.m_impl, rhs.m_impl);
            return v;
        }


        Point<ThisSpace, Implementation> operator+=(const Vector<ThisSpace, Implementation>& rhs) noexcept {
            detail::Add(m_impl, rhs.m_impl);
            return *this;
        }
        Point<ThisSpace, Implementation> operator+=(const NormalizedVector<ThisSpace, Implementation>& rhs) noexcept {
            detail::Add(m_impl, rhs.m_impl);
            return *this;
        }
        Point<ThisSpace, Implementation> operator+=(const NormalizedXYVector<ThisSpace, Implementation>& rhs) noexcept {
            detail::Add(m_impl, rhs.m_impl);
            return *this;
        }
        Point<ThisSpace, Implementation> operator+=(const XYVector<ThisSpace, Implementation>& rhs) noexcept {
            detail::Add(m_impl, rhs.m_impl);
            return *this;
        }

        [[nodiscard]] Point<ThisSpace, Implementation> operator+(const Vector<ThisSpace, Implementation>& rhs) const noexcept {
            Point<ThisSpace, Implementation> p(X(), Y(), Z());
            detail::Add(p.m_impl, rhs.m_impl);
            return p;
        }
        [[nodiscard]] Point<ThisSpace, Implementation> operator+(const NormalizedVector<ThisSpace, Implementation>& rhs) const noexcept {
            Point<ThisSpace, Implementation> p(X(), Y(), Z());
            detail::Add(p.m_impl, rhs.m_impl);
            return p;
        }
        [[nodiscard]] Point<ThisSpace, Implementation> operator+(const NormalizedXYVector<ThisSpace, Implementation>& rhs) const noexcept {
            Point<ThisSpace, Implementation> p(X(), Y(), Z());
            detail::Add(p.m_impl, rhs.m_impl);
            return p;
        }
        [[nodiscard]] Point<ThisSpace, Implementation> operator+(const XYVector<ThisSpace, Implementation>& rhs) const noexcept {
            Point<ThisSpace, Implementation> p(X(), Y(), Z());
            detail::Add(p.m_impl, rhs.m_impl);
            return p;
        }

        template <typename OtherSpace, typename TransformManager>
        [[nodiscard]] std::enable_if_t<!std::is_same_v<OtherSpace, ThisSpace>, Point<OtherSpace, Implementation>> ConvertTo(const TransformManager& transform_manager) const {
            return Point<OtherSpace, Implementation>(transform_manager.template Transform<ThisSpace, OtherSpace>(static_cast<Implementation>(*this)));
        }

        template <typename U = std::enable_if_t<static_cast<bool>(ThisSpace::hasXY), ThisSpace>>
        [[nodiscard]] XYPoint<U, Implementation> ToXY() const {
            return XYPoint<ThisSpace, Implementation>(X(), Y());
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
        using _base::operator+;
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

        StaticAssert::invalid_point_to_point_addition operator+=(const Point<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_to_point_addition{};
        }
        StaticAssert::invalid_point_to_point_addition operator+=(const XYPoint<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_to_point_addition{};
        }

        StaticAssert::invalid_point_to_point_addition operator+(const Point<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_to_point_addition{};
        }
        StaticAssert::invalid_point_to_point_addition operator+(const XYPoint<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_to_point_addition{};
        }

        StaticAssert::invalid_point_from_vector_subtraction operator-=(const Point<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_from_vector_subtraction{};
        }
        StaticAssert::invalid_point_from_vector_subtraction operator-=(const XYPoint<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_from_vector_subtraction{};
        }

        template <typename U = std::enable_if_t<!static_cast<bool>(ThisSpace::hasXY), void>>
        [[nodiscard]] StaticAssert::XYVector_not_supported ToXY() const noexcept {
            return StaticAssert::XYVector_not_supported{};
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
