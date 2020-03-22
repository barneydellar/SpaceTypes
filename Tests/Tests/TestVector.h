#pragma once

class TestVector
{
public:
    explicit TestVector() = default;
    explicit TestVector(double, double, double) noexcept;
    TestVector(const std::initializer_list<double> l);

    [[nodiscard]] friend TestVector operator*(TestVector, const double&) noexcept;
    [[nodiscard]] friend TestVector operator-(TestVector, const TestVector&) noexcept;
    [[nodiscard]] friend TestVector operator+(TestVector, const TestVector&) noexcept;

    std::array<double, 3> m_values{};
};
