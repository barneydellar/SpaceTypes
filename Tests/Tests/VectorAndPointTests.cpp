#include "pch.h"
#include "SpaceHelpers.h"

using namespace Space;

//-------------------------------------------------------------------------------------------------
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("PointsAndVectorsFromTheSameSpaceCannotBeComparedUsingEquality") {
    const View::Vector v;
    const View::Point p;

    // We should not be able to compile:
    // auto dummy = p == v;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(p == v);
    using required_type = StaticAssert::invalid_point_vector_equality;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
TEST_CASE("Point2s And Vectors From The Same Space Cannot Be Compared Using Equality") {
    const View::Vector v;
    const View::Point2 p;

    // We should not be able to compile:
    // auto dummy = p == v;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(p == v);
    using required_type = StaticAssert::invalid_point_vector_equality;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsAndPointsFromTheSameSpaceCannotBeComparedUsingEquality") {
    const View::Vector v;
    const View::Point p;

    // We should not be able to compile:
    // auto dummy = v == p;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v == p);
    using required_type = StaticAssert::invalid_point_vector_equality;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
//-------------------------------------------------------------------------------------------------

TEST_CASE("PointsAndVectorsFromTheSameSpaceCannotBeComparedUsingInequality") {
    const View::Vector v;
    const View::Point p;

    // We should not be able to compile:
    // auto dummy = p != v;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(p != v);
    using required_type = StaticAssert::invalid_point_vector_equality;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsAndPointsFromTheSameSpaceCannotBeComparedUsingInequality") {
    const View::Vector v;
    const View::Point p;

    // We should not be able to compile:
    // auto dummy = v != p;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(p != v);
    using required_type = StaticAssert::invalid_point_vector_equality;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("Vector Can Be Added To Point In The Same Space") {
    const Volume::Point p(0, 0, 1);
    const Volume::Vector v(1, 0, 0);
    const auto p_new = p + v;
    CHECK(p_new == Volume::Point(1, 0, 1));
}
TEST_CASE("Vector Can Be Added To Point2 In The Same Space") {
    const Volume::Point2 p(0, 1);
    const Volume::Vector v(1, 0, 0);
    const auto p_new = p + v;
    CHECK(p_new == Volume::Point(1, 1, 0));
}
TEST_CASE("Vector Can Be Added ToPoint2 In The Same Space To Produce A Point 3") {
    const Volume::Point2 p;
    const Volume::Vector v;
    using converted_type = decltype(p + v);
    using required_type = decltype(Volume::Point{});
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}

TEST_CASE("Normalised Vector Can Be Added To Point In The Same Space") {
    const Volume::Point p(0, 0, 1);
    const Volume::NormalizedVector v(1, 0, 0);
    const auto p_new = p + v;
    CHECK(p_new == Volume::Point(1, 0, 1));
}
TEST_CASE("Normalised Vector Can Be Added To Point2 In The Same Space") {
    const Volume::Point2 p(0, 1);
    const Volume::NormalizedVector v(1, 0, 0);
    const auto p_new = p + v;
    CHECK(p_new == Volume::Point(1, 1, 0));
}
TEST_CASE("Normalised Vector Can Be Added ToPoint2 In The Same Space To Produce A Point 3") {
    const Volume::Point2 p;
    const Volume::NormalizedVector v;
    using converted_type = decltype(p + v);
    using required_type = decltype(Volume::Point{});
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("PointCannotBeAddedToVectorInTheSameSpace") {
    const Volume::Vector v;
    const Volume::Point p;

    // We should not be able to compile:
    // auto dummy = v + p;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v + p);
    using required_type = StaticAssert::invalid_point_to_vector_addition;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}

TEST_CASE("VectorCannotBeAddedToPointInDifferentSpace") {
    const View::Point p(0, 0, 1);
    const Volume::Vector v(1, 0, 0);

    // We should not be able to compile:
    // auto dummy = p + v;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(p + v);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}

#endif

TEST_CASE("VectorCanBeAddedToPointInTheSameSpaceInPlace") {
    Volume::Point p(0, 0, 1);
    const Volume::Vector v(1, 0, 0);
    p += v;
    CHECK(p == Volume::Point(1, 0, 1));
}
TEST_CASE("Vector2 Can Be Added To Point2 In The Same Space In Place") {
    Volume::Point2 p(0, 1);
    const Volume::Vector2 v(1, 0);
    p += v;
    CHECK(p == Volume::Point2(1, 1));
}

TEST_CASE("Normalised Vector2 Can Be Added To Point In The Same Space In Place") {
    Volume::Point p(0, 0, 1);
    const Volume::NormalizedVector2 v(1, 0);
    p += v;
    CHECK(p == Volume::Point(1, 0, 1));
}

//-------------------------------------------------------------------------------------------------

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Vector Cannot Be Added To Point2 In The Same Space In Place") {
    Volume::Point2 p;
    const Volume::Vector v;

    // We should not be able to compile:
    // auto dummy = p += v;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(p += v);
    using required_type = StaticAssert::invalid_vector3_to_point2_addition;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}

TEST_CASE("VectorCannotBeAddedToPointInDifferentSpaceInPlace") {
    View::Point p;
    const Volume::Vector v;

    // We should not be able to compile:
    // auto dummy = p += v;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(p += v);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
TEST_CASE("Vector2 Cannot Be Added To Point2 In Different Space In Place") {
    View::Point2 p;
    const Volume::Vector2 v;

    // We should not be able to compile:
    // auto dummy = p += v;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(p += v);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorCanBeSubtractedFromPointInTheSameSpace") {
    const Volume::Point p(0, 0, 1);
    const Volume::Vector v(1, 0, 0);
    const auto p_new = p - v;
    CHECK(p_new == Volume::Point(-1, 0, 1));
}
TEST_CASE("Vector Can Be Subtracted From Point2 In The Same Space") {
    const Volume::Point2 p(3, 0);
    const Volume::Vector v(1, 0, 0);
    const auto p_new = p - v;
    CHECK(p_new == Volume::Point(2, 0, 0));
}
TEST_CASE("Vector Can Be Subtracted From Point2 In The Same Space to produce a 3D Point") {
    const Volume::Point2 p;
    const Volume::Vector v;

    using converted_type = decltype(p - v);
    using required_type = decltype(Volume::Point{});
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}


TEST_CASE("Vector2 Can Be Subtracted From Point In The Same Space") {
    const Volume::Point p(0, 0, 1);
    const Volume::Vector2 v(1, 0);
    const auto p_new = p - v;
    CHECK(p_new == Volume::Point(-1, 0, 1));
}
TEST_CASE("Vector2 Can Be Subtracted From Point2 In The Same Space") {
    const Volume::Point2 p(3, 0);
    const Volume::Vector2 v(1, 0);
    const auto p_new = p - v;
    CHECK(p_new == Volume::Point2(2, 0));
}
TEST_CASE("Vector2 Can Be Subtracted From Point2 In The Same Space to produce a 2D Point") {
    const Volume::Point2 p;
    const Volume::Vector2 v;

    using converted_type = decltype(p - v);
    using required_type = decltype(Volume::Point2{});
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}

TEST_CASE("Normalised Vector2 Can Be Subtracted From Point In The Same Space") {
    const Volume::Point p(3, 0, 0);
    const Volume::NormalizedVector2 v(1, 0);
    const auto p_new = p - v;
    CHECK(p_new == Volume::Point(2, 0, 0));
}
TEST_CASE("Normalised Vector2 Can Be Subtracted From Point In The Same Space to produce a 3D Point") {
    const Volume::Point p;
    const Volume::NormalizedVector2 v;

    using converted_type = decltype(p - v);
    using required_type = decltype(Volume::Point{});
}

TEST_CASE("Normalised Vector2 Can Be Subtracted From Point2 In The Same Space") {
    const Volume::Point2 p(3, 0);
    const Volume::NormalizedVector2 v(1, 0);
    const auto p_new = p - v;
    CHECK(p_new == Volume::Point2(2, 0));
}
TEST_CASE("Normalised Vector2 Can Be Subtracted From Point2 In The Same Space to produce a 2D Point") {
    const Volume::Point2 p;
    const Volume::NormalizedVector2 v;

    using converted_type = decltype(p - v);
    using required_type = decltype(Volume::Point2{});
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("PointCannotBeSubtractedFromVectorInTheSameSpace") {
    const Volume::Vector v(1, 0, 0);
    const Volume::Point p(0, 0, 1);

    // We should not be able to compile:
    // auto dummy = v - p;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v - p);
    using required_type = StaticAssert::invalid_point_from_vector_subtraction;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}

TEST_CASE("VectorCannotBeSubtractedFromPointInDifferentSpace") {
    const View::Point p(0, 0, 1);
    const Volume::Vector v(1, 0, 0);

    // We should not be able to compile:
    // auto dummy = p - v;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(p - v);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}

#endif

TEST_CASE("VectorCanBeSubtractedFromPointInTheSameSpaceInPlace") {
    Volume::Point p(0, 0, 1);
    const Volume::Vector v(1, 0, 0);
    p -= v;
    CHECK(p == Volume::Point(-1, 0, 1));
}
TEST_CASE("Vector2 Can Be Subtracted From Point In The Same Space In Place") {
    Volume::Point2 p(0, 1);
    const Volume::Vector2 v(1, 0);
    p -= v;
    CHECK(p == Volume::Point2(-1, 1));
}
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Vector Cannot Be Subtracted From Point2 In Place") {
    Volume::Point2 p;
    const Volume::Vector v;

    // We should not be able to compile:
    // auto dummy = p -= v;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(p -= v);
    using required_type = StaticAssert::invalid_vector3_from_point2_subtraction;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
TEST_CASE("VectorCannotBeSubtractedFromPointInDifferentSpaceInPlace") {
    View::Point p;
    const Volume::Vector v;

    // We should not be able to compile:
    // auto dummy = p -= v;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(p -= v);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
TEST_CASE("Vector2 Cannot Be Subtracted From Point In Different Space In Place") {
    View::Point2 p;
    const Volume::Vector2 v;

    // We should not be able to compile:
    // auto dummy = p -= v;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(p -= v);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

//-------------------------------------------------------------------------------------------------
