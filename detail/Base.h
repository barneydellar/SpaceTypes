#pragma once

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class Base
    {
    public:
        Base() noexcept
        {
            std::fill(begin(), end(), 0);
        }
        explicit Base(const Implementation& v) noexcept : m_impl(v) {}
        explicit Base(const double x, const double y, const double z) noexcept
        {
            auto iter = begin();
            *iter++ = x;
            *iter++ = y;
            *iter = z;
        }
        Base(const std::initializer_list<double>& l)
        {
            if (l.size() != 3)
            {
                throw std::invalid_argument("You can only initialise with three elements");
            }
            std::copy(
                std::cbegin(l),
                std::cend(l),
                begin()
            );
        }

        [[nodiscard]] explicit operator Implementation() const noexcept {
            return m_impl;
        }

        [[nodiscard]] double X() const noexcept { return *(cbegin() + 0); }
        [[nodiscard]] double Y() const noexcept { return *(cbegin() + 1); }


        [[nodiscard]] double operator[] (const unsigned int i) const {
            if (i > 2) {
                throw std::invalid_argument("Index is out of range");
            }
            return *(cbegin() + i);
        }

        template <int I>
        [[nodiscard]] typename std::enable_if<I == 0 || I == 1 || I == 2, double>::type at() const {
            return operator[](I);
        }

        [[nodiscard]] const double* cbegin() const noexcept {
            return reinterpret_cast<const double*>(&m_impl);
        }
        [[nodiscard]] const double* cend() const noexcept {
            return reinterpret_cast<const double*>(&m_impl) + 3;
        }

        //------------------------------------------------------------------------------------

#ifndef IGNORE_SPACE_STATIC_ASSERT
        template <int I>
        typename std::enable_if<I != 0 && I != 1 && I != 2, StaticAssert::invalid_at_access>::type at() const {
            return StaticAssert::invalid_at_access{};
        }
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

        void Add(const Base<ThisSpace, Implementation>& other)
        {
            std::transform(
                cbegin(),
                cend(),
                other.cbegin(),
                begin(),
                std::plus<>()
            );
        }

        void Sub(const Base<ThisSpace, Implementation>& other)
        {
            std::transform(
                cbegin(),
                cend(),
                other.cbegin(),
                begin(),
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

        [[nodiscard]] double Z() const noexcept { return *(cbegin() + 2); }

    private:
        Implementation m_impl;
    };
}
