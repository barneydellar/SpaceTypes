#pragma once

/// This header provides the ThisSpace Point, Vector and NormalizedVector
/// classes. Please see Readme.md for more details.

#include <array>
#include <iostream>
#include <numeric>
#include <sstream>
#include <format>
#include <print>

namespace Space::implementation {

template <typename ThisSpace, typename UnderlyingData> class Point;
template <typename ThisSpace, typename UnderlyingData> class XYPoint;
template <typename ThisSpace, typename UnderlyingData> class Vector;
template <typename ThisSpace, typename UnderlyingData> class XYVector;
template <typename ThisSpace, typename UnderlyingData> class NormalizedVector;
template <typename ThisSpace, typename UnderlyingData> class NormalizedXYVector;
} // namespace Space::implementation

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

enum class XY { IsUsed = true, IsNotUsed = false };

template <typename ThisSpace, typename UnderlyingData, XY xy, typename Units> struct SpaceBase {
    using Unit = Units;

    static constexpr bool supportsXY = static_cast<bool>(xy);
    static constexpr bool doesNotSupportXY = !static_cast<bool>(xy);

    using Point = implementation::Point<ThisSpace, UnderlyingData>;
    using XYPoint = implementation::XYPoint<ThisSpace, UnderlyingData>;
    using Vector = implementation::Vector<ThisSpace, UnderlyingData>;
    using XYVector = implementation::XYVector<ThisSpace, UnderlyingData>;
    using NormalizedVector = implementation::NormalizedVector<ThisSpace, UnderlyingData>;
    using NormalizedXYVector = implementation::NormalizedXYVector<ThisSpace, UnderlyingData>;
};
} // namespace Space
