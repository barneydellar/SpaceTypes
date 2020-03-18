#include "pch.h"
#include "SpaceHelpers.h"

using namespace Space;

//-------------------------------------------------------------------------------------------------

TEST_CASE("Point2s can be constructed") {
    View::Point2 p;
}

TEST_CASE("Point2s have zero value by default") {
    View::Point2 p;
    CHECK(p[0] == 0);
    CHECK(p[1] == 0);
}
TEST_CASE("Point2s can be created using initalizer lists of three numbers") {
    View::Point2 p{ 1, 2 };
    CHECK(p[0] == 1);
    CHECK(p[1] == 2);
}
TEST_CASE("Point2s throw when using initalizer lists that are too small") {
    try
    {
        View::Point2 p{1};
    }
    catch (std::invalid_argument&)
    {
        return;
    }
    REQUIRE(false);
}
TEST_CASE("Point2s throw when using initalizer lists that are too large") {
    try
    {
        View::Point2 p{ 1, 2, 3 };
    } catch (std::invalid_argument&)
    {
        return;
    }
    REQUIRE(false);
}


//-------------------------------------------------------------------------------------------------

TEST_CASE("Point2sCanBeConstructedFromTwoDoubles") {
    const View::Point2 p(1, 2);
    CHECK(p.X() == 1);
    CHECK(p.Y() == 2);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Point2s can be constructed from implementation") {
    const TestVector impl(3, 2, 1);
    const Patient::Point2 p(impl);
    CHECK(p.X() == 3);
    CHECK(p.Y() == 2);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Point2s Can Be Cast To The Implementation") {
    const Patient::Point2 p(1, 0);
    auto impl = static_cast<TestVector>(p);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Point2s cannot be implicitly cast to the implementation") {
    const Patient::Point2 p;

    // This does not compile:
    // TestVector impl = p;
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Point2sFromTheSameSpaceCanBeComparedUsingEqual_same") {
    const View::Point2 p1(1, 0);
    const View::Point2 p2(1, 0);
    CHECK(p1 == p2);
}

TEST_CASE("Point2sFromTheSameSpaceCanBeComparedUsingEqual_different") {
    const Patient::Point2 p1(1, 0);
    const Patient::Point2 p2(2, 0);
    CHECK(!(p1 == p2));
}
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Point2sFromDiffefentSpacesCannotBeComparedUsingEqual") {
    const View::Point2 p1;
    const Patient::Point2 p2;

    // We should not be able to compile:
    // auto dummy = p1 == p2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(p1 == p2);
    using required_type = StaticAssert::invalid_equality;
    CHECK(
        static_cast<bool>(std::is_same<converted_type, required_type>::value)
    );
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("Point2sFromTheSameSpaceCanBeComparedUsingInequality_same") {
    const View::Point2 p1(1, 0);
    const View::Point2 p2(1, 0);

    const bool c = p1 != p2;
    const auto d = !c;
}

TEST_CASE("Point2sFromTheSameSpaceCanBeComparedUsingInequality_different") {
    const Patient::Point2 p1(1, 0);
    const Patient::Point2 p2(2, 0);
    CHECK(p1 != p2);
}
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Point2sFromDiffefentSpacesCannotBeComparedUsingInequality") {
    const View::Point2 p1;
    const Patient::Point2 p2;

    // We should not be able to compile:
    // auto dummy = p1 != p2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(p1 != p2);
    using required_type = StaticAssert::invalid_equality;
    CHECK(static_cast<bool>(std::is_same<converted_type, required_type>::value));
}
#endif

//-------------------------------------------------------------------------------------------------

//TEST_CASE("Point2sFromTheSameSpaceCanBeSubtractedFromGiveAVector") {
//    const View::Point2 p1(2, 3);
//    const View::Point2 p2(1, 1);
//    const auto v = p1 - p2;
//    CHECK(v == View::Vector2(1, 2));
//}
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Point2sFromDifferfentSpacesCannotBeSubtracted") {
    const View::Point2 p1;
    const Patient::Point2 p2;

    // We should not be able to compile this:
    // auto dummy = p1 - p2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(p1 - p2);
    using required_type = StaticAssert::invalid_subtraction;
    CHECK(
        static_cast<bool>(std::is_same<converted_type, required_type>::value)
    );
}
#endif

TEST_CASE("Point2sCanBeCopied") {
    const View::Point2 p(2, 3);

    const auto copy = p;
    CHECK(copy == p);
}

TEST_CASE("Point2sCanBeCopyAssigned") {
    const View::Point2 p(2, 3);

    const auto copy(p);
    CHECK(copy == p);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Point2sSupportElementAccessByName") {
    const View::Point2 p(2, 3);
    CHECK(p.X() == 2);
    CHECK(p.Y() == 3);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Point2sSupportConstBeginAndEnd") {
    const View::Point2 p(2, 3);
    std::vector<double> values;
    std::copy(p.cbegin(), p.cend(), std::back_inserter(values));
    CHECK(values[0] == 2);
    CHECK(values[1] == 3);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Point2sSupportNonConstBeginAndEnd") {
    View::Point2 p(2, 3);
    std::vector<double> values;

    std::copy(p.begin(), p.end(), std::back_inserter(values));
    CHECK(values[0] == 2);
    CHECK(values[1] == 3);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Point2sCanBeTransformedWithTheSTL") {
    View::Point2 p(2, 3);

    std::transform(
        p.cbegin(),
        p.cend(),
        p.begin(),
        [](const double d) {return d * 2; }
    );
    CHECK(p == View::Point2(4, 6));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Point2sSupportElementAccessByRandomAccess") {
    const View::Point2 p(2, 3);
    CHECK(p[0] == 2);
    CHECK(p[1] == 3);
}

TEST_CASE("Point2sThrowIfRandomAccessIsTooHigh") {
    const View::Point2 p(2, 3);
    CHECK_THROWS_AS(p[2], std::invalid_argument);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Point2sSupportElementAccessByAt") {
    const View::Point2 p(2, 3);
    CHECK(p.at<0>() == 2);
    CHECK(p.at<1>() == 3);
}
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Point2sSupportElementAccessByAtDoesNotCompileIfTooLow") {
    const View::Point2 p;

    // We should not be able to compile:
    // auto dummy = p.at<-1>();
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(p.at<-1>());
    using required_type = StaticAssert::invalid_at_access;
    CHECK(
        static_cast<bool>(std::is_same<converted_type, required_type>::value)
    );
}
TEST_CASE("Point2sSupportElementAccessByAtDoesNotCompileIfTooHigh") {
    const View::Point2 p;

    // We should not be able to compile:
    // auto dummy = p.at<3>();
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(p.at<3>());
    using required_type = StaticAssert::invalid_at_access;
    CHECK(
        static_cast<bool>(std::is_same<converted_type, required_type>::value)
    );
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("Point2sCanBeConvertedFromOneSpaceToAnotherUsingTranslation") {

    const TransformManager tm;
    const View::Point2 p_view(1, 2);
    const auto p_patient = p_view.ConvertTo<Patient>(tm);
    CHECK(p_patient == Patient::Point(-5, -6, -7));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Point2sCanBeConvertedFromOneSpaceToAnotherProducingA3DPoint") {

    const TransformManager tm;
    const View::Point2 p_view(1, 2);

    using converted_type = decltype(p_view.ConvertTo<Patient>(tm));
    using required_type = decltype(Patient::Point{});
    CHECK(
        static_cast<bool>(std::is_same<converted_type, required_type>::value)
    );
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Point2sCanBeStreamed") {
    const Image::Point2 p(2, 3);
    std::stringstream stream;
    stream << p;
    CHECK(stream.str() == std::string("Image::Point2 (2, 3)"));
}

//-------------------------------------------------------------------------------------------------

