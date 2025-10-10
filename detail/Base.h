#pragma once

namespace Space::detail {
    
    template <typename SpaceA, typename SpaceB>
    concept SameSpaceAs = std::is_same_v<SpaceA, SpaceB>;

    template <typename ThisSpace, typename Implementation>
    class Base
    {
    public:

        template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
        StaticAssert::invalid_space operator*(const Base<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace>
        StaticAssert::invalid_space Cross(const Base<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
        StaticAssert::invalid_space operator*=(const Base<OtherSpace, Implementation>&) noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
        StaticAssert::invalid_space operator+(const Base<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
        StaticAssert::invalid_space operator+=(const Base<OtherSpace, Implementation>&) noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
        StaticAssert::invalid_space operator-(const Base<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace> requires DifferentSpaces<OtherSpace, ThisSpace>
        StaticAssert::invalid_space operator-=(const Base<OtherSpace, Implementation>&) noexcept {
            return StaticAssert::invalid_space{};
        }
        template <typename OtherSpace> 
        StaticAssert::invalid_space Dot(const Base<OtherSpace, Implementation>&) const noexcept {
            return StaticAssert::invalid_space{};
        }
        template <SameSpaceAs<ThisSpace> S, typename TransformManager>
        [[nodiscard]] StaticAssert::invalid_conversion ConvertTo(const TransformManager& transform_manager) const noexcept {
            return StaticAssert::invalid_conversion{};
        }
    };
}
