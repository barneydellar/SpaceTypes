#pragma once

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class Base
    {
    public:

        //------------------------------------------------------------------------------------

#ifndef IGNORE_SPACE_STATIC_ASSERT
        template <typename OtherSpace>
        std::enable_if_t<!std::is_same_v<OtherSpace, ThisSpace>, StaticAssert::invalid_space> operator== (const Base<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace>
        std::enable_if_t<!std::is_same_v<OtherSpace, ThisSpace>, StaticAssert::invalid_space> operator!= (const Base<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace>
        std::enable_if_t<!std::is_same_v<OtherSpace, ThisSpace>, StaticAssert::invalid_space> operator*(const Base<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace>
        std::enable_if_t<!std::is_same_v<OtherSpace, ThisSpace>, StaticAssert::invalid_space> Cross(const Base<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace>
        std::enable_if_t<!std::is_same_v<OtherSpace, ThisSpace>, StaticAssert::invalid_space> operator*=(const Base<OtherSpace, Implementation>&) noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace>
        std::enable_if_t<!std::is_same_v<OtherSpace, ThisSpace>, StaticAssert::invalid_space> operator+(const Base<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace>
        std::enable_if_t<!std::is_same_v<OtherSpace, ThisSpace>, StaticAssert::invalid_space> operator+=(const Base<OtherSpace, Implementation>&) noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace>
        std::enable_if_t<!std::is_same_v<OtherSpace, ThisSpace>, StaticAssert::invalid_space> operator-(const Base<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace>
        std::enable_if_t<!std::is_same_v<OtherSpace, ThisSpace>, StaticAssert::invalid_space> operator-=(const Base<OtherSpace, Implementation>&) noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace>
        std::enable_if_t<!std::is_same_v<OtherSpace, ThisSpace>, StaticAssert::invalid_space> Dot(const Base<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_space{};
        }

        template <typename OtherSpace, typename TransformManager>
        [[nodiscard]] std::enable_if_t<std::is_same_v<OtherSpace, ThisSpace>, StaticAssert::invalid_conversion> ConvertTo(const TransformManager& transform_manager) const noexcept {
            return StaticAssert::invalid_conversion{};
        }

#endif

    protected:

        static void Add(Base<ThisSpace, Implementation>& self, const Base<ThisSpace, Implementation>& other)
        {
            std::transform(
                self.cbegin(),
                self.cend(),
                other.cbegin(),
                self.begin(),
                std::plus<>()
            );
        }

        static void Sub(Base<ThisSpace, Implementation>& self, const Base<ThisSpace, Implementation>& other)
        {
            std::transform(
                self.cbegin(),
                self.cend(),
                other.cbegin(),
                self.begin(),
                std::minus<>()
            );
        }

        static void Scale(Base<ThisSpace, Implementation>& self, const double& d)
        {
            std::transform(
                self.cbegin(),
                self.cend(),
                self.begin(),
                [d](auto v) { return v * d; }
            );
        }

        static double Dot(const Base<ThisSpace, Implementation>& self, const Base<ThisSpace, Implementation>& other) noexcept
        {
            return std::transform_reduce(
                self.cbegin(),
                self.cend(),
                other.cbegin(),
                0.0,
                [](auto accumulation, auto v) { return accumulation + v; },
                [](auto v1, auto v2) { return v1 * v2; }
            );
        }

        static std::tuple<double, double, double> Cross_internal(const Base<ThisSpace, Implementation>& A, const Base<ThisSpace, Implementation>& B) noexcept {

            const double AX = *(A.cbegin() + 0);
            const double AY = *(A.cbegin() + 1);
            const double AZ = *(A.cbegin() + 2);

            const double BX = *(B.cbegin() + 0);
            const double BY = *(B.cbegin() + 1);
            const double BZ = *(B.cbegin() + 2);

            const double x = AY * BZ - AZ * BY;
            const double y = AZ * BX - AX * BZ;
            const double z = AX * BY - AY * BX;

            return { x, y, z };
        }

        static [[nodiscard]] double Mag_internal(const Base<ThisSpace, Implementation>& i) noexcept {

            return std::sqrt(
                std::accumulate(
                    i.cbegin(),
                    i.cend(),
                    0.0,
                    [](const auto accumulation, const auto v) { return accumulation + v * v; }
                )
            );
        }

        [[nodiscard]] static bool Equality(const double& x, const double& y)
        {
            return std::abs(x - y) < 1e-6;
        }

        [[nodiscard]] double* begin() noexcept {
            return reinterpret_cast<double*>(&m_impl);
        }
        [[nodiscard]] double* end() noexcept {
            return reinterpret_cast<double*>(&m_impl) + 3;
        }
        [[nodiscard]] const double* cbegin() const noexcept {
            return reinterpret_cast<const double*>(&m_impl);
        }
        [[nodiscard]] const double* cend() const noexcept {
            return reinterpret_cast<const double*>(&m_impl) + 3;
        }


        Implementation m_impl;
    };
}
