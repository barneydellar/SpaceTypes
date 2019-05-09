#include "pch.h"

#include "SpaceHelpers.h"

using namespace Space;

constexpr bool TEST_NON_COMPILATION{ false };

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsCanBeConstructedAndNormalizedFromThreeDoubles") {
    const Patient::NormalizedVector v(2, 0, 0);
    CHECK(v.X() == 1);
    CHECK(v.Y() == 0);
    CHECK(v.Z() == 0);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsCanBeConstructedAndNormalizedFromTwoDoubles") {
    const Patient::NormalizedVector v(2, 0);
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

TEST_CASE("NormalizedVectorsFromDiffefentSpacesCannotBeComparedUsingEqual") {
    const View::NormalizedVector v1(1, 0, 0);
    const Patient::NormalizedVector v2(1, 0, 0);
    
    // We should not be able to compile this.
    if constexpr (TEST_NON_COMPILATION) {
        v1 == v2;
    }
}

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

TEST_CASE("NormalizedVectorsFromDiffefentSpacesCannotBeComparedUsingInequality") {
    const View::NormalizedVector v1(1, 0, 0);
    const Patient::NormalizedVector v2(1, 0, 0);
    
    // We should not be able to compile this.
    if constexpr (TEST_NON_COMPILATION) {
        v1 != v2;
    }
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsCanBeMultiplied") {
    const View::NormalizedVector v_norm(1, 0, 0);
    const auto scaled_v = v_norm * 2;
    CHECK(scaled_v == View::Vector(2, 0, 0));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsCanBeScaledToProdueAVector") {
    const Image::NormalizedVector v_norm(1, 0, 0);

    using converted_type = decltype(v_norm * 2);
    using required_type = decltype(Image::Vector{ 1, 2, 3 });

    CHECK(
        static_cast<bool>(std::is_same<converted_type, required_type>::value)
    );
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsCannotBeInlineScaled") {
    const Image::NormalizedVector v_norm(1, 0, 0);

    // We should not be able to compile this.
    if constexpr (TEST_NON_COMPILATION) {
        v_norm *= 2.0f;
    }
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsCanBeAdded") {
    const Image::NormalizedVector v_norm_1(1, 0, 0);
    const Image::NormalizedVector v_norm_2(0, 1, 0);

    const auto added = v_norm_1 + v_norm_2;
    CHECK(added == Image::Vector(1, 1, 0));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsCanBeAddedToProdueAVector") {
    const Image::NormalizedVector v_norm_1(1, 0, 0);
    const Image::NormalizedVector v_norm_2(0, 1, 0);

    using converted_type = decltype(v_norm_1 + v_norm_2);
    using required_type = decltype(Image::Vector{1, 2, 3});

    CHECK(
        static_cast<bool>(std::is_same<converted_type, required_type>::value)
    );
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsFromDifferentSpacesCannotBeAdded") {
    const Image::NormalizedVector v_norm_1(1, 0, 0);
    const Patient::NormalizedVector v_norm_2(0, 1, 0);

    if constexpr (TEST_NON_COMPILATION) {
        v_norm_1 + v_norm_2;
    }
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsAndVectorsCanBeAdded") {
    const Image::NormalizedVector v_norm_1(1, 0, 0);
    const Image::Vector v_norm_2(0, 1, 0);

    const auto added = v_norm_1 + v_norm_2;
    CHECK(added == Image::Vector(1, 1, 0));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsAndVectorsCanBeAddedToProdueAVector") {
    const Image::NormalizedVector v_norm_1(1, 0, 0);
    const Image::Vector v_2(0, 1, 0);

    using converted_type = decltype(v_norm_1 + v_2);
    using required_type = decltype(Image::Vector{ 1, 2, 3 });

    CHECK(
        static_cast<bool>(std::is_same<converted_type, required_type>::value)
    );
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsAndNormalizedVectorsCanBeAddedToProdueAVector") {
    const Image::Vector v_1(1, 0, 0);
    const Image::NormalizedVector v_norm_2(0, 1, 0);

    using converted_type = decltype(v_1 + v_norm_2);
    using required_type = decltype(Image::Vector{ 1, 2, 3 });

    CHECK(
        static_cast<bool>(std::is_same<converted_type, required_type>::value)
    );
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsAndNormalizedVectorsFromDifferentSpacesCannotBeAdded") {
    const Image::Vector v_norm_1(1, 0, 0);
    const Patient::NormalizedVector v_norm_2(0, 1, 0);

    if constexpr (TEST_NON_COMPILATION) {
        v_norm_1 + v_norm_2;
    }
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsCannotBeInlineAdded") {
    const Image::NormalizedVector v_norm_1(1, 0, 0);
    const Image::NormalizedVector v_norm_2(0, 1, 0);

    // We should not be able to compile this. 
    if constexpr (TEST_NON_COMPILATION) {
        v_norm_1 += v_norm_2;
    }
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsFromTheSameSpaceCanBeDotted") {
    const View::NormalizedVector v1(1, 0, 0);
    const View::NormalizedVector v2(1, 0, 0);
    const auto dot = v1.Dot(v2);
    CHECK(dot == 1);
}

TEST_CASE("NormalizedVectorsFromDifferentSpacesCannotBeDotted") {
    const View::NormalizedVector v1(1, 0, 0);
    const Image::NormalizedVector v2(1, 0, 0);
    
    // We should not be able to compile this.
    if constexpr (TEST_NON_COMPILATION) {
        v1.Dot(v2);
    }
}

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
    using required_type = decltype(Image::NormalizedVector{ 1, 2, 3 });
    CHECK(
        static_cast<bool>(std::is_same<converted_type, required_type>::value)
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
    using required_type = decltype(Image::NormalizedVector{ 1, 2, 3 });
    CHECK(
        static_cast<bool>(std::is_same<converted_type, required_type>::value)
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
    using required_type = decltype(Image::Vector{ 1, 2, 3 });
    CHECK(
        static_cast<bool>(std::is_same<converted_type, required_type>::value)
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
    using required_type = decltype(Image::Vector{ 1, 2, 3 });
    CHECK(
        static_cast<bool>(std::is_same<converted_type, required_type>::value)
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
    using required_type = decltype(Image::Vector{ 1, 2, 3 });
    CHECK(
        static_cast<bool>(std::is_same<converted_type, required_type>::value)
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
    using required_type = decltype(Image::Vector{ 1, 2, 3 });
    CHECK(
        static_cast<bool>(std::is_same<converted_type, required_type>::value)
    );
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsSupportElementAccessByName") {
    const Image::NormalizedVector v(1, 0, 0);
    CHECK(v.X() == 1);
    CHECK(v.Y() == 0);
    CHECK(v.Z() == 0);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsSupportConstBeginAndEnd") {
    const Image::Vector v(2, 3, 4);
    std::vector<double> values;
    std::copy(v.cbegin(), v.cend(), std::back_inserter(values));
    CHECK(values[0] == 2);
    CHECK(values[1] == 3);
    CHECK(values[2] == 4);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsDoNotSupportNonConstBegin") {
    Image::NormalizedVector nv(2, 3, 4);

    if constexpr (TEST_NON_COMPILATION) {
        nv.begin();
    }
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsDoNotSupportNonConstEnd") {
    Image::NormalizedVector nv(2, 3, 4);

    if constexpr (TEST_NON_COMPILATION) {
        nv.end();
    }
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsSupportElementAccessByRandomAccess") {
    const Image::NormalizedVector v(0, 1, 0);
    CHECK(v[0u] == 0);
    CHECK(v[1u] == 1);
    CHECK(v[2u] == 0);
}

TEST_CASE("NormalizedVectorsDoNotCompileIfRandomAccessIsTooLow") {
    const Image::NormalizedVector v(0, 0, 1);
    
    // We should not be able to compile this.
    if constexpr (TEST_NON_COMPILATION) {
        v[-1];
    }
}

TEST_CASE("NormalizedVectorsThrowIfRandomAccessIsTooHigh") {
    const Image::NormalizedVector v(1, 0, 0);
    CHECK_THROWS_AS(v[3u], std::invalid_argument);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("NormalizedVectorsSupportElementAccessByAt") {
    const Image::NormalizedVector v(1, 0, 0);
    CHECK(v.at<0>() == 1);
    CHECK(v.at<1>() == 0);
    CHECK(v.at<2>() == 0);
}
TEST_CASE("NormalizedVectorsSupportElementAccessByAtDoesNotCompileIfTooLow") {
    const Image::NormalizedVector v(1, 0, 0);
    
    // We should not be able to compile this.
    if constexpr (TEST_NON_COMPILATION) {
        v.at<-1>();
    }
}
TEST_CASE("NormalizedVectorsSupportElementAccessByAtDoesNotCompileIfTooHigh") {
    const Image::NormalizedVector v(1, 0, 0);
    
    // We should not be able to compile this. 
    if constexpr (TEST_NON_COMPILATION) {
        v.at<3>();
    }
}

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
    using required_type = decltype(Patient::Vector{ 1, 2, 3 });
    CHECK(
        static_cast<bool>(std::is_same<converted_type, required_type>::value)
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
