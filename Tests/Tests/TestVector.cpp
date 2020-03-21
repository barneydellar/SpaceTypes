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

