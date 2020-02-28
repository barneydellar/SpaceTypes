#pragma once

#include "Point.h"
#include "Vector.h"
#include "NormalizedVector.h"

namespace Space {

    //--------------------------------------------------------------------------------------------

    template <typename SpaceName, typename Impl, typename Units>
    struct SpaceBase {
        using Point = Point<SpaceName, Impl>;
        using Vector = Vector<SpaceName, Impl>;
        using NormalizedVector = NormalizedVector<SpaceName, Impl>;
        using Unit = Units;
    };
}

