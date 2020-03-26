#pragma once

namespace Space::StaticAssert {

    struct invalid_base
    {
        template<typename Anything = void>
        operator Anything() const noexcept {
            return Anything{};
        }
    };

    struct invalid_space final : invalid_base
    {
        template<typename T = void>
        invalid_space() {
            static_assert(false, "You can't do anything with vectors or points from different spaces.");
        }
    };

    struct invalid_conversion final : invalid_base
    {
        template<typename T = void>
        invalid_conversion() {
            static_assert(false, "You can't convert to the same same space.");
        }
    };

    struct invalid_point_vector_equality final : invalid_base
    {
        template<typename T = void>
        invalid_point_vector_equality() {
            static_assert(false, "It is not valid to compare points and vectors.");
        }
    };

    struct invalid_point_to_point_addition final : invalid_base
    {
        template<typename T = void>
        invalid_point_to_point_addition() {
            static_assert(false, "It is not valid to add points together.");
        }
    };

    struct invalid_point_to_vector_addition final : invalid_base
    {
        template<typename T = void>
        invalid_point_to_vector_addition() {
            static_assert(false, "You can't add points to vectors.");
        }
    };

    struct invalid_point_from_vector_subtraction final : invalid_base
    {
        template<typename T = void>
        invalid_point_from_vector_subtraction() {
            static_assert(false, "You can't subtract points from vectors.");
        }
    };

    struct invalid_vector3_to_xy_point_addition final : invalid_base
    {
        template<typename T = void>
        invalid_vector3_to_xy_point_addition() {
            static_assert(false, "You can't add a 3D vector to a 2D points in-place.");
        }
    };

    struct invalid_vector3_from_xy_point_subtraction final : invalid_base
    {
        template<typename T = void>
        invalid_vector3_from_xy_point_subtraction() {
            static_assert(false, "You can't subtract a 3D vector from a 2D points in-place.");
        }
    };

    struct invalid_vector_to_vector_addition final : invalid_base
    {
        template<typename T = void>
        invalid_vector_to_vector_addition() {
            static_assert(false, "You can't add vectors to 2D vectors in place.");
        }
    };

    struct invalid_normalized_vector_addition final : invalid_base
    {
        template<typename T = void>
        invalid_normalized_vector_addition() {
            static_assert(false, "You can't add to a normalized vector.");
        }
    };

    struct invalid_normalized_vector_subtraction final : invalid_base
    {
        template<typename T = void>
        invalid_normalized_vector_subtraction() {
            static_assert(false, "You can't subtract from a normalized vector.");
        }
    };

    struct invalid_XYVector_in_place_cross final : invalid_base
    {
        template<typename T = void>
        invalid_XYVector_in_place_cross() {
            static_assert(false, "You can't cross a XYVector in place.");
        }
    };

    struct invalid_normalized_vector_in_place_cross final : invalid_base
    {
        template<typename T = void>
        invalid_normalized_vector_in_place_cross() {
            static_assert(false, "You can't cross a normalized vector in place with a non-normalized vector.");
        }
    };

    struct invalid_normalized_vector_scale final : invalid_base
    {
        template<typename T = void>
        invalid_normalized_vector_scale() {
            static_assert(false, "You can't scale a normalized vector.");
        }
    };

    struct invalid_random_access final : invalid_base
    {
        template<typename T = void>
        invalid_random_access() {
            static_assert(false, "Negative indices are invalid.");
        }
    };

    struct invalid_at_access final : invalid_base
    {
        template<typename T = void>
        invalid_at_access() {
            static_assert(false, "Index out of range.");
        }
    };

    struct normalized_vectors_do_not_support_norm final : invalid_base
    {
        template<typename T = void>
        normalized_vectors_do_not_support_norm() {
            static_assert(false, "Normalized vectors cannot be normalised.");
        }
    };

    struct normalized_vectors_do_not_support_element_modification final : invalid_base
    {
        template<typename T = void>
        normalized_vectors_do_not_support_element_modification() {
            static_assert(false, "Normalized vectors cannot have their elements modified independently.");
        }
    };

    struct z_not_supported final : invalid_base
    {
        template<typename T = void>
        z_not_supported() {
            static_assert(false, "2D vectors and points do not support z-access.");
        }
    };

    struct xy_do_not_support_removing_z final : invalid_base
    {
        template<typename T = void>
        xy_do_not_support_removing_z() {
            static_assert(false, "xy vectors or points cannot have their Z removed.");
        }
    };

}
