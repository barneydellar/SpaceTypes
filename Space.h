#pragma once

/// This header provides the Space Point, Vector and NormalizedVector clasees.
/// Please see Readme.md for more details.

namespace Space {

    template <typename Space, typename ExternalImplementation>
    class Vector;

    template <typename Space, typename ExternalImplementation>
    class Vector2;

    template <typename Space, typename ExternalImplementation>
    class Point;

    template <typename Space, typename ExternalImplementation>
    class Point2;

    template <typename Space, typename ExternalImplementation>
    class NormalizedVector;

    template <typename Space, typename ExternalImplementation>
    class NormalizedVector2;


    template <typename Space, typename ExternalImplementation>
    class VectorBase;

    template <typename Space, typename ExternalImplementation>
    class Vector2Base;

    template <typename Space, typename ExternalImplementation>
    class PointBase;

    template <typename Space, typename ExternalImplementation>
    class Point2Base;

    template <typename Space, typename ExternalImplementation>
    class NormalizedVectorBase;

    template <typename Space, typename ExternalImplementation>
    class NormalizedVector2Base;
}

#include "Point.h"
#include "Point2.h"
#include "Vector.h"
#include "Vector2.h"
#include "NormalizedVector.h"
#include "NormalizedVector2.h"

namespace Space {
    template <typename SpaceName, typename Implementation, typename Units>
    struct SpaceBase {

        using temp = Point<SpaceName, Implementation>;

        using Point = temp;
        using Point2 = Point2<SpaceName, Implementation>;
        using Vector = Vector<SpaceName, Implementation>;
        using Vector2 = Vector2<SpaceName, Implementation>;
        using NormalizedVector = NormalizedVector<SpaceName, Implementation>;
        using NormalizedVector2 = NormalizedVector2<SpaceName, Implementation>;
        using Unit = Units;
    };
}

