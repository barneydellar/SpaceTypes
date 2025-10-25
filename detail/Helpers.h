#pragma once

namespace Space::implementation
{

    template <typename UnderlyingData>
    [[nodiscard]] static double *begin(UnderlyingData &i) noexcept
    {
        return reinterpret_cast<double *>(&i);
    }
    template <typename UnderlyingData>
    [[nodiscard]] static double *end(UnderlyingData &i) noexcept
    {
        return reinterpret_cast<double *>(&i) + 3;
    }
    template <typename UnderlyingData>
    [[nodiscard]] static const double *cbegin(const UnderlyingData &i) noexcept
    {
        return reinterpret_cast<const double *>(&i);
    }
    template <typename UnderlyingData>
    [[nodiscard]] static const double *cend(const UnderlyingData &i) noexcept
    {
        return reinterpret_cast<const double *>(&i) + 3;
    }

    template <typename UnderlyingData>
    static void Add(UnderlyingData &self, const UnderlyingData &other)
    {
        std::transform(
            cbegin(self),
            cend(self),
            cbegin(other),
            begin(self),
            std::plus<>());
    }

    template <typename UnderlyingData>
    static void Sub(UnderlyingData &self, const UnderlyingData &other)
    {
        std::transform(
            cbegin(self),
            cend(self),
            cbegin(other),
            begin(self),
            std::minus<>());
    }

    template <typename UnderlyingData>
    static void Scale(UnderlyingData &self, const double &d)
    {
        std::transform(
            cbegin(self),
            cend(self),
            begin(self),
            [d](auto v)
            { return v * d; });
    }

    template <typename UnderlyingData>
    static double Dot(const UnderlyingData &A, const UnderlyingData &B) noexcept
    {
        return std::transform_reduce(
            cbegin(A),
            cend(A),
            cbegin(B),
            0.0,
            [](auto accumulation, auto v)
            { return accumulation + v; },
            [](auto v1, auto v2)
            { return v1 * v2; });
    }

    template <typename UnderlyingData>
    static auto Cross_internal(const UnderlyingData &A, const UnderlyingData &B) noexcept
    {

        const double ax = *(cbegin(A) + 0);
        const double ay = *(cbegin(A) + 1);
        const double az = *(cbegin(A) + 2);

        const double bx = *(cbegin(B) + 0);
        const double by = *(cbegin(B) + 1);
        const double bz = *(cbegin(B) + 2);

        const double x = ay * bz - az * by;
        const double y = az * bx - ax * bz;
        const double z = ax * by - ay * bx;

        return std::tuple{x, y, z};
    }

    template <typename UnderlyingData>
    [[nodiscard]] static double Mag_internal(const UnderlyingData &i) noexcept
    {

        return std::sqrt(
            std::accumulate(
                cbegin(i),
                cend(i),
                0.0,
                [](const auto accumulation, const auto v)
                { return accumulation + v * v; }));
    }

    [[nodiscard]] static bool Equality(const double &x, const double &y)
    {
        return std::abs(x - y) < 1e-6;
    }
}
