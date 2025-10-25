#include "ExternalIncludes.h"
#include "SpaceHelpers.h"
#include "ExampleTransformManager.h"

using namespace Space;

TEST_CASE("XYVectors can be constructed") {
    View::XYVector v;
}
TEST_CASE("XYVectors have zero value by default") {
    View::XYVector v;
    CHECK(v[0] == 0);
    CHECK(v[1] == 0);
}
TEST_CASE("XYVectors can be constructed from implementation") {
    TestVector impl;
    impl.m_values[0] = 3;
    impl.m_values[1] = 2;
    impl.m_values[2] = 1;
    const View::XYVector v(impl);
    CHECK(v.X() == 3);
    CHECK(v.Y() == 2);
}
TEST_CASE("XYVectors Can Be Constructed From Two Doubles") {
    const View::XYVector v(4, 5);
    CHECK(v.X() == 4);
    CHECK(v.Y() == 5);
}
TEST_CASE("XYVectors can be created using initalizer lists of two numbers") {
    View::XYVector v{1, 2};
    CHECK(v[0] == 1);
    CHECK(v[1] == 2);
}

TEST_CASE("XYVectors can be assigned from an XYVectors") {
    const View::XYVector v2(1, 2);
    const View::XYVector v = v2;
    CHECK(v.X() == 1);
    CHECK(v.Y() == 2);
}

TEST_CASE("XYVectors can be explicitly cast to the implementation") {
    const View::XYVector v(1, 2);
    auto impl = static_cast<TestVector>(v);
    CHECK(impl.m_values[0] == 1);
    CHECK(impl.m_values[1] == 2);
    CHECK(impl.m_values[2] == 0);
}

TEST_CASE("XYVector can be implicitly cast to a Vector") {
    const View::XYVector v(1, 2);
    const View::Vector v2 = v;
    CHECK(v2[0] == 1);
    CHECK(v2[1] == 2);
    CHECK(v2[2] == 0);
}

TEST_CASE("XYVectors support element access by name") {
    const Image::XYVector v(2, 3);
    CHECK(v.X() == 2);
    CHECK(v.Y() == 3);
}

TEST_CASE("XYVector elements can be modifed by name") {
    Image::XYVector v(2, 3);
    v.SetX(10);
    v.SetY(20);
    CHECK(v.X() == 10);
    CHECK(v.Y() == 20);
}

TEST_CASE("XYVectors support const begin and end") {
    const Image::XYVector v(2, 3);
    std::vector<double> values;
    std::copy(v.cbegin(), v.cend(), std::back_inserter(values));
    CHECK(values.size() == 2);
    CHECK(values[0] == 2);
    CHECK(values[1] == 3);
}
TEST_CASE("XYVectors support non-const begin and end") {
    Image::XYVector v(2, 4);
    std::fill(v.begin(), v.end(), 3);
    CHECK(v.X() == 3);
    CHECK(v.Y() == 3);
}

TEST_CASE("XYVectors support element access by random access") {
    const Image::XYVector v(2, 3);
    CHECK(v[0] == 2);
    CHECK(v[1] == 3);
}
TEST_CASE("XYVectors throw if random access is too high") {
    const Image::XYVector v;
    CHECK_THROWS_AS(v[2], std::invalid_argument);
}
TEST_CASE("XYVectors throw with the right message if random access is too high") {
    const Image::XYVector v;
    CHECK_THROWS_WITH(v[2], "Index is out of range");
}

TEST_CASE("XYVectors support element access by at") {
    const Image::XYVector v(2, 3);
    CHECK(v.at<0>() == 2);
    CHECK(v.at<1>() == 3);
}
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYVectors at does not compile if too low") {
    const Image::XYVector v;
    using converted_type = decltype(v.at<-1>());
    using required_type = StaticAssert::invalid_at_access;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
TEST_CASE("XYVectors at does not compile if too high") {
    const Image::XYVector v;
    using converted_type = decltype(v.at<2>());
    using required_type = StaticAssert::invalid_at_access;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

TEST_CASE("XYVector and Vector can be compared using equal: same") {
    const View::XYVector v(1, 0);
    const View::Vector v2(1, 0, 0);
    CHECK(v == v2);
}
TEST_CASE("XYVector and NormalizedVector can be compared using equal: same") {
    const View::XYVector v(1, 0);
    const View::NormalizedVector v2(1, 0, 0);
    CHECK(v == v2);
}
TEST_CASE("XYVector and NormalizedXYVector can be compared using equal: same") {
    const View::XYVector v(1, 0);
    const View::NormalizedXYVector v2(1, 0);
    CHECK(v == v2);
}
TEST_CASE("XYVector and XYVector can be compared using equal: same") {
    const View::XYVector v(1, 0);
    const View::XYVector v2(1, 0);
    CHECK(v == v2);
}

TEST_CASE("XYVector and Vector can be compared using equal: different") {
    const View::XYVector v(1, 1);
    const View::Vector v2(1, 0, 0);
    CHECK(!(v == v2));
}
TEST_CASE("XYVector and NormalizedVector can be compared using equal: different") {
    const View::XYVector v(1, 1);
    const View::NormalizedVector v2(1, 0, 0);
    CHECK(!(v == v2));
}
TEST_CASE("XYVector and NormalizedXYVector can be compared using equal: different") {
    const View::XYVector v(1, 1);
    const View::NormalizedXYVector v2(1, 0);
    CHECK(!(v == v2));
}
TEST_CASE("XYVector and XYVector can be compared using equal: different") {
    const View::XYVector v(1, 1);
    const View::XYVector v2(1, 0);
    CHECK(!(v == v2));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYVectors from different spaces cannot be compared using equal") {
    const View::XYVector v;
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

TEST_CASE("XYVectors and Points cannot be compared using equal") {
    const View::XYVector v;
    const View::Point p;
    const View::Point p_xy;

    using converted_type_1 = decltype(v == p);
    using converted_type_2 = decltype(v == p_xy);
    using required_type = StaticAssert::invalid_point_vector_equality;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
}
#endif

TEST_CASE("XYVector and Vector can be compared using inequality: same") {
    const View::XYVector v(1, 0);
    const View::Vector v2(1, 0, 0);
    CHECK(!(v != v2));
}
TEST_CASE("XYVector and NormalizedVector can be compared using inequality: same") {
    const View::XYVector v(1, 0);
    const View::NormalizedVector v2(1, 0, 0);
    CHECK(!(v != v2));
}
TEST_CASE("XYVector and NormalizedXYVector can be compared using inequality: same") {
    const View::XYVector v(1, 0);
    const View::NormalizedXYVector v2(1, 0);
    CHECK(!(v != v2));
}
TEST_CASE("XYVector and XYVector can be compared using inequality: same") {
    const View::XYVector v(1, 0);
    const View::XYVector v2(1, 0);
    CHECK(!(v != v2));
}

TEST_CASE("XYVector and Vector can be compared using inequality: different") {
    const View::XYVector v(1, 1);
    const View::Vector v2(1, 0, 0);
    CHECK(v != v2);
}
TEST_CASE("XYVector and NormalizedVector can be compared using inequality: different") {
    const View::XYVector v(1, 1);
    const View::NormalizedVector v2(1, 0, 0);
    CHECK(v != v2);
}
TEST_CASE("XYVector and NormalizedXYVector can be compared using inequality: different") {
    const View::XYVector v(1, 1);
    const View::NormalizedXYVector v2(1, 0);
    CHECK(v != v2);
}
TEST_CASE("XYVector and XYVector can be compared using inequality: different") {
    const View::XYVector v(1, 1);
    const View::XYVector v2(1, 0);
    CHECK(v != v2);
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYVectors from different spaces cannot be compared using inequality") {
    const View::XYVector v;
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

TEST_CASE("XYVectors and Points cannot be compared using inequality") {
    const View::XYVector v;
    const View::Point p;
    const View::Point p_xy;

    using converted_type_1 = decltype(v != p);
    using converted_type_2 = decltype(v != p_xy);
    using required_type = StaticAssert::invalid_point_vector_equality;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
}

TEST_CASE("XYVector cannot have other 3D vectors subtracted in place") {
    View::XYVector v;
    const View::Vector v_v;
    const View::NormalizedVector v_n;

    using converted_type_1 = decltype(v -= v_v);
    using converted_type_2 = decltype(v -= v_n);
    using required_type = StaticAssert::invalid_vector_from_vector_subtraction;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
}
#endif

TEST_CASE("XYVectors can have NormalizedXYVectors subtracted in place") {
    Image::XYVector v(1, 2);
    const Image::NormalizedXYVector v2(1, 0);
    v -= v2;
    CHECK(v == Image::Vector(0, 2, 3));
}
TEST_CASE("XYVectors can have XYVectors subtracted in place") {
    Image::XYVector v(1, 2);
    const Image::NormalizedXYVector v2(1, 0);
    v -= v2;
    CHECK(v == Image::Vector(0, 2, 3));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYVectors in different spaces cannot be subtracted in place") {
    View::XYVector v;
    const Image::Vector v_v;
    const Image::NormalizedVector v_n;
    const Image::NormalizedXYVector v_n_xy;
    const Image::XYVector v_xy;

    using converted_type_1 = decltype(v -= v_v);
    using converted_type_2 = decltype(v -= v_n);
    using converted_type_3 = decltype(v -= v_n_xy);
    using converted_type_4 = decltype(v -= v_xy);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_3, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_4, required_type>));
}
#endif

TEST_CASE("XYVectors can have Vectors subtracted") {
    const Image::XYVector v(1, 2);
    const Image::Vector v2(1, 0, 0);
    auto v3 = v - v2;
    CHECK(v3 == Image::Vector(0, 2, 0));
}
TEST_CASE("XYVectors can have NormalizedVector subtracted") {
    const Image::XYVector v(1, 2);
    const Image::NormalizedVector v2(1, 0, 0);
    auto v3 = v - v2;
    CHECK(v3 == Image::Vector(0, 2, 0));
}
TEST_CASE("XYVectors can have NormalizedXYVector subtracted") {
    const Image::XYVector v(1, 2);
    const Image::NormalizedXYVector v2(1, 0);
    auto v3 = v - v2;
    CHECK(v3 == Image::XYVector(0, 2));
}
TEST_CASE("XYVectors can have XYVector subtracted") {
    const Image::XYVector v(1, 2);
    const Image::XYVector v2(1, 0);
    auto v3 = v - v2;
    CHECK(v3 == Image::XYVector(0, 2));
}
TEST_CASE("XYVectors can have other XYVectors subtracted to produce a XYVector") {
    View::XYVector v;
    const View::NormalizedXYVector v_n_xy;
    const View::XYVector v_xy;

    using converted_type_3 = decltype(v - v_n_xy);
    using converted_type_4 = decltype(v - v_xy);
    using required_type = View::XYVector;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_3, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_4, required_type>));
}
TEST_CASE("XYVectors can have other 3D vectors subtracted to produce another Vector") {
    View::XYVector v;
    const View::Vector v_v;
    const View::NormalizedVector v_n;

    using converted_type_1 = decltype(v - v_v);
    using converted_type_2 = decltype(v - v_n);
    using required_type = View::Vector;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYVectors in different spaces cannot be subtracted") {
    View::XYVector v;
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

TEST_CASE("XYVectors cannot have points subtracted") {
    const View::XYVector v;
    const View::Point p;
    const View::Point p_xy;

    using converted_type_1 = decltype(v - p);
    using converted_type_2 = decltype(v - p_xy);
    using required_type = StaticAssert::invalid_point_from_vector_subtraction;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
}

TEST_CASE("XYVector cannot have other 3D vectors added in place") {
    View::XYVector v;
    const View::Vector v_v;
    const View::NormalizedVector v_n;

    using converted_type_1 = decltype(v += v_v);
    using converted_type_2 = decltype(v += v_n);
    using required_type = StaticAssert::invalid_vector_to_vector_addition;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
}
#endif

TEST_CASE("XYVectors can have NormalizedXYVectors added in place") {
    Image::XYVector v(1, 2);
    const Image::NormalizedXYVector v2(1, 0);
    v += v2;
    CHECK(v == Image::Vector(2, 2, 0));
}
TEST_CASE("XYVectors can have XYVectors added in place") {
    Image::XYVector v(1, 2);
    const Image::NormalizedXYVector v2(1, 0);
    v += v2;
    CHECK(v == Image::Vector(2, 2, 0));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYVectors in different spaces cannot be added in place") {
    View::XYVector v;
    const Image::Vector v_v;
    const Image::NormalizedVector v_n;
    const Image::NormalizedXYVector v_n_xy;
    const Image::XYVector v_xy;

    using converted_type_1 = decltype(v += v_v);
    using converted_type_2 = decltype(v += v_n);
    using converted_type_3 = decltype(v += v_n_xy);
    using converted_type_4 = decltype(v += v_xy);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_3, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_4, required_type>));
}
#endif

TEST_CASE("XYVectors can have Vectors added") {
    const Image::XYVector v(1, 2);
    const Image::Vector v2(1, 0, 0);
    auto v3 = v + v2;
    CHECK(v3 == Image::Vector(2, 2, 0));
}
TEST_CASE("XYVectors can have NormalizedVector added") {
    const Image::XYVector v(1, 2);
    const Image::NormalizedVector v2(1, 0, 0);
    auto v3 = v + v2;
    CHECK(v3 == Image::XYVector(2, 2));
}
TEST_CASE("XYVectors can have NormalizedXYVector added") {
    const Image::XYVector v(1, 2);
    const Image::NormalizedXYVector v2(1, 0);
    auto v3 = v + v2;
    CHECK(v3 == Image::XYVector(2, 2));
}
TEST_CASE("XYVectors can have XYVector added") {
    const Image::XYVector v(1, 2);
    const Image::XYVector v2(1, 0);
    auto v3 = v + v2;
    CHECK(v3 == Image::Vector(2, 2, 3));
}

TEST_CASE("XYVectors can have other XYvectors added to produce another XYVector") {
    View::XYVector v;
    const View::NormalizedXYVector v_n_xy;
    const View::XYVector v_xy;

    using converted_type_3 = decltype(v + v_n_xy);
    using converted_type_4 = decltype(v + v_xy);
    using required_type = View::XYVector;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_3, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_4, required_type>));
}
TEST_CASE("XYVectors can have other 3D vectors added to produce another Vector") {
    View::XYVector v;
    const View::Vector v_v;
    const View::NormalizedVector v_n;

    using converted_type_1 = decltype(v + v_v);
    using converted_type_2 = decltype(v + v_n);
    using required_type = View::Vector;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYVectors in different spaces cannot be added") {
    View::XYVector v;
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

TEST_CASE("XYVectors cannot have points added") {
    const View::XYVector v;
    const View::Point p;
    const View::Point p_xy;

    using converted_type_1 = decltype(v + p);
    using converted_type_2 = decltype(v + p_xy);
    using required_type = StaticAssert::invalid_point_to_vector_addition;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
}
#endif

TEST_CASE("XYVectors can be scaled") {
    View::XYVector v(1, 2);
    v *= 2;
    CHECK(v == View::Vector(2, 4, 6));
}

TEST_CASE("XYVectors cannot be crossed in place") {
    View::XYVector v;
    const View::Vector v_v;
    const View::NormalizedVector v_n;
    const View::NormalizedXYVector v_n_xy;
    const View::XYVector v_xy;

    using converted_type_1 = decltype(v *= v_v);
    using converted_type_2 = decltype(v *= v_n);
    using converted_type_3 = decltype(v *= v_n_xy);
    using converted_type_4 = decltype(v *= v_xy);
    using required_type = StaticAssert::invalid_XYVector_in_place_cross;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_3, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_4, required_type>));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYVectors in different spaces cannot be crossed in place") {
    Image::XYVector v;
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

TEST_CASE("XYVectors can have Vectors crossed using star") {
    const Image::XYVector v(0, 1);
    const Image::Vector v2(1, 0, 0);
    auto v3 = v * v2;
    CHECK(v3 == Image::Vector(0, 0, -1));
}
TEST_CASE("XYVectors can have NormalizedVector crossed using star") {
    const Image::XYVector v(0, 1);
    const Image::NormalizedVector v2(1, 0, 0);
    auto v3 = v * v2;
    CHECK(v3 == Image::Vector(0, 0, -1));
}
TEST_CASE("XYVectors can have NormalizedXYVector crossed using star") {
    const Image::XYVector v(0, 1);
    const Image::NormalizedXYVector v2(1, 0);
    auto v3 = v * v2;
    CHECK(v3 == Image::Vector(0, 0, -1));
}
TEST_CASE("XYVectors can have XYVector crossed using star") {
    const Image::XYVector v(0, 1);
    const Image::XYVector v2(1, 0);
    auto v3 = v * v2;
    CHECK(v3 == Image::Vector(0, 0, -1));
}
TEST_CASE("XYVectors can have other vectors crossed using star to produce another Vector") {
    View::XYVector v;
    const View::Vector v_v;
    const View::NormalizedVector v_n;
    const View::NormalizedXYVector v_n_xy;
    const View::XYVector v_xy;

    using converted_type_1 = decltype(v * v_v);
    using converted_type_2 = decltype(v * v_n);
    using converted_type_3 = decltype(v * v_n_xy);
    using converted_type_4 = decltype(v * v_xy);
    using required_type = View::Vector;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_3, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_4, required_type>));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYVectors in different spaces cannot be crossed using star") {
    View::XYVector v;
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

TEST_CASE("XYVectors can have Vectors crossed") {
    const Image::XYVector v(0, 1);
    const Image::Vector v2(1, 0, 0);
    auto v3 = v.Cross(v2);
    CHECK(v3 == Image::Vector(0, 0, -1));
}
TEST_CASE("XYVectors can have NormalizedVector crossed") {
    const Image::XYVector v(0, 1);
    const Image::NormalizedVector v2(1, 0, 0);
    auto v3 = v.Cross(v2);
    CHECK(v3 == Image::Vector(0, 0, -1));
}
TEST_CASE("XYVectors can have NormalizedXYVector crossed") {
    const Image::XYVector v(0, 1);
    const Image::NormalizedXYVector v2(1, 0);
    auto v3 = v.Cross(v2);
    CHECK(v3 == Image::Vector(0, 0, -1));
}
TEST_CASE("XYVectors can have XYVector crossed") {
    const Image::XYVector v(0, 1);
    const Image::XYVector v2(1, 0);
    auto v3 = v.Cross(v2);
    CHECK(v3 == Image::Vector(0, 0, -1));
}
TEST_CASE("XYVectors can have other vectors crossed to produce another Vector") {
    View::XYVector v;
    const View::Vector v_v;
    const View::NormalizedVector v_n;
    const View::NormalizedXYVector v_n_xy;
    const View::XYVector v_xy;

    using converted_type_1 = decltype(v.Cross(v_v));
    using converted_type_2 = decltype(v.Cross(v_n));
    using converted_type_3 = decltype(v.Cross(v_n_xy));
    using converted_type_4 = decltype(v.Cross(v_xy));
    using required_type = View::Vector;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_3, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_4, required_type>));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYVectors in different spaces cannot be crossed") {
    View::XYVector v;
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

TEST_CASE("XYVectors and Vectors can be dotted") {
    const View::XYVector v(3, 4);
    const View::Vector v2(1, 0, 0);
    const auto dot = v.Dot(v2);
    CHECK(dot == 3);
}
TEST_CASE("XYVectors and NormalizedVector can be dotted") {
    const View::XYVector v(3, 4);
    const View::NormalizedVector v2(1, 0, 0);
    const auto dot = v.Dot(v2);
    CHECK(dot == 3);
}
TEST_CASE("XYVectors and NormalizedXYVector can be dotted") {
    const View::XYVector v(3, 4);
    const View::NormalizedXYVector v2(1, 0);
    const auto dot = v.Dot(v2);
    CHECK(dot == 3);
}
TEST_CASE("XYVectors and XYVector can be dotted") {
    const View::XYVector v(3, 4);
    const View::XYVector v2(1, 0);
    const auto dot = v.Dot(v2);
    CHECK(dot == 3);
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYVectors from different spaces cannot be dotted") {
    View::XYVector v;
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

TEST_CASE("XYVectors can be normalized") {
    const Image::XYVector v(3, 4);
    const auto v_norm = v.Norm();
    // Mag of v = sqrt(3*3 + 4*4) = 5
    CHECK(v_norm == Image::NormalizedXYVector(3.0 / 5, 4.0 / 5));
}
TEST_CASE("XYVectors can be normalized to produce a NormalizedXYVector") {
    const View::XYVector v;
    using converted_type = decltype(v.Norm());
    using required_type = View::NormalizedXYVector;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
TEST_CASE("Zero size XYVectors cannot be normalized") {
    const Image::XYVector v(0, 0);
    CHECK_THROWS_AS(v.Norm(), std::invalid_argument);
}
TEST_CASE("Zero size XYVectors throw the correct message when you try and normalise them.") {
    const Image::XYVector v(0, 0);
    CHECK_THROWS_WITH(v.Norm(), "Zero-sized normal vectors are not allowed");
}

TEST_CASE("XYVectors can be converted from one space to another ignoring translation") {
    const TransformManager tm;
    const View::XYVector v_view(1, 0);
    auto v_patient = v_view.ConvertTo<Data>(tm);
    CHECK(v_patient == Data::Vector(15, 16, 17));
}
TEST_CASE("XYVectors can be converted from one space to another to produce a Vector") {
    const TransformManager tm;
    const View::XYVector v_view;
    using converted_type = decltype(v_view.ConvertTo<Data>(tm));
    using required_type = Data::Vector;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYVectors cannot be converted to the same space") {
    const TransformManager tm;
    const View::XYVector v;
    using converted_type = decltype(v.ConvertTo<View>(tm));
    using required_type = StaticAssert::invalid_same_space_conversion;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

TEST_CASE("XYVectors support mag") {
    const Image::XYVector v(3, 4);
    // 5 = sqrt(3*3 + 4*4)
    CHECK(v.Mag().get() == 5);
}
TEST_CASE("XYVector Mag is strongly typed") {
    const Image::XYVector v(3, 4);
    const Millimetres m{ 0 };
    CHECK(typeid(v.Mag()).name() == typeid(m).name());
}
TEST_CASE("XYVectors support Mag_double") {
    const Image::XYVector v(3, 4);
    // 5 = sqrt(3*3 + 4*4)
    CHECK(v.Mag_double() == 5);
}

TEST_CASE("XYVectors can be streamed") {
    const View::XYVector v(1.2, 2.3);
    std::stringstream stream;
    stream << v;
    CHECK(stream.str() == std::string("View::XYVector (1.2, 2.3)"));
}

