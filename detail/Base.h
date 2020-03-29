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

        void Scale(const double& d)
        {
            std::transform(
                cbegin(),
                cend(),
                begin(),
                [d](auto v) { return v * d; }
            );
        }

        [[nodiscard]] double Dot(const Base<ThisSpace, Implementation>& other) const noexcept {

            return std::transform_reduce(
                cbegin(),
                cend(),
                other.cbegin(),
                0.0,
                [](auto accumulation, auto v) { return accumulation + v; },
                [](auto v1, auto v2) { return v1 * v2; }
            );
        }

        static std::tuple<double, double, double> Cross_internal(const Base<ThisSpace, Implementation>& A, const Base<ThisSpace, Implementation>& B) noexcept {

            const double x = A.Y_internal() * B.Z_internal() - A.Z_internal() * B.Y_internal();
            const double y = A.Z_internal() * B.X_internal() - A.X_internal() * B.Z_internal();
            const double z = A.X_internal() * B.Y_internal() - A.Y_internal() * B.X_internal();
            return { x, y, z };
        }


        [[nodiscard]] double Mag_internal() const noexcept {

            return std::sqrt(
                std::accumulate(
                    cbegin(),
                    cend(),
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

        [[nodiscard]] double X_internal() const noexcept { return *(cbegin() + 0); }
        [[nodiscard]] double Y_internal() const noexcept { return *(cbegin() + 1); }
        [[nodiscard]] double Z_internal() const noexcept { return *(cbegin() + 2); }

        Implementation m_impl;
    };
}
