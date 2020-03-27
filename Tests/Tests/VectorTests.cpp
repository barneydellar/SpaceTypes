#include "pch.h"
#include "SpaceHelpers.h"

using namespace Space;

//-------------------------------------------------------------------------------------------------

TEST_CASE("Vectors can be constructed") {
    View::Vector v;
}

TEST_CASE("Vectors have zero value by default") {
    View::Vector v;
    CHECK(v[0] == 0);
    CHECK(v[1] == 0);
    CHECK(v[2] == 0);
}
TEST_CASE("Vectors can be created using initalizer lists of three numbers") {
    View::Vector v{ 1, 2, 4 };
    CHECK(v[0] == 1);
    CHECK(v[1] == 2);
    CHECK(v[2] == 4);
}
TEST_CASE("Vectors throw when using initalizer lists that are too small") {
    try
    {
        View::Vector v{ 1, 2 };
    }
    catch (std::invalid_argument&)
    {
        return;
    }
    REQUIRE(false);
}
TEST_CASE("Vectors throw when using initalizer lists that are too large") {
    try
    {
        View::Vector v{ 1, 2, 3, 4 };
    }
    catch (std::invalid_argument&)
    {
        return;
    }
    REQUIRE(false);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsCanBeConstructedFromThreeDoubles") {
    const Patient::Vector v(4, 5, 6);
    CHECK(v.X() == 4);
    CHECK(v.Y() == 5);
    CHECK(v.Z() == 6);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsCanBeConstructedFromANormalizedVector") {
    const View::NormalizedVector nv(0, 0, 1);
    //const View::Vector v(nv);

    //CHECK(v.X() == 0);
    //CHECK(v.Y() == 0);
    //CHECK(v.Z() == 1);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsCanBeAssignedFromAVector") {
    const View::Vector v1(0, 0, 1);
    const auto v2 = v1;

    CHECK(v2.X() == 0);
    CHECK(v2.Y() == 0);
    CHECK(v2.Z() == 1);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsCanBeAssignedFromANormalizedVector") {
    const View::NormalizedVector nv(0, 0, 1);
    //const View::Vector v = nv;

    //CHECK(v.X() == 0);
    //CHECK(v.Y() == 0);
    //CHECK(v.Z() == 1);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsFromTheSameSpaceCanBeComparedUsingEqual_same") {
    const View::Vector v1(1, 0, 0);
    const View::Vector v2(1, 0, 0);
    CHECK(v1 == v2);
}

TEST_CASE("VectorsFromTheSameSpaceCanBeComparedUsingEqual_different") {
    const Patient::Vector v1(1, 0, 0);
    const Patient::Vector v2(2, 0, 0);
    CHECK(!(v1 == v2));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("VectorsFromDifferentSpacesCannotBeComparedUsingEqual") {
    const View::Vector v1(1, 0, 0);
    const Patient::Vector v2(1, 0, 0);

    // We should not be able to compile:
    // auto dummy = v1 == v2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v1 == v2);
    using required_type = StaticAssert::invalid_space;
    CHECK(
        static_cast<bool>(std::is_same_v<converted_type, required_type>)
    );
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsFromTheSameSpaceCanBeComparedUsingInequality_same") {
    const View::Vector v1(1, 0, 0);
    const View::Vector v2(1, 0, 0);
    CHECK(!(v1 != v2));
}

TEST_CASE("VectorsFromTheSameSpaceCanBeComparedUsingInequality_different") {
    const Patient::Vector v1(1, 0, 0);
    const Patient::Vector v2(2, 0, 0);
    CHECK(v1 != v2);
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("VectorsFromDifferentSpacesCannotBeComparedUsingInequality") {
    const View::Vector v1(1, 0, 0);
    const Patient::Vector v2(1, 0, 0);

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

TEST_CASE("VectorsInTheSameSpaceCanBeAddedTogether") {
    const Image::Vector v1(1, 2, 3);
    const Image::Vector v2(3, 2, 1);
    const auto v_new = v1 + v2;
    CHECK(v_new == Image::Vector(4, 4, 4));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("VectorsInDifferentSpacesCannotBeAddedTogether") {
    const View::Vector v1(1, 2, 3);
    const Image::Vector v2(3, 2, 1);

    // We should not be able to compile:
    // auto dummy = v1 + v2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v1 + v2);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsAndNormalizedVectorsInTheSameSpaceCanBeAddedTogether") {
    const Image::Vector v1(1, 2, 3);
    const Image::NormalizedVector v2(1, 0, 0);
    const auto v_new = v1 + v2;
    CHECK(v_new == Image::Vector(2, 2, 3));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("VectorsAndNormalizedVectorsInDifferentSpacesCannotBeAddedTogether") {
    const View::Vector v1(1, 2, 3);
    const Image::NormalizedVector v2(1, 0, 0);

    // We should not be able to compile:
    // auto dummy = v1 + v2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v1 + v2);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsInTheSameSpaceCanBeAddedInPlace") {
    Image::Vector v1(1, 2, 3);
    const Image::Vector v2(3, 2, 1);
    v1 += v2;
    CHECK(v1 == Image::Vector(4, 4, 4));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("VectorsInDifferentSpacesCannotBeAddedInPlace") {
    View::Vector v1(1, 2, 3);
    const Image::Vector v2(3, 2, 1);

    // We should not be able to compile:
    // v1 += v2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v1 += v2);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsAndNormalizedVectorsInTheSameSpaceCanBeAddedInPlace") {
    Image::Vector v1(1, 2, 3);
    const Image::NormalizedVector v2(1, 0, 0);
    v1 += v2;
    CHECK(v1 == Image::Vector(2, 2, 3));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("VectorsAndNormalizedVectorsInDifferentSpacesCannotBeAddedInPlace") {
    View::Vector v1(1, 2, 3);
    const Image::NormalizedVector v2(1, 0, 0);

    // We should not be able to compile:
    // v1 += v2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v1 += v2);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsInTheSameSpaceCanBeSubtracted") {
    const Image::Vector v1(3, 2, 1);
    const Image::Vector v2(1, 2, 3);
    const auto v_new = v1 - v2;
    CHECK(v_new == Image::Vector(2, 0, -2));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("VectorsAndNormalizedVectorsInDifferentSpacesCannotBeSubtracted") {
    const View::Vector v1(1, 2, 3);
    const Image::NormalizedVector v2(1, 0, 0);

    // We should not be able to compile:
    // auto dummy = v1 - v2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v1 - v2);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsInTheSameSpaceCanBeSubtractedInPlace") {
    Image::Vector v1(1, 2, 3);
    const Image::Vector v2(3, 2, 1);
    v1 -= v2;
    CHECK(v1 == Image::Vector(-2, 0, 2));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("VectorsInDifferentSpacesCannotBeSubtractedInPlace") {
    View::Vector v1(1, 2, 3);
    const Image::Vector v2(3, 2, 1);

    // We should not be able to compile:
    // v1 -= v2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v1 -= v2);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsAndNormalizedVectorsInTheSameSpaceCanBeSubtractedInPlace") {
    Image::Vector v1(1, 2, 3);
    const Image::NormalizedVector v2(1, 0, 0);
    v1 -= v2;
    CHECK(v1 == Image::Vector(0, 2, 3));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("VectorsAndNormalizedVectorsInDifferentSpacesCannotBeSubtractedInPlace") {
    View::Vector v1(1, 2, 3);
    const Image::NormalizedVector v2(1, 0, 0);

    // We should not be able to compile:
    // v1 -= v2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v1 -= v2);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif


//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsCanBeMultiplied") {
    const View::Vector v(1, 2, 3);
    const auto scaled_v = v * 2;
    CHECK(scaled_v == View::Vector(2, 4, 6));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsCanBeScaled") {
    View::Vector v(1, 2, 3);
    v *= 2;
    CHECK(v == View::Vector(2, 4, 6));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsSupportMag") {
    const Image::Vector v(0, 3, 4);
    // 5 = sqrt(3*3 + 4*4)
    CHECK(v.Mag().get() == 5);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("MagIsStronglyTyped_Millimetres") {
    const Image::Vector v(0, 3, 4);
    const Millimetres m{ 0 };
    CHECK(typeid(v.Mag()).name() == typeid(m).name());
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("MagIsStronglyTyped_Pixels") {
    const View::Vector v(0, 3, 4);
    const Pixels p{ 0 };
    CHECK(typeid(v.Mag()).name() == typeid(p).name());
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsSupportMag_double") {
    const Image::Vector v(0, 3, 4);
    // 5 = sqrt(3*3 + 4*4)
    CHECK(v.Mag_double() == 5);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsCanBeNormalized") {
    const Image::Vector v(0, 3, 4);
    const auto v_norm = v.Norm();
    // Mag of v = sqrt(3*3 + 4*4) = 5
    CHECK(v_norm == Image::Vector(0, 3.0 / 5, 4.0 / 5));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("ZeroSizeVectorsCannotBeNormalized") {
    const Image::Vector v(0, 0, 0);
    CHECK_THROWS_AS(v.Norm(), std::invalid_argument);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Vectors Can Have their z-value removed") {
    const Image::Vector v(2, 3, 4);
    const auto v_norm = v.ToXY();
    CHECK(v_norm == Image::XYVector(2, 3));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Vectors Can Have their z-value removed to produce a XYVector") {
    const Image::Vector v;
    using converted_type = decltype(v.ToXY());
    using required_type = decltype(Image::XYVector{});
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Vectors can be constructed and normalized from implementation") {
    TestVector impl;
    impl.m_values[0] = 3;
    impl.m_values[1] = 2;
    impl.m_values[2] = 1;
    const Patient::Vector v(impl);
    CHECK(v.X() == 3);
    CHECK(v.Y() == 2);
    CHECK(v.Z() == 1);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Vectors Can Be Cast To The Implementation") {
    const Patient::Vector v(1, 0, 0);
    auto impl = static_cast<TestVector>(v);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Vectors cannot be implicitly cast to the implementation") {
    const Patient::Vector v(1, 0, 0);

    // We should not be able to compile:
    // TestVector impl = v;
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsFromTheSameSpaceCanBeDotted") {
    const View::Vector v1(1, 2, 3);
    const View::Vector v2(1, 2, 3);
    const auto dot = v1.Dot(v2);
    CHECK(dot == 1 * 1 + 2 * 2 + 3 * 3);
}
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("VectorsFromDifferentSpacesCannotBeDotted") {
    const View::Vector v1(1, 2, 3);
    const Image::Vector v2(1, 2, 3);

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

TEST_CASE("VectorsFromTheSameSpaceCanBeCrossed") {
    const View::Vector v1(1, 0, 0);
    const View::Vector v2(0, 1, 0);
    const auto cross = v1.Cross(v2);

    CHECK(cross == View::Vector(0, 0, 1));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("VectorsFromDifferentSpacesCannotBeCrossed") {
    const View::Vector v1(1, 2, 3);
    const Image::Vector v2(1, 2, 3);

    // We should not be able to compile:
    // auto dummy = v1.Cross(v2);
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v1.Cross(v2));
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsFromTheSameSpaceCanBeCrossedUsingStarOperator") {
    const View::Vector v1(1, 0, 0);
    const View::Vector v2(0, 1, 0);
    const auto cross = v1 * v2;
    CHECK(cross == View::Vector(0, 0, 1));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("VectorsFromDifferentSpacesCannotBeCrossedUsingStarOperator") {
    const View::Vector v1(1, 2, 3);
    const Image::Vector v2(1, 2, 3);

    // We should not be able to compile:
    // auto dummy = v1 * v2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v1 * v2);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsFromTheSameSpaceCanBeCrossedUsingStarEqualOperator") {
    View::Vector v1(1, 0, 0);
    const View::Vector v2(0, 1, 0);
    v1 *= v2;
    CHECK(v1 == View::Vector(0, 0, 1));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("VectorsFromDifferentSpacesCannotBeCrossedUsingStarEqualOperator") {
    View::Vector v1(1, 2, 3);
    const Image::Vector v2(1, 2, 3);

    // We should not be able to compile:
    // v1 *= v2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v1 *= v2);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsSupportElementAccessByName") {
    const Image::Vector v(2, 3, 4);
    CHECK(v.X() == 2);
    CHECK(v.Y() == 3);
    CHECK(v.Z() == 4);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Vectors Can Be Modifed By Name") {
    Image::Vector v(2, 3, 4);
    v.SetX(10);
    v.SetY(20);
    v.SetZ(30);
    CHECK(v.X() == 10);
    CHECK(v.Y() == 20);
    CHECK(v.Z() == 30);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsSupportConstBeginAndEnd") {
    const Image::Vector v(2, 3, 4);
    std::vector<double> values;
    std::copy(v.cbegin(), v.cend(), std::back_inserter(values));
    CHECK(values.size() == 3);
    CHECK(values[0] == 2);
    CHECK(values[1] == 3);
    CHECK(values[2] == 4);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsSupportNonConstBeginAndEnd") {
    Image::Vector v(2, 3, 4);
    std::vector<double> values;
    std::copy(v.begin(), v.end(), std::back_inserter(values));
    CHECK(values.size() == 3);
    CHECK(values[0] == 2);
    CHECK(values[1] == 3);
    CHECK(values[2] == 4);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsCanBeTransformedWithTheSTL") {
    Image::Vector v(2, 3, 4);
    std::transform(
        v.cbegin(),
        v.cend(),
        v.begin(),
        [](const double d) {return d * 2; }
    );
    CHECK(v == Image::Vector(4, 6, 8));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsSupportElementAccessByRandomAccess") {
    const Image::Vector v(2, 3, 4);
    CHECK(v[0] == 2);
    CHECK(v[1] == 3);
    CHECK(v[2] == 4);
}

TEST_CASE("VectorsThrowIfRandomAccessIsTooHigh") {
    const Image::Vector v(2, 3, 4);
    CHECK_THROWS_AS(v[3], std::invalid_argument);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsSupportElementAccessByAt") {
    const Image::Vector v(2, 3, 4);
    CHECK(v.at<0>() == 2);
    CHECK(v.at<1>() == 3);
    CHECK(v.at<2>() == 4);
}
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("VectorsSupportElementAccessByAtDoesNotCompileIfTooLow") {
    const Image::Vector v(2, 3, 4);

    // We should not be able to compile:
    // auto dummy = v.at<-1>();
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v.at<-1>());
    using required_type = StaticAssert::invalid_at_access;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
TEST_CASE("VectorsSupportElementAccessByAtDoesNotCompileIfTooHigh") {
    const Image::Vector v(2, 3, 4);

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

TEST_CASE("VectorsCanBeConvertedFromOneSpaceToAnotherIgnoringTranslation") {

    const TransformManager tm;
    const View::Vector v_view(1, 0, 0);
    auto v_patient = v_view.ConvertTo<Patient>(tm);
    CHECK(v_patient == Patient::Vector(15, 16, 17));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsCanBeConvertedFromOneSpaceToAnotherProducingAVector") {

    const TransformManager tm;
    const View::Vector v_view(1, 0, 0);
    using converted_type = decltype(v_view.ConvertTo<Patient>(tm));
    using required_type = decltype(Patient::Vector{});
    CHECK(
        static_cast<bool>(std::is_same_v<converted_type, required_type>)
    );
}

//-------------------------------------------------------------------------------------------------

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Vectors Cannot Be Converted To The Same Space") {
    const TransformManager tm;
    const View::Vector v;
    using converted_type = decltype(v.ConvertTo<View>(tm));
    using required_type = StaticAssert::invalid_conversion;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("VectorsCanBeStreamed") {
    const View::Vector v(1.2, 2.3, 3.4);
    std::stringstream stream;
    stream << v;
    CHECK(stream.str() == std::string("View::Vector (1.2, 2.3, 3.4)"));
}

//-------------------------------------------------------------------------------------------------
