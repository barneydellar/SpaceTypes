#pragma once

#include "Point.h"
#include "Vector.h"
#include "NormalizedVector.h"

namespace Space {

    //--------------------------------------------------------------------------------------------

    template <typename SpaceName, typename Units>
    struct SpaceBase {
        using Point = detail::Point<SpaceName>;
        using Vector = detail::Vector<SpaceName>;
        using NormalizedVector = detail::NormalizedVector<SpaceName>;
        using Unit = Units;
    };
}

