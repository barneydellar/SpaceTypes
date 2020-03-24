#include "pch.h"
#include "SpaceHelpers.h"

using namespace Space;

//-------------------------------------------------------------------------------------------------

TEST_CASE("Vector2s can be constructed") {
    View::Vector2 v;
}

TEST_CASE("Vector2s have zero value by default") {
    View::Vector2 v;
    CHECK(v[0] == 0);
    CHECK(v[1] == 0);
}

TEST_CASE("Vector2s can be created using initalizer lists of two numbers") {
    View::Vector2 v = { 1, 2};
    CHECK(v[0] == 1);
    CHECK(v[1] == 2);
}
TEST_CASE("Vector2s throw when using initalizer lists that are too small") {
    CHECK_THROWS_AS(View::Vector2{ 1 }, std::invalid_argument);
}
TEST_CASE("Vector2s throw when using initalizer lists that are too large") {
    try
    {
        View::Vector2 v{ 1, 2, 3 };
    }
    catch (std::invalid_argument&)
    {
        return;
    }
    REQUIRE(false);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Vector2sCanBeConstructedFromTwoDoubles") {
    const Patient::Vector2 v(4, 5);
    CHECK(v.X() == 4);
    CHECK(v.Y() == 5);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Vector2s Can Be Constructed From A Normalized Vector2") {
    const View::NormalizedVector2 nv(0, 1);
    const View::Vector2 v(nv);

    CHECK(v.X() == 0);
    CHECK(v.Y() == 1);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Vector2sCanBeAssignedFromAVector2") {
    const View::Vector2 v1(0, 1);
    const View::Vector2 v2 = v1;

    CHECK(v2.X() == 0);
    CHECK(v2.Y() == 1);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Vector2sCanBeAssignedFromANormalizedVector2") {
    const View::NormalizedVector2 nv(0, 1);
    const View::Vector2 v = nv;

    CHECK(v.X() == 0);
    CHECK(v.Y() == 1);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Vector2sFromTheSameSpaceCanBeComparedUsingEqual_same") {
    const View::Vector2 v1(1, 0);
    const View::Vector2 v2(1, 0);
    CHECK(v1 == v2);
}

TEST_CASE("Vector2sFromTheSameSpaceCanBeComparedUsingEqual_different") {
    const Patient::Vector2 v1(1, 0);
    const Patient::Vector2 v2(2, 0);
    CHECK(!(v1 == v2));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Vector2sFromDifferentSpacesCannotBeComparedUsingEqual") {
    const View::Vector2 v1(1, 0);
    const Patient::Vector2 v2(1, 0);

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

TEST_CASE("Vector2sFromTheSameSpaceCanBeComparedUsingInequality_same") {
    const View::Vector2 v1(1, 0);
    const View::Vector2 v2(1, 0);
    CHECK(!(v1 != v2));
}

TEST_CASE("Vector2sFromTheSameSpaceCanBeComparedUsingInequality_different") {
    const Patient::Vector2 v1(1, 0);
    const Patient::Vector2 v2(2, 0);
    CHECK(v1 != v2);
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Vector2sFromDifferentSpacesCannotBeComparedUsingInequality") {
    const View::Vector2 v1(1, 0);
    const Patient::Vector2 v2(1, 0);

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

TEST_CASE("Vector2sInTheSameSpaceCanBeAddedTogether") {
    const Image::Vector2 v1(1, 2);
    const Image::Vector2 v2(3, 2);
    const auto v_new = v1 + v2;
    CHECK(v_new == Image::Vector2(4, 4));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Vector2sInDifferentSpacesCannotBeAddedTogether") {
    const View::Vector2 v1;
    const Image::Vector2 v2;

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

TEST_CASE("Vector2s And Normalized Vector2s In The Same Space Can Be Added Together") {
    const Image::Vector2 v1(1, 2);
    const Image::NormalizedVector2 v2(1, 0);
    const auto v_new = v1 + v2;
    CHECK(v_new == Image::Vector2(2, 2));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Vector2s And Normalized Vector2s In Different Spaces Cannot Be Added Together") {
    const View::Vector2 v1;
    const Image::NormalizedVector2 v2;

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

TEST_CASE("Vector2sInTheSameSpaceCanBeAddedInPlace") {
    Image::Vector2 v1(1, 2);
    const Image::Vector2 v2(3, 2);
    v1 += v2;
    CHECK(v1 == Image::Vector2(4, 4));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Vector2sInDifferentSpacesCannotBeAddedInPlace") {
    View::Vector2 v1;
    const Image::Vector2 v2;

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

TEST_CASE("Vector2s And Normalized Vector2s In The Same Space Can Be Added In Place") {
    Image::Vector2 v1(1, 2);
    const Image::NormalizedVector2 v2(1, 0);
    v1 += v2;
    CHECK(v1 == Image::Vector2(2, 2));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Vector2s And 3D Vectors In The Same Space Cannot Be Added In Place") {
    const View::Vector v1;
    View::Vector2 v2;

    // We should not be able to compile:
    // v1 += v2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v2 += v1);
    using required_type = StaticAssert::invalid_vector_to_vector_addition;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}

TEST_CASE("Vector2s And Normalized Vector2s In Different Spaces Cannot Be Added In Place") {
    View::Vector2 v1;
    const Image::NormalizedVector2 v2;

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

TEST_CASE("Vector2sInTheSameSpaceCanBeSubtracted") {
    const Image::Vector2 v1(3, 2);
    const Image::Vector2 v2(1, 2);
    const auto v_new = v1 - v2;
    CHECK(v_new == Image::Vector2(2, 0));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Vector2s And Normalized Vector2s In Different Spaces Cannot Be Subtracted") {
    const View::Vector2 v1;
    const Image::NormalizedVector2 v2;

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

TEST_CASE("Vector2sInTheSameSpaceCanBeSubtractedInPlace") {
    Image::Vector2 v1(1, 2);
    const Image::Vector2 v2(3, 2);
    v1 -= v2;
    CHECK(v1 == Image::Vector2(-2, 0));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Vector2sInDifferentSpacesCannotBeSubtractedInPlace") {
    View::Vector2 v1;
    const Image::Vector2 v2;

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

TEST_CASE("Vector2s And Normalized Vector2s In TheS ame Space Can Be Subtracted In Place") {
    Image::Vector2 v1(1, 2);
    const Image::NormalizedVector2 v2(1, 0);
    v1 -= v2;
    CHECK(v1 == Image::Vector2(0, 2));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Vector2s And Normalized Vector2s In Different Spaces Cannot Be Subtracted In Place") {
    View::Vector2 v1;
    const Image::NormalizedVector2 v2;

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

TEST_CASE("Vector2sCanBeMultiplied") {
    const View::Vector2 v(1, 2);
    const auto scaled_v = v * 2;
    CHECK(scaled_v == View::Vector2(2, 4));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Vector2sCanBeScaled") {
    View::Vector2 v(1, 2);
    v *= 2;
    CHECK(v == View::Vector2(2, 4));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Vector2sSupportMag") {
    const Image::Vector2 v(3, 4);
    // 5 = sqrt(3*3 + 4*4)
    CHECK(v.Mag().get() == 5);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Vector2 Mag Is Strongly Typed: Millimetres") {
    const Image::Vector2 v(3, 4);
    const Millimetres m{ 0 };
    CHECK(typeid(v.Mag()).name() == typeid(m).name());
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Vector2 Mag Is Strongly Typed: Pixels") {
    const View::Vector2 v(3, 4);
    const Pixels p{ 0 };
    CHECK(typeid(v.Mag()).name() == typeid(p).name());
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Vector2sSupportMag_double") {
    const Image::Vector2 v(3, 4);
    // 5 = sqrt(3*3 + 4*4)
    CHECK(v.Mag_double() == 5);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Vector2 Can Be Normalized") {
    const Image::Vector2 v(3, 4);
    const auto v_norm = v.Norm();
    // Mag of v = sqrt(3*3 + 4*4) = 5
    CHECK(v_norm == Image::Vector2(3.0 / 5, 4.0 / 5));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Vector2s Can Be Normalized to produce a Normalized Vector2") {
    const Image::Vector2 v;
    using converted_type = decltype(v.Norm());
    using required_type = decltype(Image::NormalizedVector2{});
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("ZeroSizeVector2sCannotBeNormalized") {
    const Image::Vector2 v(0, 0);
    CHECK_THROWS_AS(v.Norm(), std::invalid_argument);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Vector2s can be constructed from implementation") {
    TestVector impl;
    impl.m_values[0] = 3;
    impl.m_values[1] = 4;
    impl.m_values[2] = 5;
    const Patient::Vector2 v(impl);
    CHECK(v.X() == 3);
    CHECK(v.Y() == 4);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Vector2s ignore Z when constructed from implementation") {
    TestVector impl;
    impl.m_values[0] = 3;
    impl.m_values[1] = 4;
    impl.m_values[2] = 5;
    const Patient::Vector2 v(impl);
    CHECK(v.Mag_double() == 5);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Vector2s Can Be Cast To The Implementation") {
    const Patient::Vector2 v(1, 0);
    auto impl = static_cast<TestVector>(v);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Vector2s cannot be implicitly cast to the implementation") {
    const Patient::Vector2 v(1, 0);

    // We should not be able to compile:
    // TestVector2 impl = v;
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Vector2s Can Be Passed By Value To Vector") {

    const Patient::Vector2 nv{1, 2};

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

TEST_CASE("Vector2s Can Be Passed By Const Ref To Vector") {

    const Patient::Vector2 nv(0, 4);

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

TEST_CASE("Vector2sFromTheSameSpaceCanBeDotted") {
    const View::Vector2 v1(1, 2);
    const View::Vector2 v2(1, 2);
    const auto dot = v1.Dot(v2);
    CHECK(dot == 1 * 1 + 2 * 2);
}
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Vector2sFromDifferentSpacesCannotBeDotted") {
    const View::Vector2 v1;
    const Image::Vector2 v2;

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

TEST_CASE("Vector2sFromTheSameSpaceCanBeCrossed") {
    const View::Vector2 v1(1, 0);
    const View::Vector2 v2(0, 1);
    const auto cross = v1.Cross(v2);

    CHECK(cross == View::Vector(0, 0, 1));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Vector2sFromDifferentSpacesCannotBeCrossed") {
    const View::Vector2 v1;
    const Image::Vector2 v2;

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

TEST_CASE("Vector2sFromTheSameSpaceCanBeCrossedUsingStarOperator") {
    const View::Vector2 v1(1, 0);
    const View::Vector2 v2(0, 1);
    const auto cross = v1 * v2;
    CHECK(cross == View::Vector(0, 0, 1));
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Vector2sFromDifferentSpacesCannotBeCrossedUsingStarOperator") {
    const View::Vector2 v1;
    const Image::Vector2 v2;

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
TEST_CASE("Vector2s From The Same Space Cannot Be Crossed Using Star Equal Operator") {
    View::Vector2 v1;
    const View::Vector2 v2;

    // We should not be able to compile:
    // v1 *= v2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v1 *= v2);
    using required_type = StaticAssert::invalid_vector2_in_place_cross;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}

TEST_CASE("Vector2s From Different Spaces Cannot Be Crossed Using Star Equal Operator") {
    View::Vector2 v1;
    const Image::Vector2 v2;

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

TEST_CASE("Vector2s Support Element Access By Name") {
    const Image::Vector2 v(2, 3);
    CHECK(v.X() == 2);
    CHECK(v.Y() == 3);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Vector2s Do Not Support Z Access By Name") {
    const Image::Vector2 v2;

    using converted_type = decltype(v2.Z());
    using required_type = StaticAssert::z_not_supported;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Vector2sSupportConstBeginAndEnd") {
    const Image::Vector2 v(2, 3);
    std::vector<double> values;
    std::copy(v.cbegin(), v.cend(), std::back_inserter(values));
    CHECK(values.size() == 2);
    CHECK(values[0] == 2);
    CHECK(values[1] == 3);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Vector2sSupportNonConstBeginAndEnd") {
    Image::Vector2 v(2, 3);
    std::vector<double> values;
    std::copy(v.begin(), v.end(), std::back_inserter(values));
    CHECK(values.size() == 2);
    CHECK(values[0] == 2);
    CHECK(values[1] == 3);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Vector2sCanBeTransformedWithTheSTL") {
    Image::Vector2 v(2, 3);
    std::transform(
        v.cbegin(),
        v.cend(),
        v.begin(),
        [](const double d) {return d * 2; }
    );
    CHECK(v == Image::Vector2(4, 6));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Vector2sSupportElementAccessByRandomAccess") {
    const Image::Vector2 v(2, 3);
    CHECK(v[0] == 2);
    CHECK(v[1] == 3);
}

TEST_CASE("Vector2sThrowIfRandomAccessIsTooHigh") {
    const Image::Vector2 v(2, 3);
    CHECK_THROWS_AS(v[2], std::invalid_argument);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Vector2sSupportElementAccessByAt") {
    const Image::Vector2 v(2, 3);
    CHECK(v.at<0>() == 2);
    CHECK(v.at<1>() == 3);
}
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Vector2sSupportElementAccessByAtDoesNotCompileIfTooLow") {
    const Image::Vector2 v(2, 3);

    // We should not be able to compile:
    // auto dummy = v.at<-1>();
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(v.at<-1>());
    using required_type = StaticAssert::invalid_at_access;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
TEST_CASE("Vector2sSupportElementAccessByAtDoesNotCompileIfTooHigh") {
    const Image::Vector2 v(2, 3);

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

TEST_CASE("Vector2sCanBeConvertedFromOneSpaceToAnotherIgnoringTranslation") {

    const TransformManager tm;
    const View::Vector2 v_view(1, 0);
    auto v_patient = v_view.ConvertTo<Patient>(tm);
    CHECK(v_patient == Patient::Vector(15, 16, 17));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Vector2s Can Be Converted From One Space To Another Producing A Vector") {

    const TransformManager tm;
    const View::Vector2 v_view(1, 0);
    using converted_type = decltype(v_view.ConvertTo<Patient>(tm));
    using required_type = decltype(Patient::Vector{});
    CHECK(
        static_cast<bool>(std::is_same_v<converted_type, required_type>)
    );
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Vector2sCanBeStreamed") {
    const View::Vector2 v(1.2, 2.3);
    std::stringstream stream;
    stream << v;
    CHECK(stream.str() == std::string("View::Vector2 (1.2, 2.3)"));
}

//-------------------------------------------------------------------------------------------------
