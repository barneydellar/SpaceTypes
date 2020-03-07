#pragma once
#include "SpaceHelpers.h"

class TransformManager final
{
public:

    template <typename From, typename To>
    [[nodiscard]] TestVector Transform(
        TestVector
    ) const noexcept {
        using namespace Space;
        if constexpr (From::id == Space::SpaceIDs::View) {
            return TestVector{ -5, -6, -7 };
        }
        else {
            return TestVector{ 0, 0, 0 };
        }
    }

    template <typename From, typename To>
    [[nodiscard]] TestVector Transform33(
        TestVector
    ) const noexcept {
        using namespace Space;
        if constexpr (From::id == Space::SpaceIDs::View) {
            return TestVector{ 15, 16, 17 };
        }
        else {
            return TestVector{ 0, 0, 0 };
        }
    }
};
