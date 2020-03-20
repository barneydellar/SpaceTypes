#pragma once

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class Base
    {
        friend class PointBase<ThisSpace, Implementation>;
        friend class NormalizedVectorBase<ThisSpace, Implementation>;
        friend class NormalizedVector2Base<ThisSpace, Implementation>;
        friend class VectorBase<ThisSpace, Implementation>;
        friend class Vector2Base<ThisSpace, Implementation>;
    public:
        Base() noexcept : m_impl(0, 0, 0) {}
        explicit Base(const Implementation& v) noexcept : m_impl(v.X(), v.Y(), v.Z()) {}
        explicit Base(const double x, const double y, const double z) noexcept : m_impl(x, y, z) {}
        Base(const std::initializer_list<double> l) : m_impl(l)
        {
            if (l.size() != 3)
            {
                throw std::invalid_argument("You can only initialise with three elements");
            }
        }

        [[nodiscard]] explicit operator Implementation() const noexcept {
            return m_impl;
        }

        [[nodiscard]] double X() const noexcept { return m_impl.X(); }
        [[nodiscard]] double Y() const noexcept { return m_impl.Y(); }
        [[nodiscard]] double Z() const noexcept { return m_impl.Z(); }

        [[nodiscard]] double operator[] (const unsigned int i) const {
            if (i > 2) {
                throw std::invalid_argument("Index is out of range");
            }
            return m_impl[i];
        }

        template <int I>
        [[nodiscard]] typename std::enable_if<I == 0 || I == 1 || I == 2, double>::type at() const {
            return m_impl[I];
        }

        [[nodiscard]] double* begin() noexcept {
            return m_impl.begin();
        }
        [[nodiscard]] double* end() noexcept {
            return m_impl.end();
        }

        [[nodiscard]] const double* cbegin() const noexcept {
            return m_impl.cbegin();
        }
        [[nodiscard]] const double* cend() const noexcept {
            return m_impl.cend();
        }

        //------------------------------------------------------------------------------------

#ifndef IGNORE_SPACE_STATIC_ASSERT
        template <int I>
        typename std::enable_if<I != 0 && I != 1 && I != 2, StaticAssert::invalid_at_access>::type at() const {
            return StaticAssert::invalid_at_access{};
        }
#endif

    protected:
        Implementation m_impl;
    };
}
