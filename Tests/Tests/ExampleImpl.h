#pragma once

namespace Space {

    //------------------------------------------------------------------------------------

    class ExampleImpl
    {
    public:
        constexpr explicit ExampleImpl(std::array<double, 3>) noexcept;
        constexpr explicit ExampleImpl(double, double, double) noexcept;
        constexpr explicit ExampleImpl(double, double) noexcept;
        constexpr ExampleImpl(std::initializer_list<double>);

    protected:
        constexpr ExampleImpl() = default;
    public:

        void Normalize() noexcept(false);

        [[nodiscard]] double Mag() const noexcept;
        [[nodiscard]] constexpr double operator[](unsigned int) const;

        [[nodiscard]] constexpr const double* cbegin() const noexcept;
        [[nodiscard]] constexpr const double* cend() const noexcept;
        [[nodiscard]] constexpr double* begin() noexcept;
        [[nodiscard]] constexpr double* end() noexcept;

        [[nodiscard]] constexpr double X() const noexcept;
        [[nodiscard]] constexpr double Y() const noexcept;
        [[nodiscard]] constexpr double Z() const noexcept;

        friend ExampleImpl operator*(ExampleImpl, const double&) noexcept;

        friend ExampleImpl operator-(ExampleImpl, const ExampleImpl&) noexcept;

        friend ExampleImpl operator+(ExampleImpl, const ExampleImpl&) noexcept;

        [[nodiscard]] double Dot(const ExampleImpl&) const noexcept;

        [[nodiscard]] ExampleImpl Cross(const ExampleImpl&) const noexcept;

        [[nodiscard]] bool operator ==(const ExampleImpl&) const noexcept;

    private:
        std::array<double, 3> m_values{};
    };

    //------------------------------------------------------------------------------------

    inline void ExampleImpl::Normalize() noexcept(false)
    {
        const auto mag = Mag();
        if (mag == 0)
        {
            throw std::invalid_argument("Zero-sized normal vectors are not allowed");
        }
        std::transform(
            m_values.cbegin(),
            m_values.cend(),
            m_values.begin(),
            [mag](auto v) { return v / mag; }
        );
    }

    inline double ExampleImpl::Mag() const noexcept
    {
        return std::sqrt(
            std::accumulate(
                m_values.cbegin(),
                m_values.cend(),
                0.0,
                [](const auto accumulation, const auto v) { return accumulation + v * v; }
            )
        );
    }

    inline ExampleImpl operator*(ExampleImpl lhs, const double& d) noexcept
    {
        std::transform(
            lhs.m_values.cbegin(),
            lhs.m_values.cend(),
            lhs.begin(),
            [d](auto v) { return v * d; }
        );
        return lhs;
    }

    inline ExampleImpl operator+(ExampleImpl lhs, const ExampleImpl& rhs) noexcept
    {
        std::transform(
            lhs.m_values.cbegin(),
            lhs.m_values.cend(),
            rhs.m_values.cbegin(),
            lhs.m_values.begin(),
            std::plus<>()
        );
        return lhs;
    }

    inline ExampleImpl operator-(ExampleImpl lhs, const ExampleImpl& rhs) noexcept
    {
        std::transform(
            lhs.m_values.cbegin(),
            lhs.m_values.cend(),
            rhs.m_values.cbegin(),
            lhs.m_values.begin(),
            std::minus<>()
        );
        return lhs;
    }

    inline double ExampleImpl::Dot(const ExampleImpl& other) const noexcept
    {
        return std::transform_reduce(
            m_values.cbegin(),
            m_values.cend(),
            other.m_values.cbegin(),
            0.0,
            [](auto accumulation, auto v) { return accumulation + v; },
            [](auto v1, auto v2) { return v1 * v2; }
        );
    }

    inline ExampleImpl ExampleImpl::Cross(const ExampleImpl& other) const noexcept
    {
        return ExampleImpl{
            m_values[1] * other.m_values[2] - m_values[2] * other.m_values[1],
            m_values[2] * other.m_values[0] - m_values[0] * other.m_values[2],
            m_values[0] * other.m_values[1] - m_values[1] * other.m_values[0]
        };
    }

    inline bool ExampleImpl::operator==(const ExampleImpl& other) const noexcept
    {
        return std::equal(m_values.cbegin(), m_values.cend(), other.m_values.cbegin());
    }

    constexpr ExampleImpl::ExampleImpl(const std::array<double, 3> value) noexcept: m_values{value}
    {
    }

    constexpr ExampleImpl::ExampleImpl(const double x, const double y, const double z) noexcept: m_values{x, y, z}
    {
    }

    constexpr ExampleImpl::ExampleImpl(const double x, const double y) noexcept: m_values{x, y, 0}
    {
    }

    constexpr ExampleImpl::ExampleImpl(const std::initializer_list<double> l)
    {
        if (l.size() < 2 || l.size() > 3)
        {
            throw std::invalid_argument("You can only initialise with two or three elements");
        }
        auto iter = l.begin();
        m_values[0] = *iter++;
        m_values[1] = *iter++;
        if (l.size() == 3)
        {
            m_values[2] = *iter;
        }
    }

    constexpr double ExampleImpl::operator[](const unsigned int i) const
    {
        return m_values[i];
    }

    constexpr const double* ExampleImpl::cbegin() const noexcept
    {
        return reinterpret_cast<const double*>(m_values._Unchecked_begin());
    }

    constexpr const double* ExampleImpl::cend() const noexcept
    {
        return reinterpret_cast<const double*>(m_values._Unchecked_end());
    }

    constexpr double* ExampleImpl::begin() noexcept
    {
        return reinterpret_cast<double*>(m_values._Unchecked_begin());
    }

    constexpr double* ExampleImpl::end() noexcept
    {
        return reinterpret_cast<double*>(m_values._Unchecked_end());
    }

    constexpr double ExampleImpl::X() const noexcept
    {
        return m_values[0];
    }

    constexpr double ExampleImpl::Y() const noexcept
    {
        return m_values[1];
    }

    constexpr double ExampleImpl::Z() const noexcept
    {
        return m_values[2];
    }
}
