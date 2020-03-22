#include "pch.h"
#include "SpaceHelpers.h"

using namespace Space;

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2s can be constructed") {
    View::NormalizedVector2 v;
}

TEST_CASE("Normalized Vector2s default to the i vector") {
    View::NormalizedVector2 v;
    CHECK(v[0] == 1);
    CHECK(v[1] == 0);
}
TEST_CASE("Normalized Vector2s can be created using initalizer lists of two numbers") {
    View::NormalizedVector2 v{10, 0};
    CHECK(v[0] == 1);
    CHECK(v[1] == 0);
}

TEST_CASE("Normalized Vector2s throw when using initalizer lists that are too small") {
    try
    {
        View::NormalizedVector2 v{1};
    }
    catch (std::invalid_argument&)
    {
        return;
    }
    REQUIRE(false);
}
TEST_CASE("Normalized Vector2s throw when using initalizer lists that are too large") {
    try
    {
        View::NormalizedVector2 v{ 1, 2, 3 };
    }
    catch (std::invalid_argument&)
    {
        return;
    }
    REQUIRE(false);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2s Can Be Constructed And Normalized From Implementation") {
    TestVector impl;
    impl.m_values[0] = 3;
    impl.m_values[1] = 0;
    impl.m_values[2] = 0;

    const Patient::NormalizedVector2 v(impl);
    CHECK(v.X() == 1);
    CHECK(v.Y() == 0);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2s Can Be Constructed And Normalized From Two Doubles") {
    const Patient::NormalizedVector2 v(2, 0);
    CHECK(v.X() == 1);
    CHECK(v.Y() == 0);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2s Start Off Normalized") {
    const Patient::NormalizedVector2 v(3, 4);
    CHECK(v.X() == 3/5.0);
    CHECK(v.Y() == 4/5.0);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Zero Sized Normalized Vector2s Cannot Be Created") {
    CHECK_THROWS_AS(Patient::NormalizedVector2(0, 0), std::invalid_argument);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2s can be cast to the implementation") {
    const Patient::NormalizedVector2 v(1, 0);
    auto impl = static_cast<TestVector>(v);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2s are normalised and lose their Z when constructed from an implementation") {
    TestVector impl_in;
    impl_in.m_values[0] = 3;
    impl_in.m_values[1] = 4;
    impl_in.m_values[2] = 5;

    const Patient::NormalizedVector2 v(impl_in);
    auto impl = static_cast<TestVector>(v);
    CHECK(impl.m_values[0] == 3 / 5.0);
    CHECK(impl.m_values[1] == 4 / 5.0);
    CHECK(impl.m_values[2] == 0);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2s cannot be implicitly cast to the implementation") {
    const Patient::NormalizedVector2 v(1, 0);

    // This should not compile
    //TestVector impl = v;
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2 Can Be Passed By Value To Vector") {

    const Patient::NormalizedVector2 nv(1, 0);

    const auto lambda = [](
        const Patient::Vector v
    ) {
        CHECK(v.X() == 1);
        CHECK(v.Y() == 0);
        CHECK(v.Z() == 0);

    };

    lambda(nv);
}
//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2 Can Be Passed By Const Ref To Vector") {
    const Patient::NormalizedVector2 nv(1, 0);

    const auto lambda = [](
        const Patient::Vector& v
    ) {
        CHECK(v.X() == 1);
        CHECK(v.Y() == 0);
        CHECK(v.Z() == 0);
    };

    lambda(nv);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2 Can Be Passed By Value To Vector2") {

    const Patient::NormalizedVector2 nv(1, 0);

    const auto lambda = [](
        const Patient::Vector2 v
    ) {
        CHECK(v.X() == 1);
        CHECK(v.Y() == 0);

    };

    lambda(nv);
}
//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2 Can Be Passed By Const Ref To Vector2") {
    const Patient::NormalizedVector2 nv(1, 0);

    const auto lambda = [](
        const Patient::Vector2& v
    ) {
        CHECK(v.X() == 1);
        CHECK(v.Y() == 0);
    };

    lambda(nv);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2 Can Be Passed By Value To NormalizedVector") {

    const Patient::NormalizedVector2 nv(1, 0);

    const auto lambda = [](
        const Patient::NormalizedVector v
    ) {
        CHECK(v.X() == 1);
        CHECK(v.Y() == 0);
        CHECK(v.Z() == 0);

    };

    lambda(nv);
}
//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2 Can Be Passed By Const Ref To NormalizedVector") {
    const Patient::NormalizedVector2 nv(1, 0);

    const auto lambda = [](
        const Patient::NormalizedVector& v
    ) {
        CHECK(v.X() == 1);
        CHECK(v.Y() == 0);
        CHECK(v.Z() == 0);
    };

    lambda(nv);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2s From The Same Space Can Be Compared Using Equal") {
    const View::NormalizedVector2 v1(1, 0);
    const View::NormalizedVector2 v2(1, 0);
    CHECK(v1 == v2);
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Normalized Vector2s From Diffefent Spaces Cannot Be Compared Using Equal") {
    const View::NormalizedVector2 v1;
    const Patient::NormalizedVector2 v2;

    // We should not be able to compile:
    // auto dummy = v1 == v2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v1 == v2);
    using required_type = StaticAssert::invalid_equality;
    CHECK(static_cast<bool>(std::is_same<converted_type, required_type>::value));
}
#endif
//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2s From The Same Space Can Be Compared Using Inequality") {
    const View::NormalizedVector2 v1(1, 0);
    const View::NormalizedVector2 v2(1, 0);
    CHECK(!(v1 != v2));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Normalized Vector2s From Diffefent Spaces Cannot Be Compared Using Inequality") {
    const View::NormalizedVector2 v1;
    const Patient::NormalizedVector2 v2;

    // We should not be able to compile:
    // auto dummy = v1 != v2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v1 != v2);
    using required_type = StaticAssert::invalid_equality;
    CHECK(static_cast<bool>(std::is_same<converted_type, required_type>::value));
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2s and Normalized Vectors From The Same Space Can Be Compared Using Equal") {
    const View::NormalizedVector2 v1(1, 0);
    const View::NormalizedVector v2(1, 0, 0);
    CHECK(v1 == v2);
    CHECK(v2 == v1);
}

TEST_CASE("Normalized Vector2s and Vector2s From The Same Space Can Be Compared Using Equal") {
    const View::NormalizedVector2 v1(1, 0);
    const View::Vector2 v2(1, 0);
    CHECK(v1 == v2);
    CHECK(v2 == v1);
}

TEST_CASE("Normalized Vector2s and Vectors From The Same Space Can Be Compared Using Equal") {
    const View::NormalizedVector2 v1(1, 0);
    const View::Vector v2(1, 0, 0);
    CHECK(v1 == v2);
    CHECK(v2 == v1);
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Normalized Vector2s And Normalized Vectors From Diffefent Spaces Cannot Be Compared Using Equal") {
    const View::NormalizedVector2 v1;
    const Patient::NormalizedVector v2;

    // We should not be able to compile:
    // auto dummy = v1 == v2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type_A = decltype(v1 == v2);
    using converted_type_B = decltype(v2 == v1);
    using required_type = StaticAssert::invalid_equality;
    CHECK(static_cast<bool>(std::is_same<converted_type_A, required_type>::value));
    CHECK(static_cast<bool>(std::is_same<converted_type_B, required_type>::value));
}
TEST_CASE("Normalized Vector2s And Vectors From Diffefent Spaces Cannot Be Compared Using Equal") {
    const View::NormalizedVector2 v1;
    const Patient::Vector v2;

    // We should not be able to compile:
    // auto dummy = v1 == v2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type_A = decltype(v1 == v2);
    using converted_type_B = decltype(v2 == v1);
    using required_type = StaticAssert::invalid_equality;
    CHECK(static_cast<bool>(std::is_same<converted_type_A, required_type>::value));
    CHECK(static_cast<bool>(std::is_same<converted_type_B, required_type>::value));
}
TEST_CASE("Normalized Vector2s And Vector2s From Diffefent Spaces Cannot Be Compared Using Equal") {
    const View::NormalizedVector2 v1;
    const Patient::Vector2 v2;

    // We should not be able to compile:
    // auto dummy = v1 == v2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type_A = decltype(v1 == v2);
    using converted_type_B = decltype(v2 == v1);
    using required_type = StaticAssert::invalid_equality;
    CHECK(static_cast<bool>(std::is_same<converted_type_A, required_type>::value));
    CHECK(static_cast<bool>(std::is_same<converted_type_B, required_type>::value));
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2s Can Be Multiplied") {
    const View::NormalizedVector2 v_norm(1, 0);
    const auto scaled_v = v_norm * 2;
    CHECK(scaled_v == View::Vector2(2, 0));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2s Can Be Multiplied to produce a 2D Vector") {
    const Image::NormalizedVector2 v_norm;

    using converted_type = decltype(v_norm * 2);
    using required_type = decltype(Image::Vector2{});

    CHECK(static_cast<bool>(std::is_same<converted_type, required_type>::value));
}

//-------------------------------------------------------------------------------------------------
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Normalized Vector2s Cannot Be Inline Scaled") {
    const Image::NormalizedVector2 v_norm;

    // We should not be able to compile:
    // v_norm *= 2.0;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v_norm *= 2.0);
    using required_type = StaticAssert::invalid_normalized_vector_scale;
    CHECK(static_cast<bool>(std::is_same<converted_type, required_type>::value));
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2s Can Be Added") {
    const Image::NormalizedVector2 v_norm_1(1, 0);
    const Image::NormalizedVector2 v_norm_2(0, 1);

    const auto added = v_norm_1 + v_norm_2;
    CHECK(added == Image::Vector2(1, 1));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2s and Vector2s Can Be Added") {
    const Image::NormalizedVector2 v_norm_1(1, 0);
    const Image::Vector2 v_norm_2(0, 1);

    const auto added = v_norm_1 + v_norm_2;
    CHECK(added == Image::Vector2(1, 1));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2s Can Be Added To Produce A Vector2") {
    const Image::NormalizedVector2 v_norm_1;
    const Image::NormalizedVector2 v_norm_2;

    using converted_type_A = decltype(v_norm_1 + v_norm_2);
    using converted_type_B = decltype(v_norm_2 + v_norm_1);
    using required_type = decltype(Image::Vector2{});

    CHECK(static_cast<bool>(std::is_same<converted_type_A, required_type>::value));
    CHECK(static_cast<bool>(std::is_same<converted_type_B, required_type>::value));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2s Can Be Added To Vector2s") {
    const Image::NormalizedVector2 v_norm_1(1, 0);
    const Image::Vector2 v_norm_2(0, 1);

    const auto added = v_norm_1 + v_norm_2;
    CHECK(added == Image::Vector2(1, 1));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2s Can Be Added To Vector2s to Produce A Vector2") {
    const Image::NormalizedVector2 v_norm_1;
    const Image::Vector2 v_2;

    using converted_type_A = decltype(v_norm_1 + v_2);
    using converted_type_B = decltype(v_2 + v_norm_1);
    using required_type = decltype(Image::Vector2{});

    CHECK(static_cast<bool>(std::is_same<converted_type_A, required_type>::value));
    CHECK(static_cast<bool>(std::is_same<converted_type_B, required_type>::value));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2s Can Be Added To Vectors") {
    const Image::NormalizedVector2 v_norm_1(1, 0);
    const Image::Vector v_norm_2(0, 1, 0);

    const auto added = v_norm_1 + v_norm_2;
    CHECK(added == Image::Vector(1, 1, 0));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2s Can Be Added To Vectors to Produce A Vector") {
    const Image::NormalizedVector2 v_norm_1;
    const Image::Vector v_2;

    using converted_type_A = decltype(v_norm_1 + v_2);
    using converted_type_B = decltype(v_2 + v_norm_1);
    using required_type = decltype(Image::Vector{});

    CHECK(static_cast<bool>(std::is_same<converted_type_A, required_type>::value));
    CHECK(static_cast<bool>(std::is_same<converted_type_B, required_type>::value));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2s Can Be Added To Normalized Vectors") {
    const Image::NormalizedVector2 v_norm_1(1, 0);
    const Image::NormalizedVector v_norm_2(0, 1, 0);

    const auto added = v_norm_1 + v_norm_2;
    CHECK(added == Image::Vector(1, 1, 0));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2s Can Be Added To Normalized Vectors to Produce A Vector") {
    const Image::NormalizedVector2 v_norm_1;
    const Image::NormalizedVector v_norm_2;

    using converted_type_A = decltype(v_norm_1 + v_norm_2);
    using converted_type_B = decltype(v_norm_2 + v_norm_1);
    using required_type = decltype(Image::Vector{});

    CHECK(static_cast<bool>(std::is_same<converted_type_A, required_type>::value));
    CHECK(static_cast<bool>(std::is_same<converted_type_B, required_type>::value));
}

//-------------------------------------------------------------------------------------------------
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Normalized Vector2s From Different Spaces Cannot Be Added") {
    const Image::NormalizedVector2 v_norm_1;
    const Patient::NormalizedVector2 v_norm_2;

    // We should not be able to compile:
    // auto dummy = v_norm_1 + v_norm_2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type_A = decltype(v_norm_1 + v_norm_2);
    using converted_type_B = decltype(v_norm_2 + v_norm_1);
    using required_type = StaticAssert::invalid_vector_to_vector_addition;
    CHECK(static_cast<bool>(std::is_same<converted_type_A, required_type>::value));
    CHECK(static_cast<bool>(std::is_same<converted_type_B, required_type>::value));
}
#endif

//-------------------------------------------------------------------------------------------------
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Vector2s And Normalized Vector2s From Different Spaces Cannot Be Added") {
    const Image::Vector2 v_1;
    const Patient::NormalizedVector2 v_norm_2;

    // We should not be able to compile:
    // auto dummy = v_norm_1 + v_norm_2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type_A = decltype(v_1 + v_norm_2);
    using converted_type_B = decltype(v_norm_2 + v_1);
    using required_type = StaticAssert::invalid_vector_to_vector_addition;
    CHECK(static_cast<bool>(std::is_same<converted_type_A, required_type>::value));
    CHECK(static_cast<bool>(std::is_same<converted_type_B, required_type>::value));
}
#endif

//-------------------------------------------------------------------------------------------------
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Normalized Vector2s Cannot Be Inline Added") {
    const Image::NormalizedVector2 v_norm_1;
    const Image::NormalizedVector2 v_norm_2;

    // We should not be able to compile:
    // v_norm_1 += v_norm_2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v_norm_1 += v_norm_2);
    using required_type = StaticAssert::invalid_normalized_vector_addition;
    CHECK(static_cast<bool>(std::is_same<converted_type, required_type>::value));
}
#endif


//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2s Can Be Subtracted") {
    const Image::NormalizedVector2 v_norm_1(1, 0);
    const Image::NormalizedVector2 v_norm_2(0, 1);

    const auto added = v_norm_1 - v_norm_2;
    CHECK(added == Image::Vector2(1, -1));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2s Can Be Subtracted To Produce A Vector2") {
    const Image::NormalizedVector2 v_norm_1;
    const Image::NormalizedVector2 v_norm_2;

    using converted_type = decltype(v_norm_1 - v_norm_2);
    using required_type = decltype(Image::Vector2{});

    CHECK(
        static_cast<bool>(std::is_same<converted_type, required_type>::value)
    );
}

//-------------------------------------------------------------------------------------------------
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Normalized Vector2s From Different Spaces Cannot Be Subtracted") {
    const Image::NormalizedVector2 v_norm_1;
    const Patient::NormalizedVector2 v_norm_2;

    // We should not be able to compile:
    // auto dummy = v_norm_1 - v_norm_2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v_norm_1 - v_norm_2);
    using required_type = StaticAssert::invalid_vector_to_vector_subtraction;
    CHECK(static_cast<bool>(std::is_same<converted_type, required_type>::value));
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2s And Vector2s Can Be Subtracted") {
    const Image::NormalizedVector2 v_norm_1(1, 0);
    const Image::Vector2 v_norm_2(0, 1);

    const auto added = v_norm_1 - v_norm_2;
    CHECK(added == Image::Vector2(1, -1));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2s And Vector2s Can Be Subtracted To Produce A Vector2") {
    const Image::NormalizedVector2 v_norm_1;
    const Image::Vector2 v_2;

    using converted_type_A = decltype(v_norm_1 - v_2);
    using converted_type_B = decltype(v_2 - v_norm_1);
    using required_type = decltype(Image::Vector2{});

    CHECK(static_cast<bool>(std::is_same<converted_type_A, required_type>::value));
    CHECK(static_cast<bool>(std::is_same<converted_type_B, required_type>::value));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVector2s And Vectors Can Be Subtracted To Produce A Vector") {
    const Image::NormalizedVector2 v_norm_1;
    const Image::Vector v_2;

    using converted_type_A = decltype(v_norm_1 - v_2);
    using converted_type_B = decltype(v_2 - v_norm_1);
    using required_type = decltype(Image::Vector{});

    CHECK(static_cast<bool>(std::is_same<converted_type_A, required_type>::value));
    CHECK(static_cast<bool>(std::is_same<converted_type_B, required_type>::value));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVector2s And NormalizedVectors Can Be Subtracted To Produce A Vector") {
    const Image::NormalizedVector2 v_norm_1;
    const Image::NormalizedVector v_norm_2;

    using converted_type_A = decltype(v_norm_1 - v_norm_2);
    using converted_type_B = decltype(v_norm_2 - v_norm_1);
    using required_type = decltype(Image::Vector{});

    CHECK(static_cast<bool>(std::is_same<converted_type_A, required_type>::value));
    CHECK(static_cast<bool>(std::is_same<converted_type_B, required_type>::value));
}

//-------------------------------------------------------------------------------------------------
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Vector2s And Normalized Vector2s From Different Spaces Cannot Be Subtracted") {
    const Image::Vector2 v_1;
    const Patient::NormalizedVector2 v_norm_2;

    // We should not be able to compile:
    // auto dummy = v_norm_1 - v_norm_2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type_A = decltype(v_1 - v_norm_2);
    using converted_type_B = decltype(v_norm_2 - v_1);
    using required_type = StaticAssert::invalid_vector_to_vector_subtraction;
    CHECK(static_cast<bool>(std::is_same<converted_type_A, required_type>::value));
    CHECK(static_cast<bool>(std::is_same<converted_type_B, required_type>::value));
}
#endif

//-------------------------------------------------------------------------------------------------
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Normalized Vector2s Cannot Be Inline Subtracted") {
    const Image::NormalizedVector2 v_norm_1;
    const Image::NormalizedVector2 v_norm_2;

    // We should not be able to compile:
    // v_norm_1 -= v_norm_2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v_norm_1 -= v_norm_2);
    using required_type = StaticAssert::invalid_normalized_vector_subtraction;
    CHECK(static_cast<bool>(std::is_same<converted_type, required_type>::value));
}
TEST_CASE("Normalized Vector2s and Normalized Vector2 Cannot Be Inline Subtracted") {
    const Image::NormalizedVector v_norm_1;
    const Image::NormalizedVector2 v_norm_2;

    // We should not be able to compile:
    // v_norm_1 -= v_norm_2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type_A = decltype(v_norm_1 -= v_norm_2);
    using converted_type_B = decltype(v_norm_2 -= v_norm_1);
    using required_type = StaticAssert::invalid_normalized_vector_subtraction;
    CHECK(static_cast<bool>(std::is_same<converted_type_A, required_type>::value));
    CHECK(static_cast<bool>(std::is_same<converted_type_B, required_type>::value));
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2s From The Same Space Can Be Dotted") {
    const View::NormalizedVector2 v1(1, 0);
    const View::NormalizedVector2 v2(1, 0);
    const auto dot = v1.Dot(v2);
    CHECK(dot == 1);
}
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Normalized Vector2s From Different Spaces Cannot Be Dotted") {
    const View::NormalizedVector2 v1;
    const Image::NormalizedVector2 v2;

    // We should not be able to compile:
    // auto dummy = v1.Dot(v2);
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v1.Dot(v2));
    using required_type = StaticAssert::invalid_vector_dot;
    CHECK(static_cast<bool>(std::is_same<converted_type, required_type>::value));
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("Vectors And NormalizedVector2s From The Same Space Can Be Dotted") {
    const View::Vector v1(1, 0, 4);
    const View::NormalizedVector2 v2(1, 0);
    const auto dot = v1.Dot(v2);
    CHECK(dot == 1);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2s And Vector2s From The Same Space Can Be Dotted") {
    const View::NormalizedVector2 v1(1, 0);
    const View::Vector v2(1, 0, 4);
    const auto dot = v1.Dot(v2);
    CHECK(dot == 1);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2s Can Be Assigned To A Vector") {
    const Image::NormalizedVector2 v_norm(1, 0);
    const Image::Vector v = v_norm;
    CHECK(v.X() == 1);
    CHECK(v.Y() == 0);
    CHECK(v.Z() == 0);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2s Can Be Assigned To A Vector2") {
    const Image::NormalizedVector2 v_norm(1, 0);
    const Image::Vector2 v = v_norm;
    CHECK(v.X() == 1);
    CHECK(v.Y() == 0);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVector2s Can Be Crossed") {
    const Image::NormalizedVector2 v_norm_x(1, 0);
    const Image::NormalizedVector2 v_norm_y(0, 1);

    const auto result = v_norm_x.Cross(v_norm_y);

    CHECK(result == Image::NormalizedVector(0, 0, 1));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2s Can Be Crossed To Give A New Normalized Vector") {
    const Image::NormalizedVector2 v_norm_x;
    const Image::NormalizedVector2 v_norm_y;

    using converted_type = decltype(v_norm_x.Cross(v_norm_y));
    using required_type = decltype(Image::NormalizedVector{});
    CHECK(
        static_cast<bool>(std::is_same<converted_type, required_type>::value)
    );
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2s and Normalized Vectors Can Be Crossed To Give A New Normalized Vector") {
    const Image::NormalizedVector2 v_norm_x;
    const Image::NormalizedVector v_norm_y;

    using converted_type_A = decltype(v_norm_x.Cross(v_norm_y));
    using converted_type_B = decltype(v_norm_y.Cross(v_norm_x));
    using required_type = decltype(Image::NormalizedVector{});

    CHECK(static_cast<bool>(std::is_same<converted_type_A, required_type>::value));
    CHECK(static_cast<bool>(std::is_same<converted_type_B, required_type>::value));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2s Can Be Crossed Using Star") {
    const Image::NormalizedVector2 v_norm_x(1, 0);
    const Image::NormalizedVector2 v_norm_y(0, 1);

    const auto result = v_norm_x * v_norm_y;

    CHECK(result == Image::NormalizedVector(0, 0, 1));
}
TEST_CASE("Normalized Vector2s Can Be Crossed Using Star To Give A New Normalized Vector") {
    const Image::NormalizedVector2 v_norm_x;
    const Image::NormalizedVector2 v_norm_y;

    using converted_type = decltype(v_norm_x * v_norm_y);
    using required_type = decltype(Image::NormalizedVector{});
    CHECK(
        static_cast<bool>(std::is_same<converted_type, required_type>::value)
    );
}

TEST_CASE("Normalized Vector2s And Normalized Vectors Can Be Crossed Using Star To Give A New Normalized Vector") {
    const Image::NormalizedVector v_norm_x;
    const Image::NormalizedVector2 v_norm_y;

    using converted_type_A = decltype(v_norm_x * v_norm_y);
    using converted_type_B = decltype(v_norm_y * v_norm_x);
    using required_type = decltype(Image::NormalizedVector{});

    CHECK(static_cast<bool>(std::is_same<converted_type_A, required_type>::value));
    CHECK(static_cast<bool>(std::is_same<converted_type_B, required_type>::value));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2s And Vectors Can Be Crossed") {
    const Image::NormalizedVector2 v_norm_x(1, 0);
    const Image::Vector v_y(0, 1, 0);

    const auto result = v_norm_x.Cross(v_y);

    CHECK(result == Image::NormalizedVector(0, 0, 1));
}
TEST_CASE("Normalized Vectors And Vectors Can Be Crossed To Give A New Vector") {
    const Image::NormalizedVector2 v_norm_x;
    const Image::Vector v_y;

    using converted_type_A = decltype(v_norm_x.Cross(v_y));
    using converted_type_B = decltype(v_y.Cross(v_norm_x));
    using required_type = decltype(Image::Vector{});

    CHECK(static_cast<bool>(std::is_same<converted_type_A, required_type>::value));
    CHECK(static_cast<bool>(std::is_same<converted_type_B, required_type>::value));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2s And Vectors Can Be Crossed Using Star") {
    const Image::NormalizedVector2 v_norm_x;
    const Image::Vector v_y(0, 1, 0);

    const auto result = v_norm_x * v_y;

    CHECK(result == Image::Vector(0, 0, 1));
}
TEST_CASE("Normalized Vector2s And Vectors Can Be Crossed Using Star To Give A New Vector") {
    const Image::NormalizedVector2 v_norm_x;
    const Image::Vector v_y;

    using converted_type_A = decltype(v_norm_x * v_y);
    using converted_type_B = decltype(v_y * v_norm_x);
    using required_type = decltype(Image::Vector{});

    CHECK(static_cast<bool>(std::is_same<converted_type_A, required_type>::value));
    CHECK(static_cast<bool>(std::is_same<converted_type_B, required_type>::value));
}
//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2s Support Element Access By Name") {
    const Image::NormalizedVector2 v;
    CHECK(v.X() == 1);
    CHECK(v.Y() == 0);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2s Do Not Support Z Access By Name") {
    const Image::NormalizedVector2 v2;

    using converted_type = decltype(v2.Z());
    using required_type = StaticAssert::z_not_supported;
    CHECK(static_cast<bool>(std::is_same<converted_type, required_type>::value));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2s Support Const Begin And End") {
    const Image::NormalizedVector2 v(1, 0);
    std::vector<double> values;
    std::copy(v.cbegin(), v.cend(), std::back_inserter(values));
    CHECK(values.size() == 2);
    CHECK(values[0] == 1);
    CHECK(values[1] == 0);
}

//-------------------------------------------------------------------------------------------------
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Normalized Vector2s Do Not Support Norm") {
    Image::NormalizedVector2 nv;

    // We should not be able to compile:
    // auto dummy = nv.begin();
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(nv.Norm());
    using required_type = StaticAssert::normalized_vectors_do_not_support_norm;
    CHECK(static_cast<bool>(std::is_same<converted_type, required_type>::value));
}

TEST_CASE("Normalized Vector2s Do Not Support Non Const Begin") {
    Image::NormalizedVector2 nv;

    // We should not be able to compile:
    // auto dummy = nv.begin();
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(nv.begin());
    using required_type = StaticAssert::normalized_vectors_do_not_support_non_const_iteration;
    CHECK(static_cast<bool>(std::is_same<converted_type, required_type>::value));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2s Do Not Support Non Const End") {
    Image::NormalizedVector2 nv;

    // We should not be able to compile:
    // auto dummy = nv.end();
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(nv.end());
    using required_type = StaticAssert::normalized_vectors_do_not_support_non_const_iteration;
    CHECK(static_cast<bool>(std::is_same<converted_type, required_type>::value));
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2s Support Element Access By Random Access") {
    const Image::NormalizedVector2 v(0, 1);
    CHECK(v[0] == 0);
    CHECK(v[1] == 1);
}

TEST_CASE("Normalized Vector2s Throw If Random Access Is Too High") {
    const Image::NormalizedVector2 v(1, 0);
    CHECK_THROWS_AS(v[2], std::invalid_argument);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vectors Support Element Access By At") {
    const Image::NormalizedVector2 v(1, 0);
    CHECK(v.at<0>() == 1);
    CHECK(v.at<1>() == 0);
}
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Normalized Vectors Support Element Access By At Does Not Compile If Too Low") {
    const Image::NormalizedVector2 v;
    using converted_type = decltype(v.at<-1>());
    using required_type = StaticAssert::invalid_at_access;
    CHECK(static_cast<bool>(std::is_same<converted_type, required_type>::value));
}
TEST_CASE("Normalized Vectors Support Element Access By At Does Not Compile If Too High") {
    const Image::NormalizedVector2 v;
    using converted_type = decltype(v.at<2>());
    using required_type = StaticAssert::invalid_at_access;
    CHECK(static_cast<bool>(std::is_same<converted_type, required_type>::value));
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2s Can Be Converted From One Space To Another Ignoring Translation") {

    const TransformManager tm;
    const View::NormalizedVector2 v_view(1, 0);
    auto v_patient = v_view.ConvertTo<Patient>(tm);
    CHECK(v_patient == Patient::Vector(15, 16, 17));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsCanBeConvertedFromOneSpaceToAnotherProducing A Vector") {

    const TransformManager tm;
    const View::NormalizedVector v_view(1, 0, 0);
    using converted_type = decltype(v_view.ConvertTo<Patient>(tm));
    using required_type = decltype(Patient::Vector{});
    CHECK(
        static_cast<bool>(std::is_same<converted_type, required_type>::value)
    );
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vector2 Can Be Streamed") {
    const View::NormalizedVector2 v(1, 0);
    std::stringstream stream;
    stream << v;
    CHECK(stream.str() == std::string("View::NormalizedVector2 (1, 0)"));
}

//-------------------------------------------------------------------------------------------------
