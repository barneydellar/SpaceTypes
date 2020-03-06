#include "pch.h"

#include "SpaceHelpers.h"

using namespace Space;

//-------------------------------------------------------------------------------------------------

TEST_CASE("PointsAndVectorsFromTheSameSpaceCannotBeComparedUsingEquality") {
    const View::Vector v(1, 0, 0);
    const View::Point p(1, 0, 0);

    // We should not be able to compile:
    // auto dummy = p == v;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(p == v);
    using required_type = StaticAssert::invalid_point_vector_equality;
    CHECK(static_cast<bool>(std::is_same<converted_type, required_type>::value));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsAndPointsFromTheSameSpaceCannotBeComparedUsingEquality") {
    const View::Vector v(1, 0, 0);
    const View::Point p(1, 0, 0);

    // We should not be able to compile:
    // auto dummy = v == p;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v == p);
    using required_type = StaticAssert::invalid_point_vector_equality;
    CHECK(static_cast<bool>(std::is_same<converted_type, required_type>::value));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("PointsAndVectorsFromTheSameSpaceCannotBeComparedUsingInequality") {
    const View::Vector v(1, 0, 0);
    const View::Point p(1, 0, 0);

    // We should not be able to compile:
    // auto dummy = p != v;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(p != v);
    using required_type = StaticAssert::invalid_point_vector_equality;
    CHECK(static_cast<bool>(std::is_same<converted_type, required_type>::value));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsAndPointsFromTheSameSpaceCannotBeComparedUsingInequality") {
    const View::Vector v(1, 0, 0);
    const View::Point p(1, 0, 0);

    // We should not be able to compile:
    // auto dummy = v != p;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v != p);
    using required_type = StaticAssert::invalid_point_vector_equality;
    CHECK(static_cast<bool>(std::is_same<converted_type, required_type>::value));
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

    // We should not be able to compile:
    // auto dummy = v + p;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v + p);
    using required_type = StaticAssert::invalid_point_to_vector_addition;
    CHECK(static_cast<bool>(std::is_same<converted_type, required_type>::value));
}

TEST_CASE("VectorCannotBeAddedToPointInDifferentSpace") {
    const View::Point p(0, 0, 1);
    const Volume::Vector v(1, 0, 0);

    // We should not be able to compile:
    // auto dummy = p + v;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(p + v);
    using required_type = StaticAssert::invalid_vector_to_point_addition;
    CHECK(static_cast<bool>(std::is_same<converted_type, required_type>::value));
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

    // We should not be able to compile:
    // auto dummy = p += v;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(p += v);
    using required_type = StaticAssert::invalid_vector_to_point_addition;
    CHECK(static_cast<bool>(std::is_same<converted_type, required_type>::value));
}

//-------------------------------------------------------------------------------------------------
