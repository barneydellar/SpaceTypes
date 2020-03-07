#pragma once

class TestVector
{
public:
    explicit TestVector(double, double, double) noexcept;

    [[nodiscard]] double X() const noexcept;
    [[nodiscard]] double Y() const noexcept;
    [[nodiscard]] double Z() const noexcept;

private:
    std::array<double, 3> m_values{};
};


