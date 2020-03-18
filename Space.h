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
}

#include "VectorBase.h"
#include "Point.h"
#include "Point2.h"
#include "Vector.h"
#include "Vector2.h"
#include "NormalizedVector.h"

namespace Space {
    template <typename SpaceName, typename Implementation, typename Units>
    struct SpaceBase {
        using Point = Point<SpaceName, Implementation>;
        using Point2 = Point2<SpaceName, Implementation>;
        using Vector = Vector<SpaceName, Implementation>;
        using Vector2 = Vector2<SpaceName, Implementation>;
        using NormalizedVector = NormalizedVector<SpaceName, Implementation>;
        using Unit = Units;
    };
}

