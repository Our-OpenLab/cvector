#include <gtest/gtest.h>
#include "cvector.h"

// Test vector initialization
TEST(CVectorTest, Initialization) {
    int *v = VECTOR(int, 10);
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(vector_size(v), 0);
    EXPECT_EQ(vector_capacity(v), 10);
    vector_destroy(v);
}

// Test vector initialization failure cases
TEST(CVectorTest, InitializationFailureCases) {
    void *v = vector_init(0, 10);
    EXPECT_EQ(v, nullptr);
    v = vector_init(sizeof(int), 0);
    EXPECT_EQ(v, nullptr);
    v = vector_init(0, 0);
    EXPECT_EQ(v, nullptr);
}

// Test push_back macro
TEST(CVectorTest, PushBack) {
    int *v = VECTOR(int, 5);
    ASSERT_EQ(vector_push_back(v, ((int[]){1, 2, 3}), 3), VECTOR_SUCCESS);
    ASSERT_EQ(vector_size(v), 3);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
    vector_destroy(v);
}

// Test push_back macro with a null vector
TEST(CVectorTest, PushBackNullVector) {
    int *v = nullptr;
    ASSERT_EQ(vector_push_back(v, ((int[]){1, 2, 3}), 3), VECTOR_SUCCESS);
    ASSERT_NE(v, nullptr);
    ASSERT_EQ(vector_size(v), 3);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
    vector_destroy(v);
}

// Test push_back macro failure cases
TEST(CVectorTest, PushBackFailureCases) {
    int *v = VECTOR(int, 5);
    ASSERT_NE(v, nullptr);
    ASSERT_EQ(vector_push_back(v, nullptr, 3), VECTOR_FAILURE);
    ASSERT_EQ(vector_push_back(v, ((int[]){1, 2, 3}), 0), VECTOR_FAILURE);
    void *generic_vector = nullptr;
    ASSERT_EQ(vector_push_back_impl(&generic_vector, ((int[]){1, 2, 3}), 3, 0), VECTOR_FAILURE);
    vector_destroy(v);
}

TEST(CVectorTest, PushBackInvalidPointer) {
    int *v = VECTOR(int, 5);
    ASSERT_NE(v, nullptr);
    int *invalid_val = (int *)1;
    ASSERT_EQ(vector_push_back_impl((void **)&v, invalid_val, 1, sizeof(int)), VECTOR_FAILURE);
    EXPECT_EQ(vector_size(v), 0);
    EXPECT_EQ(vector_capacity(v), 5);
    vector_destroy(v);
}

// Test vector capacity doubling with push_back
TEST(CVectorTest, CapacityDoubling) {
    int *v = VECTOR(int, 2);
    ASSERT_NE(v, nullptr);
    for (int i = 0; i < 100; ++i) {
        ASSERT_EQ(vector_push_back(v, &i, 1), VECTOR_SUCCESS);
        EXPECT_EQ(v[i], i);
    }
    EXPECT_EQ(vector_size(v), 100);
    EXPECT_GE(vector_capacity(v), 100);
    EXPECT_LE(vector_capacity(v), 128);

    vector_destroy(v);
}

// Test pop_back macro
TEST(CVectorTest, PopBack) {
    int *v = VECTOR(int, 5);
    ASSERT_EQ(vector_push_back(v, ((int[]){1, 2, 3, 4, 5}), 5), VECTOR_SUCCESS);
    ASSERT_EQ(vector_size(v), 5);

    vector_pop_back(v, 2);
    EXPECT_EQ(vector_size(v), 3);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
    vector_destroy(v);
}

// Test pop_back macro failure cases
TEST(CVectorTest, PopBackFailureCases) {
    int *v = VECTOR(int, 5);
    ASSERT_NE(v, nullptr);
    int *null_vector = nullptr;
    vector_pop_back(null_vector, 2);
    ASSERT_EQ(vector_push_back(v, ((int[]){1, 2, 3}), 3), VECTOR_SUCCESS);
    ASSERT_EQ(vector_size(v), 3);
    vector_pop_back(v, 0);
    EXPECT_EQ(vector_size(v), 3);
    vector_pop_back(v, 10);
    EXPECT_EQ(vector_size(v), 0);
    vector_destroy(v);
}


// Test reserve macro
TEST(CVectorTest, Reserve) {
    int *v = VECTOR(int, 5);
    ASSERT_EQ(vector_reserve(v, 20), VECTOR_SUCCESS);
    EXPECT_EQ(vector_capacity(v), 20);
    EXPECT_EQ(vector_size(v), 0);
    vector_destroy(v);
}

// Test reserve macro failure and edge cases
TEST(CVectorTest, ReserveFailureAndEdgeCases) {
    // Case 1: Null vector pointer
    int *null_vector = nullptr;
    ASSERT_EQ(vector_reserve(null_vector, 10), VECTOR_SUCCESS);
    ASSERT_NE(null_vector, nullptr);
    EXPECT_EQ(vector_size(null_vector), 0);
    EXPECT_EQ(vector_capacity(null_vector), 10);
    vector_destroy(null_vector);

    // Case 2: Zero capacity requested
    int *v = VECTOR(int, 5);
    ASSERT_NE(v, nullptr);
    ASSERT_EQ(vector_reserve(v, 0), VECTOR_FAILURE);

    // Case 3: Zero item_size (direct function call to bypass macro validation)
    void *generic_vector = nullptr;
    ASSERT_EQ(vector_reserve_impl(&generic_vector, 10, 0), VECTOR_FAILURE);

    // Case 4: Null vector allocation
    int *new_vector = nullptr;
    ASSERT_EQ(vector_reserve(new_vector, 10), VECTOR_SUCCESS);
    ASSERT_NE(new_vector, nullptr);
    EXPECT_EQ(vector_capacity(new_vector), 10);
    EXPECT_EQ(vector_size(new_vector), 0);
    vector_destroy(new_vector);

    // Case 5: Capacity already sufficient
    ASSERT_EQ(vector_reserve(v, 5), VECTOR_SUCCESS);
    EXPECT_EQ(vector_capacity(v), 5);
    vector_destroy(v);
}


// Test resize macro
TEST(CVectorTest, Resize) {
    int *v = VECTOR(int, 5);
    ASSERT_EQ(vector_resize(v, 10), VECTOR_SUCCESS);
    EXPECT_EQ(vector_size(v), 10);
    EXPECT_EQ(vector_capacity(v), 10);

    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(v[i], 0);
    }

    ASSERT_EQ(vector_resize(v, 5), VECTOR_SUCCESS);
    EXPECT_EQ(vector_size(v), 5);
    vector_destroy(v);
}

// Test resize macro with edge cases
TEST(CVectorTest, ResizeEdgeCases) {
    // Case 1: Null vector pointer
    int *null_vector = nullptr;
    ASSERT_EQ(vector_resize(null_vector, 10), VECTOR_SUCCESS);
    ASSERT_NE(null_vector, nullptr);
    EXPECT_EQ(vector_size(null_vector), 10);
    EXPECT_EQ(vector_capacity(null_vector), 10);
    vector_destroy(null_vector);


    // Case 2: Zero item_size (direct function call to bypass macro validation)
    void *generic_vector = nullptr;
    ASSERT_EQ(vector_resize_impl(&generic_vector, 10, 0), VECTOR_FAILURE);

    // Case 3: Null vector allocation
    int *new_vector = nullptr;
    ASSERT_EQ(vector_resize(new_vector, 10), VECTOR_SUCCESS);
    ASSERT_NE(new_vector, nullptr);
    EXPECT_EQ(vector_size(new_vector), 10);
    EXPECT_EQ(vector_capacity(new_vector), 10);

    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(new_vector[i], 0);
    }
    vector_destroy(new_vector);

    // Case 4: Resize to same size
    int *v = VECTOR(int, 5);
    ASSERT_NE(v, nullptr);
    ASSERT_EQ(vector_resize(v, 5), VECTOR_SUCCESS);
    EXPECT_EQ(vector_size(v), 5);
    EXPECT_EQ(vector_capacity(v), 5);

    vector_destroy(v);
}

// Test the insert macro and handle edge cases
TEST(CVectorTest, InsertEdgeCases) {
    // Test case: Count is zero
    int *v = VECTOR(int, 5);
    ASSERT_EQ(vector_insert(v, 0, ((int[]){42}), 0), VECTOR_FAILURE);
    vector_destroy(v);

    // Test case: Invalid pointer (below 4096)
    v = VECTOR(int, 5);
    ASSERT_EQ(vector_insert(v, 0, (int *)1, 1), VECTOR_FAILURE);
    vector_destroy(v);

    // Test case: Index greater than current size
    v = VECTOR(int, 5);
    ASSERT_EQ(vector_push_back(v, ((int[]){1, 2, 3}), 3), VECTOR_SUCCESS);
    ASSERT_EQ(vector_insert(v, 10, ((int[]){42}), 1), VECTOR_SUCCESS);
    EXPECT_EQ(vector_size(v), 11);
    EXPECT_EQ(v[3], 0); // Uninitialized elements should be zeroed
    EXPECT_EQ(v[4], 0);
    EXPECT_EQ(v[10], 42);
    vector_destroy(v);

    // Test case: Normal insert at a valid index
    v = VECTOR(int, 5);
    ASSERT_EQ(vector_push_back(v, ((int[]){1, 2, 3}), 3), VECTOR_SUCCESS);
    ASSERT_EQ(vector_insert(v, 1, ((int[]){42}), 1), VECTOR_SUCCESS);
    EXPECT_EQ(vector_size(v), 4);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 42);
    EXPECT_EQ(v[2], 2);
    EXPECT_EQ(v[3], 3);
    vector_destroy(v);

    // Test case: Insert at the end
    v = VECTOR(int, 5);
    ASSERT_EQ(vector_push_back(v, ((int[]){1, 2, 3}), 3), VECTOR_SUCCESS);
    ASSERT_EQ(vector_insert(v, vector_size(v), ((int[]){42}), 1), VECTOR_SUCCESS);
    EXPECT_EQ(vector_size(v), 4);
    EXPECT_EQ(v[3], 42);
    vector_destroy(v);

    // Test case: Insert at the beginning
    v = VECTOR(int, 5);
    ASSERT_EQ(vector_push_back(v, ((int[]){1, 2, 3}), 3), VECTOR_SUCCESS);
    ASSERT_EQ(vector_insert(v, 0, ((int[]){42}), 1), VECTOR_SUCCESS);
    EXPECT_EQ(vector_size(v), 4);
    EXPECT_EQ(v[0], 42);
    EXPECT_EQ(v[1], 1);
    EXPECT_EQ(v[2], 2);
    EXPECT_EQ(v[3], 3);
    vector_destroy(v);
}


// Test the erase macro and handle edge cases
TEST(CVectorTest, Erase) {
    // Test case: Normal erase operation
    int *v = VECTOR(int, 5);
    ASSERT_EQ(vector_push_back(v, ((int[]){1, 2, 3, 4, 5}), 5), VECTOR_SUCCESS);

    vector_erase(v, 1, 2);
    EXPECT_EQ(vector_size(v), 3);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 4);
    EXPECT_EQ(v[2], 5);
    vector_destroy(v);

    // Test case: Erase on an empty vector
    v = VECTOR(int, 5);
    vector_erase(v, 0, 1);
    EXPECT_EQ(vector_size(v), 0);
    vector_destroy(v);

    // Test case: Erase with null vector
    int *null_vector = nullptr;
    vector_erase(null_vector, 0, 1);
    EXPECT_EQ(null_vector, nullptr);

    // Test case: Erase with index >= size
    v = VECTOR(int, 5);
    ASSERT_EQ(vector_push_back(v, ((int[]){1, 2, 3}), 3), VECTOR_SUCCESS);
    vector_erase(v, 5, 1);
    EXPECT_EQ(vector_size(v), 3);
    vector_destroy(v);

    // Test case: Erase with index + count > size
    v = VECTOR(int, 5);
    ASSERT_EQ(vector_push_back(v, ((int[]){1, 2, 3, 4, 5}), 5), VECTOR_SUCCESS);
    vector_erase(v, 3, 5);
    EXPECT_EQ(vector_size(v), 3);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
    vector_destroy(v);
}

// Test shrink_to_fit macro
TEST(CVectorTest, ShrinkToFit) {
    int *v = VECTOR(int, 10);
    ASSERT_EQ(vector_push_back(v, ((int[]){1, 2, 3, 4, 5}), 5), VECTOR_SUCCESS);

    ASSERT_EQ(vector_shrink_to_fit(v), VECTOR_SUCCESS); // Reduce capacity to size
    EXPECT_EQ(vector_capacity(v), 5);
    EXPECT_EQ(vector_size(v), 5);
    vector_destroy(v);
}

// Test shrink_to_fit macro with edge cases
TEST(CVectorTest, ShrinkToFitEdgeCases) {
    // Case 1: Null vector pointer
    int *null_vector = nullptr;
    ASSERT_EQ(vector_shrink_to_fit(null_vector), VECTOR_FAILURE);

    // Case 2: Empty vector
    int *empty_vector = VECTOR(int, 10);
    ASSERT_NE(empty_vector, nullptr);
    ASSERT_EQ(vector_shrink_to_fit(empty_vector), VECTOR_SUCCESS);
    EXPECT_EQ(vector_capacity(empty_vector), 0);
    EXPECT_EQ(vector_size(empty_vector), 0);
    vector_destroy(empty_vector);

    // Case 3: Capacity already equals size
    int *v = VECTOR(int, 5);
    ASSERT_NE(v, nullptr);
    ASSERT_EQ(vector_push_back(v, ((int[]){1, 2, 3, 4, 5}), 5), VECTOR_SUCCESS);
    ASSERT_EQ(vector_shrink_to_fit(v), VECTOR_SUCCESS);
    EXPECT_EQ(vector_capacity(v), 5);
    EXPECT_EQ(vector_size(v), 5);
    vector_destroy(v);

    // Case 4: Normal shrink operation
    int *v2 = VECTOR(int, 10);
    ASSERT_EQ(vector_push_back(v2, ((int[]){1, 2, 3, 4, 5}), 5), VECTOR_SUCCESS);
    ASSERT_EQ(vector_shrink_to_fit(v2), VECTOR_SUCCESS);
    EXPECT_EQ(vector_capacity(v2), 5);
    EXPECT_EQ(vector_size(v2), 5);
    vector_destroy(v2);
}


// Test clear macro
TEST(CVectorTest, Clear) {
    int *v = VECTOR(int, 5);
    ASSERT_EQ(vector_push_back(v, ((int[]){1, 2, 3}), 3), VECTOR_SUCCESS);

    vector_clear(v); // Clear the vector
    EXPECT_EQ(vector_size(v), 0);
    EXPECT_EQ(vector_capacity(v), 5); // Capacity should remain unchanged
    vector_destroy(v);
}
