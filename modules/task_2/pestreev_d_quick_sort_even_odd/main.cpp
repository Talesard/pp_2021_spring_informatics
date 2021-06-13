// Copyright 2021 Pestreev Daniil
#include <gtest/gtest.h>
#include <vector>
#include "./quick_sort_even_odd_merge.h"

TEST(Quick_Sort_Operations, Test_manual_vector) {
    std::vector<int> vec = {-8098, 1009, -160, -1, 179796, 2,
        -1603, 166, -7396, -19, -18348, -15, 7, 82519};
    std::vector<int> vec_V = parallel_sorting(vec, 2);
    std::vector<int> vec_stan = vec;
    std::sort(vec_stan.begin(), vec_stan.end());
    ASSERT_EQ(vec_V, vec_stan);
}

TEST(Quick_Sort_Operations, Test_random_vector_0_2) {
    std::vector<int> vec = getRandomVector(0);
    std::vector<int> vec_V = parallel_sorting(vec, 2);
    std::vector<int> vec_stan = vec;
    std::sort(vec_stan.begin(), vec_stan.end());
    ASSERT_EQ(vec_V, vec_stan);
}

TEST(Quick_Sort_Operations, Test_random_vector_0_4) {
    std::vector<int> vec = getRandomVector(0);
    std::vector<int> vec_V = parallel_sorting(vec, 4);
    std::vector<int> vec_stan = vec;
    std::sort(vec_stan.begin(), vec_stan.end());
    ASSERT_EQ(vec_V, vec_stan);
}

TEST(Quick_Sort_Operations, Test_random_vector_1_2) {
    std::vector<int> vec = getRandomVector(1);
    std::vector<int> vec_V = parallel_sorting(vec, 2);
    std::vector<int> vec_stan = vec;
    std::sort(vec_stan.begin(), vec_stan.end());
    ASSERT_EQ(vec_V, vec_stan);
}

TEST(Quick_Sort_Operations, Test_random_vector_1_4) {
    std::vector<int> vec = getRandomVector(1);
    std::vector<int> vec_V = parallel_sorting(vec, 4);
    std::vector<int> vec_stan = vec;
    std::sort(vec_stan.begin(), vec_stan.end());
    ASSERT_EQ(vec_V, vec_stan);
}

TEST(Quick_Sort_Operations, Test_sorted_vector100_2) {
    std::vector<int> vec = getRandomVector(100);
    std::sort(vec.begin(), vec.end());
    std::vector<int> vec_V = parallel_sorting(vec, 2);
    std::vector<int> vec_stan = vec;
    std::sort(vec_stan.begin(), vec_stan.end());
    ASSERT_EQ(vec_V, vec_stan);
}

TEST(Quick_Sort_Operations, Test_inverted_sorted_vector100_2) {
    std::vector<int> vec = getRandomVector(100);
    std::sort(vec.begin(), vec.end(), [](int a, int b){
        return a > b;
    });
    std::vector<int> vec_V = parallel_sorting(vec, 2);
    std::vector<int> vec_stan = vec;
    std::sort(vec_stan.begin(), vec_stan.end());
    ASSERT_EQ(vec_V, vec_stan);
}

TEST(Quick_Sort_Operations, Test_random_vector_1283_2) {
    std::vector<int> vec = getRandomVector(1283);
    std::vector<int> vec_V = parallel_sorting(vec, 2);
    std::vector<int> vec_stan = vec;
    std::sort(vec_stan.begin(), vec_stan.end());
    ASSERT_EQ(vec_V, vec_stan);
}

TEST(Quick_Sort_Operations, Test_random_vector_10000_4) {
    std::vector<int> vec = getRandomVector(10000);
    std::vector<int> vec_V = parallel_sorting(vec, 4);
    std::vector<int> vec_stan = vec;
    std::sort(vec_stan.begin(), vec_stan.end());
    ASSERT_EQ(vec_V, vec_stan);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
