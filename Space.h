#pragma once

/// This header provides the ThisSpace Point, Vector and NormalizedVector classes.
/// Please see Readme.md for more details.

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class NormalizedVector;

    template <typename ThisSpace, typename Implementation>
    class NormalizedXYVector;

    template <typename ThisSpace, typename Implementation>
    class Point;

    template <typename ThisSpace, typename Implementation>
    class Vector;

    template <typename ThisSpace, typename Implementation>
    class XYPoint;

    template <typename ThisSpace, typename Implementation>
    class XYVector;
}

#include "detail/StaticAsserts.h"
#include "detail/SpaceImpl.h"
#include "detail/Base.h"
#include "detail/Helpers.h"
#include "NormalizedVector.h"
#include "NormalizedXYVector.h"
#include "Point.h"
#include "Vector.h"
#include "XYPoint.h"
#include "XYVector.h"

namespace Space {

    enum class XY
    {
        IsUsed = true,
        IsNotUsed = false
    };
    
    template <int I>
    concept ValidFor3dAt = (I >= 0 && I <= 2);

    template <int I>
    concept ValidFor2dAt = (I >= 0 && I <= 1);

    template <typename ThisSpace, typename Implementation, XY b, typename Units>
    struct SpaceBase {
        using Unit = Units;

        static constexpr bool supportsXY = static_cast<bool>(b);
        static constexpr bool doesNotSupportXY = !static_cast<bool>(b);

        using Point = Point<ThisSpace, Implementation>;
        using Vector = Vector<ThisSpace, Implementation>;
        using NormalizedVector = NormalizedVector<ThisSpace, Implementation>;

        using XYPoint = std::conditional_t<static_cast<bool>(b), XYPoint<ThisSpace, Implementation>, StaticAssert::XYVector_not_supported>;
        using XYVector = std::conditional_t<static_cast<bool>(b), XYVector<ThisSpace, Implementation>, StaticAssert::XYVector_not_supported>;
        using NormalizedXYVector = std::conditional_t<static_cast<bool>(b), NormalizedXYVector<ThisSpace, Implementation>, StaticAssert::XYVector_not_supported>;
    };
}

