#pragma once

namespace Space::implementation {

    template <typename ThisSpace, typename UnderlyingData>
    class Vector final
#ifndef IGNORE_SPACE_STATIC_ASSERT
        : public Base<ThisSpace, UnderlyingData>
#endif
    {
        friend class NormalizedVector<ThisSpace, UnderlyingData>;
        friend class NormalizedXYVector<ThisSpace, UnderlyingData>;
        friend class Point<ThisSpace, UnderlyingData>;
        friend class XYPoint<ThisSpace, UnderlyingData>;
        friend class XYVector<ThisSpace, UnderlyingData>;

    public:

        Vector() noexcept { std::fill(begin(), end(), 0); }
        explicit Vector(const UnderlyingData& v) noexcept
        {
            std::copy(
                implementation::cbegin(v),
                implementation::cend(v),
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

        [[nodiscard]] explicit operator UnderlyingData() const noexcept {
            return underlyingData;
        }

        [[nodiscard]] double X() const noexcept { return *(cbegin() + 0); }
        [[nodiscard]] double Y() const noexcept { return *(cbegin() + 1); }
        [[nodiscard]] double Z() const noexcept { return *(cbegin() + 2); }

        void SetX(const double d) noexcept { *(begin() + 0) = d; }
        void SetY(const double d) noexcept { *(begin() + 1) = d; }
        void SetZ(const double d) noexcept { *(begin() + 2) = d; }

        [[nodiscard]] double* begin() noexcept { return reinterpret_cast<double*>(&underlyingData); }
        [[nodiscard]] double* end() noexcept { return reinterpret_cast<double*>(&underlyingData) + 3; }
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

        auto operator-=(const Vector<ThisSpace, UnderlyingData>& rhs) noexcept {
            Sub(underlyingData, rhs.underlyingData);
            return *this;
        }
        auto operator-=(const NormalizedVector<ThisSpace, UnderlyingData>& rhs) noexcept {
            Sub(underlyingData, rhs.underlyingData);
            return *this;
        }
        auto operator-=(const NormalizedXYVector<ThisSpace, UnderlyingData>& rhs) noexcept {
            Sub(underlyingData, rhs.underlyingData);
            return *this;
        }
        auto operator-=(const XYVector<ThisSpace, UnderlyingData>& rhs) noexcept {
            Sub(underlyingData, rhs.underlyingData);
            return *this;
        }

        [[nodiscard]] auto operator-(const Vector<ThisSpace, UnderlyingData>& rhs) const noexcept {
            Vector<ThisSpace, UnderlyingData> v(X(), Y(), Z());
            Sub(v.underlyingData, rhs.underlyingData);
            return v;
        }
        [[nodiscard]] auto operator-(const NormalizedVector<ThisSpace, UnderlyingData>& rhs) const noexcept {
            Vector<ThisSpace, UnderlyingData> v(X(), Y(), Z());
            Sub(v.underlyingData, rhs.underlyingData);
            return v;
        }
        [[nodiscard]] auto operator-(const NormalizedXYVector<ThisSpace, UnderlyingData>& rhs) const noexcept {
            Vector<ThisSpace, UnderlyingData> v(X(), Y(), Z());
            Sub(v.underlyingData, rhs.underlyingData);
            return v;
        }
        [[nodiscard]] auto operator-(const XYVector<ThisSpace, UnderlyingData>& rhs) const noexcept {
            Vector<ThisSpace, UnderlyingData> v(X(), Y(), Z());
            Sub(v.underlyingData, rhs.underlyingData);
            return v;
        }

        auto operator+=(const Vector<ThisSpace, UnderlyingData>& rhs) noexcept {
            Add(underlyingData, rhs.underlyingData);
            return *this;
        }
        auto operator+=(const NormalizedVector<ThisSpace, UnderlyingData>& rhs) noexcept {
            Add(underlyingData, rhs.underlyingData);
            return *this;
        }
        auto operator+=(const NormalizedXYVector<ThisSpace, UnderlyingData>& rhs) noexcept {
            Add(underlyingData, rhs.underlyingData);
            return *this;
        }
        auto operator+=(const XYVector<ThisSpace, UnderlyingData>& rhs) noexcept {
            Add(underlyingData, rhs.underlyingData);
            return *this;
        }

        [[nodiscard]] auto operator+(const Vector<ThisSpace, UnderlyingData>& rhs) const noexcept {
            Vector<ThisSpace, UnderlyingData> v(X(), Y(), Z());
            Add(v.underlyingData, rhs.underlyingData);
            return v;
        }
        [[nodiscard]] auto operator+(const NormalizedVector<ThisSpace, UnderlyingData>& rhs) const noexcept {
            Vector<ThisSpace, UnderlyingData> v(X(), Y(), Z());
            Add(v.underlyingData, rhs.underlyingData);
            return v;
        }
        [[nodiscard]] auto operator+(const NormalizedXYVector<ThisSpace, UnderlyingData>& rhs) const noexcept {
            Vector<ThisSpace, UnderlyingData> v(X(), Y(), Z());
            Add(v.underlyingData, rhs.underlyingData);
            return v;
        }
        [[nodiscard]] auto operator+(const XYVector<ThisSpace, UnderlyingData>& rhs) const noexcept {
            Vector<ThisSpace, UnderlyingData> v(X(), Y(), Z());
            Add(v.underlyingData, rhs.underlyingData);
            return v;
        }

        auto operator*=(const double& d) noexcept {
            Scale(underlyingData, d);
            return *this;
        }

        auto operator*=(const Vector<ThisSpace, UnderlyingData>& rhs) noexcept {
            *this = this->Cross(rhs);
            return *this;
        }
        auto operator*=(const NormalizedVector<ThisSpace, UnderlyingData>& rhs) noexcept {
            *this = this->Cross(rhs);
            return *this;
        }
        auto operator*=(const NormalizedXYVector<ThisSpace, UnderlyingData>& rhs) noexcept {
            *this = this->Cross(rhs);
            return *this;
        }
        auto operator*=(const XYVector<ThisSpace, UnderlyingData>& rhs) noexcept {
            *this = this->Cross(rhs);
            return *this;
        }

        [[nodiscard]] auto operator*(const double& d) const noexcept {
            Vector<ThisSpace, UnderlyingData> v(X(), Y(), Z());
            Scale(v.underlyingData, d);
            return v;
        }

        [[nodiscard]] auto operator*(const Vector<ThisSpace, UnderlyingData>& rhs) const noexcept {
            return this->Cross(rhs);
        }
        [[nodiscard]] auto operator*(const NormalizedXYVector<ThisSpace, UnderlyingData>& rhs) const noexcept {
            return this->Cross(rhs);
        }
        [[nodiscard]] auto operator*(const NormalizedVector<ThisSpace, UnderlyingData>& rhs) const noexcept {
            return this->Cross(rhs);
        }
        [[nodiscard]] auto operator*(const XYVector<ThisSpace, UnderlyingData>& rhs) const noexcept {
            return this->Cross(rhs);
        }

        [[nodiscard]] auto Cross(const Vector<ThisSpace, UnderlyingData>& other) const noexcept {
            const auto[x, y, z] = Cross_internal(underlyingData, other.underlyingData);
            return Vector<ThisSpace, UnderlyingData>(x, y, z);
        }
        [[nodiscard]] auto Cross(const NormalizedVector<ThisSpace, UnderlyingData>& other) const noexcept {
            const auto[x, y, z] = Cross_internal(underlyingData, other.underlyingData);
            return Vector<ThisSpace, UnderlyingData>(x, y, z);
        }
        [[nodiscard]] auto Cross(const NormalizedXYVector<ThisSpace, UnderlyingData>& other) const noexcept {
            const auto[x, y, z] = Cross_internal(underlyingData, other.underlyingData);
            return Vector<ThisSpace, UnderlyingData>(x, y, z);
        }
        [[nodiscard]] auto Cross(const XYVector<ThisSpace, UnderlyingData>& other) const noexcept {
            const auto[x, y, z] = Cross_internal(underlyingData, other.underlyingData);
            return Vector<ThisSpace, UnderlyingData>(x, y, z);
        }

        [[nodiscard]] double Dot(const Vector<ThisSpace, UnderlyingData>& other) const noexcept { 
            return implementation::Dot(underlyingData, other.underlyingData); 
        }
        [[nodiscard]] double Dot(const NormalizedVector<ThisSpace, UnderlyingData>& other) const noexcept { 
            return implementation::Dot(underlyingData, other.underlyingData); 
        }
        [[nodiscard]] double Dot(const NormalizedXYVector<ThisSpace, UnderlyingData>& other) const noexcept { 
            return implementation::Dot(underlyingData, other.underlyingData); 
        }
        [[nodiscard]] double Dot(const XYVector<ThisSpace, UnderlyingData>& other) const noexcept { 
            return implementation::Dot(underlyingData, other.underlyingData); 
        }

        [[nodiscard]] auto ToXY() const requires ThisSpace::supportsXY {
            return XYVector<ThisSpace, UnderlyingData>(X(), Y());
        }

        [[nodiscard]] auto Norm() const {
            return NormalizedVector<ThisSpace, UnderlyingData>(X(), Y(), Z());
        }

        template <typename OtherSpace, typename TransformManager> requires DifferentSpaces<OtherSpace, ThisSpace>
        [[nodiscard]] auto ConvertTo(const TransformManager& transform_manager) const noexcept {
            return Vector < OtherSpace, UnderlyingData>(transform_manager.template TransformVector<ThisSpace, OtherSpace>(static_cast<UnderlyingData>(*this)));
        }

        [[nodiscard]] auto Mag() const noexcept {
            return typename ThisSpace::Unit{ Mag_double() };
        }

        [[nodiscard]] double Mag_double() const noexcept {return Mag_internal(underlyingData);}

        friend std::ostream& operator << (
            std::ostream& os,
            const Vector<ThisSpace, UnderlyingData>& item
        ) {
            const auto space = SpaceTypeNameMap<ThisSpace>::name;
            os << space << "::Vector (" << item.X() << ", " << item.Y() << ", " << item.Z() << ")";
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

        template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
        StaticAssert::invalid_space operator!= (const Vector<OtherSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
        StaticAssert::invalid_space operator!= (const NormalizedVector<OtherSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
        StaticAssert::invalid_space operator!= (const NormalizedXYVector<OtherSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
        StaticAssert::invalid_space operator!= (const XYVector<OtherSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_space{};
        }

        template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
        StaticAssert::invalid_space operator== (const Vector<OtherSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
        StaticAssert::invalid_space operator== (const NormalizedVector<OtherSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
        StaticAssert::invalid_space operator== (const NormalizedXYVector<OtherSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
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

        StaticAssert::invalid_point_from_vector_subtraction operator-(const Point<ThisSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_point_from_vector_subtraction{};
        }

        StaticAssert::invalid_point_to_vector_addition operator+(const Point<ThisSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_point_to_vector_addition{};
        }

        [[nodiscard]] StaticAssert::XYVector_not_supported ToXY() const noexcept requires ThisSpace::doesNotSupportXY {
            return StaticAssert::XYVector_not_supported{};
        }
#endif
    protected:
        const UnderlyingData& GetImpl() const {
            return underlyingData;
        };
        UnderlyingData underlyingData;

    };
}
