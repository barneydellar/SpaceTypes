#pragma once

class TestVector
{
public:
    explicit TestVector(double, double, double) noexcept;
    TestVector(const std::initializer_list<double> l);

    void Normalize() noexcept(false);

    [[nodiscard]] double operator[](unsigned int) const;

    [[nodiscard]] const double* cbegin() const noexcept;
    [[nodiscard]] const double* cend() const noexcept;
    [[nodiscard]] double* begin() noexcept;
    [[nodiscard]] double* end() noexcept;

    [[nodiscard]] double X() const noexcept;
    [[nodiscard]] double Y() const noexcept;
    [[nodiscard]] double Z() const noexcept;

    [[nodiscard]] friend TestVector operator*(TestVector, const double&) noexcept;
    [[nodiscard]] friend TestVector operator-(TestVector, const TestVector&) noexcept;
    [[nodiscard]] friend TestVector operator+(TestVector, const TestVector&) noexcept;
    [[nodiscard]] bool operator==(const TestVector&) const noexcept;

    [[nodiscard]] double Mag() const noexcept;
    [[nodiscard]] double Dot(const TestVector&) const noexcept;
    [[nodiscard]] TestVector Cross(const TestVector&) const noexcept;

private:
    std::array<double, 3> m_values{};
};
