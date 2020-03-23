#pragma once

class TestVector
{
public:
    explicit TestVector() = default;
    explicit TestVector(double, double, double) noexcept;
    TestVector(const std::initializer_list<double> l);

    std::array<double, 3> m_values{};
};
