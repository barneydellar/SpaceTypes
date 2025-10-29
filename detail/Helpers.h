#pragma once

namespace Space::implementation {

template <typename UnderlyingData> [[nodiscard]] static double *Begin(UnderlyingData &i) noexcept {
    return reinterpret_cast<double *>(&i);
}
template <typename UnderlyingData> [[nodiscard]] static const double *CBegin(const UnderlyingData &i) noexcept {
    return reinterpret_cast<const double *>(&i);
}
template <typename UnderlyingData> [[nodiscard]] static const double *CEnd(const UnderlyingData &i) noexcept {
    return reinterpret_cast<const double *>(&i) + 3;
}

template <typename UnderlyingData> static void Add(UnderlyingData &self, const UnderlyingData &other) {
    std::transform(CBegin(self), CEnd(self), CBegin(other), Begin(self), std::plus<>());
}

template <typename UnderlyingData> static void Sub(UnderlyingData &self, const UnderlyingData &other) {
    std::transform(CBegin(self), CEnd(self), CBegin(other), Begin(self), std::minus<>());
}

template <typename UnderlyingData> static void Scale(UnderlyingData &self, const double &d) {
    std::transform(CBegin(self), CEnd(self), Begin(self), [d](auto v) { return v * d; });
}

template <typename UnderlyingData> static double Dot(const UnderlyingData &A, const UnderlyingData &B) noexcept {
    return std::transform_reduce(
        CBegin(A), CEnd(A), CBegin(B), 0.0, [](auto accumulation, auto v) { return accumulation + v; },
        [](auto v1, auto v2) { return v1 * v2; }
    );
}

template <typename UnderlyingData> static auto Cross_internal(const UnderlyingData &A, const UnderlyingData &B) noexcept {

    const double ax = *(CBegin(A) + 0);
    const double ay = *(CBegin(A) + 1);
    const double az = *(CBegin(A) + 2);

    const double bx = *(CBegin(B) + 0);
    const double by = *(CBegin(B) + 1);
    const double bz = *(CBegin(B) + 2);

    const double x = ay * bz - az * by;
    const double y = az * bx - ax * bz;
    const double z = ax * by - ay * bx;

    return std::tuple{x, y, z};
}

template <typename UnderlyingData> [[nodiscard]] static double Mag_internal(const UnderlyingData &i) noexcept {

    return std::sqrt(std::accumulate(CBegin(i), CEnd(i), 0.0, [](const auto accumulation, const auto v) {
        return accumulation + v * v;
    }));
}

[[nodiscard]] static bool Equality(const double &x, const double &y) { return std::abs(x - y) < 1e-6; }
} // namespace Space::implementation
