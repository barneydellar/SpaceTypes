#pragma once

/// This header provides the ThisSpace Point, Vector and NormalizedVector classes.
/// Please see Readme.md for more details.

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class Vector;

    template <typename ThisSpace, typename Implementation>
    class XYVector;

    template <typename ThisSpace, typename Implementation>
    class Point;

    template <typename ThisSpace, typename Implementation>
    class XYPoint;

    template <typename ThisSpace, typename Implementation>
    class NormalizedVector;

    template <typename ThisSpace, typename Implementation>
    class NormalizedXYVector;


    template <typename ThisSpace, typename Implementation>
    class VectorBase;

    template <typename ThisSpace, typename Implementation>
    class XYVectorBase;

    template <typename ThisSpace, typename Implementation>
    class NormalizedVectorBase;

}

#include "detail/StaticAsserts.h"
#include "detail/SpaceImpl.h"
#include "detail/Base.h"
#include "Point.h"
#include "XYPoint.h"
#include "Vector.h"
#include "XYVector.h"
#include "NormalizedVector.h"
#include "NormalizedXYVector.h"

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

