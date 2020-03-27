#include "pch.h"
#include "SpaceHelpers.h"

using namespace Space;

//-------------------------------------------------------------------------------------------------

TEST_CASE("Points can be constructed") {
    View::Point p;
}

TEST_CASE("Points have zero value by default") {
    View::Point p;
    CHECK(p[0] == 0);
    CHECK(p[1] == 0);
    CHECK(p[2] == 0);
}
TEST_CASE("Points can be created using initalizer lists of three numbers") {
    View::Point p{ 1, 2, 4 };
    CHECK(p[0] == 1);
    CHECK(p[1] == 2);
    CHECK(p[2] == 4);
}
TEST_CASE("Points throw when using initalizer lists that are too small") {
    try
    {
        View::Point p{1, 2};
    }
    catch (std::invalid_argument&)
    {
        return;
    }
    REQUIRE(false);
}
TEST_CASE("Points throw when using initalizer lists that are too large") {
    try
    {
        View::Point p{ 1, 2, 3, 4 };
    } catch (std::invalid_argument&)
    {
        return;
    }
    REQUIRE(false);
}


//-------------------------------------------------------------------------------------------------

TEST_CASE("PointsCanBeConstructedFromThreeDoubles") {
    const View::Point p(1, 2, 3);
    CHECK(p.X() == 1);
    CHECK(p.Y() == 2);
    CHECK(p.Z() == 3);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Points can be constructed from implementation") {
    TestVector impl;
    impl.m_values[0] = 3;
    impl.m_values[1] = 2;
    impl.m_values[2] = 1;
    const Patient::Point p(impl);
    CHECK(p.X() == 3);
    CHECK(p.Y() == 2);
    CHECK(p.Z() == 1);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Points Can Be Cast To The Implementation") {
    const Patient::Point p(1, 0, 0);
    auto impl = static_cast<TestVector>(p);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Points cannot be implicitly cast to the implementation") {
    const Patient::Point p(1, 0, 0);

    // This does not compile:
    // TestVector impl = p;
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("PointsFromTheSameSpaceCanBeComparedUsingEqual_same") {
    const View::Point p1(1, 0, 0);
    const View::Point p2(1, 0, 0);
    CHECK(p1 == p2);
}

TEST_CASE("PointsFromTheSameSpaceCanBeComparedUsingEqual_different") {
    const Patient::Point p1(1, 0, 0);
    const Patient::Point p2(2, 0, 0);
    CHECK(!(p1 == p2));
}
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("PointsFromDifferentSpacesCannotBeComparedUsingEqual") {
    const View::Point p1(1, 0, 0);
    const Patient::Point p2(1, 0, 0);

    // We should not be able to compile:
    // auto dummy = p1 == p2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(p1 == p2);
    using required_type = StaticAssert::invalid_space;
    CHECK(
        static_cast<bool>(std::is_same_v<converted_type, required_type>)
    );
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("PointsFromTheSameSpaceCanBeComparedUsingInequality_same") {
    const View::Point p1(1, 0, 0);
    const View::Point p2(1, 0, 0);

    const bool c = p1 != p2;
    const auto d = !c;
}

TEST_CASE("PointsFromTheSameSpaceCanBeComparedUsingInequality_different") {
    const Patient::Point p1(1, 0, 0);
    const Patient::Point p2(2, 0, 0);
    CHECK(p1 != p2);
}
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("PointsFromDifferentSpacesCannotBeComparedUsingInequality") {
    const View::Point p1(1, 0, 0);
    const Patient::Point p2(1, 0, 0);

    // We should not be able to compile:
    // auto dummy = p1 != p2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(p1 != p2);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("PointsFromTheSameSpaceCanBeSubtractedFromGiveAVector") {
    const View::Point p1(2, 3, 4);
    const View::Point p2(1, 1, 1);
    const auto v = p1 - p2;
    CHECK(v == View::Vector(1, 2, 3));
}
TEST_CASE("Points And XY Points From The Same Space Can Be Subtracted") {
    const View::Point p1(2, 3, 4);
    const View::XYPoint p2(1, 1);
    const auto v = p1 - p2;
    CHECK(v == View::Vector(1, 2, 4));
}
TEST_CASE("XY Points And Points From The Same Space Can Be Subtracted") {
    const View::XYPoint p1(2, 3);
    const View::Point p2(1, 1, 1);
    const auto v = p1 - p2;
    CHECK(v == View::Vector(1, 2, -1));
}
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("PointsFromDifferfentSpacesCannotBeSubtracted") {
    const View::Point p1(2, 3, 4);
    const Patient::Point p2(1, 1, 1);

    // We should not be able to compile this:
    // auto dummy = p1 - p2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(p1 - p2);
    using required_type = StaticAssert::invalid_space;
    CHECK(
        static_cast<bool>(std::is_same_v<converted_type, required_type>)
    );
}
#endif

//-------------------------------------------------------------------------------------------------
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Points cannot be added") {
    const View::Point p1;
    const View::Point p2;
    using converted_type = decltype(p1 + p2);
    using required_type = StaticAssert::invalid_point_to_point_addition;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("PointsCanBeCopied") {
    const View::Point p(2, 3, 4);

    const auto copy = p;
    CHECK(copy == p);
}

TEST_CASE("PointsCanBeCopyAssigned") {
    const View::Point p(2, 3, 4);

    const auto copy(p);
    CHECK(copy == p);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("PointsSupportElementAccessByName") {
    const View::Point p(2, 3, 4);
    CHECK(p.X() == 2);
    CHECK(p.Y() == 3);
    CHECK(p.Z() == 4);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Points Can Be Modifed By Name") {
    Image::Point v(2, 3, 4);
    v.SetX(10);
    v.SetY(20);
    v.SetZ(30);
    CHECK(v.X() == 10);
    CHECK(v.Y() == 20);
    CHECK(v.Z() == 30);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("PointsSupportConstBeginAndEnd") {
    const View::Point p(2, 3, 4);
    std::vector<double> values;
    std::copy(p.cbegin(), p.cend(), std::back_inserter(values));
    CHECK(values.size() == 3);
    CHECK(values[0] == 2);
    CHECK(values[1] == 3);
    CHECK(values[2] == 4);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("PointsSupportNonConstBeginAndEnd") {
    View::Point p(2, 3, 4);
    std::vector<double> values;

    std::copy(p.begin(), p.end(), std::back_inserter(values));
    CHECK(values.size() == 3);
    CHECK(values[0] == 2);
    CHECK(values[1] == 3);
    CHECK(values[2] == 4);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Points Can Have their z-value removed") {
    const Image::Point v(2, 3, 4);
    const auto v_norm = v.ToXY();
    CHECK(v_norm == Image::XYPoint(2, 3));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("Points Can Have their z-value removed to produce a XYVector") {
    const Image::Point v;
    using converted_type = decltype(v.ToXY());
    using required_type = decltype(Image::XYPoint{});
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("PointsCanBeTransformedWithTheSTL") {
    View::Point p(2, 3, 4);

    std::transform(
        p.cbegin(),
        p.cend(),
        p.begin(),
        [](const double d) {return d * 2; }
    );
    CHECK(p == View::Point(4, 6, 8));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("PointsSupportElementAccessByRandomAccess") {
    const View::Point p(2, 3, 4);
    CHECK(p[0] == 2);
    CHECK(p[1] == 3);
    CHECK(p[2] == 4);
}

TEST_CASE("PointsThrowIfRandomAccessIsTooHigh") {
    const View::Point p(2, 3, 4);
    CHECK_THROWS_AS(p[3], std::invalid_argument);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("PointsSupportElementAccessByAt") {
    const View::Point p(2, 3, 4);
    CHECK(p.at<0>() == 2);
    CHECK(p.at<1>() == 3);
    CHECK(p.at<2>() == 4);
}
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("PointsSupportElementAccessByAtDoesNotCompileIfTooLow") {
    const View::Point p(2, 3, 4);

    // We should not be able to compile:
    // auto dummy = p.at<-1>();
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(p.at<-1>());
    using required_type = StaticAssert::invalid_at_access;
    CHECK(
        static_cast<bool>(std::is_same_v<converted_type, required_type>)
    );
}
TEST_CASE("PointsSupportElementAccessByAtDoesNotCompileIfTooHigh") {
    const View::Point p(2, 3, 4);

    // We should not be able to compile:
    // auto dummy = p.at<3>();
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(p.at<3>());
    using required_type = StaticAssert::invalid_at_access;
    CHECK(
        static_cast<bool>(std::is_same_v<converted_type, required_type>)
    );
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("PointsCanBeConvertedFromOneSpaceToAnotherUsingTranslation") {

    const TransformManager tm;
    const View::Point p_view(1, 2, 3);
    const auto p_patient = p_view.ConvertTo<Patient>(tm);
    CHECK(p_patient == Patient::Point(-5, -6, -7));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("PointsCanBeConvertedFromOneSpaceToAnotherProducingAPoint") {

    const TransformManager tm;
    const View::Point p_view(1, 2, 3);

    using converted_type = decltype(p_view.ConvertTo<Patient>(tm));
    using required_type = decltype(Patient::Point{});
    CHECK(
        static_cast<bool>(std::is_same_v<converted_type, required_type>)
    );
}

//-------------------------------------------------------------------------------------------------

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("Points Cannot Be Converted To The Same Space") {
    const TransformManager tm;
    const View::Point p;
    using converted_type = decltype(p.ConvertTo<View>(tm));
    using required_type = StaticAssert::invalid_conversion;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("PointsCanBeStreamed") {
    const Image::Point p(2, 3, 4);
    std::stringstream stream;
    stream << p;
    CHECK(stream.str() == std::string("Image::Point (2, 3, 4)"));
}

//-------------------------------------------------------------------------------------------------

