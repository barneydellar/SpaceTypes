#include "pch.h"
#include "SpaceHelpers.h"

using namespace Space;

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedXYVectors cannot be constructed from spaces that do not support XY") {
    using converted_type = decltype(Volume::NormalizedXYVector{});
    using required_type = StaticAssert::XYVector_not_supported;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedXYVectora cannot be constructed from spaces that do not support XY") {
    Volume::Vector v;

}

TEST_CASE("Normalized XYVectors can be constructed") {
    View::NormalizedXYVector v;
}

TEST_CASE("Normalized XYVectors default to the i vector") {
    View::NormalizedXYVector v;
    CHECK(v[0] == 1);
    CHECK(v[1] == 0);
}
TEST_CASE("Normalized XYVectors can be created using initalizer lists of two numbers") {
    View::NormalizedXYVector v{10, 0};
    CHECK(v[0] == 1);
    CHECK(v[1] == 0);
}

TEST_CASE("Normalized XYVectors throw when using initalizer lists that are too small") {
    try
    {
        View::NormalizedXYVector v{1};
    }
    catch (std::invalid_argument&)
    {
        return;
    }
    REQUIRE(false);
}
TEST_CASE("Normalized XYVectors throw when using initalizer lists that are too large") {
    try
    {
        View::NormalizedXYVector v{ 1, 2, 3 };
    }
    catch (std::invalid_argument&)
    {
        return;
    }
    REQUIRE(false);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVectors Can Be Constructed And Normalized From Implementation") {
    TestVector impl;
    impl.m_values[0] = 3;
    impl.m_values[1] = 0;
    impl.m_values[2] = 0;

    const Image::NormalizedXYVector v(impl);
    CHECK(v.X() == 1);
    CHECK(v.Y() == 0);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYVectors have their z removed and are nomalised with implementation") {
    TestVector impl_in;
    impl_in.m_values[0] = 3;
    impl_in.m_values[1] = 3;
    impl_in.m_values[2] = 3;
    const Image::NormalizedXYVector v(impl_in);
    auto impl = static_cast<TestVector>(v);
    CHECK(impl.m_values[0] == Approx(1/std::sqrt(2)));
    CHECK(impl.m_values[1] == Approx(1/std::sqrt(2)));
    CHECK(impl.m_values[2] == 0);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVectors Can Be Constructed And Normalized From Two Doubles") {
    const Image::NormalizedXYVector v(2, 0);
    CHECK(v.X() == 1);
    CHECK(v.Y() == 0);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVectors Start Off Normalized") {
    const Image::NormalizedXYVector v(3, 4);
    CHECK(v.X() == 3/5.0);
    CHECK(v.Y() == 4/5.0);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Zero Sized Normalized XYVectors Cannot Be Created") {
    CHECK_THROWS_AS(Image::NormalizedXYVector(0, 0), std::invalid_argument);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVectors can be cast to the implementation") {
    const Image::NormalizedXYVector v(1, 0);
    auto impl = static_cast<TestVector>(v);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVectors are normalised and lose their Z when constructed from an implementation") {
    TestVector impl_in;
    impl_in.m_values[0] = 3;
    impl_in.m_values[1] = 4;
    impl_in.m_values[2] = 5;

    const Image::NormalizedXYVector v(impl_in);
    auto impl = static_cast<TestVector>(v);
    CHECK(impl.m_values[0] == 3 / 5.0);
    CHECK(impl.m_values[1] == 4 / 5.0);
    CHECK(impl.m_values[2] == 0);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVectors cannot be implicitly cast to the implementation") {
    const Image::NormalizedXYVector v(1, 0);

    // This should not compile
    //TestVector impl = v;
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVector Can Be Passed By Value To Vector") {

    const Image::NormalizedXYVector nv(1, 0);

    const auto lambda = [](
        const Image::Vector v
    ) {
        CHECK(v.X() == 1);
        CHECK(v.Y() == 0);
        CHECK(v.Z() == 0);

    };

    lambda(nv);
}
//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVector Can Be Passed By Const Ref To Vector") {
    const Image::NormalizedXYVector nv(1, 0);

    const auto lambda = [](
        const Image::Vector& v
    ) {
        CHECK(v.X() == 1);
        CHECK(v.Y() == 0);
        CHECK(v.Z() == 0);
    };

    lambda(nv);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVector Can Be Passed By Value To XYVector") {

    const View::NormalizedXYVector nv(1, 0);

    const auto lambda = [](
        const View::XYVector v
    ) {
        CHECK(v.X() == 1);
        CHECK(v.Y() == 0);

    };

    lambda(nv);
}
//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVector Can Be Passed By Const Ref To XYVector") {
    const View::NormalizedXYVector nv(1, 0);

    const auto lambda = [](
        const View::XYVector& v
    ) {
        CHECK(v.X() == 1);
        CHECK(v.Y() == 0);
    };

    lambda(nv);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVector Can Be Passed By Value To NormalizedVector") {

    const View::NormalizedXYVector nv(1, 0);

    const auto lambda = [](
        const View::NormalizedVector v
    ) {
        CHECK(v.X() == 1);
        CHECK(v.Y() == 0);
        CHECK(v.Z() == 0);

    };

    lambda(nv);
}
//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVector Can Be Passed By Const Ref To NormalizedVector") {
    const View::NormalizedXYVector nv(1, 0);

    const auto lambda = [](
        const View::NormalizedVector& v
    ) {
        CHECK(v.X() == 1);
        CHECK(v.Y() == 0);
        CHECK(v.Z() == 0);
    };

    lambda(nv);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVectors From The Same Space Can Be Compared Using Equal") {
    const View::NormalizedXYVector v1(1, 0);
    const View::NormalizedXYVector v2(1, 0);
    CHECK(v1 == v2);
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Normalized XYVectors From Different Spaces Cannot Be Compared Using Equal") {
    const View::NormalizedXYVector v1;
    const Image::NormalizedXYVector v2;

    // We should not be able to compile:
    // auto dummy = v1 == v2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v1 == v2);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif
//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVectors and Vectors From The Same Space Can Be Compared Using Inequality") {
    const View::NormalizedXYVector v1(1, 0);
    const View::Vector v2(1, 0, 0);
    CHECK(!(v1 != v2));
}
TEST_CASE("Normalized XYVectors and NormalizedVectors From The Same Space Can Be Compared Using Inequality") {
    const View::NormalizedXYVector v1(1, 0);
    const View::NormalizedVector v2(1, 0, 0);
    CHECK(!(v1 != v2));
}
TEST_CASE("Normalized XYVectors and NormalizedXYVector From The Same Space Can Be Compared Using Inequality") {
    const View::NormalizedXYVector v1(1, 0);
    const View::NormalizedXYVector v2(1, 0);
    CHECK(!(v1 != v2));
}
TEST_CASE("Normalized XYVectors and XYVector From The Same Space Can Be Compared Using Inequality") {
    const View::NormalizedXYVector v1(1, 0);
    const View::XYVector v2(1, 0);
    CHECK(!(v1 != v2));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Normalized XYVectors From Different Spaces Cannot Be Compared Using Inequality") {
    const View::NormalizedXYVector v1;
    const Image::NormalizedXYVector v2;

    // We should not be able to compile:
    // auto dummy = v1 != v2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v1 != v2);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVectors and Normalized Vectors From The Same Space Can Be Compared Using Equal") {
    const View::NormalizedXYVector v1(1, 0);
    const View::NormalizedVector v2(1, 0, 0);
    CHECK(v1 == v2);
    CHECK(v2 == v1);
}

TEST_CASE("Normalized XYVectors and XYVectors From The Same Space Can Be Compared Using Equal") {
    const View::NormalizedXYVector v1(1, 0);
    const View::XYVector v2(1, 0);
    CHECK(v1 == v2);
    CHECK(v2 == v1);
}

TEST_CASE("Normalized XYVectors and Vectors From The Same Space Can Be Compared Using Equal") {
    const View::NormalizedXYVector v1(1, 0);
    const View::Vector v2(1, 0, 0);
    CHECK(v1 == v2);
    CHECK(v2 == v1);
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Normalized XYVectors And Normalized Vectors From Different Spaces Cannot Be Compared Using Equal") {
    const View::NormalizedXYVector v1;
    const Patient::NormalizedVector v2;

    // We should not be able to compile:
    // auto dummy = v1 == v2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type_A = decltype(v1 == v2);
    using converted_type_B = decltype(v2 == v1);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_A, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_B, required_type>));
}
TEST_CASE("Normalized XYVectors And Vectors From Different Spaces Cannot Be Compared Using Equal") {
    const View::NormalizedXYVector v1;
    const Patient::Vector v2;

    // We should not be able to compile:
    // auto dummy = v1 == v2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type_A = decltype(v1 == v2);
    using converted_type_B = decltype(v2 == v1);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_A, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_B, required_type>));
}
TEST_CASE("Normalized XYVectors And XYVectors From Different Spaces Cannot Be Compared Using Equal") {
    const View::NormalizedXYVector v1;
    const Image::XYVector v2;

    // We should not be able to compile:
    // auto dummy = v1 == v2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type_A = decltype(v1 == v2);
    using converted_type_B = decltype(v2 == v1);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_A, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_B, required_type>));
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVectors Can Be Multiplied") {
    const View::NormalizedXYVector v_norm(1, 0);
    const auto scaled_v = v_norm * 2;
    CHECK(scaled_v == View::XYVector(2, 0));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVectors Can Be Multiplied to produce a 2D Vector") {
    const View::NormalizedXYVector v_norm;

    using converted_type = decltype(v_norm * 2);
    using required_type = decltype(View::XYVector{});

    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}

//-------------------------------------------------------------------------------------------------
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Normalized XYVectors Cannot Be Inline Scaled") {
    const View::NormalizedXYVector v_norm;

    // We should not be able to compile:
    // v_norm *= 2.0;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v_norm *= 2.0);
    using required_type = StaticAssert::invalid_normalized_vector_scale;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVectors Can Be Added") {
    const View::NormalizedXYVector v_norm_1(1, 0);
    const View::NormalizedXYVector v_norm_2(0, 1);

    const auto added = v_norm_1 + v_norm_2;
    CHECK(added == View::XYVector(1, 1));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVectors and XYVectors Can Be Added") {
    const View::NormalizedXYVector v_norm_1(1, 0);
    const View::XYVector v_norm_2(0, 1);

    const auto added = v_norm_1 + v_norm_2;
    CHECK(added == View::XYVector(1, 1));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVectors Can Be Added To Produce A XYVector") {
    const View::NormalizedXYVector v_norm_1;
    const View::NormalizedXYVector v_norm_2;

    using converted_type_A = decltype(v_norm_1 + v_norm_2);
    using converted_type_B = decltype(v_norm_2 + v_norm_1);
    using required_type = decltype(View::XYVector{});

    CHECK(static_cast<bool>(std::is_same_v<converted_type_A, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_B, required_type>));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVectors Can Be Added To XYVectors") {
    const View::NormalizedXYVector v_norm_1(1, 0);
    const View::XYVector v_norm_2(0, 1);

    const auto added = v_norm_1 + v_norm_2;
    CHECK(added == View::XYVector(1, 1));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVectors Can Be Added To XYVectors to Produce A XYVector") {
    const View::NormalizedXYVector v_norm_1;
    const View::XYVector v_2;

    using converted_type_A = decltype(v_norm_1 + v_2);
    using converted_type_B = decltype(v_2 + v_norm_1);
    using required_type = decltype(View::XYVector{});

    CHECK(static_cast<bool>(std::is_same_v<converted_type_A, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_B, required_type>));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVectors Can Be Added To Vectors") {
    const View::NormalizedXYVector v_norm_1(1, 0);
    const View::Vector v_norm_2(0, 1, 0);

    const auto added = v_norm_1 + v_norm_2;
    CHECK(added == View::Vector(1, 1, 0));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVectors Can Be Added To Vectors to Produce A Vector") {
    const View::NormalizedXYVector v_norm_1;
    const View::Vector v_2;

    using converted_type_A = decltype(v_norm_1 + v_2);
    using converted_type_B = decltype(v_2 + v_norm_1);
    using required_type = decltype(View::Vector{});

    CHECK(static_cast<bool>(std::is_same_v<converted_type_A, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_B, required_type>));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVectors Can Be Added To Normalized Vectors") {
    const View::NormalizedXYVector v_norm_1(1, 0);
    const View::NormalizedVector v_norm_2(0, 1, 0);

    const auto added = v_norm_1 + v_norm_2;
    CHECK(added == View::Vector(1, 1, 0));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVectors Can Be Added To Normalized Vectors to Produce A Vector") {
    const View::NormalizedXYVector v_norm_1;
    const View::NormalizedVector v_norm_2;

    using converted_type_A = decltype(v_norm_1 + v_norm_2);
    using converted_type_B = decltype(v_norm_2 + v_norm_1);
    using required_type = decltype(View::Vector{});

    CHECK(static_cast<bool>(std::is_same_v<converted_type_A, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_B, required_type>));
}

//-------------------------------------------------------------------------------------------------
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Normalized XYVectors From Different Spaces Cannot Be Added") {
    const View::NormalizedXYVector v_norm_1;
    const Image::NormalizedXYVector v_norm_2;

    // We should not be able to compile:
    // auto dummy = v_norm_1 + v_norm_2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type_A = decltype(v_norm_1 + v_norm_2);
    using converted_type_B = decltype(v_norm_2 + v_norm_1);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_A, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_B, required_type>));
}
#endif

//-------------------------------------------------------------------------------------------------
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYVectors And Normalized XYVectors From Different Spaces Cannot Be Added") {
    const View::XYVector v_1;
    const Image::NormalizedXYVector v_norm_2;

    // We should not be able to compile:
    // auto dummy = v_norm_1 + v_norm_2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type_A = decltype(v_1 + v_norm_2);
    using converted_type_B = decltype(v_norm_2 + v_1);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_A, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_B, required_type>));
}
#endif

//-------------------------------------------------------------------------------------------------
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Normalized XYVectors Cannot Be Inline Added") {
    const View::NormalizedXYVector v_norm_1;
    const View::NormalizedXYVector v_norm_2;

    // We should not be able to compile:
    // v_norm_1 += v_norm_2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v_norm_1 += v_norm_2);
    using required_type = StaticAssert::invalid_normalized_vector_addition;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVectors Can Be Subtracted") {
    const View::NormalizedXYVector v_norm_1(1, 0);
    const View::NormalizedXYVector v_norm_2(0, 1);

    const auto added = v_norm_1 - v_norm_2;
    CHECK(added == View::XYVector(1, -1));
}
//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vectors Can Be Subtracted from Normalized XY Vectors") {
    const View::NormalizedXYVector v_norm_1(1, 0);
    const View::NormalizedVector v_norm_2(0, 0, 1);

    const auto added = v_norm_1 - v_norm_2;
    CHECK(added == View::Vector(1, 0, -1));
}
TEST_CASE("Vectors Can Be Subtracted from Normalized XY Vectors") {
    const View::NormalizedXYVector v_norm_1(1, 0);
    const View::Vector v_norm_2(0, 0, 1);

    const auto added = v_norm_1 - v_norm_2;
    CHECK(added == View::Vector(1, 0, -1));
}
TEST_CASE("XYVectors Can Be Subtracted from Normalized XY Vectors") {
    const View::NormalizedXYVector v_norm_1(1, 0);
    const View::XYVector v_norm_2(0, 1);

    const auto added = v_norm_1 - v_norm_2;
    CHECK(added == View::XYVector(1, -1));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVectors Can Be Subtracted To Produce A XYVector") {
    const View::NormalizedXYVector v_norm_1;
    const View::NormalizedXYVector v_norm_2;

    using converted_type = decltype(v_norm_1 - v_norm_2);
    using required_type = decltype(View::XYVector{});

    CHECK(
        static_cast<bool>(std::is_same_v<converted_type, required_type>)
    );
}

//-------------------------------------------------------------------------------------------------
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Normalized XYVectors From Different Spaces Cannot Be Subtracted") {
    const View::NormalizedXYVector v_norm_1;
    const Image::NormalizedXYVector v_norm_2;

    // We should not be able to compile:
    // auto dummy = v_norm_1 - v_norm_2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v_norm_1 - v_norm_2);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVectors And XYVectors Can Be Subtracted") {
    const View::NormalizedXYVector v_norm_1(1, 0);
    const View::XYVector v_norm_2(0, 1);

    const auto added = v_norm_1 - v_norm_2;
    CHECK(added == View::XYVector(1, -1));
}
TEST_CASE("Normalized XYVectors And XYVectors Can Be Subtracted To Produce A XYVector") {
    const View::NormalizedXYVector v_norm_1;
    const View::XYVector v_2;

    using converted_type_A = decltype(v_norm_1 - v_2);
    using converted_type_B = decltype(v_2 - v_norm_1);
    using required_type = decltype(View::XYVector{});

    CHECK(static_cast<bool>(std::is_same_v<converted_type_A, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_B, required_type>));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedXYVectors And Vectors Can Be Subtracted To Produce A Vector") {
    const View::NormalizedXYVector v_norm_1;
    const View::Vector v_2;

    using converted_type_A = decltype(v_norm_1 - v_2);
    using converted_type_B = decltype(v_2 - v_norm_1);
    using required_type = decltype(View::Vector{});

    CHECK(static_cast<bool>(std::is_same_v<converted_type_A, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_B, required_type>));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedXYVectors And NormalizedVectors Can Be Subtracted To Produce A Vector") {
    const View::NormalizedXYVector v_norm_1;
    const View::NormalizedVector v_norm_2;

    using converted_type_A = decltype(v_norm_1 - v_norm_2);
    using converted_type_B = decltype(v_norm_2 - v_norm_1);
    using required_type = decltype(View::Vector{});

    CHECK(static_cast<bool>(std::is_same_v<converted_type_A, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_B, required_type>));
}

//-------------------------------------------------------------------------------------------------
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYVectors And Normalized XYVectors From Different Spaces Cannot Be Subtracted") {
    const View::XYVector v_1;
    const Image::NormalizedXYVector v_norm_2;

    // We should not be able to compile:
    // auto dummy = v_norm_1 - v_norm_2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type_A = decltype(v_1 - v_norm_2);
    using converted_type_B = decltype(v_norm_2 - v_1);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_A, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_B, required_type>));
}
#endif

//-------------------------------------------------------------------------------------------------
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Normalized XYVectors Cannot Be Inline Subtracted") {
    const View::NormalizedXYVector v_norm_1;
    const View::NormalizedXYVector v_norm_2;

    // We should not be able to compile:
    // v_norm_1 -= v_norm_2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v_norm_1 -= v_norm_2);
    using required_type = StaticAssert::invalid_normalized_vector_subtraction;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
TEST_CASE("Normalized XYVectors and Normalized XYVector Cannot Be Inline Subtracted") {
    const View::NormalizedVector v_norm_1;
    const View::NormalizedXYVector v_norm_2;

    // We should not be able to compile:
    // v_norm_1 -= v_norm_2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type_A = decltype(v_norm_1 -= v_norm_2);
    using converted_type_B = decltype(v_norm_2 -= v_norm_1);
    using required_type = StaticAssert::invalid_normalized_vector_subtraction;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_A, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_B, required_type>));
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVectors From The Same Space Can Be Dotted") {
    const View::NormalizedXYVector v1(1, 0);
    const View::NormalizedXYVector v2(1, 0);
    const auto dot = v1.Dot(v2);
    CHECK(dot == 1);
}
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Normalized XYVectors From Different Spaces Cannot Be Dotted") {
    const Image::NormalizedXYVector v1;
    const View::NormalizedXYVector v2;

    // We should not be able to compile:
    // auto dummy = v1.Dot(v2);
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type_A = decltype(v1.Dot(v2));
    using converted_type_B = decltype(v2.Dot(v1));
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_A, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_B, required_type>));
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("Vectors And NormalizedXYVectors From The Same Space Can Be Dotted") {
    const View::Vector v1(1, 0, 4);
    const View::NormalizedXYVector v2(1, 0);
    const auto dot = v1.Dot(v2);
    CHECK(dot == 1);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVectors And Vectors From The Same Space Can Be Dotted") {
    const View::NormalizedXYVector v1(1, 0);
    const View::Vector v2(1, 0, 4);
    const auto dot = v1.Dot(v2);
    CHECK(dot == 1);
}
TEST_CASE("Normalized XYVectors And NormalizedVector From The Same Space Can Be Dotted") {
    const View::NormalizedXYVector v1(1, 0);
    const View::NormalizedVector v2(1, 0, 0);
    const auto dot = v1.Dot(v2);
    CHECK(dot == 1);
}
TEST_CASE("Normalized XYVectors And XYVectors From The Same Space Can Be Dotted") {
    const View::NormalizedXYVector v1(1, 0);
    const View::XYVector v2(1, 0);
    const auto dot = v1.Dot(v2);
    CHECK(dot == 1);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVectors Can Be Assigned To A Vector") {
    const View::NormalizedXYVector v_norm(1, 0);
    const View::Vector v = v_norm;
    CHECK(v.X() == 1);
    CHECK(v.Y() == 0);
    CHECK(v.Z() == 0);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVectors Can Be Assigned To A XYVector") {
    const View::NormalizedXYVector v_norm(1, 0);
    const View::XYVector v = v_norm;
    CHECK(v.X() == 1);
    CHECK(v.Y() == 0);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedXYVectors Can Be Crossed") {
    const View::NormalizedXYVector v_norm_x(1, 0);
    const View::NormalizedXYVector v_norm_y(0, 1);

    const auto result = v_norm_x.Cross(v_norm_y);

    CHECK(result == View::NormalizedVector(0, 0, 1));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVectors Can Be Crossed To Give A New Normalized Vector") {
    const View::NormalizedXYVector v_norm_x;
    const View::NormalizedXYVector v_norm_y;

    using converted_type = decltype(v_norm_x.Cross(v_norm_y));
    using required_type = decltype(View::NormalizedVector{});
    CHECK(
        static_cast<bool>(std::is_same_v<converted_type, required_type>)
    );
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVectors and Normalized Vectors Can Be Crossed To Give A New Normalized Vector") {
    const View::NormalizedXYVector v_norm_x;
    const View::NormalizedVector v_norm_y;

    using converted_type_A = decltype(v_norm_x.Cross(v_norm_y));
    using converted_type_B = decltype(v_norm_y.Cross(v_norm_x));
    using required_type = decltype(View::NormalizedVector{});

    CHECK(static_cast<bool>(std::is_same_v<converted_type_A, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_B, required_type>));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVectors Can Be Crossed Using Star") {
    const View::NormalizedXYVector v_norm_x(1, 0);
    const View::NormalizedXYVector v_norm_y(0, 1);

    const auto result = v_norm_x * v_norm_y;

    CHECK(result == View::NormalizedVector(0, 0, 1));
}
TEST_CASE("Normalized XYVectors Can Be Crossed Using Star To Give A New Normalized Vector") {
    const View::NormalizedXYVector v_norm_x;
    const View::NormalizedXYVector v_norm_y;

    using converted_type = decltype(v_norm_x * v_norm_y);
    using required_type = decltype(View::NormalizedVector{});
    CHECK(
        static_cast<bool>(std::is_same_v<converted_type, required_type>)
    );
}

TEST_CASE("Normalized XYVectors And Normalized Vectors Can Be Crossed Using Star") {
    const View::NormalizedXYVector v_norm_x(1, 0);
    const View::NormalizedVector v_norm_y(0, 1, 0);

    const auto result = v_norm_x * v_norm_y;

    CHECK(result == View::NormalizedVector(0, 0, 1));
}
TEST_CASE("Normalized XYVectors And Normalized Vectors Can Be Crossed Using Star To Give A New Normalized Vector") {
    const View::NormalizedVector v_norm_x;
    const View::NormalizedXYVector v_norm_y;

    using converted_type_A = decltype(v_norm_x * v_norm_y);
    using converted_type_B = decltype(v_norm_y * v_norm_x);
    using required_type = decltype(View::NormalizedVector{});

    CHECK(static_cast<bool>(std::is_same_v<converted_type_A, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_B, required_type>));
}

TEST_CASE("Normalized XYVectors And Vectors Can Be Crossed Using Star") {
    const View::NormalizedXYVector v_norm(1, 0);
    const View::Vector v(0, 1, 0);

    const auto result = v_norm * v;

    CHECK(result == View::NormalizedVector(0, 0, 1));
}
TEST_CASE("Normalized XYVectors And Vectors Can Be Crossed Using Star To Give A New Vector") {
    const View::NormalizedVector v_norm;
    const View::Vector v;

    using converted_type_A = decltype(v_norm * v);
    using converted_type_B = decltype(v * v_norm);
    using required_type = decltype(View::Vector{});

    CHECK(static_cast<bool>(std::is_same_v<converted_type_A, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_B, required_type>));
}

TEST_CASE("Normalized XYVectors And XYVectors Can Be Crossed Using Star") {
    const View::NormalizedXYVector v_norm(1, 0);
    const View::XYVector v(0, 1);

    const auto result = v_norm * v;

    CHECK(result == View::NormalizedVector(0, 0, 1));
}
TEST_CASE("Normalized XYVectors And XYVectors Can Be Crossed Using Star To Give A New Vector") {
    const View::NormalizedVector v_norm;
    const View::XYVector v;

    using converted_type_A = decltype(v_norm * v);
    using converted_type_B = decltype(v * v_norm);
    using required_type = decltype(View::Vector{});

    CHECK(static_cast<bool>(std::is_same_v<converted_type_A, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_B, required_type>));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVectors And Vectors Can Be Crossed") {
    const View::NormalizedXYVector v_norm_x(1, 0);
    const View::Vector v_y(0, 1, 0);

    const auto result = v_norm_x.Cross(v_y);

    CHECK(result == View::NormalizedVector(0, 0, 1));
}
TEST_CASE("Normalized Vectors And Vectors Can Be Crossed To Give A New Vector") {
    const View::NormalizedXYVector v_norm_x;
    const View::Vector v_y;

    using converted_type_A = decltype(v_norm_x.Cross(v_y));
    using converted_type_B = decltype(v_y.Cross(v_norm_x));
    using required_type = decltype(View::Vector{});

    CHECK(static_cast<bool>(std::is_same_v<converted_type_A, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_B, required_type>));
}

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVectors Support Element Access By Name") {
    const View::NormalizedXYVector v;
    CHECK(v.X() == 1);
    CHECK(v.Y() == 0);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVectors Do Not Support Z Access By Name") {
    const View::NormalizedXYVector v2;

    // Should not compile
    //v2.Z();
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVectors Do Not Support Modifcation By Name") {
    View::NormalizedXYVector v2;

    // Should not compile:
    //v2.SetX(5);
    //v2.SetY(5);
    //v2.SetZ(5);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVectors Support Const Begin And End") {
    const View::NormalizedXYVector v(1, 0);
    std::vector<double> values;
    std::copy(v.cbegin(), v.cend(), std::back_inserter(values));
    CHECK(values.size() == 2);
    CHECK(values[0] == 1);
    CHECK(values[1] == 0);
}

//-------------------------------------------------------------------------------------------------
TEST_CASE("Normalized XYVectors Do Not Support Norm") {
    View::NormalizedXYVector nv;

    // We should not be able to compile:
    //auto dummy = nv.Norm();
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVectors Do Not Support removing Z") {
    View::NormalizedXYVector nv;
    // Should not compile
    // nv.ToXY();
}

TEST_CASE("Normalized XYVectors Do Not Support Non Const Begin") {
    View::NormalizedXYVector nv;
    // We should not be able to compile:
    // auto dummy = nv.begin();
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVectors Do Not Support Non Const End") {
    View::NormalizedXYVector nv;

    // We should not be able to compile:
    // auto dummy = nv.end();
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVectors Support Element Access By Random Access") {
    const View::NormalizedXYVector v(0, 1);
    CHECK(v[0] == 0);
    CHECK(v[1] == 1);
}

TEST_CASE("Normalized XYVectors Throw If Random Access Is Too High") {
    const View::NormalizedXYVector v(1, 0);
    CHECK_THROWS_AS(v[2], std::invalid_argument);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vectors Support Element Access By At") {
    const View::NormalizedXYVector v(1, 0);
    CHECK(v.at<0>() == 1);
    CHECK(v.at<1>() == 0);
}
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Normalized Vectors Support Element Access By At Does Not Compile If Too Low") {
    const View::NormalizedXYVector v;
    using converted_type = decltype(v.at<-1>());
    using required_type = StaticAssert::invalid_at_access;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
TEST_CASE("Normalized Vectors Support Element Access By At Does Not Compile If Too High") {
    const View::NormalizedXYVector v;
    using converted_type = decltype(v.at<2>());
    using required_type = StaticAssert::invalid_at_access;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVectors Can Be Converted From One Space To Another Ignoring Translation") {

    const TransformManager tm;
    const View::NormalizedXYVector v_view(1, 0);
    auto v_patient = v_view.ConvertTo<Patient>(tm);
    CHECK(v_patient == Patient::Vector(15, 16, 17));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsCanBeConvertedFromOneSpaceToAnotherProducing A Vector") {

    const TransformManager tm;
    const View::NormalizedXYVector v_view(1, 0);
    using converted_type = decltype(v_view.ConvertTo<Patient>(tm));
    using required_type = decltype(Patient::Vector{});
    CHECK(
        static_cast<bool>(std::is_same_v<converted_type, required_type>)
    );
}

//-------------------------------------------------------------------------------------------------

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Normalized XY Vectors Cannot Be Converted To The Same Space") {
    const TransformManager tm;
    const View::NormalizedXYVector v;
    using converted_type = decltype(v.ConvertTo<View>(tm));
    using required_type = StaticAssert::invalid_conversion;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized XYVector Can Be Streamed") {
    const View::NormalizedXYVector v(1, 0);
    std::stringstream stream;
    stream << v;
    CHECK(stream.str() == std::string("View::NormalizedXYVector (1, 0)"));
}

//-------------------------------------------------------------------------------------------------
