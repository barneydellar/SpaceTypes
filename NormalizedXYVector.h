#pragma once

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class NormalizedXYVector final : public Base<ThisSpace, Implementation>
    {
        using _base = Base<ThisSpace, Implementation>;

    public:

        NormalizedXYVector() noexcept {
            auto iter = _base::begin();
            *iter++ = 1;
            *iter++ = 0;
            *iter = 0;
        }
        explicit NormalizedXYVector(const Implementation& v) noexcept(false) {
            auto iter = _base::begin();
            auto in = reinterpret_cast<const double*>(&v);
            *iter++ = *in++;
            *iter++ = *in++;
            *iter = 0;
            Normalize();
        }
        explicit NormalizedXYVector(const double x, const double y) noexcept(false)
        {
            auto iter = _base::begin();
            *iter++ = x;
            *iter++ = y;
            *iter = 0;
            Normalize();
        }
        NormalizedXYVector(const std::initializer_list<double>& l) noexcept(false)
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
            Normalize();
        }

        [[nodiscard]] explicit operator Implementation() const noexcept {
            return _base::m_impl;
        }

        [[nodiscard]] operator Vector<ThisSpace, Implementation>() const noexcept {
            return Vector<ThisSpace, Implementation>(X(), Y(), 0);
        }

        [[nodiscard]] operator XYVector<ThisSpace, Implementation>() const noexcept {
            return XYVector<ThisSpace, Implementation>(X(), Y());
        }

        [[nodiscard]] operator NormalizedVector<ThisSpace, Implementation>() const noexcept {
            return NormalizedVector<ThisSpace, Implementation>(X(), Y(), 0);
        }

        [[nodiscard]] double X() const noexcept { return *(cbegin() + 0); }
        [[nodiscard]] double Y() const noexcept { return *(cbegin() + 1); }

        [[nodiscard]] const double* cbegin() const noexcept { return _base::cbegin(); }
        [[nodiscard]] const double* cend() const noexcept { return reinterpret_cast<const double*>(std::prev(_base::cend())); }

        double operator[](const unsigned int i) const {
            if (i > 1) {
                throw std::invalid_argument("Index is out of range");
            }
            return *(_base::cbegin() + i);
        }

        template <int I>
        [[nodiscard]] typename std::enable_if<I == 0 || I == 1, double>::type at() const {
            return operator[](I);
        }

        void SetX(const double d) noexcept { *(_base::begin() + 0) = d; }
        void SetY(const double d) noexcept { *(_base::begin() + 1) = d; }

        using _base::operator==;
        [[nodiscard]] bool operator== (const Vector<ThisSpace, Implementation>& other) const noexcept {
            return std::equal(_base::cbegin(), _base::cend(), other.cbegin(), _base::Equality);
        }
        [[nodiscard]] bool operator== (const NormalizedVector<ThisSpace, Implementation>& other) const noexcept {
            return std::equal(_base::cbegin(), _base::cend(), other.cbegin(), _base::Equality);
        }
        [[nodiscard]] bool operator== (const NormalizedXYVector<ThisSpace, Implementation>& other) const noexcept {
            return std::equal(_base::cbegin(), _base::cend(), other.cbegin(), _base::Equality);
        }
        [[nodiscard]] bool operator== (const XYVector<ThisSpace, Implementation>& other) const noexcept {
            return std::equal(_base::cbegin(), _base::cend(), other.cbegin(), _base::Equality);
        }

        using _base::operator!=;
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

        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator-(NormalizedXYVector<ThisSpace, Implementation> lhs, const Vector<ThisSpace, Implementation>& rhs) noexcept {
            _base::Sub(lhs.m_impl, rhs.m_impl);
            return Vector<ThisSpace, Implementation>(lhs.X(), lhs.Y(), lhs.Z());
        }
        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator-(NormalizedXYVector<ThisSpace, Implementation> lhs, const NormalizedVector<ThisSpace, Implementation>& rhs) noexcept {
            _base::Sub(lhs.m_impl, rhs.m_impl);
            return Vector<ThisSpace, Implementation>(static_cast<Implementation>(lhs));
        }
        [[nodiscard]] friend XYVector<ThisSpace, Implementation> operator-(NormalizedXYVector<ThisSpace, Implementation> lhs, const NormalizedXYVector<ThisSpace, Implementation>& rhs) noexcept {
            _base::Sub(lhs.m_impl, rhs.m_impl);
            return XYVector<ThisSpace, Implementation>(lhs.X(), lhs.Y());
        }
        [[nodiscard]] friend XYVector<ThisSpace, Implementation> operator-(NormalizedXYVector<ThisSpace, Implementation> lhs, const XYVector<ThisSpace, Implementation>& rhs) noexcept {
            _base::Sub(lhs.m_impl, rhs.m_impl);
            return XYVector<ThisSpace, Implementation>(lhs.X(), lhs.Y());
        }

        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator+(NormalizedXYVector<ThisSpace, Implementation> lhs, const Vector<ThisSpace, Implementation>& rhs) noexcept {
            _base::Add(lhs.m_impl, rhs.m_impl);
            return Vector<ThisSpace, Implementation>(static_cast<Implementation>(lhs));
        }
        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator+(NormalizedXYVector<ThisSpace, Implementation> lhs, const NormalizedVector<ThisSpace, Implementation>& rhs) noexcept {
            _base::Add(lhs.m_impl, rhs.m_impl);
            return Vector<ThisSpace, Implementation>(static_cast<Implementation>(lhs));
        }
        [[nodiscard]] friend XYVector<ThisSpace, Implementation> operator+(NormalizedXYVector<ThisSpace, Implementation> lhs, const NormalizedXYVector<ThisSpace, Implementation>& rhs) noexcept {
            _base::Add(lhs.m_impl, rhs.m_impl);
            return XYVector<ThisSpace, Implementation>(lhs.X(), lhs.Y());
        }
        [[nodiscard]] friend XYVector<ThisSpace, Implementation> operator+(NormalizedXYVector<ThisSpace, Implementation> lhs, const XYVector<ThisSpace, Implementation>& rhs) noexcept {
            _base::Add(lhs.m_impl, rhs.m_impl);
            return XYVector<ThisSpace, Implementation>(lhs.X(), lhs.Y());
        }

        [[nodiscard]] friend XYVector<ThisSpace, Implementation> operator*(NormalizedXYVector<ThisSpace, Implementation> lhs, const double& d) noexcept {
            _base::Scale(lhs.m_impl, d);
            return XYVector<ThisSpace, Implementation>(lhs.X(), lhs.Y());
        }

        [[nodiscard]] Vector<ThisSpace, Implementation> operator*(const Vector<ThisSpace, Implementation>& rhs) const noexcept {
            return this->Cross(rhs);
        }
        [[nodiscard]] NormalizedVector<ThisSpace, Implementation> operator*(const NormalizedXYVector<ThisSpace, Implementation>& rhs) const noexcept {
            return this->Cross(rhs);
        }
        [[nodiscard]] NormalizedVector<ThisSpace, Implementation> operator*(const NormalizedVector<ThisSpace, Implementation>& rhs) const noexcept {
            return this->Cross(rhs);
        }
        [[nodiscard]] Vector<ThisSpace, Implementation> operator*(const XYVector<ThisSpace, Implementation>& rhs) const noexcept {
            return this->Cross(rhs);
        }

        [[nodiscard]] Vector<ThisSpace, Implementation> Cross(const Vector<ThisSpace, Implementation>& other) const noexcept {
            const auto[x, y, z] = _base::Cross_internal(_base::m_impl, other.m_impl);
            return Vector<ThisSpace, Implementation>(x, y, z);
        }
        [[nodiscard]] NormalizedVector<ThisSpace, Implementation> Cross(const NormalizedVector<ThisSpace, Implementation>& other) const noexcept {
            const auto[x, y, z] = _base::Cross_internal(_base::m_impl, other.m_impl);
            return NormalizedVector<ThisSpace, Implementation>(x, y, z);
        }
        [[nodiscard]] NormalizedVector<ThisSpace, Implementation> Cross(const NormalizedXYVector<ThisSpace, Implementation>& other) const noexcept {
            const auto[x, y, z] = _base::Cross_internal(_base::m_impl, other.m_impl);
            return NormalizedVector<ThisSpace, Implementation>(x, y, z);
        }
        [[nodiscard]] Vector<ThisSpace, Implementation> Cross(const XYVector<ThisSpace, Implementation>& other) const noexcept {
            const auto[x, y, z] = _base::Cross_internal(_base::m_impl, other.m_impl);
            return Vector<ThisSpace, Implementation>(x, y, z);
        }

        [[nodiscard]] double Dot(const Vector<ThisSpace, Implementation>& other) const noexcept { return _base::Dot(_base::m_impl, other.m_impl);; }
        [[nodiscard]] double Dot(const NormalizedVector<ThisSpace, Implementation>& other) const noexcept { return _base::Dot(_base::m_impl, other.m_impl);; }
        [[nodiscard]] double Dot(const NormalizedXYVector<ThisSpace, Implementation>& other) const noexcept { return _base::Dot(_base::m_impl, other.m_impl);; }
        [[nodiscard]] double Dot(const XYVector<ThisSpace, Implementation>& other) const noexcept { return _base::Dot(_base::m_impl, other.m_impl);; }


        template <typename OtherSpace, typename TransformManager>
        [[nodiscard]] std::enable_if_t<!std::is_same_v<OtherSpace, ThisSpace>, Vector<OtherSpace, Implementation>> ConvertTo(const TransformManager& transform_manager) const noexcept {
            return Vector < OtherSpace, Implementation>(transform_manager.template Transform33<ThisSpace, OtherSpace>(static_cast<Implementation>(*this)));
        }

        friend std::ostream& operator << (
            std::ostream& os,
            const NormalizedXYVector<ThisSpace, Implementation>& item
        ) {
            const auto space = SpaceTypeNameMap<ThisSpace>::name;
            os << space << "::NormalizedXYVector (" << item.X() << ", " << item.Y() << ")";
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


        StaticAssert::invalid_normalized_vector_scale operator*=(const double&) const noexcept {
            return StaticAssert::invalid_normalized_vector_scale{};
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
        StaticAssert::invalid_normalized_vector_in_place_cross operator*=(const XYVector<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_normalized_vector_in_place_cross{};
        }

        StaticAssert::invalid_normalized_vector_addition operator+=(const Vector<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_normalized_vector_addition{};
        }
        StaticAssert::invalid_normalized_vector_addition operator+=(const NormalizedVector<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_normalized_vector_addition{};
        }
        StaticAssert::invalid_normalized_vector_addition operator+=(const NormalizedXYVector<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_normalized_vector_addition{};
        }
        StaticAssert::invalid_normalized_vector_addition operator+=(const XYVector<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_normalized_vector_addition{};
        }

        StaticAssert::invalid_normalized_vector_subtraction operator-=(const Vector<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_normalized_vector_subtraction{};
        }
        StaticAssert::invalid_normalized_vector_subtraction operator-=(const NormalizedVector<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_normalized_vector_subtraction{};
        }
        StaticAssert::invalid_normalized_vector_subtraction operator-=(const NormalizedXYVector<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_normalized_vector_subtraction{};
        }
        StaticAssert::invalid_normalized_vector_subtraction operator-=(const XYVector<ThisSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_normalized_vector_subtraction{};
        }
#endif

    private:

        void Normalize() {
            const auto mag = _base::Mag_internal(_base::m_impl);
            if (std::abs(mag) < 1e-6) {
                throw std::invalid_argument("Zero-sized normal vectors are not allowed");
            }

            std::transform(
                _base::cbegin(),
                _base::cend(),
                _base::begin(),
                [mag](auto v) { return v / mag; }
            );
        }

    };
}
