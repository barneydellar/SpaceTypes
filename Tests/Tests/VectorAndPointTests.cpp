#include "pch.h"

#include "SpaceHelpers.h"

using namespace Space;

constexpr bool TEST_NON_COMPILATION{ false };

//-------------------------------------------------------------------------------------------------

TEST_CASE("PointsAndVectorsFromTheSameSpaceCannotBeComparedUsingEquality") {
    const View::Vector v(1, 0, 0);
    const View::Point p(1, 0, 0);

    // We should not be able to compile this.
    if constexpr (TEST_NON_COMPILATION) {
        auto dummy = p == v;
    }
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsAndPointsFromTheSameSpaceCannotBeComparedUsingEquality") {
    const View::Vector v(1, 0, 0);
    const View::Point p(1, 0, 0);

    // We should not be able to compile this.
    if constexpr (TEST_NON_COMPILATION) {
        auto dummy = v == p;
    }
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("PointsAndVectorsFromTheSameSpaceCannotBeComparedUsingInequality") {
    const View::Vector v(1, 0, 0);
    const View::Point p(1, 0, 0);

    // We should not be able to compile this.
    if constexpr (TEST_NON_COMPILATION) {
        auto dummy = p != v;
    }
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsAndPointsFromTheSameSpaceCannotBeComparedUsingInequality") {
    const View::Vector v(1, 0, 0);
    const View::Point p(1, 0, 0);

    // We should not be able to compile this.
    if constexpr (TEST_NON_COMPILATION) {
        auto dummy = v != p;
    }
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorCanBeAddedToPointInTheSameSpace") {
    const Volume::Point p(0, 0, 1);
    const Volume::Vector v(1, 0, 0);
    const auto p_new = p + v;
    CHECK(p_new == Volume::Point(1, 0, 1));
}

TEST_CASE("PointCannotBeAddedToVectorInTheSameSpace") {
    const Volume::Vector v(1, 0, 0);
    const Volume::Point p(0, 0, 1);

    // We should not be able to compile this.
    if constexpr (TEST_NON_COMPILATION) {
        auto dummy = v + p;
    }
}

TEST_CASE("VectorCannotBeAddedToPointInDifferentSpace") {
    const View::Point p(0, 0, 1);
    const Volume::Vector v(1, 0, 0);

    // We should not be able to compile this.
    if constexpr (TEST_NON_COMPILATION) {
        auto dummy = p + v;
    }
}

TEST_CASE("VectorCanBeAddedToPointInTheSameSpaceInPlace") {
    Volume::Point p(0, 0, 1);
    const Volume::Vector v(1, 0, 0);
    p += v;
    CHECK(p == Volume::Point(1, 0, 1));
}

TEST_CASE("VectorCannotBeAddedToPointInDifferentSpaceInPlace") {
    View::Point p(0, 0, 1);
    const Volume::Vector v(1, 0, 0);

    // We should not be able to compile this.
    if constexpr (TEST_NON_COMPILATION) {
        p += v;
    }
}

//-------------------------------------------------------------------------------------------------
