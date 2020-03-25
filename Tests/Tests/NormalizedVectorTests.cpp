#include "pch.h"
#include "SpaceHelpers.h"

using namespace Space;

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vectors can be constructed") {
    View::NormalizedVector v;
}

TEST_CASE("Normalized Vectors default to the i vector") {
    View::NormalizedVector v;
    CHECK(v[0] == 1);
    CHECK(v[1] == 0);
    CHECK(v[2] == 0);
}
TEST_CASE("Normalized Vectors can be created using initalizer lists of three numbers") {
    View::NormalizedVector v{10, 0, 0 };
    CHECK(v[0] == 1);
    CHECK(v[1] == 0);
    CHECK(v[2] == 0);
}

TEST_CASE("Normalized Vectors throw when using initalizer lists that are too small") {
    try
    {
        View::NormalizedVector v{ 1, 2 };
    }
    catch (std::invalid_argument&)
    {
        return;
    }
    REQUIRE(false);
}
TEST_CASE("Normalized Vectors throw when using initalizer lists that are too large") {
    try
    {
        View::NormalizedVector v{ 1, 2, 3, 4 };
    }
    catch (std::invalid_argument&)
    {
        return;
    }
    REQUIRE(false);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsCanBeConstructedAndNormalizedFromImplementation") {
    TestVector impl;
    impl.m_values[0] = 3;
    impl.m_values[1] = 0;
    impl.m_values[2] = 0;
    const Patient::NormalizedVector v(impl);
    CHECK(v.X() == 1);
    CHECK(v.Y() == 0);
    CHECK(v.Z() == 0);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vectors are normalised when constructed from an implementation") {
    TestVector impl_in;
    impl_in.m_values[0] = 3;
    impl_in.m_values[1] = 0;
    impl_in.m_values[2] = 4;
    const Patient::NormalizedVector v(impl_in);
    auto impl = static_cast<TestVector>(v);
    CHECK(impl.m_values[0] == 3 / 5.0);
    CHECK(impl.m_values[1] == 0);
    CHECK(impl.m_values[2] == 4 / 5.0);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsCanBeConstructedAndNormalizedFromThreeDoubles") {
    const Patient::NormalizedVector v(2, 0, 0);
    CHECK(v.X() == 1);
    CHECK(v.Y() == 0);
    CHECK(v.Z() == 0);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsStartOffNormalized") {
    const Patient::NormalizedVector v(3, 4, 0);
    CHECK(v.X() == 3/5.0);
    CHECK(v.Y() == 4/5.0);
    CHECK(v.Z() == 0);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("ZeroSizedNormalizedVectorsCannotBeCreated") {
    CHECK_THROWS_AS(Patient::NormalizedVector(0, 0, 0), std::invalid_argument);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vectors can be cast to the implementation") {
    const Patient::NormalizedVector v(1, 0, 0);
    auto impl = static_cast<TestVector>(v);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vectors cannot be implicitly cast to the implementation") {
    const Patient::NormalizedVector v(1, 0, 0);

    // This should not compile
    //TestVector impl = v;
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorCanBePassedByValueToVector") {

    const Patient::NormalizedVector nv(0, 0, 1);

    const auto lambda = [](
        const Patient::Vector v
    ) {
        CHECK(v.X() == 0);
        CHECK(v.Y() == 0);
        CHECK(v.Z() == 1);

    };

    lambda(nv);
}
//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorCanBePassedByConstRefToVector") {
    const Patient::NormalizedVector nv(0, 0, 1);

    const auto lambda = [](
        const Patient::Vector& v
    ) {
        CHECK(v.X() == 0);
        CHECK(v.Y() == 0);
        CHECK(v.Z() == 1);
    };

    lambda(nv);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsFromTheSameSpaceCanBeComparedUsingEqual_same") {
    const View::NormalizedVector v1(1, 0, 0);
    const View::NormalizedVector v2(1, 0, 0);
    CHECK(v1 == v2);
}

TEST_CASE("NormalizedVectorsFromTheSameSpaceCanBeComparedUsingEqual_different") {
    const Patient::NormalizedVector v1(1, 0, 0);
    const Patient::NormalizedVector v2(0, 1, 0);
    CHECK(!(v1 == v2));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("NormalizedVectorsFromDifferentSpacesCannotBeComparedUsingEqual") {
    const View::NormalizedVector v1(1, 0, 0);
    const Patient::NormalizedVector v2(1, 0, 0);

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

TEST_CASE("NormalizedVectorsFromTheSameSpaceCanBeComparedUsingInequality_same") {
    const View::NormalizedVector v1(1, 0, 0);
    const View::NormalizedVector v2(1, 0, 0);
    CHECK(!(v1 != v2));
}

TEST_CASE("NormalizedVectorsFromTheSameSpaceCanBeComparedUsingInequality_different") {
    const Patient::Vector v1(1, 0, 0);
    const Patient::Vector v2(0, 1, 0);
    CHECK(v1 != v2);
}
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("NormalizedVectorsFromDifferentSpacesCannotBeComparedUsingInequality") {
    const View::NormalizedVector v1(1, 0, 0);
    const Patient::NormalizedVector v2(1, 0, 0);

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

TEST_CASE("NormalizedVectorsCanBeMultiplied") {
    const View::NormalizedVector v_norm(1, 0, 0);
    const auto scaled_v = v_norm * 2;
    CHECK(scaled_v == View::Vector(2, 0, 0));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsCanBeScaledToProduceAVector") {
    const Image::NormalizedVector v_norm(1, 0, 0);

    using converted_type = decltype(v_norm * 2);
    using required_type = decltype(Image::Vector{});

    CHECK(
        static_cast<bool>(std::is_same_v<converted_type, required_type>)
    );
}

//-------------------------------------------------------------------------------------------------
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("NormalizedVectorsCannotBeInlineScaled") {
    const Image::NormalizedVector v_norm(1, 0, 0);

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

TEST_CASE("NormalizedVectorsCanBeAdded") {
    const Image::NormalizedVector v_norm_1(1, 0, 0);
    const Image::NormalizedVector v_norm_2(0, 1, 0);

    const auto added = v_norm_1 + v_norm_2;
    CHECK(added == Image::Vector(1, 1, 0));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsCanBeAddedToProduceAVector") {
    const Image::NormalizedVector v_norm_1(1, 0, 0);
    const Image::NormalizedVector v_norm_2(0, 1, 0);

    using converted_type = decltype(v_norm_1 + v_norm_2);
    using required_type = decltype(Image::Vector{});

    CHECK(
        static_cast<bool>(std::is_same_v<converted_type, required_type>)
    );
}

//-------------------------------------------------------------------------------------------------
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("NormalizedVectorsFromDifferentSpacesCannotBeAdded") {
    const Image::NormalizedVector v_norm_1(1, 0, 0);
    const Patient::NormalizedVector v_norm_2(0, 1, 0);

    // We should not be able to compile:
    // auto dummy = v_norm_1 + v_norm_2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v_norm_1 + v_norm_2);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsAndVectorsCanBeAdded") {
    const Image::NormalizedVector v_norm_1(1, 0, 0);
    const Image::Vector v_norm_2(0, 1, 0);

    const auto added = v_norm_1 + v_norm_2;
    CHECK(added == Image::Vector(1, 1, 0));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsAndVectorsCanBeAddedToProduceAVector") {
    const Image::NormalizedVector v_norm_1(1, 0, 0);
    const Image::Vector v_2(0, 1, 0);

    using converted_type = decltype(v_norm_1 + v_2);
    using required_type = decltype(Image::Vector{});

    CHECK(
        static_cast<bool>(std::is_same_v<converted_type, required_type>)
    );
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsAndNormalizedVectorsCanBeAddedToProduceAVector") {
    const Image::Vector v_1(1, 0, 0);
    const Image::NormalizedVector v_norm_2(0, 1, 0);

    using converted_type = decltype(v_1 + v_norm_2);
    using required_type = decltype(Image::Vector{});

    CHECK(
        static_cast<bool>(std::is_same_v<converted_type, required_type>)
    );
}

//-------------------------------------------------------------------------------------------------
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("VectorsAndNormalizedVectorsFromDifferentSpacesCannotBeAdded") {
    const Image::Vector v_norm_1(1, 0, 0);
    const Patient::NormalizedVector v_norm_2(0, 1, 0);

    // We should not be able to compile:
    // auto dummy = v_norm_1 + v_norm_2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v_norm_1 + v_norm_2);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

//-------------------------------------------------------------------------------------------------
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("NormalizedVectorsCannotBeInlineAdded") {
    const Image::NormalizedVector v_norm_1(1, 0, 0);
    const Image::NormalizedVector v_norm_2(0, 1, 0);

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

TEST_CASE("NormalizedVectorsCanBeSubtracted") {
    const Image::NormalizedVector v_norm_1(1, 0, 0);
    const Image::NormalizedVector v_norm_2(0, 1, 0);

    const auto added = v_norm_1 - v_norm_2;
    CHECK(added == Image::Vector(1, -1, 0));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsCanBeSubtractedFromProduceAVector") {
    const Image::NormalizedVector v_norm_1(1, 0, 0);
    const Image::NormalizedVector v_norm_2(0, 1, 0);

    using converted_type = decltype(v_norm_1 - v_norm_2);
    using required_type = decltype(Image::Vector{});

    CHECK(
        static_cast<bool>(std::is_same_v<converted_type, required_type>)
    );
}

//-------------------------------------------------------------------------------------------------
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("NormalizedVectorsFromDifferentSpacesCannotBeSubtracted") {
    const Image::NormalizedVector v_norm_1(1, 0, 0);
    const Patient::NormalizedVector v_norm_2(0, 1, 0);

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

TEST_CASE("NormalizedVectorsAndVectorsCanBeSubtracted") {
    const Image::NormalizedVector v_norm_1(1, 0, 0);
    const Image::Vector v_norm_2(0, 1, 0);

    const auto added = v_norm_1 - v_norm_2;
    CHECK(added == Image::Vector(1, -1, 0));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsAndVectorsCanBeSubtractedFromProduceAVector") {
    const Image::NormalizedVector v_norm_1(1, 0, 0);
    const Image::Vector v_2(0, 1, 0);

    using converted_type = decltype(v_norm_1 - v_2);
    using required_type = decltype(Image::Vector{});

    CHECK(
        static_cast<bool>(std::is_same_v<converted_type, required_type>)
    );
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsAndNormalizedVectorsCanBeSubtractedFromProduceAVector") {
    const Image::Vector v_1(1, 0, 0);
    const Image::NormalizedVector v_norm_2(0, 1, 0);

    using converted_type = decltype(v_1 - v_norm_2);
    using required_type = decltype(Image::Vector{});

    CHECK(
        static_cast<bool>(std::is_same_v<converted_type, required_type>)
    );
}

//-------------------------------------------------------------------------------------------------
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("VectorsAndNormalizedVectorsFromDifferentSpacesCannotBeSubtracted") {
    const Image::Vector v_norm_1(1, 0, 0);
    const Patient::NormalizedVector v_norm_2(0, 1, 0);

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
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("NormalizedVectorsCannotBeInlineSubtracted") {
    const Image::NormalizedVector v_norm_1(1, 0, 0);
    const Image::NormalizedVector v_norm_2(0, 1, 0);

    // We should not be able to compile:
    // v_norm_1 -= v_norm_2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v_norm_1 -= v_norm_2);
    using required_type = StaticAssert::invalid_normalized_vector_subtraction;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsFromTheSameSpaceCanBeDotted") {
    const View::NormalizedVector v1(1, 0, 0);
    const View::NormalizedVector v2(1, 0, 0);
    const auto dot = v1.Dot(v2);
    CHECK(dot == 1);
}
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("NormalizedVectorsFromDifferentSpacesCannotBeDotted") {
    const View::NormalizedVector v1(1, 0, 0);
    const Image::NormalizedVector v2(1, 0, 0);

    // We should not be able to compile:
    // auto dummy = v1.Dot(v2);
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v1.Dot(v2));
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsAndNormalizedVectorsFromTheSameSpaceCanBeDotted") {
    const View::Vector v1(1, 0, 0);
    const View::NormalizedVector v2(1, 0, 0);
    const auto dot = v1.Dot(v2);
    CHECK(dot == 1);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsAndVectorsFromTheSameSpaceCanBeDotted") {
    const View::NormalizedVector v1(1, 0, 0);
    const View::Vector v2(1, 0, 0);
    const auto dot = v1.Dot(v2);
    CHECK(dot == 1);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsCanBeAssignedToAVector") {
    const Image::NormalizedVector v_norm(1, 0, 0);
    const Image::Vector v = v_norm;
    CHECK(v.X() == 1);
    CHECK(v.Y() == 0);
    CHECK(v.Z() == 0);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsCanBeCrossed") {
    const Image::NormalizedVector v_norm_x(1, 0, 0);
    const Image::NormalizedVector v_norm_y(0, 1, 0);

    const auto result = v_norm_x.Cross(v_norm_y);

    CHECK(result == Image::NormalizedVector(0, 0, 1));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsCanBeCrossedToGiveANewNormalizedVector") {
    const Image::NormalizedVector v_norm_x(1, 0, 0);
    const Image::NormalizedVector v_norm_y(0, 1, 0);

    using converted_type = decltype(v_norm_x.Cross(v_norm_y));
    using required_type = decltype(Image::NormalizedVector{});
    CHECK(
        static_cast<bool>(std::is_same_v<converted_type, required_type>)
    );
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsCanBeCrossedUsingStar") {
    const Image::NormalizedVector v_norm_x(1, 0, 0);
    const Image::NormalizedVector v_norm_y(0, 1, 0);

    const auto result = v_norm_x * v_norm_y;

    CHECK(result == Image::NormalizedVector(0, 0, 1));
}
TEST_CASE("NormalizedVectorsCanBeCrossedUsingStarToGiveANewNormalizedVector") {
    const Image::NormalizedVector v_norm_x(1, 0, 0);
    const Image::NormalizedVector v_norm_y(0, 1, 0);

    using converted_type = decltype(v_norm_x * v_norm_y);
    using required_type = decltype(Image::NormalizedVector{});
    CHECK(
        static_cast<bool>(std::is_same_v<converted_type, required_type>)
    );
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsAndVectorsCanBeCrossed") {
    const Image::NormalizedVector v_norm_x(1, 0, 0);
    const Image::Vector v_y(0, 1, 0);

    const auto result = v_norm_x.Cross(v_y);

    CHECK(result == Image::NormalizedVector(0, 0, 1));
}
TEST_CASE("NormalizedVectorsAndVectorsCanBeCrossedToGiveANewVector") {
    const Image::NormalizedVector v_norm_x(1, 0, 0);
    const Image::Vector v_y(0, 1, 0);

    using converted_type = decltype(v_norm_x.Cross(v_y));
    using required_type = decltype(Image::Vector{});
    CHECK(
        static_cast<bool>(std::is_same_v<converted_type, required_type>)
    );
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsAndVectorsCanBeCrossedUsingStar") {
    const Image::NormalizedVector v_norm_x(1, 0, 0);
    const Image::Vector v_y(0, 1, 0);

    const auto result = v_norm_x * v_y;

    CHECK(result == Image::Vector(0, 0, 1));
}
TEST_CASE("NormalizedVectorsAndVectorsCanBeCrossedUsingStarToGiveANewVector") {
    const Image::NormalizedVector v_norm_x(1, 0, 0);
    const Image::Vector v_y(0, 1, 0);

    using converted_type = decltype(v_norm_x * v_y);
    using required_type = decltype(Image::Vector{});
    CHECK(
        static_cast<bool>(std::is_same_v<converted_type, required_type>)
    );
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsAndNormalizedVectorsCanBeCrossed") {
    const Image::Vector v_x(1, 0, 0);
    const Image::NormalizedVector v_norm_y(0, 1, 0);

    const auto result = v_x.Cross(v_norm_y);

    CHECK(result == Image::NormalizedVector(0, 0, 1));
}
TEST_CASE("VectorsAndNormalizedVectorsCanBeCrossedToGiveANewVector") {
    const Image::Vector v_x(1, 0, 0);
    const Image::NormalizedVector v_norm_y(0, 1, 0);

    using converted_type = decltype(v_x.Cross(v_norm_y));
    using required_type = decltype(Image::Vector{});
    CHECK(
        static_cast<bool>(std::is_same_v<converted_type, required_type>)
    );
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsAndNormalizedVectorsCanBeCrossedUsingStar") {
    const Image::Vector v_x(1, 0, 0);
    const Image::NormalizedVector v_norm_y(0, 1, 0);

    const auto result = v_x.Cross(v_norm_y);

    CHECK(result == Image::NormalizedVector(0, 0, 1));
}
TEST_CASE("VectorsAndNormalizedVectorsCanBeCrossedUsingStarToGiveANewVector") {
    const Image::Vector v_x(1, 0, 0);
    const Image::NormalizedVector v_norm_y(0, 1, 0);

    using converted_type = decltype(v_x * v_norm_y);
    using required_type = decltype(Image::Vector{});
    CHECK(
        static_cast<bool>(std::is_same_v<converted_type, required_type>)
    );
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalisedVectorsFromTheSameSpaceCanBeCrossedUsingStarEqualOperator") {
    View::NormalizedVector v1(1, 0, 0);
    const View::NormalizedVector v2(0, 1, 0);
    v1 *= v2;
    CHECK(v1 == View::Vector(0, 0, 1));
}

//-------------------------------------------------------------------------------------------------
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("NormalisedVectors And Vectors From The Same Space Cannot Be Crossed Using Star Equal Operator") {
    View::NormalizedVector v1;
    const View::Vector v2;
    using converted_type = decltype(v1 *= v2);
    using required_type = StaticAssert::invalid_normalized_vector_in_place_cross;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsSupportElementAccessByName") {
    const Image::NormalizedVector v(1, 0, 0);
    CHECK(v.X() == 1);
    CHECK(v.Y() == 0);
    CHECK(v.Z() == 0);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsSupportConstBeginAndEnd") {
    const Image::NormalizedVector v(1, 0, 0);
    std::vector<double> values;
    std::copy(v.cbegin(), v.cend(), std::back_inserter(values));
    CHECK(values.size() == 3);
    CHECK(values[0] == 1);
    CHECK(values[1] == 0);
    CHECK(values[2] == 0);
}

//-------------------------------------------------------------------------------------------------
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("NormalizedVectorsDoNotSupportNorm") {
    Image::NormalizedVector nv;

    // We should not be able to compile:
    // auto dummy = nv.begin();
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(nv.Norm());
    using required_type = StaticAssert::normalized_vectors_do_not_support_norm;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}

TEST_CASE("NormalizedVectorsDoNotSupportNonConstBegin") {
    Image::NormalizedVector nv(2, 3, 4);

    // We should not be able to compile:
    // auto dummy = nv.begin();
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(nv.begin());
    using required_type = StaticAssert::normalized_vectors_do_not_support_non_const_iteration;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsDoNotSupportNonConstEnd") {
    Image::NormalizedVector nv;

    // We should not be able to compile:
    // auto dummy = nv.end();
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(nv.end());
    using required_type = StaticAssert::normalized_vectors_do_not_support_non_const_iteration;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("Normalized Vectors Can Have their z-value removed") {
    const Image::NormalizedVector v(1, 0, 0);
    const auto v_norm = v.RemoveZ();
    CHECK(v_norm == Image::NormalizedXYVector(1, 0));
}

TEST_CASE("Normalized Vectors Can Have their z-value removed to produce a Normalized XYVector") {
    const Image::NormalizedVector v;
    using converted_type = decltype(v.RemoveZ());
    using required_type = decltype(Image::NormalizedXYVector{});
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsSupportElementAccessByRandomAccess") {
    const Image::NormalizedVector v(0, 1, 0);
    CHECK(v[0] == 0);
    CHECK(v[1] == 1);
    CHECK(v[2] == 0);
}

TEST_CASE("NormalizedVectorsThrowIfRandomAccessIsTooHigh") {
    const Image::NormalizedVector v(1, 0, 0);
    CHECK_THROWS_AS(v[3], std::invalid_argument);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsSupportElementAccessByAt") {
    const Image::NormalizedVector v(1, 0, 0);
    CHECK(v.at<0>() == 1);
    CHECK(v.at<1>() == 0);
    CHECK(v.at<2>() == 0);
}
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("NormalizedVectorsSupportElementAccessByAtDoesNotCompileIfTooLow") {
    const Image::NormalizedVector v(1, 0, 0);

    // We should not be able to compile:
    // auto dummy = v.at<-1>();
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v.at<-1>());
    using required_type = StaticAssert::invalid_at_access;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
TEST_CASE("NormalizedVectorsSupportElementAccessByAtDoesNotCompileIfTooHigh") {
    const Image::NormalizedVector v(1, 0, 0);

    // We should not be able to compile:
    // auto dummy = v.at<3>();
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v.at<3>());
    using required_type = StaticAssert::invalid_at_access;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsCanBeConvertedFromOneSpaceToAnotherIgnoringTranslation") {

    const TransformManager tm;
    const View::NormalizedVector v_view(1, 0, 0);
    auto v_patient = v_view.ConvertTo<Patient>(tm);
    CHECK(v_patient == Patient::Vector(15, 16, 17));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsCanBeConvertedFromOneSpaceToAnotherProducingAVector") {

    const TransformManager tm;
    const View::NormalizedVector v_view(1, 0, 0);
    using converted_type = decltype(v_view.ConvertTo<Patient>(tm));
    using required_type = decltype(Patient::Vector{});
    CHECK(
        static_cast<bool>(std::is_same_v<converted_type, required_type>)
    );
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorCanBeStreamed") {
    const View::NormalizedVector v(1, 0, 0);
    std::stringstream stream;
    stream << v;
    CHECK(stream.str() == std::string("View::NormalizedVector (1, 0, 0)"));
}

//-------------------------------------------------------------------------------------------------
