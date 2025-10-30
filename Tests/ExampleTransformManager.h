#pragma once
#include "CatchIncludes.h"
#include "SpaceHelpers.h"

class TransformManager final {
  public:

    void SetDataPointValues(double x, double y, double z) noexcept {
        dataPointValues[0] = x;
        dataPointValues[1] = y;
        dataPointValues[2] = z;
    }
    
    template <typename From, typename To> [[nodiscard]] TestVector TransformPoint(TestVector) const noexcept {
        using namespace Space;
        if (From::id == SpaceIDs::View) {
            TestVector t;
            t.m_values[0] = dataPointValues[0];
            t.m_values[1] = dataPointValues[1];
            t.m_values[2] = dataPointValues[2];
            return t;
        } else {
            TestVector t;
            t.m_values[0] = 0;
            t.m_values[1] = 0;
            t.m_values[2] = 0;
            return t;
        }
    }

    void SetDataVectorValues(double x, double y, double z) noexcept {
        dataVectorValues[0] = x;
        dataVectorValues[1] = y;
        dataVectorValues[2] = z;
    }

    template <typename From, typename To> [[nodiscard]] TestVector TransformVector(TestVector) const noexcept {
        using namespace Space;
        if (To::id == SpaceIDs::Data) {
            TestVector t;
            t.m_values[0] = dataVectorValues[0];
            t.m_values[1] = dataVectorValues[1];
            t.m_values[2] = dataVectorValues[2];
            return t;
        } else {
            TestVector t;
            t.m_values[0] = 0;
            t.m_values[1] = 0;
            t.m_values[2] = 0;
            return t;
        }
    }
private:
    std::array<double, 3> dataPointValues{0, 0, 0};
    std::array<double, 3> dataVectorValues{0, 0, 0};
};
