// Copyright 2021 Bessolitsyn Sergay


#include <gtest/gtest.h>
#include <omp.h>

#include <vector>
#include <numeric>
#include <algorithm>

#include "../../task_4/bessolitsyn_s_quick_sort/quick_sort.h"

TEST(Quick_Sort_STD, Test_INT_one_element_sort_no_throw) {
    const int size = 1;
    std::vector<int> vec1, vec2;
    vec1 = vec2 = getRandomVector(size, 0);
    ASSERT_NO_THROW(quick_sort_STD(&vec2));
    ASSERT_EQ(vec1, vec2);
}

TEST(Quick_Sort_STD, Test_merge_is_working_if_sizes_are_even) {
    const int size = 1000;
    std::vector<int> vec1, vec2;
    vec1 = vec2 = getRandomVector(size, size);
    std::sort(vec1.begin(), vec1.begin() + size / 2);
    std::sort(vec1.begin() + size / 2, vec1.end());
    std::sort(vec2.begin(), vec2.end());
    ASSERT_NO_THROW(merge(vec1.data(), size / 2, vec1.data() + size / 2, size - size / 2));
    ASSERT_EQ(vec1, vec2);
}

TEST(Quick_Sort_STD, Test_merge_is_working_if_sizes_are_odd) {
    const int size = 1001;
    std::vector<int> vec1, vec2;
    vec1 = vec2 = getRandomVector(size, size);
    std::sort(vec1.begin(), vec1.begin() + size / 2);
    std::sort(vec1.begin() + size / 2, vec1.end());
    std::sort(vec2.begin(), vec2.end());
    ASSERT_NO_THROW(merge(vec1.data(), size / 2, vec1.data() + size / 2, size - size / 2));
    ASSERT_EQ(vec1, vec2);
}

TEST(Quick_Sort_STD, Test_merge_is_working_with_big_sizes_difference) {
    const int size = 1001, size2 = 50;
    std::vector<int> vec1, vec2;
    vec1 = vec2 = getRandomVector(size, size);
    std::sort(vec1.begin(), vec1.begin() + size2);
    std::sort(vec1.begin() + size2, vec1.end());
    std::sort(vec2.begin(), vec2.end());
    ASSERT_NO_THROW(merge(vec1.data(), size2, vec1.data() + size2, size - size2));
    ASSERT_EQ(vec1, vec2);
}

TEST(Quick_Sort_STD, Test_INT_25_elements_sort) {
    const int size = 25;
    std::vector<int> vec1, vec2;
    vec1 = vec2 = getRandomVector(size);
    std::sort(vec1.begin(), vec1.end());
    ASSERT_NO_THROW(quick_sort_STD(&vec2));
    ASSERT_EQ(vec1, vec2);
}

TEST(Quick_Sort_STD, Test_INT_1000_elements_sort) {
    const int size = 1000;
    std::vector<int> vec1, vec2;
    vec1 = vec2 = getRandomVector(size);
    std::sort(vec1.begin(), vec1.end());
    ASSERT_NO_THROW(quick_sort_STD(&vec2));
    ASSERT_EQ(vec1, vec2);
}

TEST(Quick_Sort_STD, Test_INT_1007_elements_sort) {
    const int size = 1007;
    std::vector<int> vec1, vec2;
    vec1 = vec2 = getRandomVector(size);
    std::sort(vec1.begin(), vec1.end());
    ASSERT_NO_THROW(quick_sort_STD(&vec2));
    ASSERT_EQ(vec1, vec2);
}

TEST(Quick_Sort_STD, Test_DOUBLE_one_element_sort_no_throw) {
    const int size = 1;
    std::vector<double> vec1, vec2;
    vec1 = vec2 = getRandomDoubleVector(size, 0);
    ASSERT_NO_THROW(quick_sort_STD(&vec2));
    ASSERT_EQ(vec1, vec2);
}

TEST(Quick_Sort_STD, Test_DOUBLE_1000_elements_sort) {
    const int size = 1000;
    std::vector<double> vec1, vec2;
    vec1 = vec2 = getRandomDoubleVector(size);
    std::sort(vec1.begin(), vec1.end());
    ASSERT_NO_THROW(quick_sort_STD(&vec2));
    ASSERT_EQ(vec1, vec2);
}

TEST(Quick_Sort_STD, Test_DOUBLE_1007_elements_sort) {
    const int size = 1007;
    std::vector<double> vec1, vec2;
    vec1 = vec2 = getRandomDoubleVector(size);
    std::sort(vec1.begin(), vec1.end());
    ASSERT_NO_THROW(quick_sort_STD(&vec2));
    ASSERT_EQ(vec1, vec2);
}

TEST(Quick_Sort_STD, Test_DOUBLE_6000_elements_sort) {
    const int size = 6000;
    std::vector<double> vec1, vec2;
    vec1 = vec2 = getRandomDoubleVector(size);
    std::sort(vec1.begin(), vec1.end());
    ASSERT_NO_THROW(quick_sort_STD(&vec2));
    ASSERT_EQ(vec1, vec2);
}

/*TEST(Quick_Sort_STD, Test_DOUBLE_1007007_elements_sort) {
    const int size = 1007007;
    std::vector<double> vec1, vec2;
    vec1 = vec2 = getRandomDoubleVector(size);
    //std::sort(vec1.begin(), vec1.end());
    ASSERT_NO_THROW(quick_sort_STD(&vec2, size));
    //ASSERT_EQ(vec1, vec2);
}*/

// TEST(Quick_Sort_STD, Test_DOUBLE_15321007_elements_sort) {
//    const int size = 15321007;
//    std::vector<double> vec1, vec2;
//    vec1 = vec2 = getRandomDoubleVector(size, size);
//    //std::sort(vec1.begin(), vec1.end());
//    auto t1 = omp_get_wtime();  // IDK About this. CHANGE TO STD::CHRONO
//    ASSERT_NO_THROW(quick_sort_STD(&vec2));
//    auto t2 = omp_get_wtime();
//    std::cout <<"STD: " << (t2 - t1) << std::endl;
//    auto t3 = omp_get_wtime();
//    ASSERT_NO_THROW(quick_sort(vec1.data(), size));
//    auto t4 = omp_get_wtime();
//    std::cout <<"SEQ: " <<(t4 - t3) << std::endl;
//    std::cout<< "Acceleration (SEQ/STD): " << (t4 - t3)/ (t2 - t1)<< std::endl;
//    ASSERT_EQ(vec1, vec2);
//}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
