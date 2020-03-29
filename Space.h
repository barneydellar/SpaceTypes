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
    template <typename ThisSpace, typename Implementation, typename Units>
    struct SpaceBase {
        using Point = Point<ThisSpace, Implementation>;
        using XYPoint = XYPoint<ThisSpace, Implementation>;
        using Vector = Vector<ThisSpace, Implementation>;
        using XYVector = XYVector<ThisSpace, Implementation>;
        using NormalizedVector = NormalizedVector<ThisSpace, Implementation>;
        using NormalizedXYVector = NormalizedXYVector<ThisSpace, Implementation>;
        using Unit = Units;
    };
}

