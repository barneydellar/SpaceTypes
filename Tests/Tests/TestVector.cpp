#include "pch.h"
#include "TestVector.h"


TestVector::TestVector(const double x, const double y, const double z) noexcept : m_values{ x, y, z }
{
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
