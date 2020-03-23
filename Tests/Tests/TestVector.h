#pragma once

class TestVector
{
public:
    explicit TestVector() = default;
    explicit TestVector(double, double, double) noexcept;
    TestVector(const std::initializer_list<double> l);

    [[nodiscard]] friend TestVector operator*(TestVector, const double&) noexcept;

    std::array<double, 3> m_values{};
};
