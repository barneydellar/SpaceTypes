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
