#pragma once

#include "StaticAsserts.h"

namespace Space {

    template <typename T>
    struct SpaceTypeNameMap final { static const std::string name; };

    template <typename T>
    const std::string SpaceTypeNameMap <T>::name = "NoSpaceNameDefined";
}

namespace Space::detail {

    template <typename Space>
    class BaseImpl
    {
    public:
        constexpr explicit BaseImpl(const std::array<double, 3> value) noexcept : m_values{value} {}
        constexpr explicit BaseImpl(const double x, const double y, const double z) noexcept : m_values{ x , y , z } {}
        constexpr explicit BaseImpl(const double x, const double y) noexcept : m_values{ x , y , 0 }{}

    protected:
        constexpr BaseImpl() = default;
    public:

        //------------------------------------------------------------------------------------

        [[nodiscard]] constexpr double operator[] (const unsigned int i) const {
            if (i > 2) {
                throw std::invalid_argument("Index is out of range");
            }
            return m_values[i];
        }
        constexpr double operator[] (int) const {
            StaticAssert::invalid_random_access{};
        }

        //------------------------------------------------------------------------------------

        [[nodiscard]] constexpr const double* cbegin() const noexcept {
            return reinterpret_cast<const double*>(m_values._Unchecked_begin());
        }
        [[nodiscard]] constexpr const double* cend() const noexcept {
            return reinterpret_cast<const double*>(m_values._Unchecked_end());
        }

        //------------------------------------------------------------------------------------

        template <int I>
        [[nodiscard]] constexpr typename std::enable_if<I == 0 || I == 1 || I == 2, double>::type at(
        ) const noexcept {
            return *reinterpret_cast<const double* const>(&m_values[I]);
        }
        template <int I>
        constexpr typename std::enable_if<I != 0 && I != 1 && I != 2, double>::type at(
        ) const noexcept {
            StaticAssert::invalid_at_access{};
        }

        //------------------------------------------------------------------------------------

        [[nodiscard]] constexpr double X() const noexcept { return m_values[0]; }
        [[nodiscard]] constexpr double Y() const noexcept { return m_values[1]; }
        [[nodiscard]] constexpr double Z() const noexcept { return m_values[2]; }

    protected:

        [[nodiscard]] constexpr std::array<double, 3> SumArrays(const std::array<double, 3>& lhs, const std::array<double, 3>& rhs) const noexcept
        {
            std::array<double, 3> result{};
            std::transform(
                lhs.cbegin(),
                lhs.cend(),
                rhs.cbegin(),
                result.begin(),
                [](auto v1, auto v2) {return v1 + v2;}
            );
            return result;
        }

        [[nodiscard]] constexpr std::array<double, 3> ScaleArray(const std::array<double, 3>& a, const double d) const noexcept
        {
            std::array<double, 3> result{};
            std::transform(a.cbegin(), a.cend(), result.begin(), [d](auto v) {return v * d;});
            return result;
        }

        [[nodiscard]] constexpr double DotArrays(const std::array<double, 3>& lhs, const std::array<double, 3>& rhs) const noexcept
        {
            return std::transform_reduce(
                lhs.cbegin(),
                lhs.cend(),
                rhs.cbegin(),
                0.0,
                [](auto accumulation, auto v) {return accumulation + v;},
                [](auto v1, auto v2) {return v1 * v2;}
            );
        }

        [[nodiscard]] constexpr std::array<double, 3> CrossArrays(const std::array<double, 3>& lhs, const std::array<double, 3>& rhs) const noexcept
        {
            return {
                lhs[1] * rhs[2] - lhs[2] * rhs[1],
                lhs[2] * rhs[0] - lhs[0] * rhs[2],
                lhs[0] * rhs[1] - lhs[1] * rhs[0]
            };
        }

        [[nodiscard]] constexpr double MagHelper() const noexcept {

            return std::sqrt(
                std::accumulate(
                    m_values.cbegin(),
                    m_values.cend(),
                    0.0,
                    [](const auto accumulation, const auto v) {return accumulation + v * v;}
                )
            );
        }

        //------------------------------------------------------------------------------------

        std::array<double, 3> m_values{};
    };

    //-----------------------------------------------------------------------------------------

    template <typename Space>
    class ModifiableBaseImpl : public BaseImpl<Space>
    {
        using _base = BaseImpl<Space>;
    public: 

        constexpr explicit ModifiableBaseImpl(const std::array<double, 3> value) noexcept : _base(value) {}
        constexpr explicit ModifiableBaseImpl(const double x, const double y, const double z) noexcept : _base(x, y, z) {}
        constexpr explicit ModifiableBaseImpl(const double x, const double y) noexcept : _base(x, y) {}

        [[nodiscard]] constexpr double* begin() noexcept {
            return reinterpret_cast<double*>(_base::m_values._Unchecked_begin());
        }
        [[nodiscard]] constexpr double* end() noexcept {
            return reinterpret_cast<double*>(_base::m_values._Unchecked_end());
        }
    };
}
