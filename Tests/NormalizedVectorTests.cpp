#include "ExternalIncludes.h"
#include "SpaceHelpers.h"
#include "ExampleTransformManager.h"

using namespace Space;

TEST_CASE("NormalizedVectors can be constructed") {
    View::NormalizedVector v;
}
TEST_CASE("NormalizedVectors default to the i vector") {
    View::NormalizedVector v;
    CHECK(v[0] == 1);
    CHECK(v[1] == 0);
    CHECK(v[2] == 0);
}
TEST_CASE("NormalizedVectors can be constructed from implementation") {
    TestVector impl;
    impl.m_values[0] = 3;
    impl.m_values[1] = 4;
    impl.m_values[2] = 0;
    const Data::NormalizedVector v(impl);
    CHECK(v.X() == 3/5.0);
    CHECK(v.Y() == 4 / 5.0);
    CHECK(v.Z() == 0);
}
TEST_CASE("NormalizedVectors Can Be Constructed From Three Doubles") {
    const Data::NormalizedVector v(3, 4, 0);
    CHECK(v.X() == 3 / 5.0);
    CHECK(v.Y() == 4 / 5.0);
    CHECK(v.Z() == 0);
}
TEST_CASE("NormalizedVectors can be created using initalizer lists of three numbers") {
    View::NormalizedVector v{ 3, 4, 0 };
    CHECK(v.X() == 3 / 5.0);
    CHECK(v.Y() == 4 / 5.0);
    CHECK(v.Z() == 0);
}

TEST_CASE("NormalizedVectors can be assigned from a normalized vector") {
    const View::NormalizedVector v2(1, 0, 0);
    const View::NormalizedVector v = v2;
    CHECK(v.X() == 1);
    CHECK(v.Y() == 0);
    CHECK(v.Z() == 0);
}

TEST_CASE("NormalizedVectors can be explicitly cast to the implementation") {
    const Data::NormalizedVector v(1, 0, 0);
    auto impl = static_cast<TestVector>(v);
    CHECK(impl.m_values[0] == 1);
    CHECK(impl.m_values[1] == 0);
    CHECK(impl.m_values[2] == 0);
}
TEST_CASE("NormalizedVector can be implicitly cast to a Vector") {
    const Data::NormalizedVector v(1, 0, 0);
    const Data::Vector v2 = v;
    CHECK(v2[0] == 1);
    CHECK(v2[1] == 0);
    CHECK(v2[2] == 0);
}

TEST_CASE("NormalizedVectors support element access by name") {
    const Image::NormalizedVector v(1, 0, 0);
    CHECK(v.X() == 1);
    CHECK(v.Y() == 0);
    CHECK(v.Z() == 0);
}

TEST_CASE("NormalizedVectors support const begin and end") {
    const Image::NormalizedVector v(1, 0, 0);
    std::vector<double> values;
    std::copy(v.cbegin(), v.cend(), std::back_inserter(values));
    CHECK(values.size() == 3);
    CHECK(values[0] == 1);
    CHECK(values[1] == 0);
    CHECK(values[2] == 0);
}

TEST_CASE("NormalizedVectors support element access by random access") {
    const Image::NormalizedVector v(1, 0, 0);
    CHECK(v[0] == 1);
    CHECK(v[1] == 0);
    CHECK(v[2] == 0);
}
TEST_CASE("NormalizedVectors throw if random access is too high") {
    const Image::NormalizedVector v;
    CHECK_THROWS_AS(v[3], std::invalid_argument);
}
TEST_CASE("NormalizedVectors throw with the right message if random access is too high") {
    const Image::NormalizedVector v;
    CHECK_THROWS_WITH(v[3], "Index is out of range");
}

TEST_CASE("NormalizedVectors support element access by at") {
    const Image::NormalizedVector v(1, 0, 0);
    CHECK(v.at<0>() == 1);
    CHECK(v.at<1>() == 0);
    CHECK(v.at<2>() == 0);
}
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("NormalizedVectors at does not compile if too low") {
    const Image::NormalizedVector v;
    using converted_type = decltype(v.at<-1>());
    using required_type = StaticAssert::invalid_at_access;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
TEST_CASE("NormalizedVectors at does not compile if too high") {
    const Image::NormalizedVector v;
    using converted_type = decltype(v.at<3>());
    using required_type = StaticAssert::invalid_at_access;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

TEST_CASE("NormalizedVector and Vector can be compared using equal: same") {
    const View::NormalizedVector v(1, 0, 0);
    const View::Vector v2(1, 0, 0);
    CHECK(v == v2);
}
TEST_CASE("NormalizedVector and NormalizedVector can be compared using equal: same") {
    const View::NormalizedVector v(1, 0, 0);
    const View::NormalizedVector v2(1, 0, 0);
    CHECK(v == v2);
}
TEST_CASE("NormalizedVector and NormalizedXYVector can be compared using equal: same") {
    const View::NormalizedVector v(1, 0, 0);
    const View::NormalizedXYVector v2(1, 0);
    CHECK(v == v2);
}
TEST_CASE("NormalizedVector and XYVector can be compared using equal: same") {
    const View::NormalizedVector v(1, 0, 0);
    const View::XYVector v2(1, 0);
    CHECK(v == v2);
}

TEST_CASE("NormalizedVector and Vector can be compared using equal: different") {
    const View::NormalizedVector v(1, 0, 1);
    const View::Vector v2(1, 0, 0);
    CHECK(!(v == v2));
}
TEST_CASE("NormalizedVector and NormalizedVector can be compared using equal: different") {
    const View::NormalizedVector v(1, 0, 1);
    const View::NormalizedVector v2(1, 0, 0);
    CHECK(!(v == v2));
}
TEST_CASE("NormalizedVector and NormalizedXYVector can be compared using equal: different") {
    const View::NormalizedVector v(1, 0, 1);
    const View::NormalizedXYVector v2(1, 0);
    CHECK(!(v == v2));
}
TEST_CASE("NormalizedVector and XYVector can be compared using equal: different") {
    const View::NormalizedVector v(1, 0, 1);
    const View::XYVector v2(1, 0);
    CHECK(!(v == v2));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("NormalizedVectors from different spaces cannot be compared using equal") {
    const View::NormalizedVector v;
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

TEST_CASE("NormalizedVector and Points cannot be compared using equal") {
    const View::NormalizedVector v;
    const View::Point p;
    const View::Point p_xy;

    using converted_type_1 = decltype(v == p);
    using converted_type_2 = decltype(v == p_xy);
    using required_type = StaticAssert::invalid_point_vector_equality;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
}
#endif

TEST_CASE("NormalizedVector and Vector can be compared using inequality: same") {
    const View::NormalizedVector v(1, 0, 0);
    const View::Vector v2(1, 0, 0);
    CHECK(!(v != v2));
}
TEST_CASE("NormalizedVector and NormalizedVector can be compared using inequality: same") {
    const View::NormalizedVector v(1, 0, 0);
    const View::NormalizedVector v2(1, 0, 0);
    CHECK(!(v != v2));
}
TEST_CASE("NormalizedVector and NormalizedXYVector can be compared using inequality: same") {
    const View::NormalizedVector v(1, 0, 0);
    const View::NormalizedXYVector v2(1, 0);
    CHECK(!(v != v2));
}
TEST_CASE("NormalizedVector and XYVector can be compared using inequality: same") {
    const View::NormalizedVector v(1, 0, 0);
    const View::XYVector v2(1, 0);
    CHECK(!(v != v2));
}

TEST_CASE("NormalizedVector and Vector can be compared using inequality: different") {
    const View::NormalizedVector v(1, 0, 1);
    const View::Vector v2(1, 0, 0);
    CHECK(v != v2);
}
TEST_CASE("NormalizedVector and NormalizedVector can be compared using inequality: different") {
    const View::NormalizedVector v(1, 0, 1);
    const View::NormalizedVector v2(1, 0, 0);
    CHECK(v != v2);
}
TEST_CASE("NormalizedVector and NormalizedXYVector can be compared using inequality: different") {
    const View::NormalizedVector v(1, 0, 1);
    const View::NormalizedXYVector v2(1, 0);
    CHECK(v != v2);
}
TEST_CASE("NormalizedVector and XYVector can be compared using inequality: different") {
    const View::NormalizedVector v(1, 0, 1);
    const View::XYVector v2(1, 0);
    CHECK(v != v2);
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("NormalizedVectors from different spaces cannot be compared using inequality") {
    const View::NormalizedVector v;
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

TEST_CASE("NormalizedVector and Points cannot be compared using inequality") {
    const View::NormalizedVector v;
    const View::Point p;
    const View::Point p_xy;

    using converted_type_1 = decltype(v != p);
    using converted_type_2 = decltype(v != p_xy);
    using required_type = StaticAssert::invalid_point_vector_equality;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
}

TEST_CASE("NormalizedVectors cannot have other vectors subtracted in place") {
    View::NormalizedVector v;
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

TEST_CASE("NormalizedVectors can have Vectors subtracted") {
    const Image::NormalizedVector v(0, 1, 0);
    const Image::Vector v2(1, 0, 0);
    auto v3 = v - v2;
    CHECK(v3 == Image::Vector(-1, 1, 0));
}
TEST_CASE("NormalizedVectors can have NormalizedVector subtracted") {
    const Image::NormalizedVector v(0, 1, 0);
    const Image::NormalizedVector v2(1, 0, 0);
    auto v3 = v - v2;
    CHECK(v3 == Image::Vector(-1, 1, 0));
}
TEST_CASE("NormalizedVectors can have NormalizedXYVector subtracted") {
    const Image::NormalizedVector v(0, 1, 0);
    const Image::NormalizedXYVector v2(1, 0);
    auto v3 = v - v2;
    CHECK(v3 == Image::Vector(-1, 1, 0));
}
TEST_CASE("NormalizedVectors can have XYVector subtracted") {
    const Image::NormalizedVector v(0, 1, 0);
    const Image::XYVector v2(1, 0);
    auto v3 = v - v2;
    CHECK(v3 == Image::Vector(-1, 1, 0));
}
TEST_CASE("NormalizedVectors can have other vectors subtracted to produce a Vector") {
    View::NormalizedVector v;
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
TEST_CASE("NormalizedVectors in different spaces cannot be subtracted") {
    View::NormalizedVector v;
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

TEST_CASE("NormalizedVectors cannot have points subtracted") {
    const View::NormalizedVector v;
    const View::Point p;
    const View::Point p_xy;

    using converted_type_1 = decltype(v - p);
    using converted_type_2 = decltype(v - p_xy);
    using required_type = StaticAssert::invalid_point_from_vector_subtraction;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
}

TEST_CASE("NormalizedVectors cannot have other vectors added in place") {
    View::NormalizedVector v;
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

TEST_CASE("NormalizedVectors can have Vectors added") {
    const Image::NormalizedVector v(0, 1, 0);
    const Image::Vector v2(1, 0, 0);
    auto v3 = v + v2;
    CHECK(v3 == Image::Vector(1, 1, 0));
}
TEST_CASE("NormalizedVectors can have NormalizedVector added") {
    const Image::NormalizedVector v(0, 1, 0);
    const Image::NormalizedVector v2(1, 0, 0);
    auto v3 = v + v2;
    CHECK(v3 == Image::Vector(1, 1, 0));
}
TEST_CASE("NormalizedVectors can have NormalizedXYVector added") {
    const Image::NormalizedVector v(0, 1, 0);
    const Image::NormalizedXYVector v2(1, 0);
    auto v3 = v + v2;
    CHECK(v3 == Image::Vector(1, 1, 0));
}
TEST_CASE("NormalizedVectors can have XYVector added") {
    const Image::NormalizedVector v(0, 1, 0);
    const Image::XYVector v2(1, 0);
    auto v3 = v + v2;
    CHECK(v3 == Image::Vector(1, 1, 0));
}
TEST_CASE("NormalizedVectors can have other vectors added to produce another Vector") {
    View::NormalizedVector v;
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
TEST_CASE("NormalizedVectors in different spaces cannot be added") {
    View::NormalizedVector v;
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

TEST_CASE("NormalizedVectors cannot have points added") {
    const View::NormalizedVector v;
    const View::Point p;
    const View::Point p_xy;

    using converted_type_1 = decltype(v + p);
    using converted_type_2 = decltype(v + p_xy);
    using required_type = StaticAssert::invalid_point_to_vector_addition;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
}
#endif

TEST_CASE("NormalizedVectors can have NormalizedVectors crossed in place") {
    Image::NormalizedVector v(0, 1, 0);
    const Image::NormalizedVector v2(1, 0, 0);
    v *= v2;
    CHECK(v == Image::Vector(0, 0, -1));
}
TEST_CASE("NormalizedVectors can have NormalizedXYVectors crossed in place") {
    Image::NormalizedVector v(0, 1, 0);
    const Image::NormalizedXYVector v2(1, 0);
    v *= v2;
    CHECK(v == Image::Vector(0, 0, -1));
}
TEST_CASE("NormalizedVectors cannot be crossed in place with non-normalized vectors") {
    View::NormalizedVector v;
    const View::Vector v_v;
    const View::XYVector v_xy;

    using converted_type_1 = decltype(v *= v_v);
    using converted_type_4 = decltype(v *= v_xy);
    using required_type = StaticAssert::invalid_normalized_vector_in_place_cross;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_4, required_type>));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("NormalizedVectors in different spaces cannot be crossed in place") {
    Image::NormalizedVector v;
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

TEST_CASE("NormalizedVectors can have Vectors crossed using star") {
    const Image::NormalizedVector v(0, 1, 0);
    const Image::Vector v2(1, 0, 0);
    auto v3 = v * v2;
    CHECK(v3 == Image::Vector(0, 0, -1));
}
TEST_CASE("NormalizedVectors can have NormalizedVector crossed using star") {
    const Image::NormalizedVector v(0, 1, 0);
    const Image::NormalizedVector v2(1, 0, 0);
    auto v3 = v * v2;
    CHECK(v3 == Image::Vector(0, 0, -1));
}
TEST_CASE("NormalizedVectors can have NormalizedXYVector crossed using star") {
    const Image::NormalizedVector v(0, 1, 0);
    const Image::NormalizedXYVector v2(1, 0);
    auto v3 = v * v2;
    CHECK(v3 == Image::Vector(0, 0, -1));
}
TEST_CASE("NormalizedVectors can have XYVector crossed using star") {
    const Image::NormalizedVector v(0, 1, 0);
    const Image::XYVector v2(1, 0);
    auto v3 = v * v2;
    CHECK(v3 == Image::Vector(0, 0, -1));
}
TEST_CASE("NormalizedVectors can have other normalized vectors crossed using star to produce another NormalizedVector") {
    View::NormalizedVector v;
    const View::NormalizedVector v_n;
    const View::NormalizedXYVector v_n_xy;

    using converted_type_2 = decltype(v * v_n);
    using converted_type_3 = decltype(v * v_n_xy);
    using required_type = View::NormalizedVector;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_3, required_type>));
}
TEST_CASE("NormalizedVectors can have other vectors crossed using star to produce another Vector") {
    View::NormalizedVector v;
    const View::Vector v_v;
    const View::XYVector v_xy;

    using converted_type_1 = decltype(v * v_v);
    using converted_type_4 = decltype(v * v_xy);
    using required_type = View::Vector;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_4, required_type>));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("NormalizedVectors in different spaces cannot be crossed using star") {
    Image::NormalizedVector v;
    const View::Vector v_v;
    const View::NormalizedVector v_n;
    const View::NormalizedXYVector v_n_xy;
    const View::XYVector v_xy;

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

TEST_CASE("NormalizedVectors can have Vectors crossed") {
    const Image::NormalizedVector v(0, 1, 0);
    const Image::Vector v2(1, 0, 0);
    auto v3 = v.Cross(v2);
    CHECK(v3 == Image::Vector(0, 0, -1));
}
TEST_CASE("NormalizedVectors can have NormalizedVector crossed") {
    const Image::NormalizedVector v(0, 1, 0);
    const Image::NormalizedVector v2(1, 0, 0);
    auto v3 = v.Cross(v2);
    CHECK(v3 == Image::Vector(0, 0, -1));
}
TEST_CASE("NormalizedVectors can have NormalizedXYVector crossed") {
    const Image::NormalizedVector v(0, 1, 0);
    const Image::NormalizedXYVector v2(1, 0);
    auto v3 = v.Cross(v2);
    CHECK(v3 == Image::Vector(0, 0, -1));
}
TEST_CASE("NormalizedVectors can have XYVector crossed") {
    const Image::NormalizedVector v(0, 1, 0);
    const Image::XYVector v2(1, 0);
    auto v3 = v.Cross(v2);
    CHECK(v3 == Image::Vector(0, 0, -1));
}
TEST_CASE("NormalizedVectors can have other NormalizedVectors crossed to produce another NormalizedVector") {
    View::NormalizedVector v;
    const View::NormalizedVector v_n;
    const View::NormalizedXYVector v_n_xy;

    using converted_type_2 = decltype(v.Cross(v_n));
    using converted_type_3 = decltype(v.Cross(v_n_xy));
    using required_type = View::NormalizedVector;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_2, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_3, required_type>));
}
TEST_CASE("NormalizedVectors can have other vectors crossed to produce another Vector") {
    View::NormalizedVector v;
    const View::Vector v_v;
    const View::XYVector v_xy;

    using converted_type_1 = decltype(v.Cross(v_v));
    using converted_type_4 = decltype(v.Cross(v_xy));
    using required_type = View::Vector;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_1, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_4, required_type>));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("NormalizedVectors in different spaces cannot be crossed") {
    Image::NormalizedVector v;
    const View::Vector v_v;
    const View::NormalizedVector v_n;
    const View::NormalizedXYVector v_n_xy;
    const View::XYVector v_xy;

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

TEST_CASE("NormalizedVectors and Vectors can be dotted") {
    const View::NormalizedVector v(1, 0, 0);
    const View::Vector v2(2, 0, 0);
    const auto dot = v.Dot(v2);
    CHECK(dot == 2);
}
TEST_CASE("NormalizedVectors and NormalizedVector can be dotted") {
    const View::NormalizedVector v(1, 0, 0);
    const View::NormalizedVector v2(1, 0, 0);
    const auto dot = v.Dot(v2);
    CHECK(dot == 1);
}
TEST_CASE("NormalizedVectors and NormalizedXYVector can be dotted") {
    const View::NormalizedVector v(1, 0, 0);
    const View::NormalizedXYVector v2(1, 0);
    const auto dot = v.Dot(v2);
    CHECK(dot == 1);
}
TEST_CASE("NormalizedVectors and XYVector can be dotted") {
    const View::NormalizedVector v(1, 0, 0);
    const View::XYVector v2(2, 0);
    const auto dot = v.Dot(v2);
    CHECK(dot == 2);
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("NormalizedVectors from different spaces cannot be dotted") {
    View::NormalizedVector v;
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

TEST_CASE("NormalizedVectors can have their z-value removed") {
    const View::NormalizedVector v(1, 0, 0);
    const auto v2 = v.ToXY();
    CHECK(v2 == View::NormalizedXYVector(1, 0));
}
TEST_CASE("NormalizedVectors can have their z-value removed to produce a NormalizedXYVector") {
    const View::NormalizedVector v;
    using converted_type = decltype(v.ToXY());
    using required_type = View::NormalizedXYVector;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
TEST_CASE("NormalizedVectors from Spaces that do not support XY cannot have their z-value removed") {
    const Volume::NormalizedVector v;
    using converted_type = decltype(v.ToXY());
    using required_type = StaticAssert::XYVector_not_supported;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}

TEST_CASE("NormalizedVectors can be converted from one space to another ignoring translation") {
    const TransformManager tm;
    const View::NormalizedVector v_view(1, 0, 0);
    auto v_patient = v_view.ConvertTo<Data>(tm);
    CHECK(v_patient == Data::Vector(15, 16, 17));
}
TEST_CASE("NormalizedVectors can be converted from one space to another to produce a Vector") {
    const TransformManager tm;
    const View::NormalizedVector v_view;
    using converted_type = decltype(v_view.ConvertTo<Data>(tm));
    using required_type = Data::Vector;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("NormalizedVectors cannot be converted to the same space") {
    const TransformManager tm;
    const View::NormalizedVector v;
    using converted_type = decltype(v.ConvertTo<View>(tm));
    using required_type = StaticAssert::invalid_same_space_conversion;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

TEST_CASE("NormalizedVectors can be streamed") {
    const View::NormalizedVector v(1, 0, 0);
    std::stringstream stream;
    stream << v;
    CHECK(stream.str() == std::string("View::NormalizedVector (1, 0, 0)"));
}

