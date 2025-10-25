#pragma once

namespace Space::implementation {

    template <typename ThisSpace, typename UnderlyingData>
    class XYPoint final
#ifndef IGNORE_SPACE_STATIC_ASSERT
        : public Base<ThisSpace, UnderlyingData>
#endif
    {
        friend class NormalizedVector<ThisSpace, UnderlyingData>;
        friend class NormalizedXYVector<ThisSpace, UnderlyingData>;
        friend class Point<ThisSpace, UnderlyingData>;
        friend class Vector<ThisSpace, UnderlyingData>;
        friend class XYVector<ThisSpace, UnderlyingData>;
    public:

        XYPoint() noexcept {
            std::fill(begin(), end(), 0);
        }
        explicit XYPoint(const UnderlyingData& v) noexcept {
            auto iter = begin();
            auto in = implementation::cbegin(v);
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

        [[nodiscard]] explicit operator UnderlyingData() const noexcept {
            return underlyingData;
        }

        [[nodiscard]] double X() const noexcept { return *(cbegin() + 0); }
        [[nodiscard]] double Y() const noexcept { return *(cbegin() + 1); }

        void SetX(const double d) noexcept { *(begin() + 0) = d; }
        void SetY(const double d) noexcept { *(begin() + 1) = d; }

        [[nodiscard]] operator Point<ThisSpace, UnderlyingData>() const noexcept {
            return Point<ThisSpace, UnderlyingData>(X(), Y(), 0);
        }

        [[nodiscard]] double* begin() noexcept { return reinterpret_cast<double*>(&underlyingData); }
        [[nodiscard]] double* end() noexcept { return reinterpret_cast<double*>(&underlyingData) + 2; }
        [[nodiscard]] const double* cbegin() const noexcept { return reinterpret_cast<const double*>(&underlyingData); }
        [[nodiscard]] const double* cend() const noexcept { return reinterpret_cast<const double*>(&underlyingData) + 2; }

        [[nodiscard]] bool operator== (const Point<ThisSpace, UnderlyingData>& other) const noexcept {
            return std::equal(cbegin(), cend(), implementation::cbegin(other.underlyingData), Equality);
        }
        [[nodiscard]] bool operator== (const XYPoint<ThisSpace, UnderlyingData>& other) const noexcept {
            return std::equal(cbegin(), cend(), implementation::cbegin(other.underlyingData), Equality);
        }

        [[nodiscard]] bool operator!= (const Point<ThisSpace, UnderlyingData>& other) const noexcept {
            return !(operator==(other));
        }

        [[nodiscard]] bool operator!= (const XYPoint<ThisSpace, UnderlyingData>& other) const noexcept {
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

        XYPoint<ThisSpace, UnderlyingData> operator-=(const XYVector<ThisSpace, UnderlyingData>& rhs) noexcept {
            Sub(underlyingData, rhs.underlyingData);
            return *this;
        }
        XYPoint<ThisSpace, UnderlyingData> operator-=(const NormalizedXYVector<ThisSpace, UnderlyingData>& rhs) noexcept {
            Sub(underlyingData, rhs.underlyingData);
            return *this;
        }

        [[nodiscard]] Point<ThisSpace, UnderlyingData> operator-(const Vector<ThisSpace, UnderlyingData>& rhs) const noexcept {
            Point<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
            Sub(v.underlyingData, rhs.underlyingData);
            return v;
        }
        [[nodiscard]] Point<ThisSpace, UnderlyingData> operator-(const NormalizedVector<ThisSpace, UnderlyingData>& rhs) const noexcept {
            Point<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
            Sub(v.underlyingData, rhs.underlyingData);
            return v;
        }
        [[nodiscard]] XYPoint<ThisSpace, UnderlyingData> operator-(const NormalizedXYVector<ThisSpace, UnderlyingData>& rhs) const noexcept {
            XYPoint<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
            Sub(v.underlyingData, rhs.underlyingData);
            return v;
        }
        [[nodiscard]] XYPoint<ThisSpace, UnderlyingData> operator-(const XYVector<ThisSpace, UnderlyingData>& rhs) const noexcept {
            XYPoint<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
            Sub(v.underlyingData, rhs.underlyingData);
            return v;
        }

        [[nodiscard]] XYVector<ThisSpace, UnderlyingData> operator-(const XYPoint<ThisSpace, UnderlyingData>& rhs) const noexcept {
            XYVector<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
            Sub(v.underlyingData, rhs.underlyingData);
            return v;
        }
        [[nodiscard]] Vector<ThisSpace, UnderlyingData> operator-(const Point<ThisSpace, UnderlyingData>& rhs) const noexcept {
            Vector<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
            Sub(v.underlyingData, rhs.underlyingData);
            return v;
        }

        XYPoint<ThisSpace, UnderlyingData> operator+=(const XYVector<ThisSpace, UnderlyingData>& rhs) noexcept {
            Add(underlyingData, rhs.underlyingData);
            return *this;
        }
        XYPoint<ThisSpace, UnderlyingData> operator+=(const NormalizedXYVector<ThisSpace, UnderlyingData>& rhs) noexcept {
            Add(underlyingData, rhs.underlyingData);
            return *this;
        }

        [[nodiscard]] Point<ThisSpace, UnderlyingData> operator+(const Vector<ThisSpace, UnderlyingData>& rhs) const noexcept {
            Point<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
            Add(v.underlyingData, rhs.underlyingData);
            return v;
        }
        [[nodiscard]] Point<ThisSpace, UnderlyingData> operator+(const NormalizedVector<ThisSpace, UnderlyingData>& rhs) const noexcept {
            Point<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
            Add(v.underlyingData, rhs.underlyingData);
            return v;
        }
        [[nodiscard]] XYPoint<ThisSpace, UnderlyingData> operator+(const NormalizedXYVector<ThisSpace, UnderlyingData>& rhs) const noexcept {
            XYPoint<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
            Add(v.underlyingData, rhs.underlyingData);
            return v;
        }
        [[nodiscard]] XYPoint<ThisSpace, UnderlyingData> operator+(const XYVector<ThisSpace, UnderlyingData>& rhs) const noexcept {
            XYPoint<ThisSpace, UnderlyingData> v(static_cast<UnderlyingData>(*this));
            Add(v.underlyingData, rhs.underlyingData);
            return v;
        }

        template <typename OtherSpace, typename TransformManager> requires DifferentSpaces<OtherSpace, ThisSpace>
        [[nodiscard]] Point<OtherSpace, UnderlyingData> ConvertTo(const TransformManager& transform_manager) const {
            return Point<OtherSpace, UnderlyingData>(transform_manager.template TransformPoint<ThisSpace, OtherSpace>(static_cast<UnderlyingData>(*this)));
        }

        friend std::ostream& operator << (
            std::ostream& os,
            const XYPoint<ThisSpace, UnderlyingData>& item
        ) {
            const auto space = SpaceTypeNameMap<ThisSpace>::name;
            os << space << "::XYPoint (" << item.X() << ", " << item.Y() << ")";
            return os;
        }

#ifndef IGNORE_SPACE_STATIC_ASSERT
        using _base = Base<ThisSpace, UnderlyingData>;
        using _base::operator+=;
        using _base::operator+;
        using _base::operator-=;
        using _base::operator-;
        using _base::ConvertTo;

        template <int I> requires (!ValidFor2dAt<I>)
        typename StaticAssert::invalid_at_access at() const {
            return StaticAssert::invalid_at_access{};
        }

        template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
        StaticAssert::invalid_space operator!= (const Point<OtherSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
        StaticAssert::invalid_space operator!= (const XYPoint<OtherSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_space{};
        }

        template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
        StaticAssert::invalid_space operator== (const Point<OtherSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
        StaticAssert::invalid_space operator== (const XYPoint<OtherSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_space{};
        }

        StaticAssert::invalid_point_vector_equality operator== (const Vector<ThisSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        StaticAssert::invalid_point_vector_equality operator== (const NormalizedVector<ThisSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        StaticAssert::invalid_point_vector_equality operator== (const NormalizedXYVector<ThisSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        StaticAssert::invalid_point_vector_equality operator== (const XYVector<ThisSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }

        StaticAssert::invalid_point_vector_equality operator!= (const Vector<ThisSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        StaticAssert::invalid_point_vector_equality operator!= (const NormalizedVector<ThisSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        StaticAssert::invalid_point_vector_equality operator!= (const NormalizedXYVector<ThisSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }
        StaticAssert::invalid_point_vector_equality operator!= (const XYVector<ThisSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_point_vector_equality{};
        }

        StaticAssert::invalid_point_to_point_addition operator+=(const Point<ThisSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_point_to_point_addition{};
        }
        StaticAssert::invalid_point_to_point_addition operator+=(const XYPoint<ThisSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_point_to_point_addition{};
        }

        StaticAssert::invalid_vector3_to_xy_point_addition operator+=(const Vector<ThisSpace, UnderlyingData>&) noexcept {
            return StaticAssert::invalid_vector3_to_xy_point_addition{};
        }
        StaticAssert::invalid_vector3_to_xy_point_addition operator+=(const NormalizedVector<ThisSpace, UnderlyingData>&) noexcept {
            return StaticAssert::invalid_vector3_to_xy_point_addition{};
        }

        StaticAssert::invalid_point_from_vector_subtraction operator-=(const Point<ThisSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_point_from_vector_subtraction{};
        }
        StaticAssert::invalid_point_from_vector_subtraction operator-=(const XYPoint<ThisSpace, UnderlyingData>&) const noexcept {
            return StaticAssert::invalid_point_from_vector_subtraction{};
        }

        StaticAssert::invalid_vector3_from_xy_point_subtraction operator-=(const Vector<ThisSpace, UnderlyingData>&) noexcept {
            return StaticAssert::invalid_vector3_from_xy_point_subtraction{};
        }
        StaticAssert::invalid_vector3_from_xy_point_subtraction operator-=(const NormalizedVector<ThisSpace, UnderlyingData>&) noexcept {
            return StaticAssert::invalid_vector3_from_xy_point_subtraction{};
        }

        StaticAssert::invalid_point_to_point_addition operator+(const Point<ThisSpace, UnderlyingData>&) const {
            return StaticAssert::invalid_point_to_point_addition{};
        }
        StaticAssert::invalid_point_to_point_addition operator+(const XYPoint<ThisSpace, UnderlyingData>&) const {
            return StaticAssert::invalid_point_to_point_addition{};
        }
#endif
        // Hide functions from intellisense
        void Dot() = delete;
        void Cross() = delete;
        void operator*() = delete;
        void operator*=(double) = delete;

    private:
        UnderlyingData underlyingData;
    };
}
