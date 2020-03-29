#pragma once

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class Base
    {
    public:

        //------------------------------------------------------------------------------------

#ifndef IGNORE_SPACE_STATIC_ASSERT
        template <typename OtherSpace>
        std::enable_if_t<!std::is_same_v<OtherSpace, ThisSpace>, StaticAssert::invalid_space> operator== (const Base<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace>
        std::enable_if_t<!std::is_same_v<OtherSpace, ThisSpace>, StaticAssert::invalid_space> operator!= (const Base<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace>
        std::enable_if_t<!std::is_same_v<OtherSpace, ThisSpace>, StaticAssert::invalid_space> operator*(const Base<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace>
        std::enable_if_t<!std::is_same_v<OtherSpace, ThisSpace>, StaticAssert::invalid_space> Cross(const Base<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace>
        std::enable_if_t<!std::is_same_v<OtherSpace, ThisSpace>, StaticAssert::invalid_space> operator*=(const Base<OtherSpace, Implementation>&) noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace>
        std::enable_if_t<!std::is_same_v<OtherSpace, ThisSpace>, StaticAssert::invalid_space> operator+(const Base<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace>
        std::enable_if_t<!std::is_same_v<OtherSpace, ThisSpace>, StaticAssert::invalid_space> operator+=(const Base<OtherSpace, Implementation>&) noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace>
        std::enable_if_t<!std::is_same_v<OtherSpace, ThisSpace>, StaticAssert::invalid_space> operator-(const Base<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace>
        std::enable_if_t<!std::is_same_v<OtherSpace, ThisSpace>, StaticAssert::invalid_space> operator-=(const Base<OtherSpace, Implementation>&) noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace>
        std::enable_if_t<!std::is_same_v<OtherSpace, ThisSpace>, StaticAssert::invalid_space> Dot(const Base<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_space{};
        }

        template <typename OtherSpace, typename TransformManager>
        [[nodiscard]] std::enable_if_t<std::is_same_v<OtherSpace, ThisSpace>, StaticAssert::invalid_conversion> ConvertTo(const TransformManager& transform_manager) const noexcept {
            return StaticAssert::invalid_conversion{};
        }

#endif

    protected:

        static void Add(Implementation& self, const Implementation& other)
        {
            std::transform(
                cbegin(self),
                cend(self),
                cbegin(other),
                begin(self),
                std::plus<>()
            );
        }

        static void Sub(Implementation& self, const Implementation& other)
        {
            std::transform(
                cbegin(self),
                cend(self),
                cbegin(other),
                begin(self),
                std::minus<>()
            );
        }

        static void Scale(Implementation& self, const double& d)
        {
            std::transform(
                cbegin(self),
                cend(self),
                begin(self),
                [d](auto v) { return v * d; }
            );
        }

        static double Dot(const Implementation& A, const Implementation& B) noexcept
        {
            return std::transform_reduce(
                cbegin(A),
                cend(A),
                cbegin(B),
                0.0,
                [](auto accumulation, auto v) { return accumulation + v; },
                [](auto v1, auto v2) { return v1 * v2; }
            );
        }

        static std::tuple<double, double, double> Cross_internal(const Implementation& A, const Implementation& B) noexcept {

            const double ax = *(cbegin(A) + 0);
            const double ay = *(cbegin(A) + 1);
            const double az = *(cbegin(A) + 2);

            const double bx = *(cbegin(B) + 0);
            const double by = *(cbegin(B) + 1);
            const double bz = *(cbegin(B) + 2);

            const double x = ay * bz - az * by;
            const double y = az * bx - ax * bz;
            const double z = ax * by - ay * bx;

            return { x, y, z };
        }

        static [[nodiscard]] double Mag_internal(const Implementation& i) noexcept {

            return std::sqrt(
                std::accumulate(
                    cbegin(i),
                    cend(i),
                    0.0,
                    [](const auto accumulation, const auto v) { return accumulation + v * v; }
                )
            );
        }

        [[nodiscard]] static bool Equality(const double& x, const double& y)
        {
            return std::abs(x - y) < 1e-6;
        }

        [[nodiscard]] static double* begin(Implementation& i) noexcept {
            return reinterpret_cast<double*>(&i);
        }
        [[nodiscard]] static double* end(Implementation& i) noexcept {
            return reinterpret_cast<double*>(&i) + 3;
        }
        [[nodiscard]] static const double* cbegin(const Implementation& i) noexcept {
            return reinterpret_cast<const double*>(&i);
        }
        [[nodiscard]] static const double* cend(const Implementation& i) noexcept {
            return reinterpret_cast<const double*>(&i) + 3;
        }


    };
}
