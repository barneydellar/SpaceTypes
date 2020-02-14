#pragma once

#include "Point.h"
#include "Vector.h"
#include "NormalizedVector.h"

namespace Space {

    //--------------------------------------------------------------------------------------------

    template <typename SpaceName, typename Units>
    struct SpaceBase {
        using Point = Point<SpaceName>;
        using Vector = Vector<SpaceName>;
        using NormalizedVector = NormalizedVector<SpaceName>;
        using Unit = Units;
    };
}

