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

TEST_CASE("Collections of XYPoints can be created using initalizer lists") {
    const std::vector<View::XYPoint> points{
        {1, 1},
        {2, 2}
    };

    CHECK(points[0] == View::XYPoint(1, 1));
    CHECK(points[1] == View::XYPoint(2, 2));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Collections of Vectors can be created using initalizer lists") {
    const std::vector<View::Vector> vectors{
        {1, 1, 1},
        {2, 2, 2}
    };

    CHECK(vectors[0] == View::Vector(1, 1, 1));
    CHECK(vectors[1] == View::Vector(2, 2, 2));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Collections of NormalizedVectors can be created using initalizer lists") {
    const std::vector<View::NormalizedVector> vectors{
        {1, 0, 0},
        {0, 1, 0}
    };

    CHECK(vectors[0] == View::NormalizedVector(1, 0, 0));
    CHECK(vectors[1] == View::NormalizedVector(0, 1, 0));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Collections of XYVectors can be created using initalizer lists") {
    const std::vector<View::XYVector> vectors{
        {1, 1},
        {2, 2}
    };

    CHECK(vectors[0] == View::XYVector(1, 1));
    CHECK(vectors[1] == View::XYVector(2, 2));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Collections of NormalizedXYVectors can be created using initalizer lists") {
    const std::vector<View::NormalizedXYVector> vectors{
        {1, 0},
        {0, 1}
    };

    CHECK(vectors[0] == View::NormalizedXYVector(1, 0));
    CHECK(vectors[1] == View::NormalizedXYVector(0, 1));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Strongly typed collections can be used in templated functions: View Space") {
    const std::vector<View::Point> points{
        {1, 1, 1},
        {2, 2, 2}
    };

    const auto first = ReturnFirst<View>(points);

    CHECK(first == points.front());
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Strongly typed collections can be used in templated functions: Data Space") {
    const std::vector<Data::Point> points{
        Data::Point{1, 1, 1},
        Data::Point{2, 2, 2}
    };

    const auto first = ReturnFirst<Data>(points);

    CHECK(first == points.front());
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Strongly typed collections can be transformed for use in non-templated functions") {
    const std::vector<View::Point> points{
        {1, 1, 1},
        {2, 2, 2}
    };

    std::vector<TestVector> impls;
    std::transform(
        points.cbegin(),
        points.cend(),
        std::back_inserter(impls),
        [](auto v) {return static_cast<TestVector>(v);}
    );

    const auto first = ReturnFirstImpl(impls);

    CHECK(first.m_values[0] == static_cast<TestVector>(points.front()).m_values[0]);
    CHECK(first.m_values[1] == static_cast<TestVector>(points.front()).m_values[1]);
    CHECK(first.m_values[2] == static_cast<TestVector>(points.front()).m_values[2]);
}

//-------------------------------------------------------------------------------------------------

