#include "pch.h"
#include "SpaceHelpers.h"

using namespace Space;

//-------------------------------------------------------------------------------------------------

template<typename Space>
typename Space::Point ReturnFirst(std::vector<typename Space::Point> v)
{
    return v.front();
}

detail::BaseImpl ReturnFirstImpl(std::vector<detail::BaseImpl> v)
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

    const View::Point first = ReturnFirst<View>(v);

    CHECK(first == v.front());
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Strongly typed collections can be used in templated functions: Patient Space") {
    const std::vector<Patient::Point> v{
        Patient::Point{1, 1, 1},
        Patient::Point{2, 2, 2}
    };

    const Patient::Point first = ReturnFirst<Patient>(v);

    CHECK(first == v.front());
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Strongly typed collections can be transformed for use in non-templated functions") {
    const std::vector<View::Point> v{
        {1, 1, 1},
        {2, 2, 2}
    };

    std::vector<detail::BaseImpl> impls;
    std::transform(
        v.cbegin(),
        v.cend(),
        std::back_inserter(impls),
        [](auto v) {return static_cast<detail::BaseImpl>(v);}
    );

    const auto first = ReturnFirstImpl(impls);

    CHECK(first == static_cast<detail::BaseImpl>(v.front()));
}

//-------------------------------------------------------------------------------------------------

