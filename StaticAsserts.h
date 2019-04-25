#pragma once
/**************************************************************************************************

Copyright (C) 2018 Canon Medical Systems Corporation. All rights reserved.

**************************************************************************************************/

namespace Space::StaticAssert {

    struct invalid_equality final
    {
        template<typename T = void>
        invalid_equality() {
            static_assert(false, "It is not valid to compare items from different spaces");
        }
    };

    struct invalid_point_vector_equality final
    {
        template<typename T = void>
        invalid_point_vector_equality() {
            static_assert(false, "It is not valid to compare points and vectors");
        }
    };

    struct invalid_subtraction final
    {
        template<typename T = void>
        invalid_subtraction() {
            static_assert(false, "It is not valid to subtract items from different spaces");
        }
    };

    struct invalid_point_to_vector_addition final
    {
        template<typename T = void>
        invalid_point_to_vector_addition() {
            static_assert(false, "You can't add points to vectors");
        }
    };

    struct invalid_vector_to_point_addition final
    {
        template<typename T = void>
        invalid_vector_to_point_addition() {
            static_assert(false, "You can't add vectors to points in other spaces");
        }
    };

    struct invalid_vector_to_vector_addition final
    {
        template<typename T = void>
        invalid_vector_to_vector_addition() {
            static_assert(false, "You can't add vectors from different spaces");
        }
    };

    struct invalid_normalized_vector_addition final
    {
        template<typename T = void>
        invalid_normalized_vector_addition() {
            static_assert(false, "You can't add to a normalized vector");
        }
    };

    struct invalid_vector_dot final
    {
        template<typename T = void>
        invalid_vector_dot() {
            static_assert(false, "You can't dot vectors from different spaces");
        }
    };

    struct invalid_vector_cross final
    {
        template<typename T = void>
        invalid_vector_cross() {
            static_assert(false, "You can't cross vectors from different spaces");
        }
    };

    struct invalid_normalized_vector_scale final
    {
        template<typename T = void>
        invalid_normalized_vector_scale() {
            static_assert(false, "You can't scale a normalized vector");
        }
    };

    struct invalid_random_access final
    {
        template<typename T = void>
        invalid_random_access() {
            static_assert(false, "Negative indices are invalid");
        }
    };

    struct invalid_at_access final
    {
        template<typename T = void>
        invalid_at_access() {
            static_assert(false, "Index out of range");
        }
    };

    struct normalized_vectors_do_not_support_non_const_iteration final
    {
        template<typename T = void>
        normalized_vectors_do_not_support_non_const_iteration() {
            static_assert(false, "Normalized vectors do not support non const iteration");
        }
    };
}
