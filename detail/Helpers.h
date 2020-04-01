#pragma once

namespace Space::detail {

    template <typename Implementation>
    [[nodiscard]] static double* begin(Implementation& i) noexcept {
        return reinterpret_cast<double*>(&i);
    }
    template <typename Implementation>
    [[nodiscard]] static double* end(Implementation& i) noexcept {
        return reinterpret_cast<double*>(&i) + 3;
    }
    template <typename Implementation>
    [[nodiscard]] static const double* cbegin(const Implementation& i) noexcept {
        return reinterpret_cast<const double*>(&i);
    }
    template <typename Implementation>
    [[nodiscard]] static const double* cend(const Implementation& i) noexcept {
        return reinterpret_cast<const double*>(&i) + 3;
    }

    template <typename Implementation>
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

    template <typename Implementation>
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

    template <typename Implementation>
    static void Scale(Implementation& self, const double& d)
    {
        std::transform(
            cbegin(self),
            cend(self),
            begin(self),
            [d](auto v) { return v * d; }
        );
    }

    template <typename Implementation>
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

    template <typename Implementation>
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

    template <typename Implementation>
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
}
