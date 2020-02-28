#pragma once

namespace Space {

    //------------------------------------------------------------------------------------

    class ExampleImpl
    {
    public:
        constexpr explicit ExampleImpl(const std::array<double, 3> value) noexcept : m_values{value} {}
        constexpr explicit ExampleImpl(const double x, const double y, const double z) noexcept : m_values{ x , y , z } {}
        constexpr explicit ExampleImpl(const double x, const double y) noexcept : m_values{ x , y , 0 } {}
        constexpr ExampleImpl(const std::initializer_list<double> l) {
            if (l.size() < 2 || l.size() > 3) {
                throw std::invalid_argument("You can only initialise with two or three elements");
            }
            auto iter = l.begin();
            m_values[0] = *iter++;
            m_values[1] = *iter++;
            if (l.size() == 3) {
                m_values[2] = *iter;
            }
        }

    protected:
        constexpr ExampleImpl() = default;
    public:

        void Normalize() noexcept(false)
        {
            const auto mag = Mag();
            if (mag == 0) {
                throw std::invalid_argument("Zero-sized normal vectors are not allowed");
            }
            std::transform(
                m_values.cbegin(),
                m_values.cend(),
                m_values.begin(),
                [mag](auto v) {return v / mag;}
            );
        }

        [[nodiscard]] double Mag() const noexcept {
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

        [[nodiscard]] constexpr double operator[] (const unsigned int i) const {

            if (i > 2) {
                throw std::invalid_argument("Index is out of range");
            }
            return m_values[i];
        }

        //------------------------------------------------------------------------------------

        [[nodiscard]] constexpr const double* cbegin() const noexcept {
            return reinterpret_cast<const double*>(m_values._Unchecked_begin());
        }
        [[nodiscard]] constexpr const double* cend() const noexcept {
            return reinterpret_cast<const double*>(m_values._Unchecked_end());
        }

        [[nodiscard]] constexpr double* begin() noexcept {
            return reinterpret_cast<double*>(m_values._Unchecked_begin());
        }
        [[nodiscard]] constexpr double* end() noexcept {
            return reinterpret_cast<double*>(m_values._Unchecked_end());
        }

        //------------------------------------------------------------------------------------

        [[nodiscard]] constexpr double X() const noexcept { return m_values[0]; }
        [[nodiscard]] constexpr double Y() const noexcept { return m_values[1]; }
        [[nodiscard]] constexpr double Z() const noexcept { return m_values[2]; }

        [[nodiscard]] std::array<double, 3> operator*(const double& d) const noexcept {
            std::array<double, 3> result{};
            std::transform(
                m_values.cbegin(),
                m_values.cend(),
                result.begin(),
                [d] (auto v) {return v * d;}
            );
            return result;
        }

        void operator*=(const double& d) noexcept {
            m_values = operator*(d);
        }

        [[nodiscard]] std::array<double, 3> operator-(
            const ExampleImpl& rhs
        ) const noexcept {
            std::array<double, 3> result{};
            std::transform(
                m_values.cbegin(),
                m_values.cend(),
                rhs.m_values.cbegin(),
                result.begin(),
                std::minus<>()
            );
            return result;
        }

        [[nodiscard]] std::array<double, 3> operator+(
            const ExampleImpl& rhs
        ) const noexcept {
            std::array<double, 3> result{};
            std::transform(
                m_values.cbegin(),
                m_values.cend(),
                rhs.m_values.cbegin(),
                result.begin(),
                std::plus<>()
            );
            return result;
        }

        void operator+=(
            const ExampleImpl& rhs
        ) noexcept {
            std::transform(
                m_values.cbegin(),
                m_values.cend(),
                rhs.m_values.cbegin(),
                m_values.begin(),
                std::plus<>()
            );
        }

        [[nodiscard]] double Dot(const ExampleImpl& other) const noexcept {
            return std::transform_reduce(
                m_values.cbegin(),
                m_values.cend(),
                other.m_values.cbegin(),
                0.0,
                [](auto accumulation, auto v) {return accumulation + v;},
                [](auto v1, auto v2) {return v1 * v2;}
            );
        }

        [[nodiscard]] std::array<double, 3> Cross(const ExampleImpl& other) const noexcept {
            return {
                m_values[1] * other.m_values[2] - m_values[2] * other.m_values[1],
                m_values[2] * other.m_values[0] - m_values[0] * other.m_values[2],
                m_values[0] * other.m_values[1] - m_values[1] * other.m_values[0]
            };
        }

        [[nodiscard]] bool operator == (const ExampleImpl& other) const noexcept {
            return std::equal(m_values.cbegin(), m_values.cend(), other.m_values.cbegin());
        }

        //------------------------------------------------------------------------------------

        std::array<double, 3> m_values{};
    };

}
