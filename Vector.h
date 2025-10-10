#pragma once

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class Vector final
#ifndef IGNORE_SPACE_STATIC_ASSERT
        : public detail::Base<ThisSpace, Implementation>
#endif
    {
        using _base = detail::Base<ThisSpace, Implementation>;

        friend class NormalizedVector<ThisSpace, Implementation>;
        friend class NormalizedXYVector<ThisSpace, Implementation>;
        friend class Point<ThisSpace, Implementation>;
        friend class XYPoint<ThisSpace, Implementation>;
        friend class XYVector<ThisSpace, Implementation>;

    public:

        Vector() noexcept { std::fill(begin(), end(), 0); }
        explicit Vector(const Implementation& v) noexcept
        {
            std::copy(
                detail::cbegin(v),
                detail::cend(v),
                begin()
            );
        }
        Vector(const double x, const double y, const double z) noexcept
        {
            auto iter = begin();
            *iter++ = x;
            *iter++ = y;
            *iter = z;
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

        [[nodiscard]] double* begin() noexcept { return reinterpret_cast<double*>(&m_impl); }
        [[nodiscard]] double* end() noexcept { return reinterpret_cast<double*>(&m_impl) + 3; }
        [[nodiscard]] const double* cbegin() const noexcept { return reinterpret_cast<const double*>(&m_impl); }
        [[nodiscard]] const double* cend() const noexcept { return reinterpret_cast<const double*>(&m_impl) + 3; }

        [[nodiscard]] double operator[] (const unsigned int i) const {
            if (i > 2) {
                throw std::invalid_argument("Index is out of range");
            }
            return *(cbegin() + i);
        }

        template <int I> requires ValidFor3dAt<I>
        [[nodiscard]] double at() const {
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

        Vector<ThisSpace, Implementation> operator-=(const Vector<ThisSpace, Implementation>& rhs) noexcept {
            detail::Sub(m_impl, rhs.m_impl);
            return *this;
        }
        Vector<ThisSpace, Implementation> operator-=(const NormalizedVector<ThisSpace, Implementation>& rhs) noexcept {
            detail::Sub(m_impl, rhs.m_impl);
            return *this;
        }
        Vector<ThisSpace, Implementation> operator-=(const NormalizedXYVector<ThisSpace, Implementation>& rhs) noexcept {
            detail::Sub(m_impl, rhs.m_impl);
            return *this;
        }
        Vector<ThisSpace, Implementation> operator-=(const XYVector<ThisSpace, Implementation>& rhs) noexcept {
            detail::Sub(m_impl, rhs.m_impl);
            return *this;
        }

        [[nodiscard]] Vector<ThisSpace, Implementation> operator-(const Vector<ThisSpace, Implementation>& rhs) const noexcept {
            Vector<ThisSpace, Implementation> v(X(), Y(), Z());
            detail::Sub(v.m_impl, rhs.m_impl);
            return v;
        }
        [[nodiscard]] Vector<ThisSpace, Implementation> operator-(const NormalizedVector<ThisSpace, Implementation>& rhs) const noexcept {
            Vector<ThisSpace, Implementation> v(X(), Y(), Z());
            detail::Sub(v.m_impl, rhs.m_impl);
            return v;
        }
        [[nodiscard]] Vector<ThisSpace, Implementation> operator-(const NormalizedXYVector<ThisSpace, Implementation>& rhs) const noexcept {
            Vector<ThisSpace, Implementation> v(X(), Y(), Z());
            detail::Sub(v.m_impl, rhs.m_impl);
            return v;
        }
        [[nodiscard]] Vector<ThisSpace, Implementation> operator-(const XYVector<ThisSpace, Implementation>& rhs) const noexcept {
            Vector<ThisSpace, Implementation> v(X(), Y(), Z());
            detail::Sub(v.m_impl, rhs.m_impl);
            return v;
        }

        Vector<ThisSpace, Implementation> operator+=(const Vector<ThisSpace, Implementation>& rhs) noexcept {
            detail::Add(m_impl, rhs.m_impl);
            return *this;
        }
        Vector<ThisSpace, Implementation> operator+=(const NormalizedVector<ThisSpace, Implementation>& rhs) noexcept {
            detail::Add(m_impl, rhs.m_impl);
            return *this;
        }
        Vector<ThisSpace, Implementation> operator+=(const NormalizedXYVector<ThisSpace, Implementation>& rhs) noexcept {
            detail::Add(m_impl, rhs.m_impl);
            return *this;
        }
        Vector<ThisSpace, Implementation> operator+=(const XYVector<ThisSpace, Implementation>& rhs) noexcept {
            detail::Add(m_impl, rhs.m_impl);
            return *this;
        }

        [[nodiscard]] Vector<ThisSpace, Implementation> operator+(const Vector<ThisSpace, Implementation>& rhs) const noexcept {
            Vector<ThisSpace, Implementation> v(X(), Y(), Z());
            detail::Add(v.m_impl, rhs.m_impl);
            return v;
        }
        [[nodiscard]] Vector<ThisSpace, Implementation> operator+(const NormalizedVector<ThisSpace, Implementation>& rhs) const noexcept {
            Vector<ThisSpace, Implementation> v(X(), Y(), Z());
            detail::Add(v.m_impl, rhs.m_impl);
            return v;
        }
        [[nodiscard]] Vector<ThisSpace, Implementation> operator+(const NormalizedXYVector<ThisSpace, Implementation>& rhs) const noexcept {
            Vector<ThisSpace, Implementation> v(X(), Y(), Z());
            detail::Add(v.m_impl, rhs.m_impl);
            return v;
        }
        [[nodiscard]] Vector<ThisSpace, Implementation> operator+(const XYVector<ThisSpace, Implementation>& rhs) const noexcept {
            Vector<ThisSpace, Implementation> v(X(), Y(), Z());
            detail::Add(v.m_impl, rhs.m_impl);
            return v;
        }

        Vector<ThisSpace, Implementation> operator*=(const double& d) noexcept {
            detail::Scale(m_impl, d);
            return *this;
        }

        Vector<ThisSpace, Implementation> operator*=(const Vector<ThisSpace, Implementation>& rhs) noexcept {
            *this = this->Cross(rhs);
            return *this;
        }
        Vector<ThisSpace, Implementation> operator*=(const NormalizedVector<ThisSpace, Implementation>& rhs) noexcept {
            *this = this->Cross(rhs);
            return *this;
        }
        Vector<ThisSpace, Implementation> operator*=(const NormalizedXYVector<ThisSpace, Implementation>& rhs) noexcept {
            *this = this->Cross(rhs);
            return *this;
        }
        Vector<ThisSpace, Implementation> operator*=(const XYVector<ThisSpace, Implementation>& rhs) noexcept {
            *this = this->Cross(rhs);
            return *this;
        }

        [[nodiscard]] Vector<ThisSpace, Implementation> operator*(const double& d) const noexcept {
            Vector<ThisSpace, Implementation> v(X(), Y(), Z());
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

        [[nodiscard]] double Dot(const Vector<ThisSpace, Implementation>& other) const noexcept { return detail::Dot(m_impl, other.m_impl); }
        [[nodiscard]] double Dot(const NormalizedVector<ThisSpace, Implementation>& other) const noexcept { return detail::Dot(m_impl, other.m_impl); }
        [[nodiscard]] double Dot(const NormalizedXYVector<ThisSpace, Implementation>& other) const noexcept { return detail::Dot(m_impl, other.m_impl); }
        [[nodiscard]] double Dot(const XYVector<ThisSpace, Implementation>& other) const noexcept { return detail::Dot(m_impl, other.m_impl); }

        [[nodiscard]] XYVector<ThisSpace, Implementation> ToXY() const requires ThisSpace::supportsXY {
            return XYVector<ThisSpace, Implementation>(X(), Y());
        }

        [[nodiscard]] NormalizedVector<ThisSpace, Implementation> Norm() const {
            return NormalizedVector<ThisSpace, Implementation>(X(), Y(), Z());
        }

        template <typename OtherSpace, typename TransformManager> requires DifferentSpaces<OtherSpace, ThisSpace>
        [[nodiscard]] Vector<OtherSpace, Implementation> ConvertTo(const TransformManager& transform_manager) const noexcept {
            return Vector < OtherSpace, Implementation>(transform_manager.template TransformVector<ThisSpace, OtherSpace>(static_cast<Implementation>(*this)));
        }

        [[nodiscard]] typename ThisSpace::Unit Mag() const noexcept {
            return typename ThisSpace::Unit{ Mag_double() };
        }

        [[nodiscard]] double Mag_double() const noexcept {return detail::Mag_internal(m_impl);}

        friend std::ostream& operator << (
            std::ostream& os,
            const Vector<ThisSpace, Implementation>& item
        ) {
            const auto space = SpaceTypeNameMap<ThisSpace>::name;
            os << space << "::Vector (" << item.X() << ", " << item.Y() << ", " << item.Z() << ")";
            return os;
        }
#ifndef IGNORE_SPACE_STATIC_ASSERT
        using _base::operator-=;
        using _base::operator-;
        using _base::operator+=;
        using _base::operator+;
        using _base::operator*=;
        using _base::operator*;
        using _base::ConvertTo;
        using _base::Dot;
        using _base::Cross;

        template <int I> requires !ValidFor3dAt<I>
        StaticAssert::invalid_at_access at() const {
            return StaticAssert::invalid_at_access{};
        }

        template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
        StaticAssert::invalid_space operator!= (const Vector<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
        StaticAssert::invalid_space operator!= (const NormalizedVector<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
        StaticAssert::invalid_space operator!= (const NormalizedXYVector<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
        StaticAssert::invalid_space operator!= (const XYVector<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_space{};
        }

        template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
        StaticAssert::invalid_space operator== (const Vector<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
        StaticAssert::invalid_space operator== (const NormalizedVector<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
        StaticAssert::invalid_space operator== (const NormalizedXYVector<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
        StaticAssert::invalid_space operator== (const XYVector<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_space{};
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

        [[nodiscard]] StaticAssert::XYVector_not_supported ToXY() const noexcept requires ThisSpace::doesNotSupportXY {
            return StaticAssert::XYVector_not_supported{};
        }
#endif
    protected:
        const Implementation& GetImpl() const {
            return m_impl;
        };
        Implementation m_impl;

    };
}
