#include "pch.h"
#include "SpaceHelpers.h"
#include "ExampleTransformManager.h"

using namespace Space;

TEST_CASE("XYPoints can be constructed") {
    View::XYPoint p;
}
TEST_CASE("XYPoints have zero value by default") {
    View::XYPoint p;
    CHECK(p[0] == 0);
    CHECK(p[1] == 0);
}
TEST_CASE("XYPoints can be constructed from implementation") {
    TestVector impl;
    impl.m_values[0] = 3;
    impl.m_values[1] = 2;
    impl.m_values[2] = 1;
    const View::XYPoint p(impl);
    CHECK(p.X() == 3);
    CHECK(p.Y() == 2);
}
TEST_CASE("XYPoints Can Be Constructed From Three Doubles") {
    const View::XYPoint p(4, 5);
    CHECK(p.X() == 4);
    CHECK(p.Y() == 5);
}
TEST_CASE("XYPoints can be created using initalizer lists of two numbers") {
    View::XYPoint p{ 1, 2 };
    CHECK(p[0] == 1);
    CHECK(p[1] == 2);
}

TEST_CASE("XYPoints can be assigned from an XYPoint") {
    const View::XYPoint p2(1, 2);
    const View::XYPoint p = p2;
    CHECK(p.X() == 1);
    CHECK(p.Y() == 2);
}

TEST_CASE("XYPoints can be explicitly cast to the implementation") {
    const View::XYPoint p(1, 2);
    auto impl = static_cast<TestVector>(p);
    CHECK(impl.m_values[0] == 1);
    CHECK(impl.m_values[1] == 2);
}

TEST_CASE("XYPoints can be implicitly cast to Point") {
    const View::XYPoint v(1, 2);
    const View::Point v2 = v;
    CHECK(v2[0] == 1);
    CHECK(v2[1] == 2);
    CHECK(v2[2] == 0);
}

TEST_CASE("XYPoints support element access by name") {
    const Image::XYPoint p(2, 3);
    CHECK(p.X() == 2);
    CHECK(p.Y() == 3);
}

TEST_CASE("XYPoint elements can be modified by name") {
    Image::XYPoint p(2, 3);
    p.SetX(10);
    p.SetY(20);
    CHECK(p.X() == 10);
    CHECK(p.Y() == 20);
}

TEST_CASE("XYPoints support const begin and end") {
    const Image::XYPoint p(2, 3);
    std::vector<double> values;
    std::copy(p.cbegin(), p.cend(), std::back_inserter(values));
    CHECK(values.size() == 2);
    CHECK(values[0] == 2);
    CHECK(values[1] == 3);
}
TEST_CASE("XYPoints support non-const begin and end") {
    Image::XYPoint p(2, 4);
    std::fill(p.begin(), p.end(), 3);
    CHECK(p.X() == 3);
    CHECK(p.Y() == 3);
}

TEST_CASE("XYPoints support element access by random access") {
    const Image::XYPoint p(2, 3);
    CHECK(p[0] == 2);
    CHECK(p[1] == 3);
}
TEST_CASE("XYPoints throw if random access is too high") {
    const Image::XYPoint p;
    CHECK_THROWS_AS(p[2], std::invalid_argument);
}
TEST_CASE("XYPoints throw with the right message if random access is too high") {
    const Image::XYPoint p;
    CHECK_THROWS_WITH(p[2], "Index is out of range");
}

TEST_CASE("XYPoints support element access by at") {
    const Image::XYPoint p(2, 3);
    CHECK(p.at<0>() == 2);
    CHECK(p.at<1>() == 3);
}
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYPoints at does not compile if too low") {
    const Image::XYPoint p;
    using converted_type = decltype(p.at<-1>());
    using required_type = StaticAssert::invalid_at_access;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
TEST_CASE("XYPoints at does not compile if too high") {
    const Image::XYPoint p;
    using converted_type = decltype(p.at<3>());
    using required_type = StaticAssert::invalid_at_access;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

TEST_CASE("XYPoint and Point can be compared using equal: same") {
    const View::XYPoint p(1, 0);
    const View::Point p2(1, 0, 0);
    CHECK(p == p2);
}
TEST_CASE("XYPoint and XYPoint can be compared using equal: same") {
    const View::XYPoint p(1, 0);
    const View::XYPoint p2(1, 0);
    CHECK(p == p2);
}

TEST_CASE("XYPoint and Vector can be compared using equal: different") {
    const View::XYPoint p(1, 1);
    const View::Point p2(1, 0, 0);
    CHECK(!(p == p2));
}
TEST_CASE("XYPoint and XYPoint can be compared using equal: different") {
    const View::XYPoint p(1, 1);
    const View::XYPoint p2(1, 0);
    CHECK(!(p == p2));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYPoints from different spaces cannot be compared using equal") {
    const View::XYPoint p;
    const Image::Point p_p;
    const Image::XYPoint p_xy;

    using converted_type_1 = decltype(p == p_p);
    using converted_type_2 = decltype(p == p_xy);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
}
#endif

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYPoints and Vectors cannot be compared using equal") {
    const Image::XYPoint p;
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

TEST_CASE("XYPoint and Point can be compared using inequality: same") {
    const View::XYPoint p(1, 0);
    const View::Point p2(1, 0, 0);
    CHECK(!(p != p2));
}
TEST_CASE("XYPoint and XYPoint can be compared using inequality: same") {
    const View::XYPoint p(1, 0);
    const View::XYPoint p2(1, 0);
    CHECK(!(p != p2));
}

TEST_CASE("XYPoint and Point can be compared using inequality: different") {
    const View::XYPoint p(1, 1);
    const View::Point p2(1, 0, 0);
    CHECK(p != p2);
}
TEST_CASE("XYPoint and XYPoint can be compared using inequality: different") {
    const View::XYPoint p(1, 1);
    const View::XYPoint p2(1, 0);
    CHECK(p != p2);
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYPoints from different spaces cannot be compared using inequality") {
    const View::XYPoint p;
    const Image::Point p_p;
    const Image::XYPoint p_xy;

    using converted_type_1 = decltype(p != p_p);
    using converted_type_2 = decltype(p != p_xy);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
}
#endif

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYPoints and Vectors cannot be compared using inequality") {
    const View::XYPoint p;
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

TEST_CASE("XYPoints can have NormalizedXYVectors subtracted in place") {
    Image::XYPoint p(1, 2);
    const Image::NormalizedXYVector v2(1, 0);
    p -= v2;
    CHECK(p == Image::Point(0, 2, 3));
}
TEST_CASE("XYPoints can have XYVectors subtracted in place") {
    Image::XYPoint p(1, 2);
    const Image::NormalizedXYVector v2(1, 0);
    p -= v2;
    CHECK(p == Image::Point(0, 2, 3));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYPoints cannot have 3D vectors subtracted in place") {
    View::XYPoint p;
    const View::Vector v_v;
    const View::NormalizedVector v_n;

    using converted_type_1 = decltype(p -= v_v);
    using converted_type_2 = decltype(p -= v_n);
    using required_type = StaticAssert::invalid_vector3_from_xy_point_subtraction;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
}
#endif

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYPoints and vectors in different spaces cannot be subtracted in place") {
    View::XYPoint p;
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
#endif

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYPoints cannot have other Points subtracted in place") {
    View::XYPoint p;
    const View::Point p_p;
    const View::XYPoint p_xy;

    using converted_type_1 = decltype(p -= p_p);
    using converted_type_2 = decltype(p -= p_xy);
    using required_type = StaticAssert::invalid_point_from_vector_subtraction;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
}
#endif

TEST_CASE("XYPoints can have Vectors subtracted") {
    const Image::XYPoint p(1, 2);
    const Image::Vector v2(1, 0, 0);
    auto v3 = p - v2;
    CHECK(v3 == Image::Point(0, 2, 0));
}
TEST_CASE("XYPoints can have NormalizedVector subtracted") {
    const Image::XYPoint p(1, 2);
    const Image::NormalizedVector v2(1, 0, 0);
    auto v3 = p - v2;
    CHECK(v3 == Image::Point(0, 2, 0));
}
TEST_CASE("XYPoints can have NormalizedXYVector subtracted") {
    const Image::XYPoint p(1, 2);
    const Image::NormalizedXYVector v2(1, 0);
    auto v3 = p - v2;
    CHECK(v3 == Image::Point(0, 2, 0));
}
TEST_CASE("XYPoints can have XYVector subtracted") {
    const Image::XYPoint p(1, 2);
    const Image::XYVector v2(1, 0);
    auto v3 = p - v2;
    CHECK(v3 == Image::Point(0, 2, 0));
}

TEST_CASE("XYPoints can have XY vectors subtracted to produce another XYPoint") {
    View::XYPoint p;
    const View::NormalizedXYVector v_n_xy;
    const View::XYVector v_xy;

    using converted_type_3 = decltype(p - v_n_xy);
    using converted_type_4 = decltype(p - v_xy);
    using required_type = View::XYPoint;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_3, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_4, required_type>));
}

TEST_CASE("XYPoints can have 3D vectors subtracted to produce a Point") {
    View::XYPoint p;
    const View::Vector v_v;
    const View::NormalizedVector v_n;

    using converted_type_1 = decltype(p - v_v);
    using converted_type_2 = decltype(p - v_n);
    using required_type = View::Point;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
}

TEST_CASE("XYPoints can have Points subtracted") {
    const Image::XYPoint p(1, 2);
    const Image::Point p2(1, 0, 0);
    auto v = p - p2;
    CHECK(v == Image::Vector(0, 2, 0));
}
TEST_CASE("XYPoints can have XYPoints subtracted") {
    const Image::XYPoint p(1, 2);
    const Image::XYPoint p2(1, 0);
    auto v = p - p2;
    CHECK(v == Image::Vector(0, 2, 0));
}
TEST_CASE("XYPoints can have other XYPoints subtracted to produce an XYVector") {
    View::XYPoint p;
    const View::XYPoint p_xy;

    using converted_type_2 = decltype(p - p_xy);
    using required_type = View::XYVector;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
}
TEST_CASE("XYPoints can have 3D Points subtracted to produce a Vector") {
    View::XYPoint p;
    const View::Point p_p;

    using converted_type_1 = decltype(p - p_p);
    using required_type = View::Vector;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYPoints cannot have vectors in different spaces subtracted") {
    View::XYPoint p;
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
#endif

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYPoints cannot have Points from other spaces subtracted") {
    Image::XYPoint p;
    const View::Point p_p;
    const View::XYPoint p_xy;

    using converted_type_1 = decltype(p - p_p);
    using converted_type_2 = decltype(p - p_xy);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
}
#endif

TEST_CASE("XYPoints can have NormalizedXYVectors added in place") {
    Image::XYPoint p(1, 2);
    const Image::NormalizedXYVector v2(1, 0);
    p += v2;
    CHECK(p == Image::Point(2, 2, 3));
}
TEST_CASE("XYPoints can have XYVectors added in place") {
    Image::XYPoint p(1, 2);
    const Image::NormalizedXYVector v2(1, 0);
    p += v2;
    CHECK(p == Image::Point(2, 2, 3));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYPoints cannot have 3D vectors added in place") {
    View::XYPoint p;
    const View::Vector v_v;
    const View::NormalizedVector v_n;

    using converted_type_1 = decltype(p += v_v);
    using converted_type_2 = decltype(p += v_n);
    using required_type = StaticAssert::invalid_vector3_to_xy_point_addition;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
}
#endif

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYPoints cannot have vectors in different spaces added in place") {
    View::XYPoint p;
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
#endif

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYPoints cannot have points in different spaces added in place") {
    View::XYPoint p;
    const Image::Point p_p;
    const Image::XYPoint p_xy;

    using converted_type_1 = decltype(p += p_p);
    using converted_type_2 = decltype(p += p_xy);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
}
#endif

TEST_CASE("XYPoints can have Vectors added") {
    const Image::XYPoint p(1, 2);
    const Image::Vector v2(1, 0, 0);
    auto v3 = p + v2;
    CHECK(v3 == Image::Point(2, 2, 0));
}
TEST_CASE("XYPoints can have NormalizedVector added") {
    const Image::XYPoint p(1, 2);
    const Image::NormalizedVector v2(1, 0, 0);
    auto v3 = p + v2;
    CHECK(v3 == Image::Point(2, 2, 0));
}
TEST_CASE("XYPoints can have NormalizedXYVector added") {
    const Image::XYPoint p(1, 2);
    const Image::NormalizedXYVector v2(1, 0);
    auto v3 = p + v2;
    CHECK(v3 == Image::Point(2, 2, 0));
}
TEST_CASE("XYPoints can have XYVector added") {
    const Image::XYPoint p(1, 2);
    const Image::XYVector v2(1, 0);
    auto v3 = p + v2;
    CHECK(v3 == Image::Point(2, 2, 0));
}
TEST_CASE("XYPoints can have XY vectors added to produce another XY Point") {
    View::XYPoint p;
    const View::NormalizedXYVector v_n_xy;
    const View::XYVector v_xy;

    using converted_type_3 = decltype(p + v_n_xy);
    using converted_type_4 = decltype(p + v_xy);
    using required_type = View::XYPoint;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_3, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_4, required_type>));
}
TEST_CASE("XYPoints can have 3D vectors added to produce a Point") {
    View::XYPoint p;
    const View::Vector v_v;
    const View::NormalizedVector v_n;

    using converted_type_1 = decltype(p + v_v);
    using converted_type_2 = decltype(p + v_n);
    using required_type = View::Point;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYPoints can have vectors in other spaces cannot be added") {
    View::XYPoint p;
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
#endif

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYPoints cannot have points added") {
    const View::XYPoint p;
    const View::Point p_p;
    const View::XYPoint p_xy;

    using converted_type_1 = decltype(p + p_p);
    using converted_type_2 = decltype(p + p_xy);
    using required_type = StaticAssert::invalid_point_to_point_addition;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
}
#endif

TEST_CASE("XYPoints can be converted from one space to another ignoring translation") {
    const TransformManager tm;
    const View::Point p_view(1, 0, 0);
    auto v_patient = p_view.ConvertTo<Data>(tm);
    CHECK(v_patient == Data::Point(-5, -6, -7));
}
TEST_CASE("XYPoints can be converted from one space to another to produce a Point") {
    const TransformManager tm;
    const View::Point p_view;
    using converted_type = decltype(p_view.ConvertTo<Data>(tm));
    using required_type = Data::Point;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYPoints cannot be converted to the same space") {
    const TransformManager tm;
    const View::XYPoint p;
    using converted_type = decltype(p.ConvertTo<View>(tm));
    using required_type = StaticAssert::invalid_conversion;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

TEST_CASE("XYPoints can be streamed") {
    const View::XYPoint p(1.2, 2.3);
    std::stringstream stream;
    stream << p;
    CHECK(stream.str() == std::string("View::XYPoint (1.2, 2.3)"));
}

