#pragma once

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class NormalizedVector final : public Base<ThisSpace, Implementation>
    {
        using _base = Base<ThisSpace, Implementation>;

    public:


        NormalizedVector() noexcept(false) : _base() { *_base::begin() = 1; }
        explicit NormalizedVector(const Implementation& e) noexcept(false) : _base(e) { Normalize(); }
        explicit NormalizedVector(const double x, const double y, const double z) noexcept(false) : _base(x, y, z) { Normalize(); }
        NormalizedVector(const std::initializer_list<double>& l) noexcept(false) : _base(l) { Normalize(); }

        [[nodiscard]] double Z() const noexcept { return *(_base::cbegin() + 2); }
        void SetX(const double d) noexcept { *(_base::begin() + 0) = d; }
        void SetY(const double d) noexcept { *(_base::begin() + 1) = d; }
        void SetZ(const double d) noexcept { *(_base::begin() + 2) = d; }

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

        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator-(NormalizedVector<ThisSpace, Implementation> lhs, const Vector<ThisSpace, Implementation>& rhs) noexcept {
            lhs.Sub(rhs);
            return Vector<ThisSpace, Implementation>(lhs.X(), lhs.Y(), lhs.Z());
        }
        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator-(NormalizedVector<ThisSpace, Implementation> lhs, const NormalizedVector<ThisSpace, Implementation>& rhs) noexcept {
            lhs.Sub(rhs);
            return Vector<ThisSpace, Implementation>(lhs.X(), lhs.Y(), lhs.Z());
        }
        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator-(NormalizedVector<ThisSpace, Implementation> lhs, const NormalizedXYVector<ThisSpace, Implementation>& rhs) noexcept {
            lhs.Sub(rhs);
            return Vector<ThisSpace, Implementation>(lhs.X(), lhs.Y(), lhs.Z());
        }
        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator-(NormalizedVector<ThisSpace, Implementation> lhs, const XYVector<ThisSpace, Implementation>& rhs) noexcept {
            lhs.Sub(rhs);
            return Vector<ThisSpace, Implementation>(lhs.X(), lhs.Y(), lhs.Z());
        }

        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator+(NormalizedVector<ThisSpace, Implementation> lhs, const Vector<ThisSpace, Implementation>& rhs) noexcept {
            lhs.Add(rhs);
            return Vector<ThisSpace, Implementation>(lhs.X(), lhs.Y(), lhs.Z());
        }
        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator+(NormalizedVector<ThisSpace, Implementation> lhs, const NormalizedVector<ThisSpace, Implementation>& rhs) noexcept {
            lhs.Add(rhs);
            return Vector<ThisSpace, Implementation>(lhs.X(), lhs.Y(), lhs.Z());
        }
        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator+(NormalizedVector<ThisSpace, Implementation> lhs, const NormalizedXYVector<ThisSpace, Implementation>& rhs) noexcept {
            lhs.Add(rhs);
            return Vector<ThisSpace, Implementation>(lhs.X(), lhs.Y(), lhs.Z());
        }
        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator+(NormalizedVector<ThisSpace, Implementation> lhs, const XYVector<ThisSpace, Implementation>& rhs) noexcept {
            lhs.Add(rhs);
            return Vector<ThisSpace, Implementation>(lhs.X(), lhs.Y(), lhs.Z());
        }

        [[nodiscard]] friend Vector<ThisSpace, Implementation> operator*(NormalizedVector<ThisSpace, Implementation> lhs, const double& d) noexcept {
            lhs.Scale(d);
            return Vector<ThisSpace, Implementation>(lhs.X(), lhs.Y(), lhs.Z());
        }


        NormalizedVector<ThisSpace, Implementation> operator*=(const NormalizedVector<ThisSpace, Implementation>& rhs) noexcept {
            *this = this->Cross(rhs);
            return *this;
        }
        NormalizedVector<ThisSpace, Implementation> operator*=(const NormalizedXYVector<ThisSpace, Implementation>& rhs) noexcept {
            *this = this->Cross(rhs);
            return *this;
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
            return Vector<ThisSpace, Implementation>{
                _base::Y() * other.Z() - _base::Z() * other.Y(),
                _base::Z() * other.X() - _base::X() * other.Z(),
                _base::X() * other.Y() - _base::Y() * other.X()
            };
        }
        [[nodiscard]] NormalizedVector<ThisSpace, Implementation> Cross(const NormalizedVector<ThisSpace, Implementation>& other) const noexcept {
            return NormalizedVector<ThisSpace, Implementation>{
                _base::Y() * other.Z() - _base::Z() * other.Y(),
                _base::Z() * other.X() - _base::X() * other.Z(),
                _base::X() * other.Y() - _base::Y() * other.X()
            };
        }
        [[nodiscard]] NormalizedVector<ThisSpace, Implementation> Cross(const NormalizedXYVector<ThisSpace, Implementation>& other) const noexcept {
            return NormalizedVector<ThisSpace, Implementation>{
                _base::Y() * other.Z() - _base::Z() * other.Y(),
                _base::Z() * other.X() - _base::X() * other.Z(),
                _base::X() * other.Y() - _base::Y() * other.X()
            };
        }
        [[nodiscard]] Vector<ThisSpace, Implementation> Cross(const XYVector<ThisSpace, Implementation>& other) const noexcept {
            return Vector<ThisSpace, Implementation>{
                _base::Y() * other.Z() - _base::Z() * other.Y(),
                _base::Z() * other.X() - _base::X() * other.Z(),
                _base::X() * other.Y() - _base::Y() * other.X()
            };
        }

        [[nodiscard]] double Dot(const Vector<ThisSpace, Implementation>& other) const noexcept { return _base::Dot(other); }
        [[nodiscard]] double Dot(const NormalizedVector<ThisSpace, Implementation>& other) const noexcept { return _base::Dot(other); }
        [[nodiscard]] double Dot(const NormalizedXYVector<ThisSpace, Implementation>& other) const noexcept { return _base::Dot(other); }
        [[nodiscard]] double Dot(const XYVector<ThisSpace, Implementation>& other) const noexcept { return _base::Dot(other); }


        [[nodiscard]] NormalizedXYVector<ThisSpace, Implementation> ToXY() const {
            return NormalizedXYVector<ThisSpace, Implementation>(_base::X(), _base::Y());
        }

        template <typename OtherSpace, typename TransformManager>
        [[nodiscard]] std::enable_if_t<!std::is_same_v<OtherSpace, ThisSpace>, Vector<OtherSpace, Implementation>> ConvertTo(const TransformManager& transform_manager) const noexcept {
            return Vector < OtherSpace, Implementation>(transform_manager.template Transform33<ThisSpace, OtherSpace>(static_cast<Implementation>(*this)));
        }

        friend std::ostream& operator << (
            std::ostream& os,
            const NormalizedVector<ThisSpace, Implementation>& item
            ) {
            const auto space = SpaceTypeNameMap<ThisSpace>::name;
            os << space << "::NormalizedVector (" << item.X() << ", " << item.Y() << ", " << item.Z() << ")";
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
            const auto mag = _base::Mag_internal();
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
