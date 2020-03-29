#pragma once

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class XYVector final
#ifndef IGNORE_SPACE_STATIC_ASSERT
        : public detail::Base<ThisSpace, Implementation>
#endif
    {
        using _base = detail::Base<ThisSpace, Implementation>;

        friend class NormalizedVector<ThisSpace, Implementation>;
        friend class NormalizedXYVector<ThisSpace, Implementation>;
        friend class Point<ThisSpace, Implementation>;
        friend class Vector<ThisSpace, Implementation>;
        friend class XYPoint<ThisSpace, Implementation>;
    public:

        XYVector() noexcept {
            std::fill(begin(), end(), 0);
        }
        explicit XYVector(const Implementation& v) noexcept {
            auto iter = begin();
            auto in = detail::cbegin(v);
            *iter++ = *in++;
            *iter++ = *in++;
            *iter = 0;
        }
        explicit XYVector(const double x, const double y) noexcept
        {
            auto iter = begin();
            *iter++ = x;
            *iter++ = y;
            *iter = 0;
        }
        XYVector(const std::initializer_list<double>& l)
        {
            if (l.size() != 2)
            {
                throw std::invalid_argument("You can only initialise with two elements");
            }
            std::copy(
                std::cbegin(l),
                std::cend(l),
                detail::begin(m_impl)
            );
        }

        [[nodiscard]] explicit operator Implementation() const noexcept {
            return m_impl;
        }

        [[nodiscard]] operator Vector<ThisSpace, Implementation>() const noexcept {
            return Vector<ThisSpace, Implementation>(X(), Y(), 0);
        }

        [[nodiscard]] double X() const noexcept { return *(cbegin() + 0); }
        [[nodiscard]] double Y() const noexcept { return *(cbegin() + 1); }

        void SetX(const double d) noexcept { *(begin() + 0) = d; }
        void SetY(const double d) noexcept { *(begin() + 1) = d; }

        [[nodiscard]] double* begin() noexcept { return reinterpret_cast<double*>(&m_impl); }
        [[nodiscard]] double* end() noexcept { return reinterpret_cast<double*>(&m_impl) + 2; }
        [[nodiscard]] const double* cbegin() const noexcept { return reinterpret_cast<const double*>(&m_impl); }
        [[nodiscard]] const double* cend() const noexcept { return reinterpret_cast<const double*>(&m_impl) + 2; }

        double operator[](const unsigned int i) const {
            if (i > 1) {
                throw std::invalid_argument("Index is out of range");
            }
            return *(cbegin() + i);
        }

        template <int I>
        [[nodiscard]] typename std::enable_if<I == 0 || I == 1, double>::type at() const {
            return operator[](I);
        }

        [[nodiscard]] bool operator== (const Vector<ThisSpace, Implementation>& other) const noexcept {
            return std::equal(cbegin(), cend(), detail::cbegin(other.m_impl), detail::Equality);
        }
        [[nodiscard]] bool operator== (const NormalizedVector<ThisSpace, Implementation>& other) const noexcept {
            return std::equal(cbegin(), cend(), detail::cbegin(other.m_impl), detail::Equality);
        }
        [[nodiscard]] bool operator== (const NormalizedXYVector<ThisSpace, Implementation>& other) const noexcept {
            return std::equal(cbegin(), cend(), detail::cbegin(other.m_impl), detail::Equality);
        }
        [[nodiscard]] bool operator== (const XYVector<ThisSpace, Implementation>& other) const noexcept {
            return std::equal(cbegin(), cend(), detail::cbegin(other.m_impl), detail::Equality);
        }

        [[nodiscard]] bool operator!= (const Vector<ThisSpace, Implementation>& other) const noexcept {
            return !(operator==(other));
        }
        [[nodiscard]] bool operator!= (const NormalizedVector<ThisSpace, Implementation>& other) const noexcept {
            return !(operator==(other));
        }
        [[nodiscard]] bool operator!= (const NormalizedXYVector<ThisSpace, Implementation>& other) const noexcept {
            return !(operator==(other));
        }
        [[nodiscard]] bool operator!= (const XYVector<ThisSpace, Implementation>& other) const noexcept {
            return !(operator==(other));
        }

        XYVector<ThisSpace, Implementation> operator-=(const NormalizedXYVector<ThisSpace, Implementation>& rhs) noexcept {
            detail::Sub(m_impl, rhs.m_impl);
            return *this;
        }
        XYVector<ThisSpace, Implementation> operator-=(const XYVector<ThisSpace, Implementation>& rhs) noexcept {
            detail::Sub(m_impl, rhs.m_impl);
            return *this;
        }

        [[nodiscard]] Vector<ThisSpace, Implementation> operator-(const Vector<ThisSpace, Implementation>& rhs) const noexcept {
            Vector<ThisSpace, Implementation> v(static_cast<Implementation>(*this));
            detail::Sub(v.m_impl, rhs.m_impl);
            return v;
        }
        [[nodiscard]] Vector<ThisSpace, Implementation> operator-(const NormalizedVector<ThisSpace, Implementation>& rhs) const noexcept {
            Vector<ThisSpace, Implementation> v(static_cast<Implementation>(*this));
            detail::Sub(v.m_impl, rhs.m_impl);
            return v;
        }
        [[nodiscard]] XYVector<ThisSpace, Implementation> operator-(const NormalizedXYVector<ThisSpace, Implementation>& rhs) const noexcept {
            XYVector<ThisSpace, Implementation> v(static_cast<Implementation>(*this));
            detail::Sub(v.m_impl, rhs.m_impl);
            return v;
        }
        [[nodiscard]] XYVector<ThisSpace, Implementation> operator-(const XYVector<ThisSpace, Implementation>& rhs) const noexcept {
            XYVector<ThisSpace, Implementation> v(static_cast<Implementation>(*this));
            detail::Sub(v.m_impl, rhs.m_impl);
            return v;
        }

        XYVector<ThisSpace, Implementation> operator+=(const NormalizedXYVector<ThisSpace, Implementation>& rhs) noexcept {
            detail::Add(m_impl, rhs.m_impl);
            return *this;
        }
        XYVector<ThisSpace, Implementation> operator+=(const XYVector<ThisSpace, Implementation>& rhs) noexcept {
            detail::Add(m_impl, rhs.m_impl);
            return *this;
        }

        [[nodiscard]] Vector<ThisSpace, Implementation> operator+(const Vector<ThisSpace, Implementation>& rhs) const noexcept {
            Vector<ThisSpace, Implementation> v(static_cast<Implementation>(*this));
            detail::Add(v.m_impl, rhs.m_impl);
            return v;
        }
        [[nodiscard]] Vector<ThisSpace, Implementation> operator+(const NormalizedVector<ThisSpace, Implementation>& rhs) const noexcept {
            Vector<ThisSpace, Implementation> v(static_cast<Implementation>(*this));
            detail::Add(v.m_impl, rhs.m_impl);
            return v;
        }
        [[nodiscard]] XYVector<ThisSpace, Implementation> operator+(const NormalizedXYVector<ThisSpace, Implementation>& rhs) const noexcept {
            // TODO > v(
            XYVector<ThisSpace, Implementation> v(static_cast<Implementation>(*this));
            detail::Add(v.m_impl, rhs.m_impl);
            return v;
        }
        [[nodiscard]] XYVector<ThisSpace, Implementation> operator+(const XYVector<ThisSpace, Implementation>& rhs) const noexcept {
            XYVector<ThisSpace, Implementation> v(static_cast<Implementation>(*this));
            detail::Add(v.m_impl, rhs.m_impl);
            return v;
        }

        XYVector<ThisSpace, Implementation> operator*=(const double& d) noexcept {
            detail::Scale(m_impl, d);
            return *this;
        }

        [[nodiscard]] XYVector<ThisSpace, Implementation> operator*(const double& d) const noexcept {
            XYVector<ThisSpace, Implementation> v(static_cast<Implementation>(*this));
            detail::Scale(v.m_impl, d);
            return v;
        }

        [[nodiscard]] Vector<ThisSpace, Implementation> operator*(const Vector<ThisSpace, Implementation>& rhs) const noexcept {
            return this->Cross(rhs);
        }
        [[nodiscard]] Vector<ThisSpace, Implementation> operator*(const NormalizedXYVector<ThisSpace, Implementation>& rhs) const noexcept {
            return this->Cross(rhs);
        }
        [[nodiscard]] Vector<ThisSpace, Implementation> operator*(const NormalizedVector<ThisSpace, Implementation>& rhs) const noexcept {
            return this->Cross(rhs);
        }
        [[nodiscard]] Vector<ThisSpace, Implementation> operator*(const XYVector<ThisSpace, Implementation>& rhs) const noexcept {
            return this->Cross(rhs);
        }

        [[nodiscard]] Vector<ThisSpace, Implementation> Cross(const Vector<ThisSpace, Implementation>& other) const noexcept {
            const auto[x, y, z] = detail::Cross_internal(m_impl, other.m_impl);
            return Vector<ThisSpace, Implementation>(x, y, z);
        }
        [[nodiscard]] Vector<ThisSpace, Implementation> Cross(const NormalizedVector<ThisSpace, Implementation>& other) const noexcept {
            const auto[x, y, z] = detail::Cross_internal(m_impl, other.m_impl);
            return Vector<ThisSpace, Implementation>(x, y, z);
        }
        [[nodiscard]] Vector<ThisSpace, Implementation> Cross(const NormalizedXYVector<ThisSpace, Implementation>& other) const noexcept {
            const auto[x, y, z] = detail::Cross_internal(m_impl, other.m_impl);
            return Vector<ThisSpace, Implementation>(x, y, z);
        }
        [[nodiscard]] Vector<ThisSpace, Implementation> Cross(const XYVector<ThisSpace, Implementation>& other) const noexcept {
            const auto[x, y, z] = detail::Cross_internal(m_impl, other.m_impl);
            return Vector<ThisSpace, Implementation>(x, y, z);
        }

        [[nodiscard]] double Dot(const Vector<ThisSpace, Implementation>& other) const noexcept { return detail::Dot(m_impl, other.m_impl);; }
        [[nodiscard]] double Dot(const NormalizedVector<ThisSpace, Implementation>& other) const noexcept { return detail::Dot(m_impl, other.m_impl);; }
        [[nodiscard]] double Dot(const NormalizedXYVector<ThisSpace, Implementation>& other) const noexcept { return detail::Dot(m_impl, other.m_impl);; }
        [[nodiscard]] double Dot(const XYVector<ThisSpace, Implementation>& other) const noexcept { return detail::Dot(m_impl, other.m_impl);; }

        [[nodiscard]] NormalizedXYVector<ThisSpace, Implementation> Norm() const {
            return NormalizedXYVector<ThisSpace, Implementation>(X(), Y());
        }

        template <typename OtherSpace, typename TransformManager>
        [[nodiscard]] std::enable_if_t<!std::is_same_v<OtherSpace, ThisSpace>, Vector<OtherSpace, Implementation>> ConvertTo(const TransformManager& transform_manager) const noexcept {
            return Vector < OtherSpace, Implementation>(transform_manager.template Transform33<ThisSpace, OtherSpace>(static_cast<Implementation>(*this)));
        }

        [[nodiscard]] typename ThisSpace::Unit Mag() const noexcept {
            return ThisSpace::Unit{ Mag_double() };
        }

        [[nodiscard]] double Mag_double() const noexcept { return detail::Mag_internal(m_impl); }

        friend std::ostream& operator << (
            std::ostream& os,
            const XYVector<ThisSpace, Implementation>& item
        ) {
            const auto space = SpaceTypeNameMap<ThisSpace>::name;
            os << space << "::XYVector (" << item.X() << ", " << item.Y() << ")";
            return os;
        }

#ifndef IGNORE_SPACE_STATIC_ASSERT
        using _base::operator==;
        using _base::operator!=;
        using _base::operator-=;
        using _base::operator-;
        using _base::operator+=;
        using _base::operator+;
        using _base::operator*=;
        using _base::operator*;
        using _base::ConvertTo;
        using _base::Dot;
        using _base::Cross;

        template <int I>
        typename std::enable_if<I != 0 && I != 1, StaticAssert::invalid_at_access>::type at() const {
            return StaticAssert::invalid_at_access{};
        }

        StaticAssert::invalid_point_vector_equality operator== (const Point<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        StaticAssert::invalid_point_vector_equality operator== (const XYPoint<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        StaticAssert::invalid_point_vector_equality operator!= (const Point<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        StaticAssert::invalid_point_vector_equality operator!= (const XYPoint<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }

        StaticAssert::invalid_point_from_vector_subtraction operator-(const Point<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_from_vector_subtraction{};
        }

        StaticAssert::invalid_point_to_vector_addition operator+(const Point<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_point_to_vector_addition{};
        }

        StaticAssert::invalid_normalized_vector_in_place_cross operator*=(const Vector<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_normalized_vector_in_place_cross{};
        }
        StaticAssert::invalid_normalized_vector_in_place_cross operator*=(const NormalizedVector<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_normalized_vector_in_place_cross{};
        }
        StaticAssert::invalid_normalized_vector_in_place_cross operator*=(const NormalizedXYVector<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_normalized_vector_in_place_cross{};
        }
        StaticAssert::invalid_XYVector_in_place_cross operator*=(const XYVector<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_XYVector_in_place_cross{};
        }

        StaticAssert::invalid_vector_to_vector_addition operator+=(const Vector<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_vector_to_vector_addition{};
        }
        StaticAssert::invalid_vector_to_vector_addition operator+=(const NormalizedVector<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_vector_to_vector_addition{};
        }

        StaticAssert::invalid_normalized_vector_subtraction operator-=(const Vector<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_normalized_vector_subtraction{};
        }
        StaticAssert::invalid_normalized_vector_subtraction operator-=(const NormalizedVector<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_normalized_vector_subtraction{};
        }
#endif
    private:
        Implementation m_impl;

    };
}
