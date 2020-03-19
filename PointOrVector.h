#pragma once

namespace Space::detail {

    class PointOrVector
    {
    public:
        explicit PointOrVector(double, double, double) noexcept;
        PointOrVector(const std::initializer_list<double> l);

        void Normalize() noexcept(false);

        [[nodiscard]] double operator[](unsigned int) const;

        [[nodiscard]] const double* cbegin() const noexcept;
        [[nodiscard]] const double* cend() const noexcept;
        [[nodiscard]] double* begin() noexcept;
        [[nodiscard]] double* end() noexcept;

        [[nodiscard]] double X() const noexcept;
        [[nodiscard]] double Y() const noexcept;
        [[nodiscard]] double Z() const noexcept;

        [[nodiscard]] friend PointOrVector operator*(PointOrVector, const double&) noexcept;
        [[nodiscard]] friend PointOrVector operator-(PointOrVector, const PointOrVector&) noexcept;
        [[nodiscard]] friend PointOrVector operator+(PointOrVector, const PointOrVector&) noexcept;
        [[nodiscard]] bool operator==(const PointOrVector&) const noexcept;

        [[nodiscard]] double Mag() const noexcept;
        [[nodiscard]] double Dot(const PointOrVector&) const noexcept;
        [[nodiscard]] PointOrVector Cross(const PointOrVector&) const noexcept;

    private:
        std::array<double, 3> m_values{};
    };


    inline PointOrVector::PointOrVector(const double x, const double y, const double z) noexcept : m_values{ x, y, z }
    {
    }

    inline PointOrVector::PointOrVector(const std::initializer_list<double> l)
    {
        auto iter = l.begin();
        m_values[0] = *iter++;
        m_values[1] = *iter++;
        if (l.size() == 3)
        {
            m_values[2] = *iter;
        }
        else
        {
            m_values[2] = 0;
        }
    }


    inline void PointOrVector::Normalize() noexcept(false)
    {
        const auto mag = Mag();
        if (std::abs(mag) < 1e-6) {
            throw std::invalid_argument("Zero-sized normal vectors are not allowed");
        }

        std::transform(
            m_values.cbegin(),
            m_values.cend(),
            m_values.begin(),
            [mag](auto v) { return v / mag; }
        );
    }

    inline double PointOrVector::Mag() const noexcept
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

    inline PointOrVector operator*(PointOrVector lhs, const double& d) noexcept
    {
        std::transform(
            lhs.m_values.cbegin(),
            lhs.m_values.cend(),
            lhs.begin(),
            [d](auto v) { return v * d; }
        );
        return lhs;
    }

    inline PointOrVector operator+(PointOrVector lhs, const PointOrVector& rhs) noexcept
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

    inline PointOrVector operator-(PointOrVector lhs, const PointOrVector& rhs) noexcept
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

    inline double PointOrVector::Dot(const PointOrVector& other) const noexcept
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

    inline PointOrVector PointOrVector::Cross(const PointOrVector& other) const noexcept
    {
        return PointOrVector{
            m_values[1] * other.m_values[2] - m_values[2] * other.m_values[1],
            m_values[2] * other.m_values[0] - m_values[0] * other.m_values[2],
            m_values[0] * other.m_values[1] - m_values[1] * other.m_values[0]
        };
    }

    inline bool PointOrVector::operator==(const PointOrVector& other) const noexcept
    {
        return std::equal(m_values.cbegin(), m_values.cend(), other.m_values.cbegin());
    }

    inline double PointOrVector::operator[](const unsigned int i) const
    {
        if (i > 2) {
            throw std::invalid_argument("Index is out of range");
        }
        return m_values[i];
    }

    inline const double* PointOrVector::cbegin() const noexcept
    {
        return reinterpret_cast<const double*>(m_values._Unchecked_begin());
    }

    inline const double* PointOrVector::cend() const noexcept
    {
        return reinterpret_cast<const double*>(m_values._Unchecked_end());
    }

    inline double* PointOrVector::begin() noexcept
    {
        return reinterpret_cast<double*>(m_values._Unchecked_begin());
    }

    inline double* PointOrVector::end() noexcept
    {
        return reinterpret_cast<double*>(m_values._Unchecked_end());
    }

    inline double PointOrVector::X() const noexcept
    {
        return m_values[0];
    }

    inline double PointOrVector::Y() const noexcept
    {
        return m_values[1];
    }

    inline double PointOrVector::Z() const noexcept
    {
        return m_values[2];
    }
}