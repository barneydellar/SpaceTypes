#include "pch.h"
#include "TestVector.h"

TestVector::TestVector(const double x, const double y, const double z) noexcept : m_values{ x, y, z }
{
}

TestVector::TestVector(const std::initializer_list<double> l)
{
    auto iter = l.begin();
    m_values[0] = *iter++;
    m_values[1] = *iter++;
    if (l.size() == 3)
    {
        m_values[2] = *iter;
    }
    else
    {
        m_values[2] = 0;
    }
}


void TestVector::Normalize() noexcept(false)
{
    const auto mag = Mag();
    std::transform(
        m_values.cbegin(),
        m_values.cend(),
        m_values.begin(),
        [mag](auto v) { return v / mag; }
    );
}

double TestVector::Mag() const noexcept
{
    return std::sqrt(
        std::accumulate(
            m_values.cbegin(),
            m_values.cend(),
            0.0,
            [](const auto accumulation, const auto v) { return accumulation + v * v; }
        )
    );
}

TestVector operator*(TestVector lhs, const double& d) noexcept
{
    std::transform(
        lhs.m_values.cbegin(),
        lhs.m_values.cend(),
        lhs.m_values.begin(),
        [d](auto v) { return v * d; }
    );
    return lhs;
}

TestVector operator+(TestVector lhs, const TestVector& rhs) noexcept
{
    std::transform(
        lhs.m_values.cbegin(),
        lhs.m_values.cend(),
        rhs.m_values.cbegin(),
        lhs.m_values.begin(),
        std::plus<>()
    );
    return lhs;
}

TestVector operator-(TestVector lhs, const TestVector& rhs) noexcept
{
    std::transform(
        lhs.m_values.cbegin(),
        lhs.m_values.cend(),
        rhs.m_values.cbegin(),
        lhs.m_values.begin(),
        std::minus<>()
    );
    return lhs;
}

double TestVector::Dot(const TestVector& other) const noexcept
{
    return std::transform_reduce(
        m_values.cbegin(),
        m_values.cend(),
        other.m_values.cbegin(),
        0.0,
        [](auto accumulation, auto v) { return accumulation + v; },
        [](auto v1, auto v2) { return v1 * v2; }
    );
}

TestVector TestVector::Cross(const TestVector& other) const noexcept
{
    return TestVector{
        m_values[1] * other.m_values[2] - m_values[2] * other.m_values[1],
        m_values[2] * other.m_values[0] - m_values[0] * other.m_values[2],
        m_values[0] * other.m_values[1] - m_values[1] * other.m_values[0]
    };
}

bool TestVector::operator==(const TestVector& other) const noexcept
{
    return std::equal(m_values.cbegin(), m_values.cend(), other.m_values.cbegin());
}

double TestVector::X() const noexcept
{
    return m_values[0];
}

double TestVector::Y() const noexcept
{
    return m_values[1];
}

double TestVector::Z() const noexcept
{
    return m_values[2];
}