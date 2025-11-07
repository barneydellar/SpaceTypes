#include "ExampleTransformManager.h"
#include "Includes.h"
#include "SpaceHelpers.h"

using namespace Space;

TEST_CASE("NormalizedXYVectors can be constructed") { View::NormalizedXYVector v; }
TEST_CASE("NormalizedXYVectors default to the i vector") {
    View::NormalizedXYVector v;
    CHECK(v[0] == 1);
    CHECK(v[1] == 0);
}
TEST_CASE("NormalizedXYVectors can be constructed from implementation") {
    TestVector impl;
    impl.m_values[0] = 3;
    impl.m_values[1] = 4;
    impl.m_values[2] = 0;
    const View::NormalizedXYVector v(impl);
    CHECK(v.X() == 3 / 5.0);
    CHECK(v.Y() == 4 / 5.0);
}
TEST_CASE("NormalizedXYVectors Can Be Constructed From Two Doubles") {
    const View::NormalizedXYVector v(3, 4);
    CHECK(v.X() == 3 / 5.0);
    CHECK(v.Y() == 4 / 5.0);
}
TEST_CASE("NormalizedXYVectors can be created using initalizer lists of two numbers") {
    View::NormalizedXYVector v{3, 4};
    CHECK(v.X() == 3 / 5.0);
    CHECK(v.Y() == 4 / 5.0);
}

TEST_CASE("NormalizedXYVectors can be assigned from a normalized XYvector") {
    const View::NormalizedXYVector v2(1, 0);
    const View::NormalizedXYVector v = v2;
    CHECK(v.X() == 1);
    CHECK(v.Y() == 0);
}

TEST_CASE("NormalizedXYVectors can be explicitly cast to the implementation") {
    const Image::NormalizedXYVector v(1, 0);
    auto impl = static_cast<TestVector>(v);
    CHECK(impl.m_values[0] == 1);
    CHECK(impl.m_values[1] == 0);
    CHECK(impl.m_values[2] == 0);
}

TEST_CASE("NormalizedXYVector can be implicitly cast to a NormalizedVector") {
    const Image::NormalizedXYVector v(1, 0);
    const Image::NormalizedVector v2 = v;
    CHECK(v2[0] == 1);
    CHECK(v2[1] == 0);
    CHECK(v2[2] == 0);
}

TEST_CASE("NormalizedXYVector can be implicitly cast to an XYVector") {
    const Image::NormalizedXYVector v(1, 0);
    const Image::XYVector v2 = v;
    CHECK(v2[0] == 1);
    CHECK(v2[1] == 0);
}

TEST_CASE("NormalizedXYVector can be implicitly cast to a Vector") {
    const Image::NormalizedXYVector v(1, 0);
    const Image::Vector v2 = v;
    CHECK(v2[0] == 1);
    CHECK(v2[1] == 0);
    CHECK(v2[2] == 0);
}

TEST_CASE("NormalizedXYVectors support element access by name") {
    const Image::NormalizedXYVector v(1, 0);
    CHECK(v.X() == 1);
    CHECK(v.Y() == 0);
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("NormalizedXYVectors do not support Z access") {
    const Image::NormalizedXYVector v(2, 3);
    using converted_type = decltype(v.Z());
    using required_type = StaticAssert::invalid_3D_access;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("NormalizedXYVectors do not support modification by name") {
    Image::NormalizedXYVector v;
    using converted_type_x = decltype(v.SetX(1));
    using converted_type_y = decltype(v.SetY(1));
    using converted_type_z = decltype(v.SetZ(1));
    using required_type = StaticAssert::invalid_normalized_vector_modification;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_x, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_y, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_z, required_type>));
}
#endif

TEST_CASE("NormalizedXYVectors have 2 values") {
    const Image::NormalizedXYVector v(1, 0);
    std::vector<double> values;
    std::copy(v.cbegin(), v.cend(), std::back_inserter(values));
    CHECK(values.size() == 2);
}

TEST_CASE("NormalizedXYVectors support const begin and end") {
    const Image::NormalizedXYVector v(1, 0);
    std::vector<double> values;
    std::copy(v.cbegin(), v.cend(), std::back_inserter(values));
    CHECK(values[0] == 1);
    CHECK(values[1] == 0);
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("NormalizedXYVectors don't support non-const begin and end") {
    Image::NormalizedXYVector v(1, 0);
    using begin_converted_type = decltype(v.begin());
    using end_converted_type = decltype(v.end());
    using required_type = StaticAssert::invalid_normalized_vector_modification;
    CHECK(static_cast<bool>(std::is_same_v<begin_converted_type, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<end_converted_type, required_type>));
}
#endif

TEST_CASE("NormalizedXYVectors support element access by random access") {
    const Image::NormalizedXYVector v(1, 0);
    CHECK(v[0] == 1);
    CHECK(v[1] == 0);
}
TEST_CASE("NormalizedXYVectors throw if random access is too high") {
    const Image::NormalizedXYVector v;
    CHECK_THROWS_AS(v[2], std::invalid_argument);
}
TEST_CASE("NormalizedXYVector throw with the right message if random access is too high") {
    const Image::NormalizedXYVector v;
    CHECK_THROWS_WITH(v[2], "Index is out of range");
}

TEST_CASE("NormalizedXYVectors support element access by at") {
    const Image::NormalizedXYVector v(1, 0);
    CHECK(v.at<0>() == 1);
    CHECK(v.at<1>() == 0);
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("NormalizedXYVectors at does not compile if too low") {
    const Image::NormalizedXYVector v;
    using converted_type = decltype(v.at<-1>());
    using required_type = StaticAssert::invalid_at_access;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
TEST_CASE("NormalizedXYVectors at does not compile if too high") {
    const Image::NormalizedXYVector v;
    using converted_type = decltype(v.at<2>());
    using required_type = StaticAssert::invalid_at_access;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

TEST_CASE("NormalizedXYVector and Vector can be compared using equal: same") {
    const View::NormalizedXYVector v(1, 0);
    const View::Vector v2(1, 0, 0);
    CHECK(v == v2);
}
TEST_CASE("NormalizedXYVector and NormalizedVector can be compared using equal: same") {
    const View::NormalizedXYVector v(1, 0);
    const View::NormalizedVector v2(1, 0, 0);
    CHECK(v == v2);
}
TEST_CASE("NormalizedXYVector and NormalizedXYVector can be compared using equal: same") {
    const View::NormalizedXYVector v(1, 0);
    const View::NormalizedXYVector v2(1, 0);
    CHECK(v == v2);
}
TEST_CASE("NormalizedXYVector and XYVector can be compared using equal: same") {
    const View::NormalizedXYVector v(1, 0);
    const View::XYVector v2(1, 0);
    CHECK(v == v2);
}

TEST_CASE("NormalizedXYVector and Vector can be compared using equal: different") {
    const View::NormalizedXYVector v(1, 1);
    const View::Vector v2(1, 0, 0);
    CHECK(!(v == v2));
}
TEST_CASE("NormalizedXYVector and NormalizedVector can be compared using equal: different") {
    const View::NormalizedXYVector v(1, 1);
    const View::NormalizedVector v2(1, 0, 0);
    CHECK(!(v == v2));
}
TEST_CASE("NormalizedXYVector and NormalizedXYVector can be compared using equal: different") {
    const View::NormalizedXYVector v(1, 1);
    const View::NormalizedXYVector v2(1, 0);
    CHECK(!(v == v2));
}
TEST_CASE("NormalizedXYVector and XYVector can be compared using equal: different") {
    const View::NormalizedXYVector v(1, 1);
    const View::XYVector v2(1, 0);
    CHECK(!(v == v2));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("NormalizedXYVectors from different spaces cannot be compared using equal") {
    const View::NormalizedXYVector v;
    const Image::Vector v_v;
    const Image::NormalizedVector v_n;
    const Image::NormalizedXYVector v_n_xy;
    const Image::XYVector v_xy;

    using converted_type_1 = decltype(v == v_v);
    using converted_type_2 = decltype(v == v_n);
    using converted_type_3 = decltype(v == v_n_xy);
    using converted_type_4 = decltype(v == v_xy);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_3, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_4, required_type>));
}

TEST_CASE("NormalizedXYVector and Points cannot be compared using equal") {
    const View::NormalizedXYVector v;
    const View::Point p;
    const View::XYPoint p_xy;

    using converted_type_1 = decltype(v == p);
    using converted_type_2 = decltype(v == p_xy);
    using required_type = StaticAssert::invalid_point_vector_equality;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
}
#endif

TEST_CASE("NormalizedXYVector and Vector can be compared using inequality: same") {
    const View::NormalizedXYVector v(1, 0);
    const View::Vector v2(1, 0, 0);
    CHECK(!(v != v2));
}
TEST_CASE("NormalizedXYVector and NormalizedVector can be compared using inequality: same") {
    const View::NormalizedXYVector v(1, 0);
    const View::NormalizedVector v2(1, 0, 0);
    CHECK(!(v != v2));
}
TEST_CASE("NormalizedXYVector and NormalizedXYVector can be compared using inequality: same") {
    const View::NormalizedXYVector v(1, 0);
    const View::NormalizedXYVector v2(1, 0);
    CHECK(!(v != v2));
}
TEST_CASE("NormalizedXYVector and XYVector can be compared using inequality: same") {
    const View::NormalizedXYVector v(1, 0);
    const View::XYVector v2(1, 0);
    CHECK(!(v != v2));
}

TEST_CASE("NormalizedXYVector and Vector can be compared using inequality: different") {
    const View::NormalizedXYVector v(1, 1);
    const View::Vector v2(1, 0, 0);
    CHECK(v != v2);
}
TEST_CASE("NormalizedXYVector and NormalizedVector can be compared using inequality: different") {
    const View::NormalizedXYVector v(1, 1);
    const View::NormalizedVector v2(1, 0, 0);
    CHECK(v != v2);
}
TEST_CASE("NormalizedXYVector and NormalizedXYVector can be compared using inequality: different") {
    const View::NormalizedXYVector v(1, 1);
    const View::NormalizedXYVector v2(1, 0);
    CHECK(v != v2);
}
TEST_CASE("NormalizedXYVector and XYVector can be compared using inequality: different") {
    const View::NormalizedXYVector v(1, 1);
    const View::XYVector v2(1, 0);
    CHECK(v != v2);
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("NormalizedXYVectors from different spaces cannot be compared using inequality") {
    const View::NormalizedXYVector v;
    const Image::Vector v_v;
    const Image::NormalizedVector v_n;
    const Image::NormalizedXYVector v_n_xy;
    const Image::XYVector v_xy;

    using converted_type_1 = decltype(v != v_v);
    using converted_type_2 = decltype(v != v_n);
    using converted_type_3 = decltype(v != v_n_xy);
    using converted_type_4 = decltype(v != v_xy);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_3, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_4, required_type>));
}

TEST_CASE("NormalizedXYVectors and Points cannot be compared using inequality") {
    const View::NormalizedXYVector v;
    const View::Point p;
    const View::XYPoint p_xy;

    using converted_type_1 = decltype(v != p);
    using converted_type_2 = decltype(v != p_xy);
    using required_type = StaticAssert::invalid_point_vector_equality;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
}

TEST_CASE("NormalizedXYVectors cannot have other vectors subtracted in place") {
    View::NormalizedXYVector v;
    const View::Vector v_v;
    const View::NormalizedVector v_n;
    const View::NormalizedXYVector v_n_xy;
    const View::XYVector v_xy;

    using converted_type_1 = decltype(v -= v_v);
    using converted_type_2 = decltype(v -= v_n);
    using converted_type_3 = decltype(v -= v_n_xy);
    using converted_type_4 = decltype(v -= v_xy);
    using required_type = StaticAssert::invalid_normalized_vector_subtraction;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_3, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_4, required_type>));
}
#endif

TEST_CASE("NormalizedXYVectors can have Vectors subtracted") {
    const Image::NormalizedXYVector v(0, 1);
    const Image::Vector v2(1, 0, 0);
    auto v3 = v - v2;
    CHECK(v3 == Image::Vector(-1, 1, 0));
}
TEST_CASE("NormalizedXYVectors can have NormalizedVector subtracted") {
    const Image::NormalizedXYVector v(0, 1);
    const Image::NormalizedVector v2(1, 0, 0);
    auto v3 = v - v2;
    CHECK(v3 == Image::Vector(-1, 1, 0));
}
TEST_CASE("NormalizedXYVectors can have NormalizedXYVector subtracted") {
    const Image::NormalizedXYVector v(0, 1);
    const Image::NormalizedXYVector v2(1, 0);
    auto v3 = v - v2;
    CHECK(v3 == Image::XYVector(-1, 1));
}
TEST_CASE("NormalizedXYVectors can have XYVector subtracted") {
    const Image::NormalizedXYVector v(0, 1);
    const Image::XYVector v2(1, 0);
    auto v3 = v - v2;
    CHECK(v3 == Image::XYVector(-1, 1));
}
TEST_CASE("NormalizedXYVectors can have other XYVectors subtracted to produce a XYVector") {
    View::NormalizedXYVector v;
    const View::NormalizedXYVector v_n_xy;
    const View::XYVector v_xy;

    using converted_type_3 = decltype(v - v_n_xy);
    using converted_type_4 = decltype(v - v_xy);
    using required_type = View::XYVector;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_3, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_4, required_type>));
}
TEST_CASE("NormalizedXYVectors can have other 3D vectors subtracted to produce a Vector") {
    View::NormalizedXYVector v;
    const View::Vector v_v;
    const View::NormalizedVector v_n;

    using converted_type_1 = decltype(v - v_v);
    using converted_type_2 = decltype(v - v_n);
    using required_type = View::Vector;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("NormalizedXYVectors in different spaces cannot be subtracted") {
    View::NormalizedXYVector v;
    const Image::Vector v_v;
    const Image::NormalizedVector v_n;
    const Image::NormalizedXYVector v_n_xy;
    const Image::XYVector v_xy;

    using converted_type_1 = decltype(v - v_v);
    using converted_type_2 = decltype(v - v_n);
    using converted_type_3 = decltype(v - v_n_xy);
    using converted_type_4 = decltype(v - v_xy);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_3, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_4, required_type>));
}

TEST_CASE("NormalizedXYVectors cannot have points subtracted") {
    const View::NormalizedXYVector v;
    const View::Point p;
    const View::XYPoint p_xy;

    using converted_type_1 = decltype(v - p);
    using converted_type_2 = decltype(v - p_xy);
    using required_type = StaticAssert::invalid_point_from_vector_subtraction;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
}

TEST_CASE("NormalizedXYVectors cannot have other vectors added in place") {
    View::NormalizedXYVector v;
    const View::Vector v_v;
    const View::NormalizedVector v_n;
    const View::NormalizedXYVector v_n_xy;
    const View::XYVector v_xy;

    using converted_type_1 = decltype(v += v_v);
    using converted_type_2 = decltype(v += v_n);
    using converted_type_3 = decltype(v += v_n_xy);
    using converted_type_4 = decltype(v += v_xy);
    using required_type = StaticAssert::invalid_normalized_vector_addition;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_3, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_4, required_type>));
}
#endif

TEST_CASE("NormalizedXYVectors can have Vectors added") {
    const Image::NormalizedXYVector v(0, 1);
    const Image::Vector v2(1, 0, 0);
    auto v3 = v + v2;
    CHECK(v3 == Image::Vector(1, 1, 0));
}
TEST_CASE("NormalizedXYVectors can have NormalizedVector added") {
    const Image::NormalizedXYVector v(0, 1);
    const Image::NormalizedVector v2(1, 0, 0);
    auto v3 = v + v2;
    CHECK(v3 == Image::Vector(1, 1, 0));
}
TEST_CASE("NormalizedXYVectors can have NormalizedXYVector added") {
    const Image::NormalizedXYVector v(0, 1);
    const Image::NormalizedXYVector v2(1, 0);
    auto v3 = v + v2;
    CHECK(v3 == Image::XYVector(1, 1));
}
TEST_CASE("NormalizedXYVectors can have XYVector added") {
    const Image::NormalizedXYVector v(0, 1);
    const Image::XYVector v2(1, 0);
    auto v3 = v + v2;
    CHECK(v3 == Image::XYVector(1, 1));
}
TEST_CASE("NormalizedXYVectors can have other XYvectors added to produce another XYVector") {
    View::NormalizedXYVector v;
    const View::NormalizedXYVector v_n_xy;
    const View::XYVector v_xy;

    using converted_type_3 = decltype(v + v_n_xy);
    using converted_type_4 = decltype(v + v_xy);
    using required_type = View::XYVector;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_3, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_4, required_type>));
}
TEST_CASE("NormalizedXYVectors can have other 3D vectors added to produce another Vector") {
    View::NormalizedXYVector v;
    const View::Vector v_v;
    const View::NormalizedVector v_n;

    using converted_type_1 = decltype(v + v_v);
    using converted_type_2 = decltype(v + v_n);
    using required_type = View::Vector;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("NormalizedXYVectors in different spaces cannot be added") {
    View::NormalizedXYVector v;
    const Image::Vector v_v;
    const Image::NormalizedVector v_n;
    const Image::NormalizedXYVector v_n_xy;
    const Image::XYVector v_xy;

    using converted_type_1 = decltype(v + v_v);
    using converted_type_2 = decltype(v + v_n);
    using converted_type_3 = decltype(v + v_n_xy);
    using converted_type_4 = decltype(v + v_xy);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_3, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_4, required_type>));
}

TEST_CASE("NormalizedXYVectors cannot have points added") {
    const View::NormalizedXYVector v;
    const View::Point p;
    const View::XYPoint p_xy;

    using converted_type_1 = decltype(v + p);
    using converted_type_2 = decltype(v + p_xy);
    using required_type = StaticAssert::invalid_point_to_vector_addition;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
}
#endif

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("NormalizedXYVectors cannot be crossed in place") {
    View::NormalizedXYVector v;
    const View::Vector v_v;
    const View::NormalizedVector v_n;
    const View::NormalizedXYVector v_n_xy;
    const View::XYVector v_xy;

    using converted_type_1 = decltype(v *= v_v);
    using converted_type_2 = decltype(v *= v_n);
    using converted_type_3 = decltype(v *= v_n_xy);
    using converted_type_4 = decltype(v *= v_xy);
    using required_type = StaticAssert::invalid_normalized_vector_in_place_cross;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_3, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_4, required_type>));
}

TEST_CASE("NormalizedXYVectors in different spaces cannot be crossed in place") {
    Image::NormalizedXYVector v;
    const View::Vector v_v;
    const View::NormalizedVector v_n;
    const View::NormalizedXYVector v_n_xy;
    const View::XYVector v_xy;

    using converted_type_1 = decltype(v *= v_v);
    using converted_type_2 = decltype(v *= v_n);
    using converted_type_3 = decltype(v *= v_n_xy);
    using converted_type_4 = decltype(v *= v_xy);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_3, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_4, required_type>));
}
#endif

TEST_CASE("NormalizedXYVectors can have Vectors crossed using star") {
    const Image::NormalizedXYVector v(0, 1);
    const Image::Vector v2(1, 0, 0);
    auto v3 = v * v2;
    CHECK(v3 == Image::Vector(0, 0, -1));
}
TEST_CASE("NormalizedXYVectors can have NormalizedVector crossed using star") {
    const Image::NormalizedXYVector v(0, 1);
    const Image::NormalizedVector v2(1, 0, 0);
    auto v3 = v * v2;
    CHECK(v3 == Image::Vector(0, 0, -1));
}
TEST_CASE("NormalizedXYVectors can have NormalizedXYVector crossed using star") {
    const Image::NormalizedXYVector v(0, 1);
    const Image::NormalizedXYVector v2(1, 0);
    auto v3 = v * v2;
    CHECK(v3 == Image::Vector(0, 0, -1));
}
TEST_CASE("NormalizedXYVectors can have XYVector crossed using star") {
    const Image::NormalizedXYVector v(0, 1);
    const Image::XYVector v2(1, 0);
    auto v3 = v * v2;
    CHECK(v3 == Image::Vector(0, 0, -1));
}
TEST_CASE("NormalizedXYVectors can have other normalized vectors crossed using star to produce another NormalizedVector") {
    View::NormalizedXYVector v;
    const View::NormalizedVector v_n;
    const View::NormalizedXYVector v_n_xy;

    using converted_type_2 = decltype(v * v_n);
    using converted_type_3 = decltype(v * v_n_xy);
    using required_type = View::NormalizedVector;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_3, required_type>));
}
TEST_CASE("NormalizedXYVectors can have other vectors crossed using star to produce another Vector") {
    View::NormalizedXYVector v;
    const View::Vector v_v;
    const View::XYVector v_xy;

    using converted_type_1 = decltype(v * v_v);
    using converted_type_4 = decltype(v * v_xy);
    using required_type = View::Vector;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_4, required_type>));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("NormalizedXYVectors in different spaces cannot be crossed using star") {
    View::NormalizedXYVector v;
    const Image::Vector v_v;
    const Image::NormalizedVector v_n;
    const Image::NormalizedXYVector v_n_xy;
    const Image::XYVector v_xy;

    using converted_type_1 = decltype(v * v_v);
    using converted_type_2 = decltype(v * v_n);
    using converted_type_3 = decltype(v * v_n_xy);
    using converted_type_4 = decltype(v * v_xy);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_3, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_4, required_type>));
}
#endif

TEST_CASE("NormalizedXYVectors can have Vectors crossed") {
    const Image::NormalizedXYVector v(0, 1);
    const Image::Vector v2(1, 0, 0);
    auto v3 = v.Cross(v2);
    CHECK(v3 == Image::Vector(0, 0, -1));
}
TEST_CASE("NormalizedXYVectors can have NormalizedVector crossed") {
    const Image::NormalizedXYVector v(0, 1);
    const Image::NormalizedVector v2(1, 0, 0);
    auto v3 = v.Cross(v2);
    CHECK(v3 == Image::Vector(0, 0, -1));
}
TEST_CASE("NormalizedXYVectors can have NormalizedXYVector crossed") {
    const Image::NormalizedXYVector v(0, 1);
    const Image::NormalizedXYVector v2(1, 0);
    auto v3 = v.Cross(v2);
    CHECK(v3 == Image::Vector(0, 0, -1));
}
TEST_CASE("NormalizedXYVectors can have XYVector crossed") {
    const Image::NormalizedXYVector v(0, 1);
    const Image::XYVector v2(1, 0);
    auto v3 = v.Cross(v2);
    CHECK(v3 == Image::Vector(0, 0, -1));
}
TEST_CASE("NormalizedXYVectors can have other NormalizedVectors crossed to produce another NormalizedVector") {
    View::NormalizedXYVector v;
    const View::NormalizedVector v_n;
    const View::NormalizedXYVector v_n_xy;

    using converted_type_2 = decltype(v.Cross(v_n));
    using converted_type_3 = decltype(v.Cross(v_n_xy));
    using required_type = View::NormalizedVector;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_3, required_type>));
}
TEST_CASE("NormalizedXYVectors can have other vectors crossed to produce another Vector") {
    View::NormalizedXYVector v;
    const View::Vector v_v;
    const View::XYVector v_xy;

    using converted_type_1 = decltype(v.Cross(v_v));
    using converted_type_4 = decltype(v.Cross(v_xy));
    using required_type = View::Vector;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_4, required_type>));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("NormalizedXYVectors in different spaces cannot be crossed") {
    View::NormalizedXYVector v;
    const Image::Vector v_v;
    const Image::NormalizedVector v_n;
    const Image::NormalizedXYVector v_n_xy;
    const Image::XYVector v_xy;

    using converted_type_1 = decltype(v.Cross(v_v));
    using converted_type_2 = decltype(v.Cross(v_n));
    using converted_type_3 = decltype(v.Cross(v_n_xy));
    using converted_type_4 = decltype(v.Cross(v_xy));
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_3, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_4, required_type>));
}
#endif

TEST_CASE("NormalizedXYVectors and Vectors can be dotted") {
    const View::NormalizedXYVector v(1, 0);
    const View::Vector v2(2, 0, 0);
    const auto dot = v.Dot(v2);
    CHECK(dot == 2);
}
TEST_CASE("NormalizedXYVectors and NormalizedVector can be dotted") {
    const View::NormalizedXYVector v(1, 0);
    const View::NormalizedVector v2(1, 0, 0);
    const auto dot = v.Dot(v2);
    CHECK(dot == 1);
}
TEST_CASE("NormalizedXYVectors and NormalizedXYVector can be dotted") {
    const View::NormalizedXYVector v(1, 0);
    const View::NormalizedXYVector v2(1, 0);
    const auto dot = v.Dot(v2);
    CHECK(dot == 1);
}
TEST_CASE("NormalizedXYVectors and XYVector can be dotted") {
    const View::NormalizedXYVector v(1, 0);
    const View::XYVector v2(2, 0);
    const auto dot = v.Dot(v2);
    CHECK(dot == 2);
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("NormalizedXYVectors from different spaces cannot be dotted") {
    View::NormalizedXYVector v;
    const Image::Vector v_v;
    const Image::NormalizedVector v_n;
    const Image::NormalizedXYVector v_n_xy;
    const Image::XYVector v_xy;

    using converted_type_1 = decltype(v.Dot(v_v));
    using converted_type_2 = decltype(v.Dot(v_n));
    using converted_type_3 = decltype(v.Dot(v_n_xy));
    using converted_type_4 = decltype(v.Dot(v_xy));
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_3, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_4, required_type>));
}

#endif

TEST_CASE("NormalizedXYVectors can be converted from one space to another ignoring translation") {
    TransformManager tm;
    tm.SetDataVectorValues(15, 16, 17);
    const View::NormalizedXYVector v_view(1, 0);
    auto v_patient = v_view.ConvertTo<Data>(tm);
    CHECK(v_patient == Data::Vector(15, 16, 17));
}
TEST_CASE("NormalizedXYVectors can be converted from one space to another to produce a Vector") {
    const TransformManager tm;
    const View::NormalizedXYVector v_view;
    using converted_type = decltype(v_view.ConvertTo<Data>(tm));
    using required_type = Data::Vector;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("NormalizedXYVectors cannot be converted to the same space") {
    const TransformManager tm;
    const View::NormalizedXYVector v;
    using converted_type = decltype(v.ConvertTo<View>(tm));
    using required_type = StaticAssert::invalid_same_space_conversion;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

TEST_CASE("NormalizedXYVectors can be default-formatted") {
    const View::NormalizedXYVector v(1, 0);
    CHECK(std::format("{}", v) == "View::NormalizedXYVector (1, 0)");
}

TEST_CASE("NormalizedXYVectors can format the default-formatting") {
    const View::NormalizedXYVector v(1, 0);
    CHECK(std::format("{:*^39}", v) == "****View::NormalizedXYVector (1, 0)****");
}

TEST_CASE("NormalizedXYVectors can localise the default-formatting") {
    const View::NormalizedXYVector v(1, 1);
    const auto localised = std::format(std::locale("de_DE.UTF-8"), "{}", v);
    CHECK(localised.contains("0,707"));
    CHECK(!localised.contains("0.707"));
}

TEST_CASE("NormalizedXYVectors can be formatted to show the space") {
    const View::NormalizedXYVector v(1, 0);
    CHECK(std::format("{:s}", v) == "View");
}

TEST_CASE("NormalizedXYVectors can format the space") {
    const View::NormalizedXYVector v(1, 0);
    CHECK(std::format("{:s*^8}", v) == "**View**");
}

TEST_CASE("NormalizedXYVectors can be formatted to show the type") {
    const View::NormalizedXYVector v(1, 0);
    CHECK(std::format("{:t}", v) == "NormalizedXYVector");
}

TEST_CASE("NormalizedXYVectors can format the type") {
    const View::NormalizedXYVector v(1, 0);
    CHECK(std::format("{:t*^22}", v) == "**NormalizedXYVector**");
}

TEST_CASE("NormalizedXYVectors can be formatted to show the x value") {
    const View::NormalizedXYVector v(3, 4);
    CHECK(std::format("{:x}", v) == std::format("{}", v.X()));
}

TEST_CASE("NormalizedXYVectors can format the x value") {
    const View::NormalizedXYVector v(3, 4);
    CHECK(std::format("{:x.2}", v) == std::format("{:.2}", v.X()));
}

TEST_CASE("NormalizedXYVectors can be formatted to show the y value") {
    const View::NormalizedXYVector v(3, 4);
    CHECK(std::format("{:y}", v) == std::format("{}", v.Y()));
}

TEST_CASE("NormalizedXYVectors can format the y value") {
    const View::NormalizedXYVector v(3, 4);
    CHECK(std::format("{:y.2}", v) == std::format("{:.2}", v.Y()));
}

TEST_CASE("NormalizedXYVectors can be streamed") {
    const View::NormalizedXYVector v(1, 0);
    std::stringstream stream;
    stream << v;
    CHECK(stream.str() == "View::NormalizedXYVector (1, 0)");
}

TEST_CASE("NormalizedXYVectors can be printed") {
    const View::NormalizedXYVector v(1, 0);
    std::stringstream stream;
    std::print(stream, "{}", v);
    CHECK(stream.str() == "View::NormalizedXYVector (1, 0)");
}
