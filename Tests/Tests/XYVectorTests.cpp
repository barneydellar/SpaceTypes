#include "pch.h"
#include "SpaceHelpers.h"

using namespace Space;

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYVectors can be constructed") {
    View::XYVector v;
}

TEST_CASE("XYVectors have zero value by default") {
    View::XYVector v;
    CHECK(v[0] == 0);
    CHECK(v[1] == 0);
}

TEST_CASE("XYVectors can be created using initalizer lists of two numbers") {
    View::XYVector v = { 1, 2};
    CHECK(v[0] == 1);
    CHECK(v[1] == 2);
}
TEST_CASE("XYVectors throw when using initalizer lists that are too small") {
    CHECK_THROWS_AS(View::XYVector{ 1 }, std::invalid_argument);
}
TEST_CASE("XYVectors throw when using initalizer lists that are too large") {
    try
    {
        View::XYVector v{ 1, 2, 3 };
    }
    catch (std::invalid_argument&)
    {
        return;
    }
    REQUIRE(false);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYVectorsCanBeConstructedFromTwoDoubles") {
    const Patient::XYVector v(4, 5);
    CHECK(v.X() == 4);
    CHECK(v.Y() == 5);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYVectors Can Be Constructed From A Normalized XYVector") {
    const View::NormalizedXYVector nv(0, 1);
    const View::XYVector v(nv);

    CHECK(v.X() == 0);
    CHECK(v.Y() == 1);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYVectorsCanBeAssignedFromAXYVector") {
    const View::XYVector v1(0, 1);
    const auto v2 = v1;

    CHECK(v2.X() == 0);
    CHECK(v2.Y() == 1);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYVectorsCanBeAssignedFromANormalizedXYVector") {
    const View::NormalizedXYVector nv(0, 1);
    const View::XYVector v = nv;

    CHECK(v.X() == 0);
    CHECK(v.Y() == 1);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYVectorsFromTheSameSpaceCanBeComparedUsingEqual_same") {
    const View::XYVector v1(1, 0);
    const View::XYVector v2(1, 0);
    CHECK(v1 == v2);
}

TEST_CASE("XYVectorsFromTheSameSpaceCanBeComparedUsingEqual_different") {
    const Patient::XYVector v1(1, 0);
    const Patient::XYVector v2(2, 0);
    CHECK(!(v1 == v2));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYVectorsFromDifferentSpacesCannotBeComparedUsingEqual") {
    const View::XYVector v1(1, 0);
    const Patient::XYVector v2(1, 0);

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

TEST_CASE("XYVectorsFromTheSameSpaceCanBeComparedUsingInequality_same") {
    const View::XYVector v1(1, 0);
    const View::XYVector v2(1, 0);
    CHECK(!(v1 != v2));
}

TEST_CASE("XYVectorsFromTheSameSpaceCanBeComparedUsingInequality_different") {
    const Patient::XYVector v1(1, 0);
    const Patient::XYVector v2(2, 0);
    CHECK(v1 != v2);
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYVectorsFromDifferentSpacesCannotBeComparedUsingInequality") {
    const View::XYVector v1(1, 0);
    const Patient::XYVector v2(1, 0);

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

TEST_CASE("XYVectorsInTheSameSpaceCanBeAddedTogether") {
    const Image::XYVector v1(1, 2);
    const Image::XYVector v2(3, 2);
    const auto v_new = v1 + v2;
    CHECK(v_new == Image::XYVector(4, 4));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYVectorsInDifferentSpacesCannotBeAddedTogether") {
    const View::XYVector v1;
    const Image::XYVector v2;

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

TEST_CASE("XYVectors And Normalized XYVectors In The Same Space Can Be Added Together") {
    const Image::XYVector v1(1, 2);
    const Image::NormalizedXYVector v2(1, 0);
    const auto v_new = v1 + v2;
    CHECK(v_new == Image::XYVector(2, 2));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYVectors And Normalized XYVectors In Different Spaces Cannot Be Added Together") {
    const View::XYVector v1;
    const Image::NormalizedXYVector v2;

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

TEST_CASE("XYVectorsInTheSameSpaceCanBeAddedInPlace") {
    Image::XYVector v1(1, 2);
    const Image::XYVector v2(3, 2);
    v1 += v2;
    CHECK(v1 == Image::XYVector(4, 4));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYVectorsInDifferentSpacesCannotBeAddedInPlace") {
    View::XYVector v1;
    const Image::XYVector v2;

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

TEST_CASE("XYVectors And Normalized XYVectors In The Same Space Can Be Added In Place") {
    Image::XYVector v1(1, 2);
    const Image::NormalizedXYVector v2(1, 0);
    v1 += v2;
    CHECK(v1 == Image::XYVector(2, 2));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYVectors And 3D Vectors In The Same Space Cannot Be Added In Place") {
    const View::Vector v1;
    View::XYVector v2;

    // We should not be able to compile:
    // v1 += v2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v2 += v1);
    using required_type = StaticAssert::invalid_vector_to_vector_addition;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}

TEST_CASE("XYVectors And Normalized XYVectors In Different Spaces Cannot Be Added In Place") {
    View::XYVector v1;
    const Image::NormalizedXYVector v2;

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

TEST_CASE("XYVectorsInTheSameSpaceCanBeSubtracted") {
    const Image::XYVector v1(3, 2);
    const Image::XYVector v2(1, 2);
    const auto v_new = v1 - v2;
    CHECK(v_new == Image::XYVector(2, 0));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYVectors And Normalized XYVectors In Different Spaces Cannot Be Subtracted") {
    const View::XYVector v1;
    const Image::NormalizedXYVector v2;

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

TEST_CASE("XYVectorsInTheSameSpaceCanBeSubtractedInPlace") {
    Image::XYVector v1(1, 2);
    const Image::XYVector v2(3, 2);
    v1 -= v2;
    CHECK(v1 == Image::XYVector(-2, 0));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYVectorsInDifferentSpacesCannotBeSubtractedInPlace") {
    View::XYVector v1;
    const Image::XYVector v2;

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

TEST_CASE("XYVectors And Normalized XYVectors In TheS ame Space Can Be Subtracted In Place") {
    Image::XYVector v1(1, 2);
    const Image::NormalizedXYVector v2(1, 0);
    v1 -= v2;
    CHECK(v1 == Image::XYVector(0, 2));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYVectors And Normalized XYVectors In Different Spaces Cannot Be Subtracted In Place") {
    View::XYVector v1;
    const Image::NormalizedXYVector v2;

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

TEST_CASE("XYVectorsCanBeMultiplied") {
    const View::XYVector v(1, 2);
    const auto scaled_v = v * 2;
    CHECK(scaled_v == View::XYVector(2, 4));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYVectorsCanBeScaled") {
    View::XYVector v(1, 2);
    v *= 2;
    CHECK(v == View::XYVector(2, 4));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYVectorsSupportMag") {
    const Image::XYVector v(3, 4);
    // 5 = sqrt(3*3 + 4*4)
    CHECK(v.Mag().get() == 5);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYVector Mag Is Strongly Typed: Millimetres") {
    const Image::XYVector v(3, 4);
    const Millimetres m{ 0 };
    CHECK(typeid(v.Mag()).name() == typeid(m).name());
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYVector Mag Is Strongly Typed: Pixels") {
    const View::XYVector v(3, 4);
    const Pixels p{ 0 };
    CHECK(typeid(v.Mag()).name() == typeid(p).name());
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYVectorsSupportMag_double") {
    const Image::XYVector v(3, 4);
    // 5 = sqrt(3*3 + 4*4)
    CHECK(v.Mag_double() == 5);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYVector Can Be Normalized") {
    const Image::XYVector v(3, 4);
    const auto v_norm = v.Norm();
    // Mag of v = sqrt(3*3 + 4*4) = 5
    CHECK(v_norm == Image::XYVector(3.0 / 5, 4.0 / 5));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYVectors Can Be Normalized to produce a Normalized XYVector") {
    const Image::XYVector v;
    using converted_type = decltype(v.Norm());
    using required_type = decltype(Image::NormalizedXYVector{});
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("ZeroSizeXYVectorsCannotBeNormalized") {
    const Image::XYVector v(0, 0);
    CHECK_THROWS_AS(v.Norm(), std::invalid_argument);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYVectors can be constructed from implementation") {
    TestVector impl;
    impl.m_values[0] = 3;
    impl.m_values[1] = 4;
    impl.m_values[2] = 5;
    const Patient::XYVector v(impl);
    CHECK(v.X() == 3);
    CHECK(v.Y() == 4);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYVectors ignore Z when constructed from implementation") {
    TestVector impl;
    impl.m_values[0] = 3;
    impl.m_values[1] = 4;
    impl.m_values[2] = 5;
    const Patient::XYVector v(impl);
    CHECK(v.Mag_double() == 5);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYVectors Can Be Cast To The Implementation") {
    const Patient::XYVector v(1, 0);
    auto impl = static_cast<TestVector>(v);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYVectors cannot be implicitly cast to the implementation") {
    const Patient::XYVector v(1, 0);

    // We should not be able to compile:
    // TestXYVector impl = v;
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYVectors Can Be Passed By Value To Vector") {

    const Patient::XYVector nv{1, 2};

    const auto lambda = [](
        const Patient::Vector v
    ) {
        CHECK(v.X() == 1);
        CHECK(v.Y() == 2);
        CHECK(v.Z() == 0);
    };

    lambda(nv);
}
//-------------------------------------------------------------------------------------------------

TEST_CASE("XYVectors Can Be Passed By Const Ref To Vector") {

    const Patient::XYVector nv(0, 4);

    const auto lambda = [](
        const Patient::Vector& v
    ) {
        CHECK(v.X() == 0);
        CHECK(v.Y() == 4);
        CHECK(v.Z() == 0);
    };

    lambda(nv);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYVectorsFromTheSameSpaceCanBeDotted") {
    const View::XYVector v1(1, 2);
    const View::XYVector v2(1, 2);
    const auto dot = v1.Dot(v2);
    CHECK(dot == 1 * 1 + 2 * 2);
}
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYVectorsFromDifferentSpacesCannotBeDotted") {
    const View::XYVector v1;
    const Image::XYVector v2;

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

TEST_CASE("XYVectorsFromTheSameSpaceCanBeCrossed") {
    const View::XYVector v1(1, 0);
    const View::XYVector v2(0, 1);
    const auto cross = v1.Cross(v2);

    CHECK(cross == View::Vector(0, 0, 1));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYVectorsFromDifferentSpacesCannotBeCrossed") {
    const View::XYVector v1;
    const Image::XYVector v2;

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

TEST_CASE("XYVectorsFromTheSameSpaceCanBeCrossedUsingStarOperator") {
    const View::XYVector v1(1, 0);
    const View::XYVector v2(0, 1);
    const auto cross = v1 * v2;
    CHECK(cross == View::Vector(0, 0, 1));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYVectorsFromDifferentSpacesCannotBeCrossedUsingStarOperator") {
    const View::XYVector v1;
    const Image::XYVector v2;

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

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYVectors From The Same Space Cannot Be Crossed Using Star Equal Operator") {
    View::XYVector v1;
    const View::XYVector v2;

    // We should not be able to compile:
    // v1 *= v2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v1 *= v2);
    using required_type = StaticAssert::invalid_XYVector_in_place_cross;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}

TEST_CASE("XYVectors From Different Spaces Cannot Be Crossed Using Star Equal Operator") {
    View::XYVector v1;
    const Image::XYVector v2;

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

TEST_CASE("XYVectors Support Element Access By Name") {
    const Image::XYVector v(2, 3);
    CHECK(v.X() == 2);
    CHECK(v.Y() == 3);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYVectors Do Not Support Z Access By Name") {
    const Image::XYVector v2;

    using converted_type = decltype(v2.Z());
    using required_type = StaticAssert::z_not_supported;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYVectorsSupportConstBeginAndEnd") {
    const Image::XYVector v(2, 3);
    std::vector<double> values;
    std::copy(v.cbegin(), v.cend(), std::back_inserter(values));
    CHECK(values.size() == 2);
    CHECK(values[0] == 2);
    CHECK(values[1] == 3);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYVectorsSupportNonConstBeginAndEnd") {
    Image::XYVector v(2, 3);
    std::vector<double> values;
    std::copy(v.begin(), v.end(), std::back_inserter(values));
    CHECK(values.size() == 2);
    CHECK(values[0] == 2);
    CHECK(values[1] == 3);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYVectorsCanBeTransformedWithTheSTL") {
    Image::XYVector v(2, 3);
    std::transform(
        v.cbegin(),
        v.cend(),
        v.begin(),
        [](const double d) {return d * 2; }
    );
    CHECK(v == Image::XYVector(4, 6));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYVectorsSupportElementAccessByRandomAccess") {
    const Image::XYVector v(2, 3);
    CHECK(v[0] == 2);
    CHECK(v[1] == 3);
}

TEST_CASE("XYVectorsThrowIfRandomAccessIsTooHigh") {
    const Image::XYVector v(2, 3);
    CHECK_THROWS_AS(v[2], std::invalid_argument);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYVectorsSupportElementAccessByAt") {
    const Image::XYVector v(2, 3);
    CHECK(v.at<0>() == 2);
    CHECK(v.at<1>() == 3);
}
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYVectorsSupportElementAccessByAtDoesNotCompileIfTooLow") {
    const Image::XYVector v(2, 3);

    // We should not be able to compile:
    // auto dummy = v.at<-1>();
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v.at<-1>());
    using required_type = StaticAssert::invalid_at_access;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
TEST_CASE("XYVectorsSupportElementAccessByAtDoesNotCompileIfTooHigh") {
    const Image::XYVector v(2, 3);

    // We should not be able to compile:
    // auto dummy = v.at<3>();
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v.at<2>());
    using required_type = StaticAssert::invalid_at_access;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYVectorsCanBeConvertedFromOneSpaceToAnotherIgnoringTranslation") {

    const TransformManager tm;
    const View::XYVector v_view(1, 0);
    auto v_patient = v_view.ConvertTo<Patient>(tm);
    CHECK(v_patient == Patient::Vector(15, 16, 17));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYVectors Can Be Converted From One Space To Another Producing A Vector") {

    const TransformManager tm;
    const View::XYVector v_view(1, 0);
    using converted_type = decltype(v_view.ConvertTo<Patient>(tm));
    using required_type = decltype(Patient::Vector{});
    CHECK(
        static_cast<bool>(std::is_same_v<converted_type, required_type>)
    );
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYVectorsCanBeStreamed") {
    const View::XYVector v(1.2, 2.3);
    std::stringstream stream;
    stream << v;
    CHECK(stream.str() == std::string("View::XYVector (1.2, 2.3)"));
}

//-------------------------------------------------------------------------------------------------