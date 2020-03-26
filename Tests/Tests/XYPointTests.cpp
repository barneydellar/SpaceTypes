#include "pch.h"
#include "SpaceHelpers.h"

using namespace Space;

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYPoints can be constructed") {
    View::XYPoint p;
}

TEST_CASE("XYPoints have zero value by default") {
    View::XYPoint p;
    CHECK(p[0] == 0);
    CHECK(p[1] == 0);
}
TEST_CASE("XYPoints can be created using initalizer lists of two numbers") {
    View::XYPoint p{ 1, 2 };
    CHECK(p[0] == 1);
    CHECK(p[1] == 2);
}
TEST_CASE("XYPoints throw when using initalizer lists that are too small") {
    try
    {
        View::XYPoint p{1};
    }
    catch (std::invalid_argument&)
    {
        return;
    }
    REQUIRE(false);
}
TEST_CASE("XYPoints throw when using initalizer lists that are too large") {
    try
    {
        View::XYPoint p{ 1, 2, 3 };
    } catch (std::invalid_argument&)
    {
        return;
    }
    REQUIRE(false);
}


//-------------------------------------------------------------------------------------------------

TEST_CASE("XYPointsCanBeConstructedFromTwoDoubles") {
    const View::XYPoint p(1, 2);
    CHECK(p.X() == 1);
    CHECK(p.Y() == 2);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYPoints can be constructed from implementation") {
    TestVector impl;
    impl.m_values[0] = 3;
    impl.m_values[1] = 2;
    impl.m_values[2] = 1;
    const Patient::XYPoint p(impl);
    CHECK(p.X() == 3);
    CHECK(p.Y() == 2);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYPoints Can Be Cast To The Implementation") {
    const Patient::XYPoint p(3, 2);
    auto impl = static_cast<TestVector>(p);
    CHECK(impl.m_values[0] == 3);
    CHECK(impl.m_values[1] == 2);
    CHECK(impl.m_values[2] == 0);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYPoints have their z removed with implementation") {
    TestVector impl_in;
    impl_in.m_values[0] = 3;
    impl_in.m_values[1] = 2;
    impl_in.m_values[2] = 1;
    const Patient::XYPoint p(impl_in);
    auto impl = static_cast<TestVector>(p);
    CHECK(impl.m_values[0] == 3);
    CHECK(impl.m_values[1] == 2);
    CHECK(impl.m_values[2] == 0);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYPoints cannot be implicitly cast to the implementation") {
    const Patient::XYPoint p;

    // This does not compile:
    //TestVector impl = p;
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYPoints Can Be Passed By Value To Point") {

    const Patient::XYPoint nv{ 1, 2 };

    const auto lambda = [](
        const Patient::Point v
    ) {
        CHECK(v.X() == 1);
        CHECK(v.Y() == 2);
        CHECK(v.Z() == 0);
    };

    lambda(nv);
}
//-------------------------------------------------------------------------------------------------

TEST_CASE("XYPoints Can Be Passed By Const Ref To Point") {

    const Patient::XYPoint nv(0, 4);

    const auto lambda = [](
        const Patient::Point& v
    ) {
        CHECK(v.X() == 0);
        CHECK(v.Y() == 4);
    };

    lambda(nv);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYPointsFromTheSameSpaceCanBeComparedUsingEqual_same") {
    const View::XYPoint p1(1, 0);
    const View::XYPoint p2(1, 0);
    CHECK(p1 == p2);
}

TEST_CASE("XYPointsFromTheSameSpaceCanBeComparedUsingEqual_different") {
    const Patient::XYPoint p1(1, 0);
    const Patient::XYPoint p2(2, 0);
    CHECK(!(p1 == p2));
}
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYPointsFromDifferentSpacesCannotBeComparedUsingEqual") {
    const View::XYPoint p1;
    const Patient::XYPoint p2;

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

TEST_CASE("XYPointsFromTheSameSpaceCanBeComparedUsingInequality_same") {
    const View::XYPoint p1(1, 0);
    const View::XYPoint p2(1, 0);

    CHECK(p1 == p2);
}

TEST_CASE("XYPointsFromTheSameSpaceCanBeComparedUsingInequality_different") {
    const Patient::XYPoint p1(1, 0);
    const Patient::XYPoint p2(2, 0);
    CHECK(p1 != p2);
}

//-------------------------------------------------------------------------------------------------

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYPointsFromDifferentSpacesCannotBeComparedUsingInequality") {
    const View::XYPoint p1;
    const Patient::XYPoint p2;

    // We should not be able to compile:
    // auto dummy = p1 != p2;
    // But we can check the return type,
    // to make sure we get an invalid type:
    using converted_type = decltype(p1 != p2);
    using required_type = StaticAssert::invalid_space;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

TEST_CASE("Points and XYPoints From The Same Space Can Be Compared") {
    const View::Point p(1, 0, 0);
    const View::XYPoint p2(1, 0);

    CHECK(p == p2);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYPoints From The Same Space Can Be Subtracted From") {
    const View::XYPoint p1(2, 3);
    const View::XYPoint p2(1, 1);
    const auto v = p1 - p2;
    CHECK(v == View::XYVector(1, 2));
}

TEST_CASE("XYPoints From The Same Space Can Be Subtracted From to give a 2D Vector") {
    const View::XYPoint p1;
    const View::XYPoint p2;
    using converted_type = decltype(p1 - p2);
    using required_type = decltype(View::XYVector{});
    CHECK(
        static_cast<bool>(std::is_same_v<converted_type, required_type>)
    );
}
TEST_CASE("XYPoints Can Be Subtracted From Points in the same space") {
    const View::Point p(2, 3, 4);
    const View::XYPoint p2(1, 1);
    const auto v = p - p2;
    CHECK(v == View::Vector(1, 2, 4));
}

TEST_CASE("XYPoints Can Be Subtracted From Points in the same space to give a 3D Vector") {
    const View::Point p;
    const View::XYPoint p2;
    using converted_type = decltype(p - p2);
    using required_type = decltype(View::Vector{});
    CHECK(
        static_cast<bool>(std::is_same_v<converted_type, required_type>)
    );
}
TEST_CASE("Points Can Be Subtracted From XYPoints in the same space") {
    const View::Point p(2, 3, 4);
    const View::XYPoint p2(1, 1);
    const auto v = p2 - p;
    CHECK(v == View::Vector(-1, -2, -4));
}

TEST_CASE("Points Can Be Subtracted From XYPoints in the same space to give a 3D Vector") {
    const View::Point p;
    const View::XYPoint p2;
    using converted_type = decltype(p2 - p);
    using required_type = decltype(View::Vector{});
    CHECK(
        static_cast<bool>(std::is_same_v<converted_type, required_type>)
    );
}

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYPointsFromDifferfentSpacesCannotBeSubtracted") {
    const View::XYPoint p1;
    const Patient::XYPoint p2;

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

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYPoints cannot be added") {
    const View::XYPoint p1;
    const View::XYPoint p2;
    using converted_type = decltype(p1 + p2);
    using required_type = StaticAssert::invalid_point_to_point_addition;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYPoints and Points cannot be added") {
    const View::Point p1;
    const View::XYPoint p2;
    using converted_type_A = decltype(p1 + p2);
    using converted_type_B = decltype(p2 + p1);
    using required_type = StaticAssert::invalid_point_to_point_addition;
    CHECK(static_cast<bool>(std::is_same_v<converted_type_A, required_type>));
    CHECK(static_cast<bool>(std::is_same_v<converted_type_B, required_type>));
}

#endif
//-------------------------------------------------------------------------------------------------

TEST_CASE("XYPointsCanBeCopied") {
    const View::XYPoint p(2, 3);

    const auto copy = p;
    CHECK(copy == p);
}

TEST_CASE("XYPointsCanBeCopyAssigned") {
    const View::XYPoint p(2, 3);

    const auto copy(p);
    CHECK(copy == p);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYPointsSupportElementAccessByName") {
    const View::XYPoint p(2, 3);
    CHECK(p.X() == 2);
    CHECK(p.Y() == 3);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYPoints Can Be Modifed By Name") {
    Image::XYPoint v(2, 3);
    v.SetX(10);
    v.SetY(20);
    CHECK(v.X() == 10);
    CHECK(v.Y() == 20);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYPoints Do Not Support Z Modifcation By Name") {
    Image::XYPoint v2;

    // Should not compile:
    // v2.SetZ(5);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYPointsSupportConstBeginAndEnd") {
    const View::XYPoint p(2, 3);
    std::vector<double> values;
    std::copy(p.cbegin(), p.cend(), std::back_inserter(values));
    CHECK(values.size() == 2);
    CHECK(values[0] == 2);
    CHECK(values[1] == 3);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYPointsSupportNonConstBeginAndEnd") {
    View::XYPoint p(2, 3);
    std::vector<double> values;

    std::copy(p.begin(), p.end(), std::back_inserter(values));
    CHECK(values.size() == 2);
    CHECK(values[0] == 2);
    CHECK(values[1] == 3);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYPointsCanBeTransformedWithTheSTL") {
    View::XYPoint p(2, 3);

    std::transform(
        p.cbegin(),
        p.cend(),
        p.begin(),
        [](const double d) {return d * 2; }
    );
    CHECK(p == View::XYPoint(4, 6));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYPointsSupportElementAccessByRandomAccess") {
    const View::XYPoint p(2, 3);
    CHECK(p[0] == 2);
    CHECK(p[1] == 3);
}

TEST_CASE("XYPointsThrowIfRandomAccessIsTooHigh") {
    const View::XYPoint p(2, 3);
    CHECK_THROWS_AS(p[2], std::invalid_argument);
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYPointsSupportElementAccessByAt") {
    const View::XYPoint p(2, 3);
    CHECK(p.at<0>() == 2);
    CHECK(p.at<1>() == 3);
}
#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XYPointsSupportElementAccessByAtDoesNotCompileIfTooLow") {
    const View::XYPoint p;

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
TEST_CASE("XYPointsSupportElementAccessByAtDoesNotCompileIfTooHigh") {
    const View::XYPoint p;

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

TEST_CASE("XYPoints Do Not Support removing Z") {
    Image::XYPoint p;

    // Should not compile:
    // p.ToXY();
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYPointsCanBeConvertedFromOneSpaceToAnotherUsingTranslation") {

    const TransformManager tm;
    const View::XYPoint p_view(1, 2);
    const auto p_patient = p_view.ConvertTo<Patient>(tm);
    CHECK(p_patient == Patient::Point(-5, -6, -7));
}

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYPointsCanBeConvertedFromOneSpaceToAnotherProducingA3DPoint") {

    const TransformManager tm;
    const View::XYPoint p_view(1, 2);

    using converted_type = decltype(p_view.ConvertTo<Patient>(tm));
    using required_type = decltype(Patient::Point{});
    CHECK(
        static_cast<bool>(std::is_same_v<converted_type, required_type>)
    );
}

//-------------------------------------------------------------------------------------------------

#ifndef IGNORE_SPACE_STATIC_ASSERT
TEST_CASE("XY Points Cannot Be Converted To The Same Space") {
    const TransformManager tm;
    const View::XYPoint p;
    using converted_type = decltype(p.ConvertTo<View>(tm));
    using required_type = StaticAssert::invalid_conversion;
    CHECK(static_cast<bool>(std::is_same_v<converted_type, required_type>));
}
#endif

//-------------------------------------------------------------------------------------------------

TEST_CASE("XYPointsCanBeStreamed") {
    const Image::XYPoint p(2, 3);
    std::stringstream stream;
    stream << p;
    CHECK(stream.str() == std::string("Image::XYPoint (2, 3)"));
}

//-------------------------------------------------------------------------------------------------

