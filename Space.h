#pragma once

/// This header provides the ThisSpace Point, Vector and NormalizedVector clasees.
/// Please see Readme.md for more details.

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class Vector;

    template <typename ThisSpace, typename Implementation>
    class Vector2;

    template <typename ThisSpace, typename Implementation>
    class Point;

    template <typename ThisSpace, typename Implementation>
    class Point2;

    template <typename ThisSpace, typename Implementation>
    class NormalizedVector;

    template <typename ThisSpace, typename Implementation>
    class NormalizedVector2;


    template <typename ThisSpace, typename Implementation>
    class VectorBase;

    template <typename ThisSpace, typename Implementation>
    class Vector2Base;

    template <typename ThisSpace, typename Implementation>
    class PointBase;

    template <typename ThisSpace, typename Implementation>
    class Point2Base;

    template <typename ThisSpace, typename Implementation>
    class NormalizedVectorBase;

    template <typename ThisSpace, typename Implementation>
    class NormalizedVector2Base;
}

#include "detail/StaticAsserts.h"
#include "detail/SpaceImpl.h"
#include "detail/Base.h"
#include "Point.h"
#include "Point2.h"
#include "Vector.h"
#include "Vector2.h"
#include "NormalizedVector.h"
#include "NormalizedVector2.h"

namespace Space {
    template <typename ThisSpace, typename Implementation, typename Units>
    struct SpaceBase {
        using Point = Point<ThisSpace, Implementation>;
        using Point2 = Point2<ThisSpace, Implementation>;
        using Vector = Vector<ThisSpace, Implementation>;
        using Vector2 = Vector2<ThisSpace, Implementation>;
        using NormalizedVector = NormalizedVector<ThisSpace, Implementation>;
        using NormalizedVector2 = NormalizedVector2<ThisSpace, Implementation>;
        using Unit = Units;
    };
}

