#pragma once

class TestVector
{
public:
    explicit TestVector(std::array<double, 3>) noexcept;
    explicit TestVector(double, double, double) noexcept;
    explicit TestVector(double, double) noexcept;
    TestVector(std::initializer_list<double>);

protected:
    TestVector() = default;
public:

    void Normalize() noexcept(false);

    [[nodiscard]] double Mag() const noexcept;
    [[nodiscard]] double operator[](unsigned int) const;

    [[nodiscard]] const double* cbegin() const noexcept;
    [[nodiscard]] const double* cend() const noexcept;
    [[nodiscard]] double* begin() noexcept;
    [[nodiscard]] double* end() noexcept;

    [[nodiscard]] double X() const noexcept;
    [[nodiscard]] double Y() const noexcept;
    [[nodiscard]] double Z() const noexcept;

    friend TestVector operator*(TestVector, const double&) noexcept;

    friend TestVector operator-(TestVector, const TestVector&) noexcept;

    friend TestVector operator+(TestVector, const TestVector&) noexcept;

    [[nodiscard]] double Dot(const TestVector&) const noexcept;

    [[nodiscard]] TestVector Cross(const TestVector&) const noexcept;

    [[nodiscard]] bool operator ==(const TestVector&) const noexcept;

private:
    std::array<double, 3> m_values{};
};


