#pragma once
#include "ExampleImpl.h"

class TransformManager final
{
public:

    template <typename From, typename To>
    [[nodiscard]] Space::ExampleImpl Transform(
        Space::ExampleImpl
    ) const noexcept {
        using namespace Space;
        if constexpr (From::id == Space::SpaceIDs::View) {
            return { -5, -6, -7 };
        }
        else {
            return { 0, 0, 0 };
        }
    }

    template <typename From, typename To>
    [[nodiscard]] Space::ExampleImpl Transform33(
        Space::ExampleImpl
    ) const noexcept {
        using namespace Space;
        if constexpr (From::id == Space::SpaceIDs::View) {
            return { 15, 16, 17 };
        }
        else {
            return { 0, 0, 0 };
        }
    }
};
