#include "ExternalIncludes.h"
#include "SpaceHelpers.h"
#include "ExampleTransformManager.h"

using namespace Space;

TEST_CASE("Vectors can be constructed")
{
    View::Vector v;
}
TEST_CASE("Vectors have zero value by default")
{
    View::Vector v;
    CHECK(v[0] == 0);
    CHECK(v[1] == 0);
    CHECK(v[2] == 0);
}
TEST_CASE("Vectors can be constructed from implementation")
{
    TestVector impl;
    impl.m_values[0] = 3;
    impl.m_values[1] = 2;
    impl.m_values[2] = 1;
    const Data::Vector v(impl);
    CHECK(v.X() == 3);
    CHECK(v.Y() == 2);
    CHECK(v.Z() == 1);
}
TEST_CASE("Vectors Can Be Constructed From Three Doubles")
{
    const Data::Vector v(4, 5, 6);
    CHECK(v.X() == 4);
    CHECK(v.Y() == 5);
    CHECK(v.Z() == 6);
}
TEST_CASE("Vectors can be created using initalizer lists of three numbers")
{
    View::Vector v{1, 2, 4};
    CHECK(v[0] == 1);
    CHECK(v[1] == 2);
    CHECK(v[2] == 4);
}

TEST_CASE("Vectors can be assigned from a vector")
{
    const View::Vector v2(1, 2, 3);
    const View::Vector v = v2;
    CHECK(v.X() == 1);
    CHECK(v.Y() == 2);
    CHECK(v.Z() == 3);
}

TEST_CASE("Vectors can be explicitly cast to the implementation")
{
    const Data::Vector v(1, 2, 3);
    auto impl = static_cast<TestVector>(v);
    CHECK(impl.m_values[0] == 1);
    CHECK(impl.m_values[1] == 2);
    CHECK(impl.m_values[2] == 3);
}

TEST_CASE("Vectors support element access by name")
{
    const Image::Vector v(2, 3, 4);
    CHECK(v.X() == 2);
    CHECK(v.Y() == 3);
    CHECK(v.Z() == 4);
}

TEST_CASE("Vector elements can be modified by name")
{
    Image::Vector v(2, 3, 4);
    v.SetX(10);
    v.SetY(20);
    v.SetZ(30);
    CHECK(v.X() == 10);
    CHECK(v.Y() == 20);
    CHECK(v.Z() == 30);
}

TEST_CASE("Vectors support const begin and end")
{
    const Image::Vector v(2, 3, 4);
    std::vector<double> values;
    std::copy(v.cbegin(), v.cend(), std::back_inserter(values));
    CHECK(values.size() == 3);
    CHECK(values[0] == 2);
    CHECK(values[1] == 3);
    CHECK(values[2] == 4);
}
TEST_CASE("Vectors support non-const begin and end")
{
    Image::Vector v(2, 3, 4);
    std::fill(v.begin(), v.end(), 3);
    CHECK(v.X() == 3);
    CHECK(v.Y() == 3);
    CHECK(v.Z() == 3);
}

TEST_CASE("Vectors support element access by random access")
{
    const Image::Vector v(2, 3, 4);
    CHECK(v[0] == 2);
    CHECK(v[1] == 3);
    CHECK(v[2] == 4);
}
TEST_CASE("Vectors throw if random access is too high")
{
    const Image::Vector v;
    CHECK_THROWS_AS(v[3], std::invalid_argument);
}
TEST_CASE("Vectors throw with the right message if random access is too high")
{
    const Image::Vector v;
    CHECK_THROWS_WITH(v[3], "Index is out of range");
}

TEST_CASE("Vectors support element access by at")
{
    const Image::Vector v(2, 3, 4);
    CHECK(v.at<0>() == 2);
    CHECK(v.at<1>() == 3);
    CHECK(v.at<2>() == 4);
}
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Vectors at does not compile if too low")
{
    const Image::Vector v;
    using converted_type = decltype(v.at<-1>());
    using required_type = StaticAssert::invalid_at_access;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
TEST_CASE("Vectors at does not compile if too high")
{
    const Image::Vector v;
    using converted_type = decltype(v.at<3>());
    using required_type = StaticAssert::invalid_at_access;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

TEST_CASE("Vector and Vector can be compared using equal: same")
{
    const View::Vector v(1, 0, 0);
    const View::Vector v2(1, 0, 0);
    CHECK(v == v2);
}
TEST_CASE("Vector and NormalizedVector can be compared using equal: same")
{
    const View::Vector v(1, 0, 0);
    const View::NormalizedVector v2(1, 0, 0);
    CHECK(v == v2);
}
TEST_CASE("Vector and NormalizedXYVector can be compared using equal: same")
{
    const View::Vector v(1, 0, 0);
    const View::NormalizedXYVector v2(1, 0);
    CHECK(v == v2);
}
TEST_CASE("Vector and XYVector can be compared using equal: same")
{
    const View::Vector v(1, 0, 0);
    const View::XYVector v2(1, 0);
    CHECK(v == v2);
}

TEST_CASE("Vector and Vector can be compared using equal: different")
{
    const View::Vector v(1, 0, 1);
    const View::Vector v2(1, 0, 0);
    CHECK(!(v == v2));
}
TEST_CASE("Vector and NormalizedVector can be compared using equal: different")
{
    const View::Vector v(1, 0, 1);
    const View::NormalizedVector v2(1, 0, 0);
    CHECK(!(v == v2));
}
TEST_CASE("Vector and NormalizedXYVector can be compared using equal: different")
{
    const View::Vector v(1, 0, 1);
    const View::NormalizedXYVector v2(1, 0);
    CHECK(!(v == v2));
}
TEST_CASE("Vector and XYVector can be compared using equal: different")
{
    const View::Vector v(1, 0, 1);
    const View::XYVector v2(1, 0);
    CHECK(!(v == v2));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Vectors from different spaces cannot be compared using equal")
{
    const View::Vector v;
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

TEST_CASE("Vectors and Points cannot be compared using equal")
{
    const View::Vector v;
    const View::Point p;
    const View::Point p_xy;

    using converted_type_1 = decltype(v == p);
    using converted_type_2 = decltype(v == p_xy);
    using required_type = StaticAssert::invalid_point_vector_equality;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
}
#endif

TEST_CASE("Vector and Vector can be compared using inequality: same")
{
    const View::Vector v(1, 0, 0);
    const View::Vector v2(1, 0, 0);
    CHECK(!(v != v2));
}
TEST_CASE("Vector and NormalizedVector can be compared using inequality: same")
{
    const View::Vector v(1, 0, 0);
    const View::NormalizedVector v2(1, 0, 0);
    CHECK(!(v != v2));
}
TEST_CASE("Vector and NormalizedXYVector can be compared using inequality: same")
{
    const View::Vector v(1, 0, 0);
    const View::NormalizedXYVector v2(1, 0);
    CHECK(!(v != v2));
}
TEST_CASE("Vector and XYVector can be compared using inequality: same")
{
    const View::Vector v(1, 0, 0);
    const View::XYVector v2(1, 0);
    CHECK(!(v != v2));
}

TEST_CASE("Vector and Vector can be compared using inequality: different")
{
    const View::Vector v(1, 0, 1);
    const View::Vector v2(1, 0, 0);
    CHECK(v != v2);
}
TEST_CASE("Vector and NormalizedVector can be compared using inequality: different")
{
    const View::Vector v(1, 0, 1);
    const View::NormalizedVector v2(1, 0, 0);
    CHECK(v != v2);
}
TEST_CASE("Vector and NormalizedXYVector can be compared using inequality: different")
{
    const View::Vector v(1, 0, 1);
    const View::NormalizedXYVector v2(1, 0);
    CHECK(v != v2);
}
TEST_CASE("Vector and XYVector can be compared using inequality: different")
{
    const View::Vector v(1, 0, 1);
    const View::XYVector v2(1, 0);
    CHECK(v != v2);
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Vectors from different spaces cannot be compared using inequality")
{
    const View::Vector v;
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

TEST_CASE("Vectors and Points cannot be compared using inequality")
{
    const View::Vector v;
    const View::Point p;
    const View::Point p_xy;

    using converted_type_1 = decltype(v != p);
    using converted_type_2 = decltype(v != p_xy);
    using required_type = StaticAssert::invalid_point_vector_equality;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
}
#endif

TEST_CASE("Vectors can have Vectors subtracted in place")
{
    Image::Vector v(1, 2, 3);
    const Image::Vector v2(1, 0, 0);
    v -= v2;
    CHECK(v == Image::Vector(0, 2, 3));
}
TEST_CASE("Vectors can have NormalizedVectors subtracted in place")
{
    Image::Vector v(1, 2, 3);
    const Image::NormalizedVector v2(1, 0, 0);
    v -= v2;
    CHECK(v == Image::Vector(0, 2, 3));
}
TEST_CASE("Vectors can have NormalizedXYVectors subtracted in place")
{
    Image::Vector v(1, 2, 3);
    const Image::NormalizedXYVector v2(1, 0);
    v -= v2;
    CHECK(v == Image::Vector(0, 2, 3));
}
TEST_CASE("Vectors can have XYVectors subtracted in place")
{
    Image::Vector v(1, 2, 3);
    const Image::NormalizedXYVector v2(1, 0);
    v -= v2;
    CHECK(v == Image::Vector(0, 2, 3));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Vectors in different spaces cannot be subtracted in place")
{
    View::Vector v;
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

TEST_CASE("Vectors can have Vectors subtracted")
{
    const Image::Vector v(1, 2, 3);
    const Image::Vector v2(1, 0, 0);
    auto v3 = v - v2;
    CHECK(v3 == Image::Vector(0, 2, 3));
}
TEST_CASE("Vectors can have NormalizedVector subtracted")
{
    const Image::Vector v(1, 2, 3);
    const Image::NormalizedVector v2(1, 0, 0);
    auto v3 = v - v2;
    CHECK(v3 == Image::Vector(0, 2, 3));
}
TEST_CASE("Vectors can have NormalizedXYVector subtracted")
{
    const Image::Vector v(1, 2, 3);
    const Image::NormalizedXYVector v2(1, 0);
    auto v3 = v - v2;
    CHECK(v3 == Image::Vector(0, 2, 3));
}
TEST_CASE("Vectors can have XYVector subtracted")
{
    const Image::Vector v(1, 2, 3);
    const Image::XYVector v2(1, 0);
    auto v3 = v - v2;
    CHECK(v3 == Image::Vector(0, 2, 3));
}
TEST_CASE("Vectors can have other vectors subtracted to produce another Vector")
{
    View::Vector v;
    const View::Vector v_v;
    const View::NormalizedVector v_n;
    const View::NormalizedXYVector v_n_xy;
    const View::XYVector v_xy;

    using converted_type_1 = decltype(v - v_v);
    using converted_type_2 = decltype(v - v_n);
    using converted_type_3 = decltype(v - v_n_xy);
    using converted_type_4 = decltype(v - v_xy);
    using required_type = View::Vector;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_3, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_4, required_type>));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Vectors in different spaces cannot be subtracted")
{
    View::Vector v;
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

TEST_CASE("Vectors cannot have points subtracted")
{
    const View::Vector v;
    const View::Point p;
    const View::Point p_xy;

    using converted_type_1 = decltype(v - p);
    using converted_type_2 = decltype(v - p_xy);
    using required_type = StaticAssert::invalid_point_from_vector_subtraction;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
}
#endif

TEST_CASE("Vectors can have Vectors added in place")
{
    Image::Vector v(1, 2, 3);
    const Image::Vector v2(1, 0, 0);
    v += v2;
    CHECK(v == Image::Vector(2, 2, 3));
}
TEST_CASE("Vectors can have NormalizedVectors added in place")
{
    Image::Vector v(1, 2, 3);
    const Image::NormalizedVector v2(1, 0, 0);
    v += v2;
    CHECK(v == Image::Vector(2, 2, 3));
}
TEST_CASE("Vectors can have NormalizedXYVectors added in place")
{
    Image::Vector v(1, 2, 3);
    const Image::NormalizedXYVector v2(1, 0);
    v += v2;
    CHECK(v == Image::Vector(2, 2, 3));
}
TEST_CASE("Vectors can have XYVectors added in place")
{
    Image::Vector v(1, 2, 3);
    const Image::NormalizedXYVector v2(1, 0);
    v += v2;
    CHECK(v == Image::Vector(2, 2, 3));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Vectors in different spaces cannot be added in place")
{
    View::Vector v;
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

TEST_CASE("Vectors can have Vectors added")
{
    const Image::Vector v(1, 2, 3);
    const Image::Vector v2(1, 0, 0);
    auto v3 = v + v2;
    CHECK(v3 == Image::Vector(2, 2, 3));
}
TEST_CASE("Vectors can have NormalizedVector added")
{
    const Image::Vector v(1, 2, 3);
    const Image::NormalizedVector v2(1, 0, 0);
    auto v3 = v + v2;
    CHECK(v3 == Image::Vector(2, 2, 3));
}
TEST_CASE("Vectors can have NormalizedXYVector added")
{
    const Image::Vector v(1, 2, 3);
    const Image::NormalizedXYVector v2(1, 0);
    auto v3 = v + v2;
    CHECK(v3 == Image::Vector(2, 2, 3));
}
TEST_CASE("Vectors can have XYVector added")
{
    const Image::Vector v(1, 2, 3);
    const Image::XYVector v2(1, 0);
    auto v3 = v + v2;
    CHECK(v3 == Image::Vector(2, 2, 3));
}
TEST_CASE("Vectors can have other vectors added to produce another Vector")
{
    View::Vector v;
    const View::Vector v_v;
    const View::NormalizedVector v_n;
    const View::NormalizedXYVector v_n_xy;
    const View::XYVector v_xy;

    using converted_type_1 = decltype(v + v_v);
    using converted_type_2 = decltype(v + v_n);
    using converted_type_3 = decltype(v + v_n_xy);
    using converted_type_4 = decltype(v + v_xy);
    using required_type = View::Vector;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_3, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_4, required_type>));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Vectors in different spaces cannot be added")
{
    View::Vector v;
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

TEST_CASE("Vectors cannot have points added")
{
    const View::Vector v;
    const View::Point p;
    const View::Point p_xy;

    using converted_type_1 = decltype(v + p);
    using converted_type_2 = decltype(v + p_xy);
    using required_type = StaticAssert::invalid_point_to_vector_addition;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
}
#endif

TEST_CASE("Vectors can be scaled")
{
    View::Vector v(1, 2, 3);
    v *= 2;
    CHECK(v == View::Vector(2, 4, 6));
}

TEST_CASE("Vectors can have Vectors crossed in place")
{
    Image::Vector v(0, 1, 0);
    const Image::Vector v2(1, 0, 0);
    v *= v2;
    CHECK(v == Image::Vector(0, 0, -1));
}
TEST_CASE("Vectors can have NormalizedVectors crossed in place")
{
    Image::Vector v(0, 1, 0);
    const Image::NormalizedVector v2(1, 0, 0);
    v *= v2;
    CHECK(v == Image::Vector(0, 0, -1));
}
TEST_CASE("Vectors can have NormalizedXYVectors crossed in place")
{
    Image::Vector v(0, 1, 0);
    const Image::NormalizedXYVector v2(1, 0);
    v *= v2;
    CHECK(v == Image::Vector(0, 0, -1));
}
TEST_CASE("Vectors can have XYVectors crossed in place")
{
    Image::Vector v(0, 1, 0);
    const Image::NormalizedXYVector v2(1, 0);
    v *= v2;
    CHECK(v == Image::Vector(0, 0, -1));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Vectors in different spaces cannot be crossed in place")
{
    Image::Vector v;
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

TEST_CASE("Vectors can have Vectors crossed using star")
{
    const Image::Vector v(0, 1, 0);
    const Image::Vector v2(1, 0, 0);
    auto v3 = v * v2;
    CHECK(v3 == Image::Vector(0, 0, -1));
}
TEST_CASE("Vectors can have NormalizedVector crossed using star")
{
    const Image::Vector v(0, 1, 0);
    const Image::NormalizedVector v2(1, 0, 0);
    auto v3 = v * v2;
    CHECK(v3 == Image::Vector(0, 0, -1));
}
TEST_CASE("Vectors can have NormalizedXYVector crossed using star")
{
    const Image::Vector v(0, 1, 0);
    const Image::NormalizedXYVector v2(1, 0);
    auto v3 = v * v2;
    CHECK(v3 == Image::Vector(0, 0, -1));
}
TEST_CASE("Vectors can have XYVector crossed using star")
{
    const Image::Vector v(0, 1, 0);
    const Image::XYVector v2(1, 0);
    auto v3 = v * v2;
    CHECK(v3 == Image::Vector(0, 0, -1));
}
TEST_CASE("Vectors can have other vectors crossed using star to produce another Vector")
{
    View::Vector v;
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
TEST_CASE("Vectors in different spaces cannot be crossed using star")
{
    View::Vector v;
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

TEST_CASE("Vectors can have Vectors crossed")
{
    const Image::Vector v(0, 1, 0);
    const Image::Vector v2(1, 0, 0);
    auto v3 = v.Cross(v2);
    CHECK(v3 == Image::Vector(0, 0, -1));
}
TEST_CASE("Vectors can have NormalizedVector crossed")
{
    const Image::Vector v(0, 1, 0);
    const Image::NormalizedVector v2(1, 0, 0);
    auto v3 = v.Cross(v2);
    CHECK(v3 == Image::Vector(0, 0, -1));
}
TEST_CASE("Vectors can have NormalizedXYVector crossed")
{
    const Image::Vector v(0, 1, 0);
    const Image::NormalizedXYVector v2(1, 0);
    auto v3 = v.Cross(v2);
    CHECK(v3 == Image::Vector(0, 0, -1));
}
TEST_CASE("Vectors can have XYVector crossed")
{
    const Image::Vector v(0, 1, 0);
    const Image::XYVector v2(1, 0);
    auto v3 = v.Cross(v2);
    CHECK(v3 == Image::Vector(0, 0, -1));
}
TEST_CASE("Vectors can have other vectors crossed to produce another Vector")
{
    View::Vector v;
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
TEST_CASE("Vectors in different spaces cannot be crossed")
{
    View::Vector v;
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

TEST_CASE("Vectors and Vectors can be dotted")
{
    const View::Vector v(3, 4, 5);
    const View::Vector v2(1, 0, 0);
    const auto dot = v.Dot(v2);
    CHECK(dot == 3);
}
TEST_CASE("Vectors and NormalizedVector can be dotted")
{
    const View::Vector v(3, 4, 5);
    const View::NormalizedVector v2(1, 0, 0);
    const auto dot = v.Dot(v2);
    CHECK(dot == 3);
}
TEST_CASE("Vectors and NormalizedXYVector can be dotted")
{
    const View::Vector v(3, 4, 5);
    const View::NormalizedXYVector v2(1, 0);
    const auto dot = v.Dot(v2);
    CHECK(dot == 3);
}
TEST_CASE("Vectors and XYVector can be dotted")
{
    const View::Vector v(3, 4, 5);
    const View::XYVector v2(1, 0);
    const auto dot = v.Dot(v2);
    CHECK(dot == 3);
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Vectors from different spaces cannot be dotted")
{
    View::Vector v;
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

TEST_CASE("Vectors can have their z-value removed")
{
    const View::Vector v(2, 3, 4);
    const auto v2 = v.ToXY();
    CHECK(v2 == View::XYVector(2, 3));
}
TEST_CASE("Vectors can have their z-value removed to produce a XYVector")
{
    const View::Vector v;
    using converted_type = decltype(v.ToXY());
    using required_type = View::XYVector;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
TEST_CASE("Vectors from Spaces that do not support XY cannot have their z-value removed")
{
    const Volume::Vector v;
    using converted_type = decltype(v.ToXY());
    using required_type = StaticAssert::XYVector_not_supported;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}

TEST_CASE("Vectors can be normalized")
{
    const Image::Vector v(0, 3, 4);
    const auto v_norm = v.Norm();
    // Mag of v = sqrt(3*3 + 4*4) = 5
    CHECK(v_norm == Image::NormalizedVector(0, 3.0 / 5, 4.0 / 5));
}
TEST_CASE("Vectors can be normalized to produce a NormalizedVector")
{
    const View::Vector v;
    using converted_type = decltype(v.Norm());
    using required_type = View::NormalizedVector;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
TEST_CASE("Zero size vectors cannot be normalized")
{
    const Image::Vector v(0, 0, 0);
    CHECK_THROWS_AS(v.Norm(), std::invalid_argument);
}
TEST_CASE("Zero size vectors throw the correct message when you try and normalise them.")
{
    const Image::Vector v(0, 0, 0);
    CHECK_THROWS_WITH(v.Norm(), "Zero-sized normal vectors are not allowed");
}

TEST_CASE("Vectors can be converted from one space to another ignoring translation")
{
    const TransformManager tm;
    const View::Vector v_view(1, 0, 0);
    auto v_patient = v_view.ConvertTo<Data>(tm);
    CHECK(v_patient == Data::Vector(15, 16, 17));
}
TEST_CASE("Vectors can be converted from one space to another to produce a Vector")
{
    const TransformManager tm;
    const View::Vector v_view;
    using converted_type = decltype(v_view.ConvertTo<Data>(tm));
    using required_type = Data::Vector;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Vectors cannot be converted to the same space")
{
    const TransformManager tm;
    const View::Vector v;
    using converted_type = decltype(v.ConvertTo<View>(tm));
    using required_type = StaticAssert::invalid_same_space_conversion;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

TEST_CASE("Vectors support mag")
{
    const Image::Vector v(0, 3, 4);
    // 5 = sqrt(3*3 + 4*4)
    CHECK(v.Mag().get() == 5);
}
TEST_CASE("Vector Mag is strongly typed")
{
    const Image::Vector v(0, 3, 4);
    const Millimetres m{0};
    CHECK(typeid(v.Mag()).name() == typeid(m).name());
}
TEST_CASE("Vectors support Mag_double")
{
    const Image::Vector v(0, 3, 4);
    // 5 = sqrt(3*3 + 4*4)
    CHECK(v.Mag_double() == 5);
}

TEST_CASE("Vectors can be streamed")
{
    const View::Vector v(1.2, 2.3, 3.4);
    std::stringstream stream;
    stream << v;
    CHECK(stream.str() == std::string("View::Vector (1.2, 2.3, 3.4)"));
}
