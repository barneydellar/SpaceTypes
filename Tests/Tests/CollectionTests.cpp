#include "pch.h"
#include "SpaceHelpers.h"
#include "TestVector.h"


using namespace Space;

//-------------------------------------------------------------------------------------------------

template<typename Space>
typename Space::Point ReturnFirst(std::vector<typename Space::Point> v)
{
    return v.front();
}

TestVector ReturnFirstImpl(std::vector<TestVector> v)
{
    return v.front();
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Collections of Points can be created using initalizer lists") {
    const std::vector<View::Point> points{
        {1, 1, 1},
        {2, 2, 2}
    };

    CHECK(points[0] == View::Point(1, 1, 1));
    CHECK(points[1] == View::Point(2, 2, 2));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Strongly typed collections can be used in templated functions: View Space") {
    const std::vector<View::Point> v{
        {1, 1, 1},
        {2, 2, 2}
    };

    const auto first = ReturnFirst<View>(v);

    CHECK(first == v.front());
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Strongly typed collections can be used in templated functions: Data Space") {
    const std::vector<Data::Point> v{
        Data::Point{1, 1, 1},
        Data::Point{2, 2, 2}
    };

    const auto first = ReturnFirst<Data>(v);

    CHECK(first == v.front());
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Strongly typed collections can be transformed for use in non-templated functions") {
    const std::vector<View::Point> v{
        {1, 1, 1},
        {2, 2, 2}
    };

    std::vector<TestVector> impls;
    std::transform(
        v.cbegin(),
        v.cend(),
        std::back_inserter(impls),
        [](auto v) {return static_cast<TestVector>(v);}
    );

    const auto first = ReturnFirstImpl(impls);

    CHECK(first.m_values[0] == static_cast<TestVector>(v.front()).m_values[0]);
    CHECK(first.m_values[1] == static_cast<TestVector>(v.front()).m_values[1]);
    CHECK(first.m_values[2] == static_cast<TestVector>(v.front()).m_values[2]);
}

//-------------------------------------------------------------------------------------------------

