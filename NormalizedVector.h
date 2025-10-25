#pragma once

using namespace std::string_literals;

namespace Space::implementation {

    template <typename ThisSpace, typename UnderlyingData>
    class NormalizedVector final
#ifndef IGNORE_SPACE_STATIC_ASSERT
        : public Base<ThisSpace, UnderlyingData>
#endif
    {
        friend class NormalizedXYVector<ThisSpace, UnderlyingData>;
        friend class Point<ThisSpace, UnderlyingData>;
        friend class Vector<ThisSpace, UnderlyingData>;
        friend class XYPoint<ThisSpace, UnderlyingData>;
        friend class XYVector<ThisSpace, UnderlyingData>;

    public:

        NormalizedVector() {
            auto iter = begin(underlyingData);
            *iter++ = 1;
            *iter++ = 0;
            *iter = 0;
        }
        explicit NormalizedVector(const UnderlyingData& v) noexcept(false)
        {
            std::copy(
                implementation::cbegin(v),
                implementation::cend(v),
                begin(underlyingData)
            );
            Normalize();
        }
        NormalizedVector(const double x, const double y, const double z) noexcept(false)
        {
            auto iter = begin(underlyingData);
            *iter++ = x;
            *iter++ = y;
            *iter = z;
            Normalize();
        }

        [[nodiscard]] explicit operator UnderlyingData() const noexcept {
            return underlyingData;
        }

        [[nodiscard]] operator Vector<ThisSpace, UnderlyingData>() const noexcept {
           return Vector<ThisSpace, UnderlyingData>(X(), Y(), Z());
        }

        [[nodiscard]] double X() const noexcept { return *(cbegin() + 0); }
        [[nodiscard]] double Y() const noexcept { return *(cbegin() + 1); }
        [[nodiscard]] double Z() const noexcept { return *(cbegin() + 2); }

        [[nodiscard]] const double* cbegin() const noexcept { return reinterpret_cast<const double*>(&underlyingData); }
        [[nodiscard]] const double* cend() const noexcept { return reinterpret_cast<const double*>(&underlyingData) + 3; }

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

        [[nodiscard]] bool operator== (const Vector<ThisSpace, UnderlyingData>& other) const noexcept {
            return std::equal(cbegin(), cend(), implementation::cbegin(other.underlyingData), Equality);
        }
        [[nodiscard]] bool operator== (const NormalizedVector<ThisSpace, UnderlyingData>& other) const noexcept {
            return std::equal(cbegin(), cend(), implementation::cbegin(other.underlyingData), Equality);
        }
        [[nodiscard]] bool operator== (const NormalizedXYVector<ThisSpace, UnderlyingData>& other) const noexcept {
            return std::equal(cbegin(), cend(), implementation::cbegin(other.underlyingData), Equality);
        }
        [[nodiscard]] bool operator== (const XYVector<ThisSpace, UnderlyingData>& other) const noexcept {
            return std::equal(cbegin(), cend(), implementation::cbegin(other.underlyingData), Equality);
        }

        [[nodiscard]] bool operator!= (const Vector<ThisSpace, UnderlyingData>& other) const noexcept {
            return !(operator==(other));
        }
        [[nodiscard]] bool operator!= (const NormalizedVector<ThisSpace, UnderlyingData>& other) const noexcept {
            return !(operator==(other));
        }
        [[nodiscard]] bool operator!= (const NormalizedXYVector<ThisSpace, UnderlyingData>& other) const noexcept {
            return !(operator==(other));
        }
        [[nodiscard]] bool operator!= (const XYVector<ThisSpace, UnderlyingData>& other) const noexcept {
            return !(operator==(other));
        }

        [[nodiscard]] Vector<ThisSpace, UnderlyingData> operator-(const Vector<ThisSpace, UnderlyingData>& rhs) const noexcept {
            Vector<ThisSpace, UnderlyingData> v(X(), Y(), Z());
            Sub(v.underlyingData, rhs.underlyingData);
            return v;
        }
        [[nodiscard]] Vector<ThisSpace, UnderlyingData> operator-(const NormalizedVector<ThisSpace, UnderlyingData>& rhs) const noexcept {
            Vector<ThisSpace, UnderlyingData> v(X(), Y(), Z());
            Sub(v.underlyingData, rhs.underlyingData);
            return v;
        }
        [[nodiscard]] Vector<ThisSpace, UnderlyingData> operator-(const NormalizedXYVector<ThisSpace, UnderlyingData>& rhs) const noexcept {
            Vector<ThisSpace, UnderlyingData> v(X(), Y(), Z());
            Sub(v.underlyingData, rhs.underlyingData);
            return v;
        }
        [[nodiscard]] Vector<ThisSpace, UnderlyingData> operator-(const XYVector<ThisSpace, UnderlyingData>& rhs) const noexcept {
            Vector<ThisSpace, UnderlyingData> v(X(), Y(), Z());
            Sub(v.underlyingData, rhs.underlyingData);
            return v;
        }

        [[nodiscard]] Vector<ThisSpace, UnderlyingData> operator+(const Vector<ThisSpace, UnderlyingData>& rhs) const noexcept {
            Vector<ThisSpace, UnderlyingData> v(X(), Y(), Z());
            Add(v.underlyingData, rhs.underlyingData);
            return v;
        }
        [[nodiscard]] Vector<ThisSpace, UnderlyingData> operator+(const NormalizedVector<ThisSpace, UnderlyingData>& rhs) const noexcept {
            Vector<ThisSpace, UnderlyingData> v(X(), Y(), Z());
            Add(v.underlyingData, rhs.underlyingData);
            return v;
        }
        [[nodiscard]] Vector<ThisSpace, UnderlyingData> operator+(const NormalizedXYVector<ThisSpace, UnderlyingData>& rhs) const noexcept {
            Vector<ThisSpace, UnderlyingData> v(X(), Y(), Z());
            Add(v.underlyingData, rhs.underlyingData);
            return v;
        }
        [[nodiscard]] Vector<ThisSpace, UnderlyingData> operator+(const XYVector<ThisSpace, UnderlyingData>& rhs) const noexcept {
            Vector<ThisSpace, UnderlyingData> v(X(), Y(), Z());
            Add(v.underlyingData, rhs.underlyingData);
            return v;
        }

        [[nodiscard]] Vector<ThisSpace, UnderlyingData> operator*(const double& d) const noexcept {
            Vector<ThisSpace, UnderlyingData> v(X(), Y(), Z());
            Scale(v.underlyingData, d);
            return v;
        }

        NormalizedVector<ThisSpace, UnderlyingData> operator*=(const NormalizedVector<ThisSpace, UnderlyingData>& rhs) noexcept {
            *this = this->Cross(rhs);
            return *this;
        }
        NormalizedVector<ThisSpace, UnderlyingData> operator*=(const NormalizedXYVector<ThisSpace, UnderlyingData>& rhs) noexcept {
            *this = this->Cross(rhs);
            return *this;
        }

        [[nodiscard]] Vector<ThisSpace, UnderlyingData> operator*(const Vector<ThisSpace, UnderlyingData>& rhs) const noexcept {
            return this->Cross(rhs);
        }
        [[nodiscard]] NormalizedVector<ThisSpace, UnderlyingData> operator*(const NormalizedXYVector<ThisSpace, UnderlyingData>& rhs) const noexcept {
            return this->Cross(rhs);
        }
        [[nodiscard]] NormalizedVector<ThisSpace, UnderlyingData> operator*(const NormalizedVector<ThisSpace, UnderlyingData>& rhs) const noexcept {
            return this->Cross(rhs);
        }
        [[nodiscard]] Vector<ThisSpace, UnderlyingData> operator*(const XYVector<ThisSpace, UnderlyingData>& rhs) const noexcept {
            return this->Cross(rhs);
        }

        [[nodiscard]] Vector<ThisSpace, UnderlyingData> Cross(const Vector<ThisSpace, UnderlyingData>& other) const noexcept {
            const auto[x, y, z] = Cross_internal(underlyingData, other.underlyingData);
            return Vector<ThisSpace, UnderlyingData>(x, y, z);
        }
        [[nodiscard]] NormalizedVector<ThisSpace, UnderlyingData> Cross(const NormalizedVector<ThisSpace, UnderlyingData>& other) const noexcept {
            const auto[x, y, z] = Cross_internal(underlyingData, other.underlyingData);
            return NormalizedVector<ThisSpace, UnderlyingData>(x, y, z);
        }
        [[nodiscard]] NormalizedVector<ThisSpace, UnderlyingData> Cross(const NormalizedXYVector<ThisSpace, UnderlyingData>& other) const noexcept {
            const auto[x, y, z] = Cross_internal(underlyingData, other.underlyingData);
            return NormalizedVector<ThisSpace, UnderlyingData>(x, y, z);
        }
        [[nodiscard]] Vector<ThisSpace, UnderlyingData> Cross(const XYVector<ThisSpace, UnderlyingData>& other) const noexcept {
            const auto[x, y, z] = Cross_internal(underlyingData, other.underlyingData);
            return Vector<ThisSpace, UnderlyingData>(x, y, z);
        }

        [[nodiscard]] double Dot(const Vector<ThisSpace, UnderlyingData>& other) const noexcept
        {
            return implementation::Dot(underlyingData, other.underlyingData);
        }
        [[nodiscard]] double Dot(const NormalizedVector<ThisSpace, UnderlyingData>& other) const noexcept
        {
            return implementation::Dot(underlyingData, other.underlyingData);
        }
        [[nodiscard]] double Dot(const NormalizedXYVector<ThisSpace, UnderlyingData>& other) const noexcept
        {
            return implementation::Dot(underlyingData, other.underlyingData);
        }
        [[nodiscard]] double Dot(const XYVector<ThisSpace, UnderlyingData>& other) const noexcept
        {
            return implementation::Dot(underlyingData, other.underlyingData);
        }

        [[nodiscard]] NormalizedXYVector<ThisSpace, UnderlyingData> ToXY() const requires ThisSpace::supportsXY {
            return NormalizedXYVector<ThisSpace, UnderlyingData>(X(), Y());
        }

        template <typename OtherSpace, typename TransformManager> requires  DifferentSpaces<OtherSpace, ThisSpace>
        [[nodiscard]] Vector<OtherSpace, UnderlyingData> ConvertTo(const TransformManager& transform_manager) const noexcept {
            return Vector < OtherSpace, UnderlyingData>(transform_manager.template TransformVector<ThisSpace, OtherSpace>(static_cast<UnderlyingData>(*this)));
        }

        friend std::ostream& operator << (
            std::ostream& os,
            const NormalizedVector<ThisSpace, UnderlyingData>& item
        ) {
            const auto space = SpaceTypeNameMap<ThisSpace>::name;
            os << space << "::NormalizedVector (" << item.X() << ", " << item.Y() << ", " << item.Z() << ")";
            return os;
        }
#ifndef IGNORE_SPACE_STATIC_ASSERT
        using _base = Base<ThisSpace, UnderlyingData>;
        using _base::operator-=;
        using _base::operator-;
        using _base::operator+=;
        using _base::operator+;
        using _base::operator*=;
        using _base::operator*;
        using _base::ConvertTo;
        using _base::Dot;
        using _base::Cross;

        template <int I> requires (!ValidFor3dAt<I>)
        StaticAssert::invalid_at_access at() const {
            return StaticAssert::invalid_at_access{};
        }

        template <typename OtherSpace> requires  DifferentSpaces<OtherSpace, ThisSpace>
        StaticAssert::invalid_space operator!= (const Vector<OtherSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace> requires  DifferentSpaces<OtherSpace, ThisSpace>
        StaticAssert::invalid_space operator!= (const NormalizedVector<OtherSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace> requires  DifferentSpaces<OtherSpace, ThisSpace>
        StaticAssert::invalid_space operator!= (const NormalizedXYVector<OtherSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace> requires  DifferentSpaces<OtherSpace, ThisSpace>
        StaticAssert::invalid_space operator!= (const XYVector<OtherSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_space{};
        }

        template <typename OtherSpace> requires  DifferentSpaces<OtherSpace, ThisSpace>
        StaticAssert::invalid_space operator== (const Vector<OtherSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace> requires  DifferentSpaces<OtherSpace, ThisSpace>
        StaticAssert::invalid_space operator== (const NormalizedVector<OtherSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace> requires  DifferentSpaces<OtherSpace, ThisSpace>
        StaticAssert::invalid_space operator== (const NormalizedXYVector<OtherSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace> requires  DifferentSpaces<OtherSpace, ThisSpace>
        StaticAssert::invalid_space operator== (const XYVector<OtherSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_space{};
        }

        StaticAssert::invalid_point_vector_equality operator== (const Point<ThisSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        StaticAssert::invalid_point_vector_equality operator== (const XYPoint<ThisSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        StaticAssert::invalid_point_vector_equality operator!= (const Point<ThisSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        StaticAssert::invalid_point_vector_equality operator!= (const XYPoint<ThisSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }

        StaticAssert::invalid_point_to_vector_addition operator+(const Point<ThisSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_point_to_vector_addition{};
        }

        StaticAssert::invalid_normalized_vector_addition operator+=(const Vector<ThisSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_normalized_vector_addition{};
        }
        StaticAssert::invalid_normalized_vector_addition operator+=(const NormalizedVector<ThisSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_normalized_vector_addition{};
        }
        StaticAssert::invalid_normalized_vector_addition operator+=(const NormalizedXYVector<ThisSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_normalized_vector_addition{};
        }
        StaticAssert::invalid_normalized_vector_addition operator+=(const XYVector<ThisSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_normalized_vector_addition{};
        }

        StaticAssert::invalid_point_from_vector_subtraction operator-(const Point<ThisSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_point_from_vector_subtraction{};
        }

        StaticAssert::invalid_normalized_vector_subtraction operator-=(const Vector<ThisSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_normalized_vector_subtraction{};
        }
        StaticAssert::invalid_normalized_vector_subtraction operator-=(const NormalizedVector<ThisSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_normalized_vector_subtraction{};
        }
        StaticAssert::invalid_normalized_vector_subtraction operator-=(const NormalizedXYVector<ThisSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_normalized_vector_subtraction{};
        }
        StaticAssert::invalid_normalized_vector_subtraction operator-=(const XYVector<ThisSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_normalized_vector_subtraction{};
        }

        StaticAssert::invalid_normalized_vector_scale operator*=(const double&) const noexcept {
            return StaticAssert::invalid_normalized_vector_scale{};
        }

        StaticAssert::invalid_normalized_vector_in_place_cross operator*=(const Vector<ThisSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_normalized_vector_in_place_cross{};
        }
        StaticAssert::invalid_normalized_vector_in_place_cross operator*=(const XYVector<ThisSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_normalized_vector_in_place_cross{};
        }

        [[nodiscard]] StaticAssert::XYVector_not_supported ToXY() const noexcept requires ThisSpace::doesNotSupportXY {
            return StaticAssert::XYVector_not_supported{};
        }
#endif

    private:

        void Normalize() {
            const auto mag = Mag_internal(underlyingData);
            if (std::abs(mag) < 1e-6) {
                throw std::invalid_argument("Zero-sized normal vectors are not allowed");
            }

            std::transform(
                cbegin(),
                cend(),
                begin(underlyingData),
                [mag](auto v) { return v / mag; }
            );
        }

        UnderlyingData underlyingData;

    };
}
