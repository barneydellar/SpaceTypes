#pragma once

#include "Point.h"
#include "Vector.h"
#include "NormalizedVector.h"

namespace Space {

    //--------------------------------------------------------------------------------------------

    template <typename SpaceName, typename Implementation, typename Units>
    struct SpaceBase {
        using Point = Point<SpaceName, Implementation>;
        using Vector = Vector<SpaceName, Implementation>;
        using NormalizedVector = NormalizedVector<SpaceName, Implementation>;
        using Unit = Units;
    };
}

