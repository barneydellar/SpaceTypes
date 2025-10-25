#include "ExternalIncludes.h"
#include "SpaceHelpers.h"
#include "ExampleTransformManager.h"

using namespace Space;

TEST_CASE("Points can be constructed") {
    View::Point p;
}
TEST_CASE("Points have zero value by default") {
    View::Point p;
    CHECK(p[0] == 0);
    CHECK(p[1] == 0);
    CHECK(p[2] == 0);
}
TEST_CASE("Points can be constructed from implementation") {
    TestVector impl;
    impl.m_values[0] = 3;
    impl.m_values[1] = 2;
    impl.m_values[2] = 1;
    const Data::Point p(impl);
    CHECK(p.X() == 3);
    CHECK(p.Y() == 2);
    CHECK(p.Z() == 1);
}
TEST_CASE("Points Can Be Constructed From Three Doubles") {
    const Data::Point p(4, 5, 6);
    CHECK(p.X() == 4);
    CHECK(p.Y() == 5);
    CHECK(p.Z() == 6);
}
TEST_CASE("Points can be created using initalizer lists of three numbers") {
    View::Point p{ 1, 2, 4 };
    CHECK(p[0] == 1);
    CHECK(p[1] == 2);
    CHECK(p[2] == 4);
}

TEST_CASE("Points can be assigned from a point") {
    const View::Point p2(1, 2, 3);
    const View::Point p = p2;
    CHECK(p.X() == 1);
    CHECK(p.Y() == 2);
    CHECK(p.Z() == 3);
}

TEST_CASE("Points can be explicitly cast to the implementation") {
    const Data::Point p(1, 2, 3);
    auto impl = static_cast<TestVector>(p);
    CHECK(impl.m_values[0] == 1);
    CHECK(impl.m_values[1] == 2);
    CHECK(impl.m_values[2] == 3);
}

TEST_CASE("Points support element access by name") {
    const Image::Point p(2, 3, 4);
    CHECK(p.X() == 2);
    CHECK(p.Y() == 3);
    CHECK(p.Z() == 4);
}

TEST_CASE("Point elements can be modified by name") {
    Image::Point p(2, 3, 4);
    p.SetX(10);
    p.SetY(20);
    p.SetZ(30);
    CHECK(p.X() == 10);
    CHECK(p.Y() == 20);
    CHECK(p.Z() == 30);
}

TEST_CASE("Points support const begin and end") {
    const Image::Point p(2, 3, 4);
    std::vector<double> values;
    std::copy(p.cbegin(), p.cend(), std::back_inserter(values));
    CHECK(values.size() == 3);
    CHECK(values[0] == 2);
    CHECK(values[1] == 3);
    CHECK(values[2] == 4);
}
TEST_CASE("Points support non-const begin and end") {
    Image::Point p(2, 3, 4);
    std::fill(p.begin(), p.end(), 3);
    CHECK(p.X() == 3);
    CHECK(p.Y() == 3);
    CHECK(p.Z() == 3);
}

TEST_CASE("Points support element access by random access") {
    const Image::Point p(2, 3, 4);
    CHECK(p[0] == 2);
    CHECK(p[1] == 3);
    CHECK(p[2] == 4);
}
TEST_CASE("Points throw if random access is too high") {
    const Image::Point p;
    CHECK_THROWS_AS(p[3], std::invalid_argument);
}
TEST_CASE("Points throw with the right message if random access is too high") {
    const Image::Point p;
    CHECK_THROWS_WITH(p[3], "Index is out of range");
}

TEST_CASE("Points support element access by at") {
    const Image::Point p(2, 3, 4);
    CHECK(p.at<0>() == 2);
    CHECK(p.at<1>() == 3);
    CHECK(p.at<2>() == 4);
}
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Points at does not compile if too low") {
    const Image::Point p;
    using converted_type = decltype(p.at<-1>());
    using required_type = StaticAssert::invalid_at_access;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
TEST_CASE("Points at does not compile if too high") {
    const Image::Point p;
    using converted_type = decltype(p.at<3>());
    using required_type = StaticAssert::invalid_at_access;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

TEST_CASE("Point and Point can be compared using equal: same") {
    const View::Point p(1, 0, 0);
    const View::Point p2(1, 0, 0);
    CHECK(p == p2);
}
TEST_CASE("Point and XYPoint can be compared using equal: same") {
    const View::Point p(1, 0, 0);
    const View::XYPoint p2(1, 0);
    CHECK(p == p2);
}

TEST_CASE("Point and Vector can be compared using equal: different") {
    const View::Point p(1, 0, 1);
    const View::Point p2(1, 0, 0);
    CHECK(!(p == p2));
}
TEST_CASE("Point and XYPoint can be compared using equal: different") {
    const View::Point p(1, 0, 1);
    const View::XYPoint p2(1, 0);
    CHECK(!(p == p2));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Points from different spaces cannot be compared using equal") {
    const View::Point p;
    const Image::Point p_p;
    const Image::XYPoint p_xy;

    using converted_type_1 = decltype(p == p_p);
    using converted_type_2 = decltype(p == p_xy);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
}

TEST_CASE("Points and Vectors cannot be compared using equal") {
    const Image::Point p;
    const Image::Vector v_v;
    const Image::NormalizedVector v_n;
    const Image::NormalizedXYVector v_n_xy;
    const Image::XYVector v_xy;

    using converted_type_1 = decltype(p == v_v);
    using converted_type_2 = decltype(p == v_n);
    using converted_type_3 = decltype(p == v_n_xy);
    using converted_type_4 = decltype(p == v_xy);
    using required_type = StaticAssert::invalid_point_vector_equality;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_3, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_4, required_type>));
}
#endif

TEST_CASE("Point and Point can be compared using inequality: same") {
    const View::Point p(1, 0, 0);
    const View::Point p2(1, 0, 0);
    CHECK(!(p != p2));
}
TEST_CASE("Point and XYPoint can be compared using inequality: same") {
    const View::Point p(1, 0, 0);
    const View::XYPoint p2(1, 0);
    CHECK(!(p != p2));
}

TEST_CASE("Point and Point can be compared using inequality: different") {
    const View::Point p(1, 0, 1);
    const View::Point p2(1, 0, 0);
    CHECK(p != p2);
}
TEST_CASE("Point and XYPoint can be compared using inequality: different") {
    const View::Point p(1, 0, 1);
    const View::XYPoint p2(1, 0);
    CHECK(p != p2);
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Points from different spaces cannot be compared using inequality") {
    const View::Point p;
    const Image::Point p_p;
    const Image::XYPoint p_xy;

    using converted_type_1 = decltype(p != p_p);
    using converted_type_2 = decltype(p != p_xy);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
}

TEST_CASE("Points and Vectors cannot be compared using inequality") {
    const View::Point p;
    const View::Vector v_v;
    const View::NormalizedVector v_n;
    const View::NormalizedXYVector v_n_xy;
    const View::XYVector v_xy;

    using converted_type_1 = decltype(p != v_v);
    using converted_type_2 = decltype(p != v_n);
    using converted_type_3 = decltype(p != v_n_xy);
    using converted_type_4 = decltype(p != v_xy);
    using required_type = StaticAssert::invalid_point_vector_equality;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_3, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_4, required_type>));
}
#endif

TEST_CASE("Points can have Vectors subtracted in place") {
    Image::Point p(1, 2, 3);
    const Image::Vector v2(1, 0, 0);
    p -= v2;
    CHECK(p == Image::Point(0, 2, 3));
}
TEST_CASE("Points can have NormalizedVectors subtracted in place") {
    Image::Point p(1, 2, 3);
    const Image::NormalizedVector v2(1, 0, 0);
    p -= v2;
    CHECK(p == Image::Point(0, 2, 3));
}
TEST_CASE("Points can have NormalizedXYVectors subtracted in place") {
    Image::Point p(1, 2, 3);
    const Image::NormalizedXYVector v2(1, 0);
    p -= v2;
    CHECK(p == Image::Point(0, 2, 3));
}
TEST_CASE("Points can have XYVectors subtracted in place") {
    Image::Point p(1, 2, 3);
    const Image::NormalizedXYVector v2(1, 0);
    p -= v2;
    CHECK(p == Image::Point(0, 2, 3));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Points and vectors in different spaces cannot be subtracted in place") {
    View::Point p;
    const Image::Vector v_v;
    const Image::NormalizedVector v_n;
    const Image::NormalizedXYVector v_n_xy;
    const Image::XYVector v_xy;

    using converted_type_1 = decltype(p -= v_v);
    using converted_type_2 = decltype(p -= v_n);
    using converted_type_3 = decltype(p -= v_n_xy);
    using converted_type_4 = decltype(p -= v_xy);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_3, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_4, required_type>));
}

TEST_CASE("Points cannot have other Points subtracted in place") {
    View::Point p;
    const View::Point p_p;
    const View::XYPoint p_xy;

    using converted_type_1 = decltype(p -= p_p);
    using converted_type_2 = decltype(p -= p_xy);
    using required_type = StaticAssert::invalid_point_from_vector_subtraction;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
}
#endif

TEST_CASE("Points can have Vectors subtracted") {
    const Image::Point p(1, 2, 3);
    const Image::Vector v2(1, 0, 0);
    auto v3 = p - v2;
    CHECK(v3 == Image::Point(0, 2, 3));
}
TEST_CASE("Points can have NormalizedVector subtracted") {
    const Image::Point p(1, 2, 3);
    const Image::NormalizedVector v2(1, 0, 0);
    auto v3 = p - v2;
    CHECK(v3 == Image::Point(0, 2, 3));
}
TEST_CASE("Points can have NormalizedXYVector subtracted") {
    const Image::Point p(1, 2, 3);
    const Image::NormalizedXYVector v2(1, 0);
    auto v3 = p - v2;
    CHECK(v3 == Image::Point(0, 2, 3));
}
TEST_CASE("Points can have XYVector subtracted") {
    const Image::Point p(1, 2, 3);
    const Image::XYVector v2(1, 0);
    auto v3 = p - v2;
    CHECK(v3 == Image::Point(0, 2, 3));
}
TEST_CASE("Points can have other vectors subtracted to produce another Point") {
    View::Point p;
    const View::Vector v_v;
    const View::NormalizedVector v_n;
    const View::NormalizedXYVector v_n_xy;
    const View::XYVector v_xy;

    using converted_type_1 = decltype(p - v_v);
    using converted_type_2 = decltype(p - v_n);
    using converted_type_3 = decltype(p - v_n_xy);
    using converted_type_4 = decltype(p - v_xy);
    using required_type = View::Point;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_3, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_4, required_type>));
}

TEST_CASE("Points can have Points subtracted") {
    const Image::Point p(1, 2, 3);
    const Image::Point p2(1, 0, 0);
    auto v = p - p2;
    CHECK(v == Image::Vector(0, 2, 3));
}
TEST_CASE("Points can have XYPoints subtracted") {
    const Image::Point p(1, 2, 3);
    const Image::XYPoint p2(1, 0);
    auto v = p - p2;
    CHECK(v == Image::Vector(0, 2, 3));
}
TEST_CASE("Points can have other Points subtracted to produce a Vector") {
    View::Point p;
    const View::Point p_p;
    const View::XYPoint p_xy;

    using converted_type_1 = decltype(p - p_p);
    using converted_type_2 = decltype(p - p_xy);
    using required_type = View::Vector;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Points cannot have vectors in different spaces subtracted") {
    View::Point p;
    const Image::Vector v_v;
    const Image::NormalizedVector v_n;
    const Image::NormalizedXYVector v_n_xy;
    const Image::XYVector v_xy;

    using converted_type_1 = decltype(p - v_v);
    using converted_type_2 = decltype(p - v_n);
    using converted_type_3 = decltype(p - v_n_xy);
    using converted_type_4 = decltype(p - v_xy);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_3, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_4, required_type>));
}

TEST_CASE("Points cannot have Points from other spaces subtracted") {
    Image::Point p;
    const View::Point p_p;
    const View::XYPoint p_xy;

    using converted_type_1 = decltype(p - p_p);
    using converted_type_2 = decltype(p - p_xy);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
}
#endif

TEST_CASE("Points can have Vectors added in place") {
    Image::Point p(1, 2, 3);
    const Image::Vector v2(1, 0, 0);
    p += v2;
    CHECK(p == Image::Point(2, 2, 3));
}
TEST_CASE("Points can have NormalizedVectors added in place") {
    Image::Point p(1, 2, 3);
    const Image::NormalizedVector v2(1, 0, 0);
    p += v2;
    CHECK(p == Image::Point(2, 2, 3));
}
TEST_CASE("Points can have NormalizedXYVectors added in place") {
    Image::Point p(1, 2, 3);
    const Image::NormalizedXYVector v2(1, 0);
    p += v2;
    CHECK(p == Image::Point(2, 2, 3));
}
TEST_CASE("Points can have XYVectors added in place") {
    Image::Point p(1, 2, 3);
    const Image::NormalizedXYVector v2(1, 0);
    p += v2;
    CHECK(p == Image::Point(2, 2, 3));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Points cannot have vectors in different spaces added in place") {
    View::Point p;
    const Image::Vector v_v;
    const Image::NormalizedVector v_n;
    const Image::NormalizedXYVector v_n_xy;
    const Image::XYVector v_xy;

    using converted_type_1 = decltype(p += v_v);
    using converted_type_2 = decltype(p += v_n);
    using converted_type_3 = decltype(p += v_n_xy);
    using converted_type_4 = decltype(p += v_xy);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_3, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_4, required_type>));
}

TEST_CASE("Points cannot have points in different spaces added in place") {
    View::Point p;
    const Image::Point p_p;
    const Image::XYPoint p_xy;

    using converted_type_1 = decltype(p += p_p);
    using converted_type_2 = decltype(p += p_xy);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
}
#endif

TEST_CASE("Points can have Vectors added") {
    const Image::Point p(1, 2, 3);
    const Image::Vector v2(1, 0, 0);
    auto v3 = p + v2;
    CHECK(v3 == Image::Point(2, 2, 3));
}
TEST_CASE("Points can have NormalizedVector added") {
    const Image::Point p(1, 2, 3);
    const Image::NormalizedVector v2(1, 0, 0);
    auto v3 = p + v2;
    CHECK(v3 == Image::Point(2, 2, 3));
}
TEST_CASE("Points can have NormalizedXYVector added") {
    const Image::Point p(1, 2, 3);
    const Image::NormalizedXYVector v2(1, 0);
    auto v3 = p + v2;
    CHECK(v3 == Image::Point(2, 2, 3));
}
TEST_CASE("Points can have XYVector added") {
    const Image::Point p(1, 2, 3);
    const Image::XYVector v2(1, 0);
    auto v3 = p + v2;
    CHECK(v3 == Image::Point(2, 2, 3));
}
TEST_CASE("Points can have other vectors added to produce another Point") {
    View::Point p;
    const View::Vector v_v;
    const View::NormalizedVector v_n;
    const View::NormalizedXYVector v_n_xy;
    const View::XYVector v_xy;

    using converted_type_1 = decltype(p + v_v);
    using converted_type_2 = decltype(p + v_n);
    using converted_type_3 = decltype(p + v_n_xy);
    using converted_type_4 = decltype(p + v_xy);
    using required_type = View::Point;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_3, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_4, required_type>));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Vectors in other spaces cannot be added") {
    View::Point p;
    const Image::Vector v_v;
    const Image::NormalizedVector v_n;
    const Image::NormalizedXYVector v_n_xy;
    const Image::XYVector v_xy;

    using converted_type_1 = decltype(p + v_v);
    using converted_type_2 = decltype(p + v_n);
    using converted_type_3 = decltype(p + v_n_xy);
    using converted_type_4 = decltype(p + v_xy);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_3, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_4, required_type>));
}

TEST_CASE("Points cannot have points added") {
    const View::Point p;
    const View::Point p_p;
    const View::XYPoint p_xy;

    using converted_type_1 = decltype(p + p_p);
    using converted_type_2 = decltype(p + p_xy);
    using required_type = StaticAssert::invalid_point_to_point_addition;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
}
#endif

TEST_CASE("Points can have their z-value removed") {
    const View::Point p(2, 3, 4);
    const auto v2 = p.ToXY();
    CHECK(v2 == View::XYPoint(2, 3));
}
TEST_CASE("Points can have their z-value removed to produce a XYPoint") {
    const View::Point p;
    using converted_type = decltype(p.ToXY());
    using required_type = View::XYPoint;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
TEST_CASE("Points from Spaces that do not support XY cannot have their z-value removed") {
    const Volume::Point p;
    using converted_type = decltype(p.ToXY());
    using required_type = StaticAssert::XYVector_not_supported;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}

TEST_CASE("Points can be converted from one space to another ignoring translation") {
    const TransformManager tm;
    const View::Point p_view(1, 0, 0);
    auto v_patient = p_view.ConvertTo<Data>(tm);
    CHECK(v_patient == Data::Point(-5, -6, -7));
}
TEST_CASE("Points can be converted from one space to another to produce a Point") {
    const TransformManager tm;
    const View::Point p_view;
    using converted_type = decltype(p_view.ConvertTo<Data>(tm));
    using required_type = Data::Point;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Points cannot be converted to the same space") {
    const TransformManager tm;
    const View::Point p;
    using converted_type = decltype(p.ConvertTo<View>(tm));
    using required_type = StaticAssert::invalid_same_space_conversion;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

TEST_CASE("Points can be streamed") {
    const View::Point p(1.2, 2.3, 3.4);
    std::stringstream stream;
    stream << p;

    CHECK(stream.str() == std::string("View::Point (1.2, 2.3, 3.4)"));
}

