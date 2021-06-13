// Copyright 2021 Gapon Andrey

#include <gtest/gtest.h>
#include <vector>
// #include <chrono>
#include "./dijkstra.h"

/* TEST(dijkstra_algorithm, test_matrix_generation_TIMER) {
    std::vector<int> g(25000000);
    g = Create_Graph(5000);
    std::vector<int> res = { 5000, 1 };
    auto t1 = std::chrono::high_resolution_clock::now();
    dijkstra_algorithm(g, 1, 5000);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto posled = std::chrono::duration<double>(t2 - t1).count();
    std::cout << posled << std::endl;
    auto t3 = std::chrono::high_resolution_clock::now();
    dijkstra_parallel(g, 1, 5000);
    auto t4 = std::chrono::high_resolution_clock::now();
    auto parallel = std::chrono::duration<double>(t4 - t3).count();
    std::cout << parallel << std::endl;
    EXPECT_EQ(dijkstra_algorithm(g, 1, 5000), res);
} */

TEST(dijkstra_algorithm, six_point_nomer_2_1) {
    std::vector<int> res = { 5, 6, 3, 1 };

    std::vector<int> graf = { 0, 9, 11, 0, 0, 16,
                          9, 0, 12, 17, 0, 0,
                          11, 12, 0, 13, 0, 4,
                          0, 17, 13, 0, 8, 0,
                          0, 0, 0, 8, 0, 11,
                          16, 0, 4, 0, 11, 0 };

    EXPECT_EQ(dijkstra_algorithm(graf, 1, 5), res);
}

TEST(dijkstra_algorithm, test_matrix_generation) {
    std::vector<int> g(16);
    g = Create_Graph(4);
    std::vector<int> res = { 4, 1 };
    EXPECT_EQ(dijkstra_algorithm(g, 1, 4), res);
}

TEST(dijkstra_algorithm, test_three_points) {
    std::vector<int> res = { 3, 1 };

    std::vector<int> graf = { 0, 2, 3,
                          2, 0, 1,
                          3, 1, 0 };

    EXPECT_EQ(dijkstra_algorithm(graf, 1, 3), res);
}

TEST(dijkstra_algorithm, six_point_nomer_2_12) {
    std::vector<int> res = { 5, 6, 3, 1 };

    std::vector<int> graf = { 0, 9, 11, 0, 0, 16,
                          9, 0, 12, 17, 0, 0,
                          11, 12, 0, 13, 0, 4,
                          0, 17, 13, 0, 8, 0,
                          0, 0, 0, 8, 0, 11,
                          16, 0, 4, 0, 11, 0 };

    EXPECT_EQ(dijkstra_algorithm(graf, 1, 5), res);
}

TEST(dijkstra_algorithm, seven_points_nomer_2_12_4) {
    std::vector<int> res = { 5, 6, 3, 1 };

    std::vector<int> graf = { 0, 9, 11, 0, 0, 16,
                          9, 0, 12, 17, 0, 0,
                          11, 12, 0, 13, 0, 4,
                          0, 17, 13, 0, 8, 0,
                          0, 0, 0, 8, 0, 11,
                          16, 0, 4, 0, 11, 0 };

    EXPECT_EQ(dijkstra_algorithm(graf, 1, 5), res);
}

TEST(dijkstra_algorithm, seven_point_nomer_2_12_3) {
    std::vector<int> res = { 5, 6, 3, 1 };

    std::vector<int> graf = { 0, 9, 11, 0, 0, 16,
                          9, 0, 12, 17, 0, 0,
                          11, 12, 0, 13, 0, 4,
                          0, 17, 13, 0, 8, 0,
                          0, 0, 0, 8, 0, 11,
                          16, 0, 4, 0, 11, 0 };

    EXPECT_EQ(dijkstra_algorithm(graf, 1, 5), res);
}

TEST(dijkstra_algorithm, seven_parallel_point_nomer_2_12) {
    std::vector<int> res = { 5, 6, 3, 1 };

    std::vector<int> graf = { 0, 9, 11, 0, 0, 16,
                          9, 0, 12, 17, 0, 0,
                          11, 12, 0, 13, 0, 4,
                          0, 17, 13, 0, 8, 0,
                          0, 0, 0, 8, 0, 11,
                          16, 0, 4, 0, 11, 0 };

    EXPECT_EQ(dijkstra_algorithm(graf, 1, 5), res);
}

TEST(dijkstra_algorithm, throws_with_negative_weight) {
    std::vector<int> res = { 5, 5, 5, 5 };

    std::vector<int> graf = { 0, -5, 9, 0, 0, 14,
                          7, 0, 10, 15, 0, 0,
                          9, 10, 0, 11, 0, 2,
                          0, 15, 11, 0, 6, 0,
                          0, 0, 0, 6, 0, 9,
                          14, 0, 2, 0, 9, 0 };

    ASSERT_ANY_THROW(dijkstra_algorithm(graf, 5, 1));
}

TEST(dijkstra_algorithm, throws_with_wrong_arguments) {
    std::vector<int> res = { 5, 5, 5, 5 };

    std::vector<int> graf = { 0, -5, 9, 0, 0, 14,
                          7, 0, 10, 15, 0, 0,
                          9, 10, 0, 11, 0, 2,
                          0, 15, 11, 0, 6, 0,
                          0, 0, 0, 6, 0, 9,
                          14, 0, 2, 0, 9, 0, 99, 9 };

    ASSERT_ANY_THROW(dijkstra_algorithm(graf, 5, 1));
}

TEST(dijkstra_algorithm, passes_if_start_equal_end) {
    std::vector<int> graf = { 0, 2, 3,
                          2, 0, 1,
                          3, 1, 0 };

    ASSERT_NO_THROW(dijkstra_algorithm(graf, 3, 3));
}

TEST(dijkstra_algorithm, six_point_nomer_2) {
    std::vector<int> res = { 5, 6, 3, 1 };

    std::vector<int> graf = { 0, 9, 11, 0, 0, 16,
                          9, 0, 12, 17, 0, 0,
                          11, 12, 0, 13, 0, 4,
                          0, 17, 13, 0, 8, 0,
                          0, 0, 0, 8, 0, 11,
                          16, 0, 4, 0, 11, 0 };

    EXPECT_EQ(dijkstra_algorithm(graf, 1, 5), res);
}

TEST(dijkstra_algorithm, six_point_nomer_2_parallel) {
    std::vector<int> res = { 5, 6, 3, 1 };

    std::vector<int> graf = { 0, 9, 11, 0, 0, 16,
                          9, 0, 12, 17, 0, 0,
                          11, 12, 0, 13, 0, 4,
                          0, 17, 13, 0, 8, 0,
                          0, 0, 0, 8, 0, 11,
                          16, 0, 4, 0, 11, 0 };

    EXPECT_EQ(dijkstra_algorithm(graf, 1, 5), res);
}

TEST(dijkstra_algorithm, test_six_point) {
    std::vector<int> res = { 5, 6, 3, 1 };

    std::vector<int> graf = { 0, 8, 10, 0, 0, 15,
                          8, 0, 11, 16, 0, 0,
                          10, 11, 0, 12, 0, 3,
                          0, 16, 12, 0, 7, 0,
                          0, 0, 0, 7, 0, 10,
                          15, 0, 3, 0, 10, 0 };

    EXPECT_EQ(dijkstra_algorithm(graf, 1, 5), res);
}

TEST(dijkstra_algorithm, test_parallel_six_point) {
    std::vector<int> result = { 5, 6, 3, 1 };

    std::vector<int> graf = { 0, 8, 10, 0, 0, 15,
                          8, 0, 11, 16, 0, 0,
                          10, 11, 0, 12, 0, 3,
                          0, 16, 12, 0, 7, 0,
                          0, 0, 0, 7, 0, 10,
                          15, 0, 3, 0, 10, 0 };

    EXPECT_EQ(dijkstra_algorithm(graf, 1, 5), result);
}
