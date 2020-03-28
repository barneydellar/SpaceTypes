#pragma once

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class Vector final : public Base<ThisSpace, Implementation>
    {
        using _base = Base<ThisSpace, Implementation>;
        using _base::_base;

    public:

        [[nodiscard]] double X() const noexcept { return _base::X_internal(); }
        [[nodiscard]] double Y() const noexcept { return _base::Y_internal(); }
        [[nodiscard]] double Z() const noexcept { return _base::Z_internal(); }


        [[nodiscard]] double* begin() noexcept { return _base::begin(); }
        [[nodiscard]] double* end() noexcept { return _base::end(); }
        [[nodiscard]] const double* cbegin() const noexcept { return _base::cbegin(); }
        [[nodiscard]] const double* cend() const noexcept { return _base::cend(); }

        void SetX(const double d) noexcept { *(begin() + 0) = d; }
        void SetY(const double d) noexcept { *(begin() + 1) = d; }
        void SetZ(const double d) noexcept { *(begin() + 2) = d; }

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

        Vector<ThisSpace, Implementation> operator-=(const Vector<ThisSpace, Implementation>& rhs) noexcept {
            _base::Sub(rhs);
            return *this;
        }
        Vector<ThisSpace, Implementation> operator-=(const NormalizedVector<ThisSpace, Implementation>& rhs) noexcept {
            _base::Sub(rhs);
            return *this;
        }
        Vector<ThisSpace, Implementation> operator-=(const NormalizedXYVector<ThisSpace, Implementation>& rhs) noexcept {
            _base::Sub(rhs);
            return *this;
        }
        Vector<ThisSpace, Implementation> operator-=(const XYVector<ThisSpace, Implementation>& rhs) noexcept {
            _base::Sub(rhs);
            return *this;
        }

        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator-(Vector<ThisSpace, Implementation> lhs, const Vector<ThisSpace, Implementation>& rhs) noexcept {
            lhs.Sub(rhs);
            return lhs;
        }
        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator-(Vector<ThisSpace, Implementation> lhs, const NormalizedVector<ThisSpace, Implementation>& rhs) noexcept {
            lhs.Sub(rhs);
            return lhs;
        }
        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator-(Vector<ThisSpace, Implementation> lhs, const NormalizedXYVector<ThisSpace, Implementation>& rhs) noexcept {
            lhs.Sub(rhs);
            return lhs;
        }
        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator-(Vector<ThisSpace, Implementation> lhs, const XYVector<ThisSpace, Implementation>& rhs) noexcept {
            lhs.Sub(rhs);
            return lhs;
        }

        Vector<ThisSpace, Implementation> operator+=(const Vector<ThisSpace, Implementation>& rhs) noexcept {
            _base::Add(rhs);
            return *this;
        }
        Vector<ThisSpace, Implementation> operator+=(const NormalizedVector<ThisSpace, Implementation>& rhs) noexcept {
            _base::Add(rhs);
            return *this;
        }
        Vector<ThisSpace, Implementation> operator+=(const NormalizedXYVector<ThisSpace, Implementation>& rhs) noexcept {
            _base::Add(rhs);
            return *this;
        }
        Vector<ThisSpace, Implementation> operator+=(const XYVector<ThisSpace, Implementation>& rhs) noexcept {
            _base::Add(rhs);
            return *this;
        }

        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator+(Vector<ThisSpace, Implementation> lhs, const Vector<ThisSpace, Implementation>& rhs) noexcept {
            lhs.Add(rhs);
            return lhs;
        }
        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator+(Vector<ThisSpace, Implementation> lhs, const NormalizedVector<ThisSpace, Implementation>& rhs) noexcept {
            lhs.Add(rhs);
            return lhs;
        }
        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator+(Vector<ThisSpace, Implementation> lhs, const NormalizedXYVector<ThisSpace, Implementation>& rhs) noexcept {
            lhs.Add(rhs);
            return lhs;
        }
        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator+(Vector<ThisSpace, Implementation> lhs, const XYVector<ThisSpace, Implementation>& rhs) noexcept {
            lhs.Add(rhs);
            return lhs;
        }

        Vector<ThisSpace, Implementation> operator*=(const double& d) noexcept {
            _base::Scale(d);
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

        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator*(Vector<ThisSpace, Implementation> lhs, const double& d) noexcept {
            lhs *= d;
            return lhs;
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
            const auto[x, y, z] = _base::Cross_internal(*this, other);
            return Vector<ThisSpace, Implementation>(x, y, z);
        }
        [[nodiscard]] Vector<ThisSpace, Implementation> Cross(const NormalizedVector<ThisSpace, Implementation>& other) const noexcept {
            const auto[x, y, z] = _base::Cross_internal(*this, other);
            return Vector<ThisSpace, Implementation>(x, y, z);
        }
        [[nodiscard]] Vector<ThisSpace, Implementation> Cross(const NormalizedXYVector<ThisSpace, Implementation>& other) const noexcept {
            const auto[x, y, z] = _base::Cross_internal(*this, other);
            return Vector<ThisSpace, Implementation>(x, y, z);
        }
        [[nodiscard]] Vector<ThisSpace, Implementation> Cross(const XYVector<ThisSpace, Implementation>& other) const noexcept {
            const auto[x, y, z] = _base::Cross_internal(*this, other);
            return Vector<ThisSpace, Implementation>(x, y, z);
        }

        [[nodiscard]] double Dot(const Vector<ThisSpace, Implementation>& other) const noexcept { return _base::Dot(other); }
        [[nodiscard]] double Dot(const NormalizedVector<ThisSpace, Implementation>& other) const noexcept { return _base::Dot(other); }
        [[nodiscard]] double Dot(const NormalizedXYVector<ThisSpace, Implementation>& other) const noexcept { return _base::Dot(other); }
        [[nodiscard]] double Dot(const XYVector<ThisSpace, Implementation>& other) const noexcept { return _base::Dot(other); }


        [[nodiscard]] XYVector<ThisSpace, Implementation> ToXY() const {
            return XYVector<ThisSpace, Implementation>(X(), Y());
        }

        [[nodiscard]] NormalizedVector<ThisSpace, Implementation> Norm() const {
            return NormalizedVector<ThisSpace, Implementation>(X(), Y(), Z());
        }

        template <typename OtherSpace, typename TransformManager>
        [[nodiscard]] std::enable_if_t<!std::is_same_v<OtherSpace, ThisSpace>, Vector<OtherSpace, Implementation>> ConvertTo(const TransformManager& transform_manager) const noexcept {
            return Vector < OtherSpace, Implementation>(transform_manager.template Transform33<ThisSpace, OtherSpace>(static_cast<Implementation>(*this)));
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
        using _base::at;


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
#endif

    };
}
