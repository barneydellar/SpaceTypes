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
        if (From::id == Space::SpaceIDs::View) {
            TestVector t;
            t.m_values[0] = -5;
            t.m_values[1] = -6;
            t.m_values[2] = -7;
            return t;
        }
        else {
            TestVector t;
            t.m_values[0] = 0;
            t.m_values[1] = 0;
            t.m_values[2] = 0;
            return t;
        }
    }

    template <typename From, typename To>
    [[nodiscard]] TestVector Transform33(
        TestVector
    ) const noexcept {
        using namespace Space;
        if (From::id == Space::SpaceIDs::View) {
            TestVector t;
            t.m_values[0] = 15;
            t.m_values[1] = 16;
            t.m_values[2] = 17;
            return t;
        }
        else {
            TestVector t;
            t.m_values[0] = 0;
            t.m_values[1] = 0;
            t.m_values[2] = 0;
            return t;
        }
    }
};
